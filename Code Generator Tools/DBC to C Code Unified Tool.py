import cantools
import tkinter as tk
from tkinter import filedialog
import os
from jinja2 import Template

# This tool will only work if Node TX RX mapping is correct. 


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
    is_scale_int = (signal.scale == int(signal.scale))
    is_offset_int = (signal.offset == int(signal.offset))
    
    if signal.is_float:
        return "float"
    
    if not is_scale_int or not is_offset_int:
        return "float"

    length = signal.length
    if signal.is_signed:
        raw_min = -(1 << (length - 1))
    else:
        raw_min = 0
        raw_max = (1 << length) - 1
        
    scale = int(signal.scale)
    offset = int(signal.offset)
    
    phys_min = (raw_min * scale) + offset
    phys_max = (raw_max * scale) + offset
    
    if phys_min == 0 and phys_max == 1:
        return "bool"
        
    if phys_min < 0:
        if phys_min >= -128 and phys_max <= 127: return "int8_t"
        elif phys_min >= -32768 and phys_max <= 32767: return "int16_t"
        else: return "int32_t"
    else:
        if phys_max <= 255: return "uint8_t"
        elif phys_max <= 65535: return "uint16_t"
        else: return "uint32_t"

def get_dbc_datatype_int(signal):
    # For dbc_decode
    if signal.is_float:
        if signal.length > 32: return 4
        return 2
    if signal.is_signed:
        return 1
    return 0

def get_dbc_datatype_enum(signal):
    # For dbc_encode
    if signal.is_float:
        if signal.length > 32: return "DBC_DOUBLE"
        return "DBC_FLOAT"
    if signal.is_signed:
        return "DBC_SIGNED"
    return "DBC_UNSIGNED"

def sanitize_node_name(name):
    return "".join(c for c in name if c.isalnum() or c == '_')

def get_formatted_signal_name(signal):
    base_name = signal.name
    unit = signal.unit if signal.unit else ""
    replacements = {'%':'Pct','/':'',' ':'','-':'Minus','+':'Plus','=':'Eq','>':'Gt','<':'Lt','[':'','(':'','.':'Dot','*':'Mul','^':'Pow','&':'And','|':'Or','~':'Tilde','!':'Not','@':'At','#':'Num','$':'Dollar','°':'Deg','"':"","'":""}
    for k,v in replacements.items(): unit = unit.replace(k,v)
    safe_unit = "".join(c for c in unit if c.isalnum() or c == '_')
    return f"{base_name}_{safe_unit}" if safe_unit else base_name

# ----------------- Main Logic -----------------

# Identify Target Node
target_node = None
single_struct_mode = False
main_struct_name = "CAN_Node"

if len(db.nodes) == 1:
    target_node = db.nodes[0].name
    main_struct_name = sanitize_node_name(target_node)
    single_struct_mode = True
    print(f"Single node detected: {target_node}. Using unified struct: {main_struct_name}_Data_t")
else:
    print(f"Warning: {len(db.nodes)} nodes found. Standard Sniffer Mode (Receive All).")
    # In sniffer mode, we might still want to receive everything but keep structs separate by sender.
    # But if User forces, we could merge. For now, we'll respect the single_struct_mode flag only if target_node detected.

# Data Stores
node_structs = {}
rx_messages_data = []
tx_messages_data = []

sorted_messages = sorted(db.messages, key=lambda m: m.frame_id)

def ensure_node_in_structs(n_name):
    if n_name not in node_structs:
        node_structs[n_name] = {}

def update_struct_signal(n_name, sig_obj):
    s_name = get_formatted_signal_name(sig_obj)
    s_type = get_signal_type(sig_obj)
    if s_name in node_structs[n_name]:
        if node_structs[n_name][s_name] != s_type:
            node_structs[n_name][s_name] = "float"
    else:
        node_structs[n_name][s_name] = s_type

