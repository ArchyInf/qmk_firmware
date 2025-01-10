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

#include "i2c_master.h"

#include "keymap_german.h"
#include <transactions.h>

#define FPT_BITS 32
#define FPT_WBITS 14
#include "fptc.h"

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
  GAME_S,
  PLOOPY_SCROLL
};

#define CT_COMM LCTL(KC_COMM)

// nav back/forward (intellij)
//#define CA_LEFT LCTL(LALT(KC_LEFT))
//#define CA_RIGHT LCTL(LALT(KC_RIGHT))
#define CA_LEFT LCTL(LALT(KC_PGDN))
#define CA_RIGHT LCTL(LALT(KC_PGUP))

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

// IDE
#define DBGATT LSFT(KC_F9) // attach debugger
#define GODEC LCTL(KC_B) // goto declaration
#define GOUSG LALT(KC_F7) // find usages
#define ANASTK LCTL(LSFT(KC_F4)) // analyze stack trace
#define UTYRFS LCTL(LSFT(KC_F5)) // unity refresh
#define TGBRK LCTL(KC_F8) // toggle breakpoint

// tap dance
enum {
    TD_MINE_MINEALT,
    TD_SHFT_SHFTALT,
    TD_PSCR_MID,
};

void td_dummy(tap_dance_state_t *state, void *user_data) {
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_MINE_MINEALT] = ACTION_TAP_DANCE_FN_ADVANCED(td_dummy, td_dummy, td_dummy),
    [TD_SHFT_SHFTALT] = ACTION_TAP_DANCE_FN_ADVANCED(td_dummy, td_dummy, td_dummy),
    [TD_PSCR_MID] = ACTION_TAP_DANCE_FN_ADVANCED(td_dummy, td_dummy, td_dummy),
};

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_MINE_MINEALT):
        case TD(TD_SHFT_SHFTALT):
        case TD(TD_PSCR_MID):
            return 400;
        default:
            return 150;
    }
}



// split SYNCING

typedef struct _sync_int_t {
  int data;
} sync_int_t;

bool leaderActive;

void SetLeaderActive(bool state) {
  if (leaderActive == state)
    return;

  leaderActive = state;

  if (is_keyboard_master()) {
    sync_int_t m2s = {state};
    transaction_rpc_send(USER_SYNC_LEADER, sizeof(m2s), &m2s);
  }
}

void user_sync_leader_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const sync_int_t *m2s = (const sync_int_t*)in_data;
    SetLeaderActive(m2s->data != 0);
}

void keyboard_post_init_user(void) {
    transaction_register_rpc(USER_SYNC_LEADER, user_sync_leader_slave_handler);
}



// keymaps

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
    QK_LEAD,  KC_DEL, GODEC,   GOUSG,  ANASTK,   KC_F5,                UTYRFS, TD(TD_PSCR_MID), KC_BTN2, KC_WBAK, KC_F5, KC_DEL,
    KC_TAB,   DE_UDIA, DE_L,    DE_U,    DE_A,    DE_J,                          DE_W,     DE_B,     DE_D,    DE_G, DE_ADIA, DE_ODIA,
    CTESC,    DE_C,    DE_R,    DE_I,    DE_E,    DE_O,                          DE_M,     DE_N,     DE_T,    DE_S,    DE_H,  KC_ENT,
    KC_LCTL,  DE_V,    DE_X,    DE_Z,    DE_Y,    DE_Q,    KC_MUTE,   KC_MPLY,   DE_P,     DE_F,  DE_COMM,  DE_DOT,    DE_K, QK_LEAD,
            KC_LGUI,  TD(TD_MINE_MINEALT), TD(TD_SHFT_SHFTALT), KC_LALT,    KC_SPC,    QK_LEAD, KC_SPC,    RAISE,    LOWER,  _______
),

// QWERTY based; P key moved to more accessible place; added umlauts
[_MINEQWERTY] = LAYOUT(
    QK_LEAD,  KC_DEL, KC_F5,  DBGATT,  ANASTK,  UTYRFS,                KC_BTN1, TD(TD_PSCR_MID), KC_BTN2, KC_WBAK, KC_F5, KC_DEL,
    KC_TAB,   DE_Q,    DE_W,    DE_E,    DE_R,    DE_T,                          DE_Y,    DE_U,    DE_I,   DE_O, DE_ODIA,  DE_UDIA,
    CTESC,    DE_A,    DE_S,    DE_D,    DE_F,    DE_G,                          DE_H,    DE_J,    DE_K,   DE_L,    DE_P,  KC_ENT,
    KC_LCTL,  DE_Z,    DE_X,    DE_C,    DE_V,    DE_B,   KC_MUTE,   KC_MPLY,    DE_N,    DE_M, KC_COMM, KC_DOT, DE_ADIA,  QK_LEAD,
            KC_LGUI,  TD(TD_MINE_MINEALT), TD(TD_SHFT_SHFTALT), KC_LALT,    KC_SPC,    QK_LEAD, KC_SPC,    RAISE,    LOWER,  _______
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
    _______,   TGBRK, _______, _______, _______,  _______,                   _______, _______, DE_SLSH, DE_ASTR, _______, _______,
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
    { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV) },
    { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV) },
    { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV) },
    { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV) },
    { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV) },
    { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV) },
    { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV) },
    { ENCODER_CCW_CW(KC_VOLU, KC_VOLD), ENCODER_CCW_CW(KC_MNXT, KC_MPRV) }
};
#else
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    }
    return false;
}
#endif

