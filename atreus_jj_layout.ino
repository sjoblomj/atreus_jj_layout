/* -*- mode: c++ -*-
   Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
   Copyright (C) 2018, 2019  Keyboard.io, Inc

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/

#include "Kaleidoscope.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-ShapeShifter.h"

const int MOUSE_SPEED_SLOW = 5;
const int MOUSE_SPEED_FAST = 15;

enum {
  MACRO_MOUSE_SPEED
};

enum {
  COLEMAK,
  CHAR,
  FUN,
  MOVE
};

/* *INDENT-OFF* */
/* *LAYOUTER-START* */
#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

// Key definitions at https://github.com/keyboardio/Kaleidoscope/blob/master/src/kaleidoscope/key_defs/keyboard.h
#define Key_Exclamation        LSHIFT(Key_1)                     // !
#define Key_DoubleQuote        LSHIFT(Key_2)                     // "
#define Key_At                 RALT(Key_2)                       // @
#define Key_Hash               LSHIFT(Key_3)                     // #
#define Key_Dollar             RALT(Key_4)                       // $
#define Key_Percent            LSHIFT(Key_5)                     // %
#define Key_And                LSHIFT(Key_6)                     // &
#define Key_SlashForward       LSHIFT(Key_7)                     // /
#define Key_LeftCurlyBracket   RALT(Key_7)                       // {
#define Key_LeftRoundBracket   LSHIFT(Key_8)                     // (
#define Key_LeftSquareBracket  RALT(Key_8)                       // [
#define Key_RightSquareBracket RALT(Key_9)                       // ]
#define Key_RightRoundBracket  LSHIFT(Key_9)                     // )
#define Key_RightCurlyBracket  RALT(Key_0)                       // }
#define Key_EqualSign          LSHIFT(Key_0)                     // =
#define Key_Question           LSHIFT(Key_Minus)                 // ? Shifted !
#define Key_SlashBackward      RALT(Key_Minus)                   // Backslash
#define Key_PlusSign           Key_Minus                         // +
#define Key_LeftSingleQuote    LSHIFT(Key_Equals)                // `
#define Key_RightSingleQuote   Key_Equals                        // ´
#define Key_Caret              LSHIFT(Key_RightBracket)          // ^
#define Key_Tilde              RALT(Key_RightBracket)            // ~

#define Key_Star               LSHIFT(Key_Backslash)             // *
#define Key_SingleQuote        Key_Backslash                     // '
#define Key_Aa                 Key_LeftBracket                   // Å
#define Key_Ae                 Key_Quote                         // Ä
#define Key_Oe                 Key_Semicolon                     // Ö
#define Key_Nae                RALT(Key_Quote)                   // Æ
#define Key_Noe                RALT(Key_Semicolon)               // Ø
#define Key_MinusSign          Key_Slash                         // -
#define Key_Underscore         LSHIFT(Key_Slash)                 // _
#define Key_SectionSign        Key_Backtick                      // §
#define Key_OneOverTwo         LSHIFT(Key_Backtick)              // ½
#define Key_LeftAngleBracket   Key_NonUsBackslashAndPipe         // <
#define Key_RightAngleBracket  LSHIFT(Key_NonUsBackslashAndPipe) // >
#define Key_Pipe               RALT(Key_NonUsBackslashAndPipe)   // |
#define Key_Euro               RALT(Key_E)                       // €
#define Key_PeriodSign         Key_Period                        // . Shifted :
#define Key_CommaSign          Key_Comma                         // , Shifted ;

#define Key_Bksp               Key_Backspace                     // Bksp
#define Key_Ctrl               Key_LeftControl                   // Ctrl
#define Key_Shift              Key_LeftShift                     // Shift
#define Key_Super              Key_LeftGui                       // Super
#define Key_Alt                Key_LeftAlt                       // Alt
#define Key_Ins                Key_Insert                        // Ins
#define Key_Del                Key_Delete                        // Del
#define Key_PgUp               Key_PageUp                        // Pg↑
#define Key_PgDn               Key_PageDown                      // Pg↓
#define Key_PrtSc              Key_PrintScreen                   // PrtSc
#define Key_ArrowUp            Key_UpArrow                       // ↑
#define Key_ArrowDown          Key_DownArrow                     // ↓
#define Key_ArrowLeft          Key_LeftArrow                     // ←
#define Key_ArrowRight         Key_RightArrow                    // →
#define Key_MouseUp            Key_mouseUp                       // M↑
#define Key_MouseDown          Key_mouseDn                       // M↓
#define Key_MouseLeft          Key_mouseL                        // M←
#define Key_MouseRight         Key_mouseR                        // M→
#define Key_MouseClickL        Key_mouseBtnL                     // McL
#define Key_MouseClickM        Key_mouseBtnM                     // McM
#define Key_MouseClickR        Key_mouseBtnR                     // McR
#define Key_MouseScrollU       Key_mouseScrollUp                 // MSc↑
#define Key_MouseScrollD       Key_mouseScrollDn                 // MSc↓
#define Key_MouseSpeed         M(MACRO_MOUSE_SPEED)              // MSpd

#define Key_IntelliJScratch    LSHIFT(LALT(LCTRL(Key_Insert)))   // Isf
#define Key_IntelliJRunDebug   LALT(LSHIFT(Key_F9))              // IrD
#define Key_IntelliJRunTests   LALT(LSHIFT(Key_F10))             // IrT
#define Key_FocusSearchBar     LALT(Key_D)                       // FSB
#define Key_Mute               Consumer_Mute                     // &#128264; 0
#define Key_VolumeIncrease     Consumer_VolumeIncrement          // &#128264; +
#define Key_VolumeDecrease     Consumer_VolumeDecrement          // &#128264; -

