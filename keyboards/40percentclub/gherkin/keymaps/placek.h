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
  PRN,
  DQUO,
  QUOT,
  GRV,
  ABK
};

const uint16_t PROGMEM btn_combo[]  = {FN3_V,   FN2_BSPC, COMBO_END};
const uint16_t PROGMEM abk_combo[]  = {KC_LABK, KC_RABK,  COMBO_END};
const uint16_t PROGMEM c_a_combo[]  = {CTL_A,   KC_S,     COMBO_END};
const uint16_t PROGMEM caps_combo[] = {SFT_Z,   SFT_ESC,  COMBO_END};
const uint16_t PROGMEM cbr_combo[]  = {KC_LCBR, KC_RCBR,  COMBO_END};
const uint16_t PROGMEM dquo_combo[] = {KC_END,  KC_DQUO,  COMBO_END};
const uint16_t PROGMEM grv_combo[]  = {KC_RGHT, KC_GRV,   COMBO_END};
const uint16_t PROGMEM prn_combo[]  = {KC_LPRN, KC_RPRN,  COMBO_END};
const uint16_t PROGMEM quot_combo[] = {KC_BSLS, KC_QUOT,  COMBO_END};
const uint16_t PROGMEM rbr_combo[]  = {KC_LBRC, KC_RBRC,  COMBO_END};
const uint16_t PROGMEM tab_combo[]  = {KC_Q,    KC_W,     COMBO_END};
const uint16_t PROGMEM c_x_combo[]  = {SFT_Z,   GUI_X,    COMBO_END};
const uint16_t PROGMEM c_c_combo[]  = {GUI_X,   KC_C,     COMBO_END};
const uint16_t PROGMEM c_v_combo[]  = {KC_C,    FN3_V,    COMBO_END};

combo_t key_combos[] = {
  COMBO(btn_combo, KC_BTN1),
  COMBO(abk_combo, ABK),
  COMBO(c_a_combo, C_A),
  COMBO(caps_combo, CW_TOGG),
  COMBO(cbr_combo, CBR),
  COMBO(dquo_combo, DQUO),
  COMBO(grv_combo, GRV),
  COMBO(prn_combo, PRN),
  COMBO(quot_combo, QUOT),
  COMBO(rbr_combo, RBR),
  COMBO(tab_combo, KC_TAB),
  COMBO(c_x_combo, KC_CUT),
  COMBO(c_c_combo, KC_COPY),
  COMBO(c_v_combo, KC_PASTE)
};

#endif // PLACEK_H
