import cantools
from tkinter.filedialog import askopenfilename, asksaveasfilename
import time

# Load your DBC file
dbcfilename = askopenfilename(title="Select DBC File", filetypes=(("DBC Files", "*.dbc"), ("all files", "*.*")))
outputfile = asksaveasfilename(title="Save Exported txt File", filetypes=(("txt Files", "*.txt"), ("all files", "*.*")))
db = cantools.database.load_file(dbcfilename)

# Step 1: Extract and sort message IDs
raw_dbc = db.messages
arb_id_list = []

for iterable in raw_dbc:
    listmsgs = str(iterable).split(',')
    arb_id = int(listmsgs[1], 0)
    arb_id_list.append(arb_id)
arb_id_list.sort()

# Step 2: Gather detailed signal information for each message
complete_structured_list = []

for count, arb_id in enumerate(arb_id_list):
    frameID = db.get_message_by_frame_id(arb_id)
    isExtendedID = frameID.is_extended_frame
    datalength = frameID.length
    signalset = frameID.signals

    if len(signalset) > 0:
        for i, iterable in enumerate(signalset):
            sig_name = str(frameID.signals[i].name)
            sig_unit = frameID.signals[i].unit if frameID.signals[i].unit else ""
            sig_byteorder = frameID.signals[i].byte_order
            sig_len = frameID.signals[i].length
            sig_startbit = frameID.signals[i].start
            is_Big_Endian = 1 if sig_byteorder == "big_endian" else 0
            isSigned = 1 if frameID.signals[i].is_signed else 0
            isFloat = 1 if frameID.signals[i].is_float else 0
            sig_scale = frameID.signals[i].scale
            sig_offset = frameID.signals[i].offset
            signal_Multiplexer = frameID.signals[i].multiplexer_signal
            multiplexer_Value = frameID.signals[i].multiplexer_ids
            mux_Value = multiplexer_Value[0] if multiplexer_Value else None
            is_multiplexed = True if signal_Multiplexer else False

            if not is_multiplexed:
                hierarchylevel = 0
            else:
                if signal_Multiplexer:
                    hierarchylevel = 1
                else:
                    hierarchylevel = 0

            list = [isExtendedID, arb_id, datalength, hierarchylevel, signal_Multiplexer, mux_Value, sig_startbit,
                    sig_name, sig_unit, is_Big_Endian, sig_len, isSigned, isFloat, sig_scale, sig_offset]
            complete_structured_list.append(list)

# Step 3: Sort the structured list by hierarchy level and other parameters
ordered_structured_list = sorted(complete_structured_list, key=lambda x: (x[0], x[1], x[3], x[4], x[6]))

# Define the array once
array = [
    7, 6, 5, 4, 3, 2, 1, 0, 15, 14, 13, 12, 11, 10, 9, 8,
    23, 22, 21, 20, 19, 18, 17, 16, 31, 30, 29, 28, 27, 26, 25, 24,
    39, 38, 37, 36, 35, 34, 33, 32, 47, 46, 45, 44, 43, 42, 41, 40,
    55, 54, 53, 52, 51, 50, 49, 48, 63, 62, 61, 60, 59, 58, 57, 56
]

# Step 4: Generate C code based on the structured information
global_declarations = ""
c_code = ""

