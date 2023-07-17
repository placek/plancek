/* Copyright 2022 placek
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

enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  CUSTOM_A = SAFE_RANGE,
  CUSTOM_B
};

// Tap Dance declarations
typedef enum {
  TD_NONE,
  TD_UNKNOWN,
  TD_SINGLE_TAP,
  TD_SINGLE_HOLD,
  TD_DOUBLE_TAP,
  TD_DOUBLE_HOLD,
  TD_DOUBLE_SINGLE_TAP,
  TD_TRIPLE_TAP,
  TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
  bool is_press_action;
  td_state_t state;
} td_tap_t;

enum {
  PWRSLP,
  MUTE,
  ML,
  MD,
  MU,
  MR,
  FB
};

// Tap Dance definitions
td_state_t cur_dance(qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
    else return TD_SINGLE_HOLD;
  } else if (state->count == 2) {
    if (state->interrupted) {
      return TD_DOUBLE_SINGLE_TAP;
    } else if (state->pressed) {
      return TD_DOUBLE_HOLD;
    } else {
      return TD_DOUBLE_TAP;
    }
  }
  return TD_NONE;
}

static td_tap_t fb_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
  },
  mute_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
  },
  mousel_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
  },
  moused_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
  },
  mouseu_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
  },
  mouser_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
  };

void mousel_finished(qk_tap_dance_state_t *state, void *user_data) {
  mousel_tap_state.state = cur_dance(state);
  switch (mousel_tap_state.state) {
    case TD_SINGLE_TAP:  register_code(KC_MS_L); unregister_code(KC_MS_L); break;
    case TD_SINGLE_HOLD: register_code(KC_MS_L); break;
    case TD_DOUBLE_TAP:  register_code(KC_BTN1); unregister_code(KC_BTN1); break;
    case TD_DOUBLE_HOLD: register_code(KC_WH_L); break;
    default: break;
  }
}

void mousel_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (mousel_tap_state.state) {
    case TD_SINGLE_HOLD: unregister_code(KC_MS_L); break;
    case TD_DOUBLE_HOLD: unregister_code(KC_WH_L); break;
    default: break;
  }
  mousel_tap_state.state = TD_NONE;
}

void moused_finished(qk_tap_dance_state_t *state, void *user_data) {
  moused_tap_state.state = cur_dance(state);
  switch (moused_tap_state.state) {
    case TD_SINGLE_TAP:  register_code(KC_MS_D); unregister_code(KC_MS_D); break;
    case TD_SINGLE_HOLD: register_code(KC_MS_D); break;
    case TD_DOUBLE_TAP:  register_code(KC_BTN3); unregister_code(KC_BTN3); break;
    case TD_DOUBLE_HOLD: register_code(KC_WH_D); break;
    default: break;
  }
}

void moused_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (moused_tap_state.state) {
    case TD_SINGLE_HOLD: unregister_code(KC_MS_D); break;
    case TD_DOUBLE_HOLD: unregister_code(KC_WH_D); break;
    default: break;
  }
  moused_tap_state.state = TD_NONE;
}

void mouseu_finished(qk_tap_dance_state_t *state, void *user_data) {
  mouseu_tap_state.state = cur_dance(state);
  switch (mouseu_tap_state.state) {
    case TD_SINGLE_TAP:  register_code(KC_MS_U); unregister_code(KC_MS_U); break;
    case TD_SINGLE_HOLD: register_code(KC_MS_U); break;
    case TD_DOUBLE_TAP:  register_code(KC_BTN3); unregister_code(KC_BTN3); break;
    case TD_DOUBLE_HOLD: register_code(KC_WH_U); break;
    default: break;
  }
}

void mouseu_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (mouseu_tap_state.state) {
    case TD_SINGLE_HOLD: unregister_code(KC_MS_U); break;
    case TD_DOUBLE_HOLD: unregister_code(KC_WH_U); break;
    default: break;
  }
  mouseu_tap_state.state = TD_NONE;
}

void mouser_finished(qk_tap_dance_state_t *state, void *user_data) {
  mouser_tap_state.state = cur_dance(state);
  switch (mouser_tap_state.state) {
    case TD_SINGLE_TAP:  register_code(KC_MS_R); unregister_code(KC_MS_R); break;
    case TD_SINGLE_HOLD: register_code(KC_MS_R); break;
    case TD_DOUBLE_TAP:  register_code(KC_BTN2); unregister_code(KC_BTN2); break;
    case TD_DOUBLE_HOLD: register_code(KC_WH_R); break;
    default: break;
  }
}

void mouser_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (mouser_tap_state.state) {
    case TD_SINGLE_HOLD: unregister_code(KC_MS_R); break;
    case TD_DOUBLE_HOLD: unregister_code(KC_WH_R); break;
    default: break;
  }
  mouser_tap_state.state = TD_NONE;
}

void fb_finished(qk_tap_dance_state_t *state, void *user_data) {
  fb_tap_state.state = cur_dance(state);
  switch (fb_tap_state.state) {
    case TD_SINGLE_TAP: register_code(KC_LCTL); register_code(KC_LALT); register_code(KC_F7); unregister_code(KC_F7); unregister_code(KC_LALT); unregister_code(KC_LCTL); break;
    case TD_DOUBLE_TAP: register_code(KC_LCTL); register_code(KC_LALT); register_code(KC_F1); unregister_code(KC_F1); unregister_code(KC_LALT); unregister_code(KC_LCTL); break;
    default: break;
  }
}

void mute_finished(qk_tap_dance_state_t *state, void *user_data) {
  mute_tap_state.state = cur_dance(state);
  switch (mute_tap_state.state) {
    case TD_SINGLE_TAP: register_code(KC_CALC); unregister_code(KC_CALC); break;
    case TD_DOUBLE_TAP: register_code(KC_AUDIO_MUTE); unregister_code(KC_AUDIO_MUTE); break;
    default: break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [PWRSLP] = ACTION_TAP_DANCE_DOUBLE(KC_PWR, KC_SLEP),
  [MUTE]   = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mute_finished, NULL),
  [FB]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, fb_finished, NULL),
  [ML]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mousel_finished, mousel_reset),
  [MD]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, moused_finished, moused_reset),
  [MU]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mouseu_finished, mouseu_reset),
  [MR]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, mouser_finished, mouser_reset)
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * +-----------------------------------------------------------------------------------+
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |  Up  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl |   /  | GUI  | Alt  |Lower |    Space    | Raise| AltR | Left | Down |Right |
 * +-----------------------------------------------------------------------------------+
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,          KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,          KC_A,    KC_S,    KC_D,    KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    LSFT_T(KC_BSLS), KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_UP,   KC_SFTENT,
    KC_LCTL,         KC_SLSH, KC_LGUI, KC_LALT, LOWER, KC_SPC, KC_SPC, RAISE, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Lower
 * +-----------------------------------------------------------------------------------+
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   =  |   [  |   ]  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      | PrSc | PgUp |Pause |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |  AG< |      |             |      |      | Home | PgDn | End  |
 * +-----------------------------------------------------------------------------------+
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD, KC_EXLM, KC_AT,   KC_HASH,      KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,        KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_TRNS,
    KC_TRNS, KC_F7,   KC_F8,   KC_F9,        KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_PSCR, KC_PGUP, KC_PAUS,
    KC_TRNS, KC_TRNS, KC_TRNS, LAG(KC_LEFT), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END
),

/* Raise
 * +-----------------------------------------------------------------------------------+
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   -  |   +  |   {  |   }  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |   |  |      |      |      |      |      |      |      |      | Mute | Vol+ | Play |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |  AG> | Prev | Vol- | Next |
 * +-----------------------------------------------------------------------------------+
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,         KC_9,     KC_0,    KC_DEL,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MINS, KC_PLUS,      KC_LCBR,  KC_RCBR, KC_TRNS,
    KC_PIPE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,      TD(MUTE), KC_VOLU, KC_MPLY,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LAG(KC_RGHT), KC_MPRV,  KC_VOLD, KC_MNXT
),

/* Adjust (Lower + Raise)
 * +-----------------------------------------------------------------------------------+
 * | Dspl |FBtogg|      |      |      | Rec  | Play |      |      |      |      |Power |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      | RGB  | Bri+ | Hue+ | Sat+ |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |Cycle | Bri- | Hue- | Sat- |      |  MB1 |  MUP | MB3  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Reset |Debug |      |      |      |             |      |      |  MLT |  MDN |  MRT |
 * +-----------------------------------------------------------------------------------+
 */
[_ADJUST] = LAYOUT_planck_grid(
    KC_FIND, TD(FB),  KC_TRNS, KC_TRNS, KC_TRNS, DM_REC1, DM_PLY1, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TD(PWRSLP),
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RGB_TOG, KC_BRIU, RGB_HUI, RGB_SAI, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, BL_STEP, KC_BRID, RGB_HUD, RGB_SAD, KC_TRNS, KC_BTN1, TD(MU),  KC_BTN3,
    QK_BOOT, DEBUG,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, TD(ML),  TD(MD),  TD(MR)
)

};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    switch (keycode) {
      case CUSTOM_A:
        break;
      case CUSTOM_B:
        break;
      default:
        break;
    }
  }
  return true;
}
