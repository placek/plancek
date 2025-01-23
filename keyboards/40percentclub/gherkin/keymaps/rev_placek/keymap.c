#include QMK_KEYBOARD_H
#include "../placek.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_ortho_3x10(
    SFT_Z,   GUI_X,   KC_C,    FN3_V,   FN2_BSPC,  FN1_SPC, FN4_B,   ALT_N,   ALT_M,   SFT_ESC,
    CTL_A,   KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
  ),

  [_SPC] = LAYOUT_ortho_3x10(
    _______,  _______, _______, _______, KC_DEL,    _______, KC_COLN, KC_QUES, KC_COMM, KC_DOT,
    KC_F1,    KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_MINS, KC_PLUS, KC_SLSH, KC_TILD,
    KC_1,     KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0
  ),

  [_BSPC] = LAYOUT_ortho_3x10(
    _______,  _______, _______, _______, _______,   KC_DEL,  KC_SCLN, KC_PIPE, KC_LABK, KC_RABK,
    KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,  KC_UNDS, KC_EQL,  KC_BSLS, KC_QUOT,
    KC_EXLM,  KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN
  ),

  [_V] = LAYOUT_ortho_3x10(
    _______,  _______, MUTE,    _______, KC_VOLD,   KC_VOLU, QK_RBT,  _______, _______, KC_PSCR,
    _______,  _______, _______, _______, _______,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DQUO,
    _______,  _______, _______, _______, DM_REC1,   DM_PLY1, _______, _______, KC_LCBR, KC_RCBR
  ),

  [_B] = LAYOUT_ortho_3x10(
    _______,  _______, _______, QK_BOOT, KC_MPRV,   KC_MNXT, _______, KC_MPLY, _______, KC_PWR,
    _______,  _______, _______, _______, _______,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_GRV,
    _______,  _______, _______, _______, DM_REC1,   DM_PLY1, _______, _______, KC_LBRC, KC_RBRC
  )

};

#define SCROLL_RATE 0.1

float scroll_accumulated_h = 0;
float scroll_accumulated_v = 0;

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
  mouse_report.buttons &= MOUSE_BTN1;
  if (layer_state_is(_SPC)) { // scroll
    pimoroni_trackball_set_rgbw(0x80, 0x00, 0x00, 0x00);
    scroll_accumulated_h += (float)mouse_report.x * SCROLL_RATE;
    scroll_accumulated_v -= (float)mouse_report.y * SCROLL_RATE;
    mouse_report.h = (int8_t)scroll_accumulated_h;
    mouse_report.v = (int8_t)scroll_accumulated_v;
    scroll_accumulated_h -= (int8_t)scroll_accumulated_h;
    scroll_accumulated_v -= (int8_t)scroll_accumulated_v;
    mouse_report.x = 0;
    mouse_report.y = 0;

  } else if (layer_state_is(_BSPC)) { // right click
    pimoroni_trackball_set_rgbw(0x00, 0x80, 0x00, 0x00);
    mouse_report.x = 0;
    mouse_report.y = 0;
    if (mouse_report.buttons & MOUSE_BTN1) { mouse_report.buttons = MOUSE_BTN2; }

  } else if (layer_state_is(_V)) { // middle click
    pimoroni_trackball_set_rgbw(0x00, 0x00, 0x80, 0x00);
    mouse_report.x = 0;
    mouse_report.y = 0;
    if (mouse_report.buttons & MOUSE_BTN1) { mouse_report.buttons = MOUSE_BTN3; }

  } else if (layer_state_is(_B)) { // speed up
    pimoroni_trackball_set_rgbw(0x80, 0x00, 0x80, 0x00);
    mouse_report.x *= 3;
    mouse_report.y *= 3;

  } else {
    pimoroni_trackball_set_rgbw(0x00, 0x00, 0x00, 0x00);
  }
  return mouse_report;
}

const uint16_t PROGMEM c_a_combo[] = {CTL_A, KC_S, COMBO_END};
const uint16_t PROGMEM btn_combo[] = {FN3_V, FN2_BSPC, COMBO_END};
const uint16_t PROGMEM tab_combo[] = {KC_Q, KC_W, COMBO_END};

combo_t key_combos[] = {
  COMBO(tab_combo, KC_TAB),
  COMBO(c_a_combo, C_A),
  COMBO(btn_combo, KC_BTN1)
};
