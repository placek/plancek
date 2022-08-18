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
#include "muse.h"


enum planck_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  BACKLIT,
  TMUX_COPY,
  TMUX_PASTE
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
} td_state_t;

typedef struct {
  bool is_press_action;
  td_state_t state;
} td_tap_t;

enum {
  TMUX_CTL,
  VIM_ALT,
  PWRSLP
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

static td_tap_t btap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

static td_tap_t wtap_state = {
  .is_press_action = true,
  .state = TD_NONE
};

void b_finished(qk_tap_dance_state_t *state, void *user_data) {
  btap_state.state = cur_dance(state);
  switch (btap_state.state) {
    case TD_SINGLE_TAP: register_code(KC_LCTL); register_code(KC_B); unregister_code(KC_B); unregister_code(KC_LCTL); break;
    case TD_SINGLE_HOLD: register_code(KC_LCTL); break;
    default: break;
  }
}

void b_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (btap_state.state) {
    case TD_SINGLE_HOLD: unregister_code(KC_LCTL); break;
    default: break;
  }
  btap_state.state = TD_NONE;
}

void w_finished(qk_tap_dance_state_t *state, void *user_data) {
  wtap_state.state = cur_dance(state);
  switch (wtap_state.state) {
    case TD_SINGLE_TAP: register_code(KC_LCTL); register_code(KC_W); unregister_code(KC_W); unregister_code(KC_LCTL); break;
    case TD_SINGLE_HOLD: register_code(KC_LALT); break;
    default: break;
  }
}

void w_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (wtap_state.state) {
    case TD_SINGLE_HOLD: unregister_code(KC_LALT); break;
    default: break;
  }
  wtap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TMUX_CTL] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, b_finished, b_reset),
  [VIM_ALT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, w_finished, w_reset),
  [PWRSLP]   = ACTION_TAP_DANCE_DOUBLE(KC_PWR, KC_SLEP)
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
 * | Ctrl |   /  | GUI  | Alt  |Lower |    Space    |Raise | AltR | Left | Down |Right |
 * +-----------------------------------------------------------------------------------+
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,          KC_Q,    KC_W,    KC_E,        KC_R,  KC_T,   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,          KC_A,    KC_S,    KC_D,        KC_F,  KC_G,   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    LSFT_T(KC_BSLS), KC_Z,    KC_X,    KC_C,        KC_V,  KC_B,   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_UP,   KC_SFTENT,
    TD(TMUX_CTL),    KC_SLSH, KC_LGUI, TD(VIM_ALT), LOWER, KC_SPC, KC_SPC, RAISE, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
),

/* Lower
 * +-----------------------------------------------------------------------------------+
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   =  |   [  |   ]  |  |   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      | PrSc | PgUp |Pause |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |TPASTE|      |      |  AG< |      |             |      |      | Home | PgDn | End  |
 * +-----------------------------------------------------------------------------------+
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_TILD,    KC_EXLM, KC_AT,   KC_HASH,      KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL,
    KC_TRNS,    KC_F1,   KC_F2,   KC_F3,        KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_EQL,  KC_LBRC, KC_RBRC, KC_PIPE,
    KC_TRNS,    KC_F7,   KC_F8,   KC_F9,        KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS, KC_PSCR, KC_PGUP, KC_PAUS,
    TMUX_PASTE, KC_TRNS, KC_TRNS, LAG(KC_LEFT), KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGDN, KC_END
),

/* Raise
 * +-----------------------------------------------------------------------------------+
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   +  |   {  |   }  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      | Mute | Vol+ | Play |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |TCOPY |      |      |      |      |             |      |  AG> | Prev | Vol- | Next |
 * +-----------------------------------------------------------------------------------+
 */
[_RAISE] = LAYOUT_planck_grid(
    KC_GRV,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,         KC_9,    KC_0,    KC_DEL,
    KC_TRNS,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_PLUS,      KC_LCBR, KC_RCBR, KC_BSLS,
    KC_TRNS,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS,      KC_MUTE, KC_VOLU, KC_MPLY,
    TMUX_COPY, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, LAG(KC_RGHT), KC_MPRV, KC_VOLD, KC_MNXT
),

