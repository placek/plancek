#ifndef PLACEK_H
#define PLACEK_H

#define FN1_SPC     LT(1, KC_SPC)
#define FN2_BSPC    LT(2, KC_BSPC)
#define FN3_V       LT(3, KC_V)
#define FN4_B       LT(4, KC_B)
#define SFT_Z       RSFT_T(KC_Z)
#define SFT_ESC     RSFT_T(KC_ESC)
#define CTL_A       RCTL_T(KC_A)
#define C_A         LCTL(KC_A)
#define ALT_N       ALT_T(KC_N)
#define ALT_M       ALGR_T(KC_M)
#define GUI_X       LGUI_T(KC_X)
#define MUTE        KC_AUDIO_MUTE

enum layer_names {
  _QWERTY,
  _SPC,
  _BSPC,
  _V,
  _B
};

enum custom_keycodes {
  RBR = SAFE_RANGE,
  CBR,
  PRN
};

#endif // PLACEK_H
