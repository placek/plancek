#include QMK_KEYBOARD_H
#include "placek.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case TG_SCRL:
      tap_code(KC_NUM_LOCK);
      return false;
    default:
      return true;
  }
}
