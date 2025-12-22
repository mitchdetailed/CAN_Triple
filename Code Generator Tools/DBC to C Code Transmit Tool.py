import cantools
import tkinter as tk
from tkinter import filedialog
import os
from jinja2 import Template

# Create the root window and hide it
root = tk.Tk()
root.withdraw()

# Load your DBC file
dbcfilename = filedialog.askopenfilename(title="Select DBC File", filetypes=(("DBC Files", "*.dbc"), ("all files", "*.*")))
if not dbcfilename:
    print("No file selected.")
    exit()

outputfile = filedialog.asksaveasfilename(title="Save Exported txt File", filetypes=(("txt Files", "*.txt"), ("all files", "*.*")), defaultextension=".txt")
if not outputfile:
    print("No output file selected.")
    exit()

db = cantools.database.load_file(dbcfilename, strict=False)

# Bit mapping array for Big Endian LSB calculation
array = [
    7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8,
    23, 22, 21, 20, 19, 18, 17, 16, 31, 30, 29, 28, 27, 26, 25, 24,
    39, 38, 37, 36, 35, 34, 33, 32, 47, 46, 45, 44, 43, 42, 41, 40,
    55, 54, 53, 52, 51, 50, 49, 48, 63, 62, 61, 60, 59, 58, 57, 56
]

# ----------------- Helpers -----------------

def get_dbc_start_bit(signal):
    if signal.byte_order == 'big_endian':
        try:
            start_bit = signal.start
            length = signal.length
            idx = array.index(start_bit)
            lsb_val = array[idx + length - 1]
            return lsb_val
        except (ValueError, IndexError):
            print(f"Warning: Could not calculate BE LSB for signal {signal.name}. Using default start bit.")
            return signal.start
    else:
        return signal.start

def get_signal_type(signal):
    # 1. Float Check
    # If the scale or offset are not integers (e.g. 0.5, 1.5), we must use float.
    is_scale_int = (signal.scale == int(signal.scale))
    is_offset_int = (signal.offset == int(signal.offset))
    
    # If DBC explicitly says Float/Double, we must respect it (raw bits are IEEE 754)
    if signal.is_float:
        return "float"
        
    # If scaling implies fractional values, use float
    if not is_scale_int or not is_offset_int:
        return "float"

    # 2. Integer Range Calculation
    length = signal.length
    if signal.is_signed:
        raw_min = -(1 << (length - 1))
        raw_max = (1 << (length - 1)) - 1
    else:
        raw_min = 0
        raw_max = (1 << length) - 1
        
    scale = int(signal.scale)
    offset = int(signal.offset)
    
    phys_min = (raw_min * scale) + offset
    phys_max = (raw_max * scale) + offset
    
    # 3. Type Selection
    
    # Check for Boolean (0 or 1)
    if phys_min == 0 and phys_max == 1:
        return "bool"
        
    # Signed Logic
    if phys_min < 0:
        if phys_min >= -128 and phys_max <= 127:
            return "int8_t"
        elif phys_min >= -32768 and phys_max <= 32767:
            return "int16_t"
        else:
            return "int32_t"
            
    # Unsigned Logic
    else:
        if phys_max <= 255:
            return "uint8_t"
        elif phys_max <= 65535:
            return "uint16_t"
        else:
            return "uint32_t"

def get_dbc_datatype_enum(signal):
    # DBC_UNSIGNED = 0, DBC_SIGNED = 1, DBC_FLOAT = 2, DBC_DOUBLE = 4
    if signal.is_float:
        if signal.length > 32: return "DBC_DOUBLE"
        return "DBC_FLOAT"
    if signal.is_signed:
        return "DBC_SIGNED"
    return "DBC_UNSIGNED"

def get_decimal_places(signal):
    """
    Calculate required decimal places based on Scale factor.
    Logic mirrored from conversion_worker.py
    """
    if get_signal_type(signal) != "float":
        return 0

    dps = 0
    scale = signal.scale
    if scale:
        try:
            scale_val = float(scale)
            rem = scale_val % 1
            
            if rem < 1e-9: # Effectively Integer
                dps = 0
            elif scale_val >= 1:
                if rem >= 0.85:
                    dps = 0
                else:
                    dps = 1
            elif scale_val >= 0.1:
                if rem >= 0.085:
                    dps = 1
                else:
                    dps = 2
            elif scale_val >= 0.01:
                if rem >= 0.00085:
                    dps = 2
            elif scale_val >= 0.001:
                if rem >= 0.000085:
                    dps = 3
            elif scale_val >= 0.0001:
                if rem >= 0.0000085:
                    dps = 4
            elif scale_val >= 0.00001:
                if rem >= 0.00000085:
                    dps = 5
            elif scale_val >= 0.000001:
                if rem >= 0.000000085:
                    dps = 6
            elif scale_val >= 0.0000001:
                if rem >= 0.0000000085:
                    dps = 7
            else:
                dps = 7
        except:
            dps = 3
    return dps