void rgb_base(uint8_t led_min, uint8_t led_max) {
  for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
    for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
        uint8_t index = g_led_config.matrix_co[row][col];

        if (index < led_min || index >= led_max || index == NO_LED)
          continue;

        unsigned short keycode = keymap_key_to_keycode(0, (keypos_t){col,row});
        switch (keycode) {
          case DE_C:
          case DE_R:
          case DE_I:
          case DE_H:
          case DE_S:
          case DE_T:
            rgb_matrix_set_color(index, RGB_GREEN);
            break;
          case DE_E:
          case DE_N:
          case KC_LSFT:
          case TD(TD_SHFT_SHFTALT):
          case RAISE:
            rgb_matrix_set_color(index, RGB_TEAL);
            break;
          case QK_LEAD:
            if (leaderActive) {
              rgb_matrix_set_color(index, RGB_BLUE);
            }
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

uint32_t lastTime;
fpt time;

void keyboard_pre_init_user(void) {
    lastTime = timer_read32();
    time = FPT_ZERO;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    fpt elapsed = i2fpt(timer_elapsed(lastTime));
    lastTime = timer_read32();

    fpt delta = fpt_div(elapsed, i2fpt(1000));
    time = fpt_add(time, delta);

    uint8_t layer = get_highest_layer(layer_state);

    HSV color = tohsv(HSV_RED);
    switch (layer)
    {
    default:
      color = tohsv(HSV_RED);
      break;
    case _LOWER:
      color = tohsv(HSV_GREEN);
      break;
    case _RAISE:
      color = tohsv(HSV_CORAL);
      break;
    case _MINE_S:
      color = tohsv(HSV_TURQUOISE);
      break;
    }

    fpt t = fpt_div(time, i2fpt(3));
    t = fpt_mul(t, FPT_PI);
    t = fpt_sin(t);
    t = fpt_add(t, FPT_ONE);
    t = fpt_div(t, FPT_TWO);
    color.v = fpt2i(fpt_mul(t, i2fpt(50)));

    // animation still inaccurate
    color.v = 5;

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
  static bool state_PLOOPY_SCROLL = false;

  tap_dance_action_t *action;
  switch (keycode) {
        case PLOOPY_SCROLL:
          if (record->event.pressed != state_PLOOPY_SCROLL)
          {
            SEND_STRING(SS_TAP(X_NUM)SS_DELAY(10)SS_TAP(X_NUM));
          }
          state_PLOOPY_SCROLL = record->event.pressed;
          break;

        case TD(TD_MINE_MINEALT):
          action = &tap_dance_actions[TD_INDEX(keycode)];
          if (record->event.pressed)
          {
            layer_on(_MINE_S);
            if (action->state.count > 0) {
              register_code(KC_LALT);
            }
          }
          else
          {
            layer_off(_MINE_S);
            if (action->state.count > 1) {
              unregister_code(KC_LALT);
            }
          }
          return true;
          break;

        case TD(TD_SHFT_SHFTALT):
          action = &tap_dance_actions[TD_INDEX(keycode)];
          if (record->event.pressed)
          {
            register_code(KC_LSFT);
            if (action->state.count > 0) {
              register_code(KC_LALT);
            }
          }
          else
          {
            unregister_code(KC_LSFT);
            if (action->state.count > 1) {
              unregister_code(KC_LALT);
            }
          }
          return true;
          break;

        case TD(TD_PSCR_MID):
          action = &tap_dance_actions[TD_INDEX(keycode)];
          if (record->event.pressed)
          {
            if (action->state.count == 0) {
              SEND_STRING(SS_TAP(X_NUM)SS_DELAY(10)SS_TAP(X_NUM));
            }
            if (action->state.count >= 1) {
              register_code(KC_BTN3);
            }
          }
          else
          {
            if (action->state.count <= 1) {
              SEND_STRING(SS_TAP(X_NUM)SS_DELAY(10)SS_TAP(X_NUM));
            }
            if (action->state.count > 1) {
              unregister_code(KC_BTN3);
            }
          }
          return true;
          break;

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
  SetLeaderActive(true);
}

void leader_end_user(void) {
  SetLeaderActive(false);

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
      SEND_STRING(SS_LCTL(SS_LALT(SS_TAP(X_T)))SS_DELAY(50)SS_TAP(X_7));
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
    if(leader_sequence_one_key(KC_BTN2)) {
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_F3))));
    }

    // task manager
    if(leader_sequence_one_key(KC_LCTL)) {
      SEND_STRING(SS_LCTL(SS_LSFT(SS_TAP(X_ESC))));
    }
    // alt+f4
    if(leader_sequence_one_key(KC_TAB)) {
      SEND_STRING(SS_LALT(SS_TAP(X_F4)));
    }
}

//static void render_logo(void) {
//    static const char PROGMEM qmk_logo[] = {
//        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
//        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
//        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
//    };
//
//    oled_write_P(qmk_logo, false);
//}

//bool oled_task_user(void) {
//    oled_clear();
//    oled_write("hello", false);
//
//    return false;
//}
