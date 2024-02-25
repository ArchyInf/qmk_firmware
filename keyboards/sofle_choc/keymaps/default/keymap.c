/* Copyright 2023 Brian Low
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "keymap_german.h"

enum preonic_layers {
  _MINE,
  _GAME,
  _MINEQWERTY,
  _LOWER,
  _RAISE,
  _MINE_S,
  _GAME_S,
  _ADJUST
};

enum preonic_keycodes {
  MINE = SAFE_RANGE,
  GAME,
  MINEQ,
  LOWER,
  RAISE,
  MINE_S,
  GAME_S
};

#define CT_COMM LCTL(KC_COMM)

// nav back/forward (intellij)
#define CA_LEFT LCTL(LALT(KC_LEFT))
#define CA_RIGHT LCTL(LALT(KC_RIGHT))

// add caret at find result (intellij)
#define CR_NEXT LALT(KC_J)
#define CR_ALL LCTL(LALT(LSFT(KC_J)))

// Jump To
#define AL_HOME LCTL(LALT(LSFT(KC_HOME)))

#define CPY LCTL(KC_C)
#define CUT LCTL(KC_X)
#define PST LCTL(KC_V)
#define UNDO LCTL(KC_Y)
#define CTESC CTL_T(KC_ESC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | CTESC  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LCTL | LGUI | LCMD | LALT | /Enter  /       \Space \  | RALT | RCMD | RGUI | RCTL |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */

[_MINE] = LAYOUT(
    QK_LEAD,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,     KC_7,     KC_8,    KC_9,    KC_0,  KC_DEL,
    KC_TAB,   DE_UDIA, DE_L,    DE_U,    DE_A,    DE_J,                          DE_W,     DE_B,     DE_D,    DE_G, DE_ADIA, DE_ODIA,
    CTESC,    DE_C,    DE_R,    DE_I,    DE_E,    DE_O,                          DE_M,     DE_N,     DE_T,    DE_S,    DE_H,  KC_ENT,
    KC_LCTL,  DE_V,    DE_X,    DE_Z,    DE_Y,    DE_Q,    KC_MUTE,   KC_MPLY,   DE_P,     DE_F,  DE_COMM,  DE_DOT,    DE_K, QK_LEAD,
                    KC_LGUI,  MINE_S, KC_LSFT, KC_LALT,    KC_SPC,    QK_LEAD, KC_SPC,    RAISE,    LOWER,  _______
),

[_MINEQWERTY] = LAYOUT(
    QK_LEAD,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                          KC_6,    KC_7,    KC_8,   KC_9,    KC_0,  KC_DEL,
    KC_ESC,   DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,                          DE_Z,    DE_U,    DE_I,   DE_O,    DE_P,  DE_ODIA,
    CTESC,    DE_A,    DE_S,    DE_D,    DE_F,    DE_G,                          DE_H,    DE_J,    DE_K,   DE_L, _______,  KC_ENT,
    KC_LCTL,  DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,   KC_MUTE,   KC_MPLY,    DE_N,    DE_M, KC_COMM, KC_DOT,   KC_UP,  QK_LEAD,
                   KC_LGUI,  MINE_S, KC_LSFT, KC_LALT,    KC_SPC,    QK_LEAD, KC_SPC,    RAISE,    LOWER,  _______
),

[_GAME] = LAYOUT(
    DE_TILD, DE_1,    DE_2,    DE_3,    DE_4,    DE_5,                          DE_6,    DE_7,    DE_8,    DE_9,    DE_0,    KC_BSPC,
    KC_TAB,  DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,                          DE_Z,    DE_U,    DE_I,     DE_O,    DE_P,    KC_DEL,
    KC_ESC,  DE_A,    DE_S,    DE_D,    DE_F,    DE_G,                          DE_H,    DE_J,    DE_K,    DE_L,    _______, KC_ENT,
    KC_LSFT, DE_Y,    DE_X,    DE_C,    DE_V,    DE_B,    KC_MUTE,   KC_MPLY,   DE_N,    DE_M,    KC_COMM, KC_DOT,  KC_UP,   KC_ENT,
                      KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  GAME_S,    _______, KC_SPC,    RAISE,    LOWER,  _______
),

[_LOWER] = LAYOUT(
    _______, _______, _______, _______, _______,  _______,                    _______, _______, _______, _______, _______, _______, 
    DE_CIRC, DE_QUES, DE_PERC, DE_PLUS, DE_EXLM,  _______,                    _______, _______, DE_LABK, DE_RABK, _______, _______,
    DE_HASH, DE_SLSH, DE_EQL,  DE_MINS, DE_DQUO,  DE_QUOT,                    _______, DE_AMPR, DE_PIPE,   DE_SS, DE_TILD, _______,
    _______,  DE_BSLS, DE_UNDS, DE_ASTR, DE_GRV,  _______, _______,  _______, _______,   DE_AT,  DE_DLR, DE_EURO, _______, _______,
                       _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
),

