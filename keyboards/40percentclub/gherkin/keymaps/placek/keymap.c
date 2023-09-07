#include QMK_KEYBOARD_H

#define FN1_SPC     LT(1, KC_SPC)
#define FN2_BSPC    LT(2, KC_BSPC)
#define FN3_V       LT(3, KC_V)
#define FN4_C       LT(4, KC_C)
#define FN5_B       LT(5, KC_B)
#define CTL_Z       CTL_T(KC_Z)
#define ALT_N       ALT_T(KC_N)
#define ALT_M       ALGR_T(KC_M)
#define CTL_M       RCTL_T(KC_M)
#define SFT_ESC     RSFT_T(KC_ESC)
#define SFT_A       RSFT_T(KC_A)
#define GUI_X       LGUI_T(KC_X)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [0] = LAYOUT_ortho_3x10(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    SFT_A,   KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_ENT,
    CTL_Z,   GUI_X,   FN4_C,   FN3_V,   FN2_BSPC,FN1_SPC, FN5_B,   ALT_N,   ALT_M,   SFT_ESC
  ),

  [1] = LAYOUT_ortho_3x10(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, KC_TILD,
    _______, _______, _______, _______, KC_DEL,  _______, _______, _______, _______, _______
  ),

  [2] = LAYOUT_ortho_3x10(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_F7,  KC_F8,    KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, KC_GRV,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
  ),

  [3] = LAYOUT_ortho_3x10(
    KC_PIPE, _______, _______, _______, _______, _______, KC_UNDS, KC_EQL,  KC_LCBR, KC_RCBR,
    KC_TAB,  KC_BSLS, _______, _______, _______, _______, KC_LABK, KC_RABK, KC_PGUP, KC_DQUO,
    _______, _______, _______, _______, _______, _______, KC_COLN, KC_HOME, KC_PGDN, KC_END
  ),

  [4] = LAYOUT_ortho_3x10(
    KC_QUES, _______, _______, _______, _______, _______, KC_MINS, KC_PLUS, KC_LBRC, KC_RBRC,
    KC_TAB,  KC_SLSH, _______, _______, _______, _______, KC_COMM, KC_DOT,  KC_UP,   KC_QUOT,
    _______, _______, _______, _______, _______, _______, KC_SCLN, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [5] = LAYOUT_ortho_3x10(
    KC_PWR,  _______, _______, _______, _______, _______, _______, _______,       _______, KC_PSCR,
    _______, _______, _______, _______, _______, _______, _______, KC_AUDIO_MUTE, KC_VOLU, KC_MPLY,
    _______, _______, _______, _______, _______, _______, _______, KC_MPRV,       KC_VOLD, KC_MNXT
  )

};

void keyboard_pre_init_user(void) {
  // Call the keyboard pre init code.

  // Set our LED pins as output
  setPinOutput(D5);
  setPinOutput(B0);
}

void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinLow(D5);
  } else {
    writePinHigh(D5);
  }

  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(B0);
  } else {
    writePinHigh(B0);
  }
}
