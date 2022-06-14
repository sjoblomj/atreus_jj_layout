#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import re

KEYBOARD_ROWS = 4
SPECIAL_SYMBOLS = {
    "Backslash": "\\",
    "&": "&amp;",
    "<": "&lt;",
    ">": "&gt;"
}

# Constants relating to where the texts of different layers will appear, and to key positioning
key_pos_offset = [100, 50, 0, 50, 100, 50, 50, 100, 50, 0, 50, 100]
colours = {"COLEMAK": "black", "FUN": "red", "MOVE": "green", "CHAR": "blue"}
anchors = {"COLEMAK": "start", "FUN": "start", "MOVE": "middle", "CHAR": "end"}
font_size = {"COLEMAK": 35, "FUN": 25, "MOVE": 25, "CHAR": 25}
x_positions = {"COLEMAK": 250, "FUN": 240, "MOVE": 300, "CHAR": 360}
y_positions = {"COLEMAK": 160, "FUN": 71, "MOVE": 100, "CHAR": 71}
key_size = 175
x_key_rectangle_offset = 225
y_key_rectangle_offset = 25
shift_position_offset = -40

definition_dict = {}
shifted_dict = {}


def read_file(file_name):
    with open(file_name) as infile:
        return infile.read().splitlines()


def get_key_representation(key):
    returned_key = None
    if key == None or key == "___":
        returned_key = None
    elif key in definition_dict:
        returned_key = definition_dict[key]
    else:
        returned_key = key.replace("Key_", "")
    if returned_key in SPECIAL_SYMBOLS:
        returned_key = SPECIAL_SYMBOLS[returned_key]
    return returned_key


def read_keylayout(keymaps):
    layouts = {}
    current_keyboard_row = 1
    keymap_name = None
    left_half   = None
    right_half  = None

    for line in keymaps:
        res = re.search(r" *\[(.+)\] *= *KEYMAP_STACKED", line)
        if res != None:
            if keymap_name != None:
                layouts[keymap_name] = [left_half, right_half]
            keymap_name = res.group(1)
            current_keyboard_row = 1
            left_half  = [[], [], [], [], [], []]
            right_half = [[], [], [], [], [], []]

        key_name_chars = "([0-9a-zA-Z_\-()]+)"
        res = re.search(r" *,? *" + key_name_chars + " *, *" + key_name_chars + " *, *" + key_name_chars + " *, *" + key_name_chars + " *, *" + key_name_chars + " *,? *" + key_name_chars + "?", line)

        if res != None:
            keyrow = res.groups()
            start_index = 0
            if current_keyboard_row == KEYBOARD_ROWS + 1 or current_keyboard_row == KEYBOARD_ROWS + 2:
                start_index = -1

            for index in range(0, len(keyrow)):
                k = keyrow[(start_index + index) % len(keyrow)]
                if current_keyboard_row <= KEYBOARD_ROWS:
                    left_half[index].append(k)
                else:
                    right_half[index].append(k)

            current_keyboard_row += 1

    layouts[keymap_name] = [left_half, right_half]

    output = []
    for i in range(0, 12):
        output.append([])
        for j in range(0, 4):
            output[i].append([])

    for layout in layouts:
        col_num = 0
        for half in layouts[layout]:
            for col in half:
                row_num = 0
                for key in col:
                    if output[col_num][row_num] == []:
                        output[col_num][row_num] = {layout: key}
                    else:
                        output[col_num][row_num].update({layout: key})
                    row_num += 1
                col_num += 1
    return output

def read_definitions(line):
    res = re.search(r"#define ([^ ]*) .*// ?(.*)", line)
    if res != None:
        shiftMatch = re.search(r"([^ ]+) +[sS][hH][iI][fF][tT][eE][dD] +([^ ]+)", res.group(2))
        if shiftMatch != None:
            definition_dict[res.group(1)] = shiftMatch.group(1)
            shifted_dict[res.group(1)] = shiftMatch.group(2)
        else:
            definition_dict[res.group(1)] = res.group(2)