def sanitize_node_name(name):
    # Ensure C-valid variable name
    return "".join(c for c in name if c.isalnum() or c == '_')

def get_formatted_signal_name(signal):
    """
    Concatenate Signal Name + Unit with sanitization.
    Substitutes special chars to text or removes them to ensure valid C syntax.
    """
    base_name = signal.name
    unit = signal.unit
    
    if not unit:
        return base_name
        
    # Replacements for C-breaking characters in Units
    replacements = {
        '%': 'Pct',
        '/': '',    # Remove
        ' ': '',    # Remove spaces
        '-': 'Minus',
        '+': 'Plus',
        '=': 'Eq',
        '>': 'Gt',
        '<': 'Lt',
        '[': '',    # Remove
        ']': '',    # Remove
        '(': '',    # Remove
        ')': '',    # Remove
        '.': 'Dot',
        '*': 'Mul',
        '^': 'Pow',
        '&': 'And',
        '|': 'Or',
        '~': 'Tilde',
        '!': 'Not',
        '@': 'At',
        '#': 'Num',
        '$': 'Dollar',
        '°': 'Deg', # Common in temperature
        '"': '',
        "'": ''
    }

    for char, substr in replacements.items():
        unit = unit.replace(char, substr)
    
    # Final Sanitization - keep only a-z 0-9 _ to be absolutely sure
    safe_unit = "".join(c for c in unit if c.isalnum() or c == '_')
    
    if safe_unit:
        return f"{base_name}_{safe_unit}"
        
    return base_name

# ----------------- Logic Preparation -----------------

# Organizes signals by Node (Sender) -> SignalName -> Type
# { "TEST_ECU": { "EngineSpeed": "float", ... }, ... }
node_structs = {}

messages_data = []

sorted_messages = sorted(db.messages, key=lambda m: m.frame_id)

for msg in sorted_messages:
    if not msg.signals:
        continue

    # Determine Sender (Node Name)
    # A message might have multiple senders, we usually pick the first one for the struct owner.
    # If no sender is defined, we'll bucket it under "CAN_Node" (generic)
    if msg.senders:
        node_name = sanitize_node_name(msg.senders[0])
    else:
        node_name = "CAN_Node"

    # Ensure this node exists in our struct tracker
    if node_name not in node_structs:
        node_structs[node_name] = {}

    # 1. Update Node Struct Definitions based on signals in this message
    for sig in msg.signals:
        s_name = get_formatted_signal_name(sig)
        s_type = get_signal_type(sig)
        if s_name in node_structs[node_name]:
             if node_structs[node_name][s_name] != s_type: # Conflict check
                node_structs[node_name][s_name] = "float" # Upgrade to float on conflict
        else:
            node_structs[node_name][s_name] = s_type

    # 2. Build Message Data for Encoding
    msg_data = {
        'id': f"{msg.frame_id:X}", # Hex string
        'name': msg.name,
        'dlc': msg.length,
        'is_extended': "true" if msg.is_extended_frame else "false",
        'node_name': node_name,     # The struct instance to use
        'common_signals': [],
        'mux_switch': None,      # The defined Multiplexer Switch Signal
        'multiplexed_groups': {} # id -> list of signal dicts
    }

    # Group Signals
    for sig in msg.signals:
        
        # Prepare the context for this signal to pass to Jinja
        dbc_start = get_dbc_start_bit(sig)
        datatype = get_dbc_datatype_enum(sig)
        is_big = "true" if sig.byte_order == 'big_endian' else "false"
        # decimals = get_decimal_places(sig) # Removed
        
        s_name = get_formatted_signal_name(sig)
        
        # Args for dbc_encode:
        # (data, msg_data_length, datatype, is_big_endian, scaled_value, dbc_start_bit, dbc_bit_length, factor, offset)
        
        # Default: Use variable from struct
        encode_args_var = f"{node_name}.Message, {msg.length}, {datatype}, {is_big}, {node_name}.{s_name}, {dbc_start}, {sig.length}, {sig.scale}, {sig.offset}"
        
        # Placeholder version for Mux Switch (Values will be injected)
        encode_args_val_pattern = f"{node_name}.Message, {msg.length}, {datatype}, {is_big}, REPLACE_VAL, {dbc_start}, {sig.length}, {sig.scale}, {sig.offset}"

        sig_ctx = {
            'name': s_name,
            'args': encode_args_var
        }
        
        if sig.is_multiplexer:
            # This is the Switch
            msg_data['mux_switch'] = {
                'name': s_name,
                'args_var': encode_args_var,
                'args_val': encode_args_val_pattern
            }
            # Do NOT add to common_signals
            continue

        if sig.multiplexer_ids:
            for mux_id in sig.multiplexer_ids:
                mux_hex = f"0x{mux_id:X}"
                if mux_hex not in msg_data['multiplexed_groups']:
                    msg_data['multiplexed_groups'][mux_hex] = []
                msg_data['multiplexed_groups'][mux_hex].append(sig_ctx)
        else:
            msg_data['common_signals'].append(sig_ctx)

    # Sort multiplexed groups by ID value (ascending)
    if msg_data['multiplexed_groups']:
        sorted_groups = sorted(msg_data['multiplexed_groups'].items(), key=lambda item: int(item[0], 16))
        msg_data['multiplexed_groups'] = dict(sorted_groups)

    messages_data.append(msg_data)

