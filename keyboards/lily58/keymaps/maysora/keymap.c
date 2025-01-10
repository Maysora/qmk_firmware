#include QMK_KEYBOARD_H

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};


enum my_keycodes {
  POMO1 = SAFE_RANGE,
  POMO2
};
enum combo_events {
  TOGGLE_POMO,
};
const uint16_t PROGMEM pomo_combo[] = {POMO1, POMO2, COMBO_END};
combo_t key_combos[] = {
  [TOGGLE_POMO] = COMBO_ACTION(pomo_combo),
};


typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD
} td_state_t;
typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;
enum {
    RS_MO_TG,
    LW_MO_TG,
};
td_state_t cur_dance(tap_dance_state_t *state);
void td_rs_finished(tap_dance_state_t *state, void *user_data);
void td_lw_finished(tap_dance_state_t *state, void *user_data);
void td_ly_reset(tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |RAISE |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LCtl | LAlt | LGUI | /Space  /       \Enter \  |BackSP|  =   |LOWER |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_QWERTY] = LAYOUT(
  KC_ESC,     KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV,
  KC_TAB,     KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
  TD(RS_MO_TG),KC_A,  KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT,    KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, KC_LBRC,  KC_RBRC,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_RSFT,
                            KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,   KC_ENT, KC_BSPC,   KC_EQL,  TD(LW_MO_TG)
),
/* LOWER
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |RAISE |   1  |   2  |   3  |   4  |   5  |-------.    ,-------|   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   \  |   `  |   =  |   {  |   }  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_LOWER] = LAYOUT(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
  _______, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5),                   S(KC_6), S(KC_7), S(KC_8), S(KC_9), S(KC_0), _______,
  _______,KC_1,  KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, KC_GRV,  KC_EQL,  KC_LCBR, KC_RCBR, _______,
                             _______, _______, _______, _______, _______,  _______, _______, _______
),
/* RAISE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |   `  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | MSWR | MSWD |  MSU | MSWU | MSWL |                    |      |PG_UP |  UP  |PG_DN |      |POMO1 |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | MSB2 | MSL  |  MSD | MSR  | MSB1 |-------.    ,-------|      | Left | Down |Right |      |POMO2 |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |LOWER |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_RAISE] = LAYOUT(
  KC_ESC,    _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, KC_GRV,
  KC_TAB,    MS_WHLR, MS_WHLD, MS_UP,   MS_WHLU, MS_WHLL,                     XXXXXXX, KC_PGUP, KC_UP,   KC_PGDN, XXXXXXX, POMO1,
  _______,MS_BTN2, MS_LEFT, MS_DOWN, MS_RGHT, MS_BTN1,                     XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, POMO2,
  KC_LSFT,   KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,     _______, _______,  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                               KC_LCTL, KC_LALT, KC_LGUI,  KC_SPC,  KC_ENT,   KC_BSPC, KC_EQL,  _______
),
/* ADJUST
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |RGB ON| HUE+ | SAT+ | VAL+ |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      | MODE | HUE- | SAT- | VAL- |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt | LGUI |LOWER | /Space  /       \Enter \  |RAISE |BackSP| RGUI |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
  [_ADJUST] = LAYOUT(
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                             _______, _______, _______, _______, _______,  _______, _______, _______
  )
};

// layer_state_t layer_state_set_user(layer_state_t state) {
//   return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
// }m

//SSD1306 OLED update loop, make sure to enable OLED_ENABLE=yes in rules.mk
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (is_keyboard_master())
    return OLED_ROTATION_270;
  else
    return OLED_ROTATION_90;
    // return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
// const char *read_layer_state(void);
// const char *read_logo(void);
// void set_keylog(uint16_t keycode, keyrecord_t *record);
// const char *read_keylog(void);
// const char *read_keylogs(void);
// const char *read_timelog(void);

void toggle_pomodoro(void);
const char* read_pomodoro_state(void);
void update_pomodoro_display(void);

void update_layer_image(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

bool oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    // oled_write_ln(read_layer_state(), false);
    // oled_write_ln("", false);
    // oled_write_ln(read_keylog(), false);
    // oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
    // oled_write_ln(read_pomodoro_state(), false);
    update_layer_image();
  } else {
    // oled_write(read_logo(), false);
    update_pomodoro_display();
  }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case POMO1:
    case POMO2:
    case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
      break;
    default:
      if(record->event.pressed && strcmp(read_pomodoro_state(), "REST") == 0) return false;
    }
    return true;
}

void process_combo_event(uint16_t combo_index, bool pressed) {
  switch(combo_index) {
    case TOGGLE_POMO:
      if (pressed) {
        toggle_pomodoro();
      }
      break;
  }
}
#endif // OLED_ENABLE


// Determine the current tap dance state
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else return TD_UNKNOWN;
}

// Initialize tap structure associated with example tap dance key
static td_tap_t ql_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void td_rs_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            if (layer_state_is(_RAISE)) {
                // If already set, then switch it off
                layer_off(_RAISE);
            } else {
                // If not already set, then switch the layer on
                layer_move(_RAISE);
            }
            break;
        case TD_SINGLE_HOLD:
            layer_move(_RAISE);
            break;
        default:
            break;
    }
}
void td_lw_finished(tap_dance_state_t *state, void *user_data) {
    ql_tap_state.state = cur_dance(state);
    switch (ql_tap_state.state) {
        case TD_SINGLE_TAP:
            if (layer_state_is(_LOWER)) {
                // If already set, then switch it off
                layer_off(_LOWER);
            } else {
                // If not already set, then switch the layer on
                layer_move(_LOWER);
            }
            break;
        case TD_SINGLE_HOLD:
            layer_move(_LOWER);
            break;
        default:
            break;
    }
}

void td_ly_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (ql_tap_state.state == TD_SINGLE_HOLD) {
        layer_clear();
    }
    ql_tap_state.state = TD_NONE;
}

// Associate our tap dance key with its functionality
tap_dance_action_t tap_dance_actions[] = {
    [RS_MO_TG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_rs_finished, td_ly_reset),
    [LW_MO_TG] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_lw_finished, td_ly_reset),
};

// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//   if (record->event.pressed) {
// #ifdef OLED_ENABLE
//     set_keylog(keycode, record);
// #endif
//     // set_timelog();
//   }
//   return true;
// }