KEYMAPS(
  [COLEMAK] = KEYMAP_STACKED
  (
                              Key_Q                ,Key_W                 ,Key_F                ,Key_P                 ,Key_G
                             ,Key_A                ,Key_R                 ,Key_S                ,Key_T                 ,Key_D
                             ,Key_Z                ,Key_X                 ,Key_C                ,Key_V                 ,Key_B                 ,Key_And
                             ,Key_Esc              ,Key_Tab               ,Key_Super            ,Key_Shift             ,Key_Bksp              ,Key_Ctrl

                             ,Key_J                ,Key_L                 ,Key_U                ,Key_Y                 ,Key_Aa
                             ,Key_H                ,Key_N                 ,Key_E                ,Key_I                 ,Key_O
      ,Key_Tilde             ,Key_K                ,Key_M                 ,Key_PeriodSign       ,Key_Oe                ,Key_Ae
      ,Key_Alt               ,Key_Space            ,MO(CHAR)              ,Key_CommaSign        ,Key_Question          ,Key_Enter
  ),

  [CHAR] = KEYMAP_STACKED
  (
                              Key_SlashForward     ,Key_At                ,Key_ArrowUp          ,Key_Euro              ,Key_Dollar
                             ,Key_DoubleQuote      ,Key_ArrowLeft         ,Key_ArrowDown        ,Key_ArrowRight        ,Key_Hash
                             ,Key_LeftRoundBracket ,Key_RightRoundBracket ,Key_LeftCurlyBracket ,Key_RightCurlyBracket ,Key_LeftSquareBracket ,Key_RightSquareBracket
                             ,TG(FUN)              ,___                   ,___                  ,___                   ,Key_Del               ,___

                             ,Key_PgUp             ,Key_7                 ,Key_8                ,Key_9                 ,Key_EqualSign
                             ,Key_PgDn             ,Key_4                 ,Key_5                ,Key_6                 ,Key_Star
      ,Key_LeftAngleBracket  ,Key_OneOverTwo       ,Key_1                 ,Key_2                ,Key_3                 ,Key_PlusSign
      ,___                   ,TG(MOVE)             ,___                   ,Key_0                ,Key_0                 ,Key_MinusSign
  ),

  [FUN] = KEYMAP_STACKED
  (
                              Key_SlashBackward    ,Key_IntelliJScratch   ,Key_IntelliJRunTests ,Key_IntelliJRunDebug  ,Key_FocusSearchBar
                             ,Key_SingleQuote      ,Key_Mute              ,Key_VolumeDecrease   ,Key_VolumeIncrease    ,Key_Percent
                             ,Key_LeftSingleQuote  ,Key_RightSingleQuote  ,Key_Nae              ,Key_Noe               ,Key_Caret             ,Key_Pipe
                             ,MoveToLayer(COLEMAK) ,___                   ,___                  ,___                   ,Key_Ins               ,___

                             ,Key_Home             ,Key_F7                ,Key_F8               ,Key_F9                ,Key_F10
                             ,Key_End              ,Key_F4                ,Key_F5               ,Key_F6                ,Key_F11
      ,Key_RightAngleBracket ,Key_SectionSign      ,Key_F1                ,Key_F2               ,Key_F3                ,Key_F12
      ,___                   ,___                  ,MoveToLayer(COLEMAK)  ,Key_PrtSc            ,___                   ,Key_Underscore
  ),

  [MOVE] = KEYMAP_STACKED
  (
                              Key_MouseScrollU     ,Key_MouseClickL       ,Key_MouseUp          ,Key_MouseClickM       ,Key_MouseClickR
                             ,Key_MouseSpeed       ,Key_MouseLeft         ,Key_MouseDown        ,Key_MouseRight        ,___
                             ,Key_MouseScrollD     ,Key_PgUp              ,Key_PgDn             ,Key_Home              ,Key_End               ,___
                             ,MoveToLayer(COLEMAK) ,___                   ,___                  ,___                   ,___                   ,___

                             ,Key_PgUp             ,___                   ,Key_ArrowUp          ,___                   ,Key_Home
                             ,Key_PgDn             ,Key_ArrowLeft         ,Key_ArrowDown        ,Key_ArrowRight        ,Key_End
      ,___                   ,___                  ,___                   ,___                  ,___                   ,___
      ,___                   ,___                  ,MoveToLayer(COLEMAK)  ,___                  ,___                   ,___
  ),
)
/* *LAYOUTER-STOP* */
/* *INDENT-ON* */


KALEIDOSCOPE_INIT_PLUGINS(
  Macros,
  MouseKeys,
  ShapeShifter
);

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    switch (macro_id) {
      case MACRO_MOUSE_SPEED:
        MouseKeys.speed = (MouseKeys.speed == MOUSE_SPEED_FAST) ? MOUSE_SPEED_SLOW : MOUSE_SPEED_FAST;
        break;
      default:
        break;
    }
  }
  return MACRO_NONE;
}

static const kaleidoscope::plugin::ShapeShifter::dictionary_t shape_shifter_dictionary[] PROGMEM = {
  {Key_Question, Key_1}, // Replace Shift+'?' with Shift+'1' => '!'
  {Key_NoKey, Key_NoKey},
};

void setup() {
  Kaleidoscope.setup();

  MouseKeys.setSpeedLimit(25);
  MouseKeys.speed = MOUSE_SPEED_SLOW;
  MouseKeys.accelSpeed = 0;

  ShapeShifter.dictionary = shape_shifter_dictionary;
}

void loop() {
  Kaleidoscope.loop();
}