# Sort struct signals for stable output
# Convert {Node: {Sig: Type}} to sorted list of (Node, [(Sig, Type)])
final_node_structs = []
for node, signals in sorted(node_structs.items()):
    final_node_structs.append((node, sorted(signals.items())))

# ----------------- Jinja Template -----------------

template_string = """
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

//################ Generated Struct Definitions ################
{%- for node_name, signals in node_structs %}
typedef struct {
    uint8_t Message[8];
{%- for name, type in signals %}
    {{ type }} {{ name }};
{%- endfor %}
} {{ node_name }}_Data_t;

{{ node_name }}_Data_t {{ node_name }};
{% endfor %}
//################ End Generated Struct Definitions ################

//################ Generated Encode Logic ################
//################ You will need to define the CAN Bus  you're wanting to transmit to for each message send_message() function.  ################
//################ Copy each block to the appropriate function frequency you want the message to be sent at.  ################
{% for msg in messages %}
// Message: {{ msg.name }} (ID: 0x{{ msg.id }})
{%- if msg.multiplexed_groups %}

    {# MULTIPLEXED MESSAGE GENERATION #}
    {%- for mux_id, group_signals in msg.multiplexed_groups.items() %}

    // --- Mux ID: {{ mux_id }} ---
    memset({{ msg.node_name }}.Message, 0, 8);
    
    // Mux Switch Signal (Value: {{ mux_id }})
    dbc_encode({{ msg.mux_switch.args_val | replace('REPLACE_VAL', mux_id) }});
    
    // Common Signals
    {%- for sig in msg.common_signals %}
    dbc_encode({{ sig.args }});
    {%- endfor %}
    
    // Mux-Specific Signals
    {%- for sig in group_signals %}
    dbc_encode({{ sig.args }});
    {%- endfor %}
    
    // Send
    send_message($BUS$, {{ msg.is_extended }}, 0x{{ msg.id }}, {{ msg.dlc }}, {{ msg.node_name }}.Message);
    
    {%- endfor %}

{%- else %}

    {# STANDARD MESSAGE GENERATION #}
    memset({{ msg.node_name }}.Message, 0, 8);
    
    // Common Signals
    {%- for sig in msg.common_signals %}
    dbc_encode({{ sig.args }});
    {%- endfor %}
    
    {%- if msg.mux_switch %}
    // Mux Switch (If applicable, fallback)
    dbc_encode({{ msg.mux_switch.args_var }});
    {%- endif %}
    
    // Send
    send_message($BUS$, {{ msg.is_extended }}, 0x{{ msg.id }}, {{ msg.dlc }}, {{ msg.node_name }}.Message);

{%- endif %}

{% endfor %}
//################ End Generated Encode Logic ################
"""

# ----------------- Rendering -----------------

template = Template(template_string)
c_code_output = template.render(
    node_structs=final_node_structs,
    messages=messages_data
)

with open(outputfile, "w") as f:
    f.write(c_code_output)

print("Done. Generated code saved to", outputfile)