/* Adjust (Lower + Raise)
 * +-----------------------------------------------------------------------------------+
 * | Dspl |Reset |Debug | RGB  |      | HUE+ | HUE- | SAT+ | SAT- |      |      |Power |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |MUSmod|Aud on|Audoff|      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|TermOn|TermOf|      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * +-----------------------------------------------------------------------------------+
 */
[_ADJUST] = LAYOUT_planck_grid(
    KC_FIND, QK_BOOT, DEBUG,   RGB_TOG, KC_TRNS, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD,  KC_TRNS, KC_TRNS, TD(PWRSLP),
    KC_TRNS, KC_TRNS, MU_MOD,  AU_ON,   AU_OFF,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,   MI_OFF,  TERM_ON, TERM_OFF, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
)

};

#ifdef AUDIO_ENABLE
  float plover_song[][2]    = SONG(PLOVER_SOUND);
  float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TMUX_COPY:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_B);
        unregister_code(KC_B);
        unregister_code(KC_LCTL);
        register_code(KC_LBRC);
        unregister_code(KC_LBRC);
      }
      return false;
      break;
    case TMUX_PASTE:
      if (record->event.pressed) {
        register_code(KC_LCTL);
        register_code(KC_B);
        unregister_code(KC_B);
        unregister_code(KC_LCTL);
        register_code(KC_RBRC);
        unregister_code(KC_RBRC);
      }
      return false;
      break;
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
        #ifdef KEYBOARD_planck_rev5
          writePinLow(E6);
        #endif
      } else {
        unregister_code(KC_RSFT);
        #ifdef KEYBOARD_planck_rev5
          writePinHigh(E6);
        #endif
      }
      return false;
      break;
  }
  return true;
}

bool muse_mode = false;
uint8_t last_muse_note = 0;
uint16_t muse_counter = 0;
uint8_t muse_offset = 70;
uint16_t muse_tempo = 50;

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (muse_mode) {
    if (IS_LAYER_ON(_RAISE)) {
      if (clockwise) {
        muse_offset++;
      } else {
        muse_offset--;
      }
    } else {
      if (clockwise) {
        muse_tempo+=1;
      } else {
        muse_tempo-=1;
      }
    }
  } else {
    if (clockwise) {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_DOWN);
      #else
        tap_code(KC_PGDN);
      #endif
    } else {
      #ifdef MOUSEKEY_ENABLE
        tap_code(KC_MS_WH_UP);
      #else
        tap_code(KC_PGUP);
      #endif
    }
  }
    return true;
}

bool dip_switch_update_user(uint8_t index, bool active) {
  switch (index) {
    case 0: {
#ifdef AUDIO_ENABLE
      static bool play_sound = false;
#endif
      if (active) {
#ifdef AUDIO_ENABLE
        if (play_sound) { PLAY_SONG(plover_song); }
#endif
        layer_on(_ADJUST);
      } else {
#ifdef AUDIO_ENABLE
        if (play_sound) { PLAY_SONG(plover_gb_song); }
#endif
        layer_off(_ADJUST);
      }
#ifdef AUDIO_ENABLE
      play_sound = true;
#endif
      break;
    }
    case 1:
      if (active) {
        muse_mode = true;
      } else {
        muse_mode = false;
      }
  }
  return true;
}

void matrix_scan_user(void) {
#ifdef AUDIO_ENABLE
  if (muse_mode) {
    if (muse_counter == 0) {
      uint8_t muse_note = muse_offset + SCALE[muse_clock_pulse()];
      if (muse_note != last_muse_note) {
        stop_note(compute_freq_for_midi_note(last_muse_note));
        play_note(compute_freq_for_midi_note(muse_note), 0xF);
        last_muse_note = muse_note;
      }
    }
    muse_counter = (muse_counter + 1) % muse_tempo;
  } else {
    if (muse_counter) {
      stop_all_notes();
      muse_counter = 0;
    }
  }
#endif
}

bool music_mask_user(uint16_t keycode) {
  switch (keycode) {
    case RAISE:
    case LOWER:
      return false;
    default:
      return true;
  }
}