def generate_signal_code(signal_info, array):
    global global_declarations, c_code

    isExtendedID, arb_id, datalength, hierarchylevel, signal_Multiplexer, mux_Value, sig_startbit, sig_name, sig_unit, \
    is_Big_Endian, sig_len, isSigned, isFloat, sig_scale, sig_offset = signal_info

    bitmask = (1 << sig_len) - 1
    is_signed = 'true' if isSigned else 'false'
    endianness = 'big' if is_Big_Endian else 'little'

    if (sig_scale > 0 and sig_scale == int(sig_scale) and sig_offset >= 0 and not isSigned and not isFloat):
        typecast = 'uint32_t'
    elif (sig_scale == int(sig_scale) and sig_offset == int(sig_offset) and not isFloat):
        typecast = 'int32_t'
    else:
        typecast = 'float'

    global_declarations += f"{typecast} {sig_name};\n"

    indent = "\t" * (hierarchylevel + 2)
    c_code += f"{indent}// Signal: {sig_name}\n"
    c_code += f"{indent}// Start bit: {sig_startbit}, Length: {sig_len}, Byte Order: {endianness}\n"
    
    if endianness == 'big':
        BE_Signal_LSb = array[(array.index(sig_startbit) + (sig_len - 1))]
        BE_rightshifts = BE_Signal_LSb % 8
        true_bitmask = (bitmask << BE_rightshifts)
        BE_LSbyte = BE_Signal_LSb // 8
        BE_MSbyte = sig_startbit // 8
        difference = BE_LSbyte - BE_MSbyte

        raw_value_parts = []
        for i in range(difference + 1):
            bitshiftvalue = ((BE_LSbyte - BE_MSbyte - i) * 8)
            if bitshiftvalue > 0:
                raw_value_parts.append(f"((uint32_t)Message.data[{BE_MSbyte + i}] << {bitshiftvalue})")
            else:
                raw_value_parts.append(f"(uint32_t)Message.data[{BE_MSbyte + i}]")
    else:
        LE_rightshifts = sig_startbit % 8
        true_bitmask = (bitmask << LE_rightshifts)
        LE_LSbyte = sig_startbit // 8
        LE_MSbyte = (sig_startbit + LE_rightshifts + sig_len - 1) // 8
        difference = LE_MSbyte - LE_LSbyte
        count = 0

        raw_value_parts = []
        for i in range(difference + 1, 0, -1):
            bitshiftvalue = ((LE_MSbyte - LE_LSbyte - count) * 8)
            if bitshiftvalue > 0:
                raw_value_parts.append(f"((uint32_t)Message.data[{LE_LSbyte + i - 1}] << {bitshiftvalue})")
            else:
                raw_value_parts.append(f"(uint32_t)Message.data[{LE_LSbyte + i - 1}]")
            count += 1

    raw_value_expression = " | ".join(raw_value_parts)

    # Determine the appropriate processing function to use
    if isFloat == True:
        process_function = "process_ieee754"
    elif isinstance(sig_scale, float) or round(sig_offset, 3) != sig_offset:
        process_function = "process_float_value"
    elif not isSigned and sig_scale == 1 and sig_offset == 0:
        process_function = "process_raw_value"
    elif not isSigned and sig_scale > 0 and sig_offset >= 0:
        process_function = "process_unsigned_int_value"
    else:
        process_function = "process_int_value"

    if process_function == "process_ieee754":
        c_code += f"{indent}{sig_name} = {process_function}({raw_value_expression}, 0x{true_bitmask:X}, {is_signed}, {sig_scale}, {sig_offset}, 3);\n\n"
    if process_function == "process_float_value":
        c_code += f"{indent}{sig_name} = {process_function}({raw_value_expression}, 0x{true_bitmask:X}, {is_signed}, {sig_scale}, {sig_offset}, 3);\n\n"
    elif process_function == "process_raw_value":
        c_code += f"{indent}{sig_name} = {process_function}({raw_value_expression}, 0x{true_bitmask:X});\n\n"
    elif process_function == "process_unsigned_int_value":
        c_code += f"{indent}{sig_name} = {process_function}({raw_value_expression}, 0x{true_bitmask:X}, {sig_scale}, {sig_offset});\n\n"
    else:
        c_code += f"{indent}{sig_name} = {process_function}({raw_value_expression}, 0x{true_bitmask:X}, {is_signed}, {int(sig_scale)}, {int(sig_offset)});\n\n"

current_arbitration_id = None
current_multiplexer = None

for signal_info in ordered_structured_list:
    isExtendedID, arb_id, datalength, hierarchylevel, signal_Multiplexer, mux_Value, sig_startbit, sig_name, sig_unit, \
    is_Big_Endian, sig_len, isSigned, isFloat, sig_scale, sig_offset = signal_info

    if arb_id != current_arbitration_id:
        if current_arbitration_id is not None:
            c_code += "\t\t}\n\n"
        current_arbitration_id = arb_id
        c_code += f"\t\tif (Message.arbitration_id == 0x{arb_id:X}) {{\n"

    if signal_Multiplexer != current_multiplexer:
        if current_multiplexer is not None:
            c_code += "\t\t\t}\n"
        current_multiplexer = signal_Multiplexer
        if signal_Multiplexer:
            c_code += f"\t\t\tif ({signal_Multiplexer} == {mux_Value}) {{\n"

    generate_signal_code(signal_info, array)

if current_arbitration_id is not None:
    c_code += "\t\t}\n\n"
if current_multiplexer is not None:
    c_code += "\t\t\t}\n"

# Combine global declarations with the rest of the C code
final_code = "//################ Generated Variable Declarations ################\n// Copy to Variable Declarations area in user_code.c \n\n" + global_declarations + "//################ End Generated Variable Declarations ################\n\n//################ Generated CAN Code ################\n//Copy Code Below to appropriate Message.bus statement in user_code.c\n\n" + c_code + "\n//################ End Generated CAN Code ################\n"

# Write the generated code to a file
with open(outputfile, "w") as outfile:
    outfile.write(final_code)
outfile.close()
print("all done...")
time.sleep(3)