def create_svg_key(x_index, y_index, key_data):

    xpos = x_index * key_size
    ypos = y_index * key_size + key_pos_offset[x_index]

    shifted = None
    if key_data["COLEMAK"] in shifted_dict:
        shifted = shifted_dict[key_data["COLEMAK"]]

    output = "    <rect x=\"" + str(xpos + x_key_rectangle_offset) + "\" y=\"" + str(ypos + y_key_rectangle_offset) + "\" rx=\"20\" ry=\"20\" width=\"150\" height=\"150\" style=\"fill:white;fill-opacity:0;stroke:black;stroke-width:3;stroke-opacity:0.71\" />\n"
    if shifted != None:
        output += "    <text x=\"" + str(xpos + x_positions["COLEMAK"]) + "\" y=\"" + str(ypos + y_positions["COLEMAK"] + shift_position_offset) + "\" font-size=\"" + str(font_size["COLEMAK"]) + "\" text-anchor=\"" + anchors["COLEMAK"] + "\" fill=\"" + colours["COLEMAK"] + "\">" + shifted + "</text>\n"

    for layer in list(key_data.keys()):
        key = get_key_representation(key_data[layer])
        if key != None:
            res = re.search(r"MoveToLayer\(.*\)", key)
            if res != None:
                continue

            # Colour the Layer names in their own colour, rather than that of the layer they are on.
            colour = colours[layer]
            res = re.search(r"(TG|MO)\((.*)\)", key)
            if res != None:
                key = res[2]
                colour = colours[key]

            output += "    <text x=\"" + str(xpos + x_positions[layer]) + "\" y=\"" + str(ypos + y_positions[layer]) + "\" font-family=\"Arial\" font-size=\"" + str(font_size[layer]) + "\" text-anchor=\"" + anchors[layer] + "\" fill=\"" + colour + "\">" + key + "</text>\n"

    output += "\n"
    return output

def create_svg(layouts, outfile):
    with open(outfile, "w") as f:
        f.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
        f.write("<svg xmlns=\"http://www.w3.org/2000/svg\"\n     xmlns:xlink=\"http://www.w3.org/1999/xlink\"\n     xmlns:ev=\"http://www.w3.org/2001/xml-events\"\n     width=\"2300\" height=\"975\">\n")
        f.write("  <rect width=\"100%\" height=\"100%\" fill=\"white\" />\n")
        f.write("  <polyline points=\"185,20 2100,20 2290,715 1450,950 830,950 5,715 185,20\" style=\"fill:none;stroke:black;stroke-width:3;stroke-opacity:0.71\" />\n")

        col_num = 0
        row_num = 0
        for col in range(0, 12):
            if col == 0:
                f.write("  <g id=\"left\" transform=\"rotate(15, 500, 0)\">\n")
            elif col == 6:
                f.write("  </g>\n\n")
                f.write("  <g id=\"right\" transform=\"rotate(-15, 1900, 900)\">\n")
            for key_data in layouts[col]:
                if (col_num == 5 or col_num == 6) and (row_num == 0 or row_num == 1):
                    row_num += 1
                    continue

                f.write(create_svg_key(col_num, row_num, key_data))
                row_num += 1
            col_num += 1
            row_num = 0
        f.write("  </g>\n")
        f.write("</svg>\n")



def parse_content(infile, outfile):
    is_reading_content = False
    is_reading_keymaps = False
    keymaps = []
    for line in read_file(infile):
        if "LAYOUTER-START" in line:
            is_reading_content = True
        elif "LAYOUTER-STOP" in line:
            is_reading_content = False
        if is_reading_content and line.startswith("KEYMAPS"):
            is_reading_keymaps = True

        if is_reading_content and line.startswith("#define"):
            read_definitions(line)
        if is_reading_content and is_reading_keymaps:
            keymaps.append(line)

    layouts = read_keylayout(keymaps)
    create_svg(layouts, outfile)

if len(sys.argv) == 2 and (sys.argv[1] == "-h" or sys.argv[1] == "--help" or sys.argv[1] == "-v" or sys.argv[1] == "--version"):
    print("Keyboardio Layout Creator 1.0")
    print("By Johan Sjöblom")
    exit(0)
if len(sys.argv) != 3:
    print("Keyboardio Layout Creator usage:")
    print(sys.argv[0] + " input_file.ino output_file.svg")
    exit(1)

parse_content(sys.argv[1], sys.argv[2])
