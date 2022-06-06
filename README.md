<a href="https://github.com/sjoblomj/atreus_jj_layout/blob/main/layout.svg">
  <img src="https://github.com/sjoblomj/atreus_jj_layout/blob/main/layout.svg" style="max-width: 1200px; width:100%; max-height:509px; height: 100%" />
</a>

# Atreus jj layout
This is a layout / firmware for the [Keyboardio Atreus](https://shop.keyboard.io/collections/keyboardio-atreus/products/keyboardio-atreus), an ultra-compact, light-weight keyboard powered by the open-source [Kaleidoscope](https://github.com/keyboardio/Kaleidoscope) firmware. A traditional keyboard has 104 keys. A compact laptop keyboard typically weighs in at 78 keys. The Keyboardio Atreus manages to fit all the same functionality into just 44 keys. This is possible by assigning keys to different layers.

## Features
* Four layers: Letters, Fun, Upper and Move.
* The Letters layer uses the [Colemak layout](https://en.wikipedia.org/wiki/Colemak) instead of Qwerty.
* The Swedish characters Å, Ä and Ö have their distinct keys.
* The Norwegian / Danish characters Æ an Ø are accessible in the Upper layer.
* ? has a dedicated key, and pressing shift on it will produce a !.
* Special characters are accessible from the Fun and Upper layers.
* The Move layer has keys for moving the cursor, Page Up and Down, Home and End, and also for controlling the mouse and clicking.

## Layout Creator
A Python script, `layout_creator.py`, is included. Given a file with a Kaleidoscope keyboard layout (*.ino-file), it will create an SVG with the layout. The script is not battle-tested and might fail if fed layouts "from the wild", but it works with the layout included in this repository (atreus_jj_layout.ino).

In the layout files, `#define`-directives are used to map key names to the combinations pressed to create them on the OS locale keymap, and they also doubles as the map to symbols for the Layout Creator. For example:
```
#define Key_Equals   LSHIFT(Key_0)     // =
#define Key_Question LSHIFT(Key_Minus) // ? Shifted !
```

This defines `Key_Equals` as being Left Shift + 0 (used by the firmware), and the comment tells the Layout Creator that this should be represented by `=` in the generated layout. The next line defines `Key_Question` as Left Shift + - (used by the firmware), and the comment tells the Layout creator to represent this as `?`, and `!` when shifted.