# Loop through all messages
for msg in sorted_messages:
    if not msg.signals: continue

    sender_name_raw = msg.senders[0] if msg.senders else "CAN_Node"
    sender_name_sanitized = sanitize_node_name(sender_name_raw)

    # Determine which struct this message belongs to (for variable storage)
    if single_struct_mode:
        # Everything goes into the Main Struct
        struct_name = main_struct_name
    else:
        # Separate structs by sender (Sniffer / default)
        struct_name = sender_name_sanitized

    ensure_node_in_structs(struct_name)

    # --- RX Logic ---
    # We allow reception if:
    # 1. We are in Single Node Mode AND we are a receiver
    # 2. We are in Default Mode (Receive Everything)
    
    is_rx_message = False
    
    if single_struct_mode:
        # Check receivers
        # (Note: In cantools, signals have receivers. If ANY signal is for us, we process message)
        for s in msg.signals:
            if target_node in s.receivers:
                is_rx_message = True
                break
    else:
        is_rx_message = True

    if is_rx_message:
        # 1. Update Struct with RX signals
        for sig in msg.signals:
            if single_struct_mode and target_node not in sig.receivers:
                continue # Skip signals not for us in this message
            update_struct_signal(struct_name, sig)
            
        # 2. Build RX Data
        rx_data = {
            'id': f"{msg.frame_id:X}",
            'node_name': struct_name,
            'comment': f"From {sender_name_raw}",
            'common_signals': [],
            'mux_signal_name': None,
            'multiplexed_groups': {}
        }
        
        # Mux detection
        for sig in msg.signals:
            if sig.is_multiplexer:
                rx_data['mux_signal_name'] = get_formatted_signal_name(sig)
                break
        
        for sig in msg.signals:
            if single_struct_mode and target_node not in sig.receivers:
                continue

            s_name = get_formatted_signal_name(sig)
            dbc_start = get_dbc_start_bit(sig)
            datatype = get_dbc_datatype_int(sig)
            is_big = "true" if sig.byte_order == 'big_endian' else "false"
            decs = 3 

            # StartLine / Cast
            # If the signal is float in struct, no cast needed usually, but good to be explicit/safe.
            # We defer looking up the final type until template time? No, we can trust update_struct_signal happened.
            s_type = node_structs[struct_name][s_name]
            cast = f"({s_type})" if s_type != "float" else ""

            sig_ctx = {
                'name': s_name,
                'cast': cast,
                'args': f"Message.data, {datatype}, {is_big}, {dbc_start}, {sig.length}, {sig.scale}, {sig.offset}, {decs}"
            }

            if sig.multiplexer_ids:
                for mux_id in sig.multiplexer_ids:
                    if mux_id not in rx_data['multiplexed_groups']: rx_data['multiplexed_groups'][mux_id] = []
                    rx_data['multiplexed_groups'][mux_id].append(sig_ctx)
            else:
                rx_data['common_signals'].append(sig_ctx)
        
        rx_messages_data.append(rx_data)

    # --- TX Logic ---
    # We transmit if:
    # 1. sender is US (Single Mode)
    # 2. Default mode: We don't really transmit in sniffer mode, usually. But if you wanted to mock everything, we could.
    #    Let's restrict TX to Single Node Mode matching target_node.

    is_tx_message = False
    if single_struct_mode and sender_name_raw == target_node:
        is_tx_message = True
    
    if is_tx_message:
        # 1. Update Struct with TX signals (Variables we need to populate before sending)
        for sig in msg.signals:
            update_struct_signal(struct_name, sig)
        
        # 2. Build TX Data
        tx_data = {
            'id': f"{msg.frame_id:X}",
            'name': msg.name,
            'dlc': msg.length,
            'is_extended': "true" if msg.is_extended_frame else "false",
            'node_name': struct_name,
            'common_signals': [],
            'mux_switch': None,
            'multiplexed_groups': {}
        }
        
        for sig in msg.signals:
            s_name = get_formatted_signal_name(sig)
            dbc_start = get_dbc_start_bit(sig)
            datatype = get_dbc_datatype_enum(sig)
            is_big = "true" if sig.byte_order == 'big_endian' else "false"

            # Use variables from the struct
            encode_args_var = f"{struct_name}.Message, {msg.length}, {datatype}, {is_big}, {struct_name}.{s_name}, {dbc_start}, {sig.length}, {sig.scale}, {sig.offset}"
            encode_args_val_patt = f"{struct_name}.Message, {msg.length}, {datatype}, {is_big}, REPLACE_VAL, {dbc_start}, {sig.length}, {sig.scale}, {sig.offset}"

            sig_ctx = {'name': s_name, 'args': encode_args_var}

            if sig.is_multiplexer:
                 tx_data['mux_switch'] = {'name': s_name, 'args_var': encode_args_var, 'args_val': encode_args_val_patt}
                 continue

            if sig.multiplexer_ids:
                for mux_id in sig.multiplexer_ids:
                    mux_hex = f"0x{mux_id:X}"
                    if mux_hex not in tx_data['multiplexed_groups']: tx_data['multiplexed_groups'][mux_hex] = []
                    tx_data['multiplexed_groups'][mux_hex].append(sig_ctx)
            else:
                tx_data['common_signals'].append(sig_ctx)
        
        if tx_data['multiplexed_groups']:
            sorted_grps = sorted(tx_data['multiplexed_groups'].items(), key=lambda x: int(x[0], 16))
            tx_data['multiplexed_groups'] = dict(sorted_grps)

        tx_messages_data.append(tx_data)


# Sort Structs
final_node_structs = []
for node, signals in sorted(node_structs.items()):
    final_node_structs.append((node, sorted(signals.items())))

# Template
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


//################ Generated Receive (Decode) Logic ################
{% for msg in rx_messages %}
if(Message.arbitration_id == 0x{{ msg.id }})
{
    // Node: {{ msg.node_name }} ({{ msg.comment }})
    // Common Signals
    {%- for sig in msg.common_signals %}
    {{ msg.node_name }}.{{ sig.name }} = {{ sig.cast }}dbc_decode({{ sig.args }});
    {%- endfor %}

    {%- if msg.mux_signal_name %}
    // Multiplexed Signals
    switch ((int){{ msg.node_name }}.{{ msg.mux_signal_name }}) {
        {%- for mux_id, group_signals in msg.multiplexed_groups.items()|sort %}
        case 0x{{ '%X' % mux_id }}:
            {%- for sig in group_signals %}
            {{ msg.node_name }}.{{ sig.name }} = {{ sig.cast }}dbc_decode({{ sig.args }});
            {%- endfor %}
            break;
        {%- endfor %}
        default:
            break;
    }
    {%- endif %}
}
{% endfor %}
//################ End Generated Receive Logic ################


//################ Generated Transmit (Encode) Logic ################
//################ You will need to define the CAN Bus you're wanting to transmit to for each message send_message() function. ################
{% for msg in tx_messages %}
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
    // Mux Switch
    dbc_encode({{ msg.mux_switch.args_var }});
    {%- endif %}
    
    // Send
    send_message($BUS$, {{ msg.is_extended }}, 0x{{ msg.id }}, {{ msg.dlc }}, {{ msg.node_name }}.Message);

{%- endif %}

{% endfor %}
//################ End Generated Transmit Logic ################
"""

template = Template(template_string)
c_code_output = template.render(
    node_structs=final_node_structs,
    rx_messages=rx_messages_data,
    tx_messages=tx_messages_data
)

with open(outputfile, "w") as f:
    f.write(c_code_output)

print("Done. Generated code saved to", outputfile)