[_RAISE] = LAYOUT(
    _______, _______, _______, _______, _______,  _______,                   _______, _______, KC_PGUP, _______,  _______,  _______, 
    _______, DE_LBRC, DE_LCBR, DE_RCBR, DE_RBRC,  _______,                   _______, KC_BSPC,   KC_UP, KC_DEL,   _______,  _______,
    _______,     CPY, DE_LPRN, DE_RPRN, DE_SCLN,  AL_HOME,                   CA_LEFT, KC_LEFT, KC_DOWN, KC_RGHT,  CA_RIGHT, _______,
    _______,     PST,     CUT,    UNDO, CR_NEXT,   CR_ALL, _______, _______, _______, KC_HOME, KC_PGDN, KC_END,   KC_LCTL,  _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_MINE_S] = LAYOUT(
    _______, _______, _______, _______, _______,  _______,                   _______, _______, DE_SLSH, DE_ASTR, _______, _______, 
    DE_CIRC,   KC_F9,  KC_F10,  KC_F11,  KC_F12,  _______,                   _______,    KC_7,    KC_8,    KC_9, DE_MINS, KC_BSPC,
    _______,   KC_F5,   KC_F6,   KC_F7,   KC_F8,  _______,                   _______,    KC_4,    KC_5,    KC_6, DE_PLUS, _______,
    _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,  _______, _______, _______, KC_PSCR,    KC_1,    KC_2,    KC_3, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______,    KC_0, _______, _______
),

[_GAME_S] = LAYOUT(
    _______, _______, _______, _______, _______,  _______,                   _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______,  _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_ADJUST] = LAYOUT(
    _______, _______, _______, _______, _______,  _______,                   _______, _______, _______, _______, _______, _______, 
    _______, _______, _______, _______, _______,  _______,                   _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______,  _______,                   _______,    MINE,    GAME,   MINEQ, _______, RGB_MOD,
    _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, RGB_RMOD,
                       _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_U, KC_WH_D) },
    { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_WH_U, KC_WH_D) }
};
#endif

void rgb_base(uint8_t led_min, uint8_t led_max) {
  for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
    for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
        uint8_t index = g_led_config.matrix_co[row][col];
        
        if (index < led_min || index >= led_max || index == NO_LED)
          continue;

        unsigned short keycode = keymap_key_to_keycode(0, (keypos_t){col,row});
        switch (keycode) {
        case DE_E:
          rgb_matrix_set_color(index, RGB_TEAL);
          break;
        case DE_N:
          rgb_matrix_set_color(index, RGB_TEAL);
          break;
        }
    }
  }
}

