#include QMK_KEYBOARD_H

#define FN1_SPC     LT(1, KC_SPC)
#define FN2_BSPC    LT(2, KC_BSPC)
#define FN3_V       LT(3, KC_V)
#define FN4_B       LT(4, KC_B)
#define SFT_Z       RSFT_T(KC_Z)
#define SFT_ESC     RSFT_T(KC_ESC)
#define CTL_A       RCTL_T(KC_A)
#define ALT_N       ALT_T(KC_N)
#define ALT_M       ALGR_T(KC_M)
#define GUI_X       LGUI_T(KC_X)
#define MUTE        KC_AUDIO_MUTE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_3x10(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    CTL_A,   KC_S,    KC_D,    KC_F,    KC_G,      KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
    SFT_Z,   GUI_X,   KC_C,    FN3_V,   FN2_BSPC,  FN1_SPC, FN4_B,   ALT_N,   ALT_M,   SFT_ESC
  ),

  [1] = LAYOUT_ortho_3x10(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,     KC_F6,   KC_MINS, KC_PLUS, KC_SLSH, KC_TILD,
    KC_TAB,  _______, _______, _______, KC_DEL,    _______, KC_COLN, KC_QUES, KC_COMM, KC_DOT
  ),

  [2] = LAYOUT_ortho_3x10(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,    KC_F12,  KC_UNDS, KC_EQL,  KC_BSLS, KC_QUOT,
    KC_TAB,  _______, _______, _______, _______,   KC_DEL,  KC_SCLN, KC_PIPE, KC_LABK, KC_RABK
  ),

  [3] = LAYOUT_ortho_3x10(
    KC_BTN1, KC_BTN3, KC_BTN2, _______, DM_REC1,   DM_PLY1, _______, _______, KC_LCBR, KC_RCBR,
    _______, _______, _______, _______, _______,   KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_DQUO,
    KC_TAB,  _______, MUTE,    _______, KC_VOLD,   KC_VOLU, _______, _______, _______, KC_PSCR
  ),

  [4] = LAYOUT_ortho_3x10(
    _______, _______, _______, _______, DM_REC1,   DM_PLY1, _______, _______, KC_LBRC, KC_RBRC,
    _______, _______, _______, _______, _______,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_GRV,
    KC_TAB,  _______, _______, _______, KC_MPRV,   KC_MNXT, _______, KC_MPLY, _______, KC_PWR
  )

};