HSV tohsv(uint8_t h, uint8_t s, uint8_t v) {
  HSV hsv;
  hsv.h = h;
  hsv.s = s;
  hsv.v = v;
  return hsv;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
        
    uint8_t layer = get_highest_layer(layer_state);

    HSV color = tohsv(HSV_TURQUOISE);
    switch (layer)
    {
    default:
      color = tohsv(HSV_TURQUOISE);
      break;
    case _LOWER: 
      color = tohsv(HSV_GREEN);
      break;
    case _RAISE:
      color = tohsv(HSV_CORAL);
      break;
    case _MINE_S:
      color = tohsv(HSV_RED);
      break;
    }
    
    color.v = 20;

    RGB rgb = hsv_to_rgb(color);

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index < led_min || index >= led_max || index == NO_LED)
              continue;
            
             rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
        }
    }
        
    rgb_base(led_min, led_max);

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
        case DE_CIRC:
          if (record->event.pressed) {
            register_code(KC_GRV);
          } else {
            unregister_code(KC_GRV);
            tap_code(KC_SPC);
          }
          return false;
          break;
        case DE_GRV:
          if (record->event.pressed) {
            register_code(KC_EQL);
          } else {
            unregister_code(KC_EQL);
            tap_code(KC_SPC);
          }
          return false;
          break;
        case MINE:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_MINE);
          }
          return false;
          break;
        case GAME:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_GAME);
          }
          return false;
          break;
        case MINEQ:
          if (record->event.pressed) {
            set_single_persistent_default_layer(_MINEQWERTY);
          }
          return false;
          break;
        case LOWER:
          if (record->event.pressed) {
            layer_on(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_LOWER);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case RAISE:
          if (record->event.pressed) {
            layer_on(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          } else {
            layer_off(_RAISE);
            update_tri_layer(_LOWER, _RAISE, _ADJUST);
          }
          return false;
          break;
        case MINE_S:
          if (record->event.pressed) {
            layer_on(_MINE_S);
          } else {
            layer_off(_MINE_S);
          }
          return false;
          break;
        case GAME_S:
          if (record->event.pressed) {
            layer_on(_GAME_S);
          } else {
            layer_off(_GAME_S);
          }
          return false;
          break;
      }
    return true;
};

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    // navigate to class
    if(leader_sequence_one_key(DE_R)) {
      SEND_STRING(SS_LCTL(SS_TAP(X_N)));
    }
    // navigate to file
    if(leader_sequence_one_key(DE_I)) {
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_N))));
    }
    // navigate to symbol
    if(leader_sequence_one_key(DE_E)) {
      SEND_STRING(SS_LCTL(SS_LALT(SS_LSFT(SS_TAP(X_N)))));
    }
    // navigate to local symbol; ESC closes navigate to dialog if openf
    if(leader_sequence_one_key(DE_Y)) {
      SEND_STRING(SS_TAP(X_ESC)SS_DELAY(10)SS_LCTL(SS_TAP(X_F12)));
    }

    // save
    if(leader_sequence_one_key(DE_UDIA)) {
      SEND_STRING(SS_LCTL(SS_TAP(X_S)));
    }
    // usages
    if(leader_sequence_one_key(DE_U)) {
      SEND_STRING(SS_LALT(SS_TAP(X_F7)));
    }
    // breakpoint
    if(leader_sequence_one_key(DE_B)) {
      SEND_STRING(SS_LCTL(SS_TAP(X_F8)));
    }
    // goto declaration
    if(leader_sequence_one_key(DE_C)) {
      SEND_STRING(SS_LCTL(SS_TAP(X_B)));
    }
    // surround {}
    if(leader_sequence_one_key(DE_S)) {
      SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_T)))SS_DELAY(50)SS_TAP(X_7)SS_DELAY(50)SS_TAP(X_ENT));
    }
    // find word at carret
    if(leader_sequence_one_key(DE_F)) {
      SEND_STRING(SS_LCTL(SS_TAP(X_F3)));
    }
    // select containing declaration
    if(leader_sequence_one_key(DE_X)) {
      SEND_STRING(SS_LCTL(SS_LALT(SS_LSFT(SS_TAP(X_D)))));
    }
    // reformat code
    if(leader_sequence_one_key(DE_L)) {
      SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_L))));
    }
    // rename refactor
    if(leader_sequence_one_key(DE_Z)) {
      SEND_STRING(SS_LSFT(SS_TAP(X_F6)));
    }
    // introduce variable
    if(leader_sequence_one_key(DE_V)) {
      SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_V))));
    }
    // inline
    if(leader_sequence_one_key(DE_N)) {
      SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_N))));
    }
    // console
    if(leader_sequence_one_key(DE_A)) {
      SEND_STRING(SS_LALT(SS_TAP(X_F12)));
    }
    // clear windows
    if(leader_sequence_one_key(DE_J)) {
      SEND_STRING(SS_LSFT(SS_LCTL(SS_TAP(X_F12))));
    }
    // vcs file history
    if(leader_sequence_one_key(DE_Q)) {
      SEND_STRING(SS_LSFT(SS_LCTL(SS_TAP(X_Q))));
    }
    // convert selection to carets
    if(leader_sequence_one_key(KC_COMM)) {
      SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_COMM))));
    }
    // smart keep line carets
    if(leader_sequence_one_key(KC_DOT)) {
      SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_DOT))));
    }
    // duplicate line for carets in clipboard
    if(leader_sequence_one_key(DE_D)) {
      SEND_STRING(SS_LSFT(SS_LCTL(SS_TAP(X_D))));
    }
    // Navigate to
    if(leader_sequence_one_key(DE_G)) {
      SEND_STRING(SS_LSFT(SS_LCTL(SS_TAP(X_G))));
    }
    // minimize/maximize tool window
    if(leader_sequence_one_key(DE_3)) {
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_F3))));
    }
    // analyze stack trace
    if(leader_sequence_one_key(DE_4)) {
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_F4))));
    }
    // refresh Unity
    if(leader_sequence_one_key(DE_5)) {
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_F5))));
    }

    // task manager
    if(leader_sequence_one_key(KC_ESC)) {
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_ESC))));
    }
    // alt+f4
    if(leader_sequence_one_key(KC_TAB)) {
      SEND_STRING(SS_LALT(SS_TAP(X_F4)));
    }
}

