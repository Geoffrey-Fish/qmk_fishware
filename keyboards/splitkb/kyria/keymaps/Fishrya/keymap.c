#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "lib/graphics.c"
#include "timer.h"
#define ANIM_FRAME_TIME 250
#define ANIM_FRAME_WIDTH 8
#define BOUNCE_HEIGHT 4
#define EUR 0x20AC   //EURO
char wpm_str[10];
// Jiggler tracking token (global) - accessible in all functions
deferred_token token = INVALID_DEFERRED_TOKEN;
//Layer Names
enum layers {
    _trns = 0,
    _qwer,
    _nr,
    _fn,
    _nav
};

//custom defined special key codes
enum custom_keycodes {
    P_LOREM = SAFE_RANGE,
    LENNYF,
    FLIP,
    SHRUG,
    SHOT,
    LOGIN,
    JIGGLE
};

//Tap Dances
enum TapDances{
    TD_C_S,
    TD_D_C,
    TD_S_D,
    TD_M_L
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// @formatter:off


//-----------------------------------------------------------------------WRITING--LAYOUTS---------------------------------------------------------------------------------------------------
/*,-----------------------------------------------.                       TRNS LAYOUT                            ,-----------------------------------------------.
* |   Q   |   J   |   Ä   |   O   |   U   |   K   |                                                              |   Z   |   C   |   L   |   V   |   X   |   ß   |
* |-------+-------+-------+-------+-------+-------|                                                              |-------+-------+-------+-------+-------+-------|
* |   ?   |(NR) H |(ALT)A |(CTRL)E|   I   |   G   |                                                              |   D   |   T   |(CTRL)N|(ALT)R |(NR) S |   !   |
* |-------+-------+-------+-------+-------+-------+-------+-------.                              ,-------+-------+-------+-------+-------+-------+-------+-------|
* |(fn)TAB|  .:   |   Y   |   ,;  |   Ö   |   Ü   | (nav)#| ENTER |                              |  SHOT |   -_  |   B   |   P   |   M   |   W   |(FN) F | SHIFT |
* `-----------------------+-------+-------+-------+-------+-------|                              |-------+-------+-------+-------+-------+-----------------------'
*                         |  qwer |  META |  ESC  |C/SHIFT| SPACE |                              | ENTER | SPACE |  BSPC |   DEL |   OPY |
*                         `---------------------------------------'                              `---------------------------------------'     */
    [_trns] = LAYOUT(
    DE_Q,           DE_J,         DE_ADIA,     DE_O,        DE_U,    DE_K,                                                    DE_Z,    DE_C,   DE_L,        DE_V,        DE_X,         KC_MINS,
    DE_QUES,        LT(_nr,DE_H), ALT_T(DE_A), CTL_T(DE_E), DE_I,    DE_G,                            DE_D,   DE_T,    CTL_T(DE_N), ALT_T(DE_R), LT(_nr,DE_S), DE_EXLM,
    LT(_fn,KC_TAB), TD(TD_D_C),   DE_Y,        TD(TD_C_S),  DE_ODIA, DE_UDIA, LT(_nav,DE_HASH), KC_ENT, /**/ SHOT,   TD(TD_M_L), DE_B,    DE_P,   DE_M,        DE_W,        LT(_fn,DE_F), KC_RSFT,
                                               TG(_qwer) ,  KC_LGUI, KC_ESC,  KC_LSFT,          KC_SPC, /**/ KC_ENT, KC_SPC,     KC_BSPC, KC_DEL, TG(_qwer)),
 //-----------------------------------------------------------------------WRITING--LAYOUTS---------------------------------------------------------------------------------------------------
 /*,-----------------------------------------------.                  QWERTY LAYER               ,----------------------------------------------.
 * |ESC    |   Q   |   W   |   E   |   R   |   T   |                                             |   Y   |   U   |   I   |   O   |   P   |   Ü   |
 * |-------+-------+-------+-------+-------+-------|                                             |------+-------+-------+--------+--------+------|
 * |CAPS   |   A   |   S   |   D   |   F   |   G   |                                             |   H   |   J   |   K   |   L   |   Ö   |  Ä    |
 * |-------+-------+-------+-------+-------+-------+-------+-------.             .-------+-------+-------+-------+-------+-------+-------+-------|
 * |SHIFT  |   Y   |   X   |   C   |   V   |   B   | Nr    | SHOT  |             |   VOU |       |   C   |   V   |   N   |   M   |   ,   |   .   |
 * `-----------------------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-----------------------'
 *                         |gay    |  ALT  |SUPER  | CTRL  | SPACE |             | ENTER | BSPC  |  DEL  |   fn  |       |
 *                         `---------------------------------------'             '---------------------------------------'*/
    [_qwer] = LAYOUT(
    KC_ESC,  DE_Q,   DE_W, DE_E,    DE_R,    DE_T, 				                                  DE_Y,   DE_U,    DE_I,    DE_O,   DE_P,    DE_UDIA,
    KC_TAB,  DE_A,   DE_S, DE_D,    DE_F,    DE_G, 				                                  DE_H,   DE_J,    DE_K,    DE_L,   DE_ODIA, DE_ADIA,
    KC_LSFT, DE_Z,   DE_X, DE_C,    DE_V,    DE_B,    MO(_nr), SHOT,            KC_TRNS, XXXXXXX, DE_N,   DE_M,    DE_COMM, DE_DOT, DE_MINS, KC_RSFT,
                           KC_TRNS, KC_LALT, KC_LGUI, KC_LCTL, KC_SPC,          KC_ENT,  KC_BSPC, KC_DEL, MO(_fn), XXXXXXX),
//----------------------------------------------------------------UTILITY--LAYOUTS-----------------------------------------------------------------------------------------
 /*,-----------------------------------------.              NUM N SYM LAYER                        ,-----------------------------------------.
 * |   @  |   |  |   €  |  {   |   }  |   <  |                                                     |   *  |   7  |  8   |   9  |   %  |   ^  |
 * |------+------+------+------+------+------|                                                     |------+------+------+------+------+------|
 * |   "  |   \  |   /  |  (   |   )  |   >  |                                                     |  -   |   4  |  5   |   6  |   =  |   &  |
 * |------+------+------+------+------+------+-------------.                         ,-------------+------+------+------+------+------+------|
 * |   '  |  #   |   ~  |   [  |   ]  |  $   |   !  |  ?   |                         |      |JIGGLE|   _  |   1  |  2   |   3  |   0  |   +  |
 * `--------------------+------+------+------+------+------|                         |------+------+------+------+------+--------------------'
 *                      |      |      |      |      |      |                         |      |      |      |      |      |
 *                      `----------------------------------'                         `----------------------------------'*/
    [_nr] = LAYOUT(
    DE_AT,   DE_PIPE, UC(EUR), DE_LCBR, DE_RCBR, DE_LABK,                                            DE_ASTR, KC_P7,   KC_P8, KC_P9, DE_PERC, DE_CIRC,
    DE_DQUO, DE_BSLS, DE_SLSH, DE_LPRN, DE_RPRN, DE_RABK,                                            DE_MINS, KC_P4,   KC_P5, KC_P6, DE_EQL,  DE_AMPR,
    DE_QUOT, DE_HASH, DE_TILD, DE_LBRC, DE_RBRC, KC_DLR, DE_EXLM, DE_QUES,         XXXXXXX, JIGGLE,  DE_UNDS, KC_P1,   KC_P2, KC_P3, KC_P0,   DE_PLUS,
                               XXXXXXX, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

  /*,-----------------------------------------------.                FUNCTION LAYER             ,-------------------------------------------.
  * |VALUP  |SATUP  |HUEUP  |SPEEDUP|RGBNXT |RGB IO |                                           | laut |  F7  |  F8  |  F9  | F10  |  SHRUG |
  * |-------+-------+-------+-------+-------+-------|                                           |------+------+------+------+------+--------|
  * |VALDWN |SATDWN |HUEDWN |SPEEDWN|RGBLST |       |                                           | mute |  F4  |  F5  |  F6  | F11  |   FLIP |
  * |-------+-------+-------+-------+-------+-------+-------------.               ,-------------+------+------+------+------+------+--------|
  * |       |       |       |       |       |       |      |      |               | LOGIN|ZOMBIE| leise|  F1  |  F2  |  F3  | F12  | LENNYF |
  * `-----------------------+-------+-------+-------+------+------|               |------+------+------+------+------+----------------------'
  *                         |       |       |       |      |      |               |      |      |      |      |      |
  *                         `-------------------------------------'               `----------------------------------'*/
    [_fn] = LAYOUT(
    RGB_VAI, RGB_SAI, RGB_HUI, RGB_SPI, RGB_MOD,  RGB_TOG,                                           KC_VOLU, KC_F7,   KC_F8,  KC_F9, KC_F10, SHRUG,
    RGB_VAD, RGB_SAD, RGB_HUD, RGB_SPD, RGB_RMOD, XXXXXXX,                                           KC_MUTE, KC_F4,   KC_F5,  KC_F6, KC_F11, FLIP,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,       LOGIN  , P_LOREM, KC_VOLD, KC_F1,   KC_F2,  KC_F3, KC_F12, LENNYF,
                               XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),
  /*,-------------------------------------------.                      NAVI LAYER                  ,-------------------------------------------.
  * |        |      |      |      |      |      |                                                  |  LB  | home |   up | pgup |      |        |
  * |--------+------+------+------+------+------|                                                  |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                                                  |  MB  |   <- |lock  |  ->  |INSERT| PRINT  |
  * |--------+------+------+------+------+------+-------------.                      ,-------------+------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |      |                      |      |      |  RB  | end  |  dwn | pgdn |      |        |
  * `----------------------+------+------+------+------+------|                      |------+------+------+------+------+----------------------'
  *                        |      |      |      |      |      |                      |      |      |      |      |      |
  *                        `----------------------------------'                      `----------------------------------'*/
    [_nav] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                           MS_BTN1, KC_HOME, KC_UP,   KC_PGUP, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                           MS_BTN2, KC_LEFT, KC_SCRL, KC_RGHT, KC_INS,  KC_PSCR,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, MS_BTN3, KC_END,  KC_DOWN, KC_PGDN, XXXXXXX, XXXXXXX,
                                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX)};

//@formatter:on
//Tap Dances
tap_dance_action_t tap_dance_actions[]={
    [TD_C_S] = ACTION_TAP_DANCE_DOUBLE(DE_COMM,DE_SCLN),
    [TD_D_C] = ACTION_TAP_DANCE_DOUBLE(DE_DOT,DE_COLN),
    [TD_S_D] = ACTION_TAP_DANCE_DOUBLE(KC_MINS,KC_DLR),
    [TD_M_L] = ACTION_TAP_DANCE_DOUBLE(DE_MINS,DE_UNDS)
};
//Shorts Switchcases
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    //Mouse Jiggler
    static report_mouse_t report = {0};  // Mouse report initialized
      if (record->event.pressed) {
        if (token != INVALID_DEFERRED_TOKEN) {
            // If jiggler is currently running, stop it when any key is pressed
            cancel_deferred_exec(token);
            token = INVALID_DEFERRED_TOKEN;
            report = (report_mouse_t){};  // Clear the mouse
            host_mouse_send(&report);
        } else if (keycode == JIGGLE) {
            // Jiggler callback function
            uint32_t jiggler_callback(uint32_t trigger_time, void* cb_arg) {
                static const int8_t deltas[32] = {
                    0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0,
                    0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 1, 0};
                static uint8_t phase = 0;
                // Get x delta from table and y delta by rotating a quarter cycle
                report.x = deltas[phase];
                report.y = deltas[(phase + 8) & 31];
                phase = (phase + 1) & 31;
                host_mouse_send(&report);
                return 16;  // Callback every 16 ms
            }
            // Start jiggler
            token = defer_exec(1, jiggler_callback, NULL);
        }
    }
    switch (keycode) {
        case P_LOREM:
            if (record->event.pressed) {
                SEND_STRING(
                        "Zombie ipsum reversus ab viral inferno, nam rick grimes malum cerebro.\n De carne lumbering animata corpora quaeritis.\n");
                return false;
            }
        case LENNYF:  // ( ͡° ͜ʖ ͡°)
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_RALT)
                SS_TAP(X_L)
                SS_TAP(X_F)
                SS_UP(X_RALT));
                return false;
            }
        case FLIP:  // (ﾉಥ益ಥ）ﾉ彡┻━┻)
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_RALT)
                SS_TAP(X_T)
                SS_TAP(X_F)
                SS_UP(X_RALT));
                return false;
            }
        case SHRUG:  // ¯\_(ツ)_/¯
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_RALT)
                SS_TAP(X_S)
                SS_TAP(X_F)
                SS_UP(X_RALT));
                return false;
            }
        case SHOT:  // screenshot
            if (record->event.pressed) {
                SEND_STRING(SS_DOWN(X_LSFT)
                SS_DOWN(X_LGUI)
                SS_TAP(X_S)
                SS_UP(X_LGUI)
                SS_UP(X_LSFT));
                return false;
            }
        case LOGIN:
            if (record->event.pressed) {
                SEND_STRING("Bananadrama1");
                return false;
            }
    }
    return true;
}

//Rotary Encoder
bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;
void matrix_scan_user(void) {
    if (is_alt_tab_active) {
        if (timer_elapsed(alt_tab_timer) > 1000) {
            unregister_code(KC_LALT);
            is_alt_tab_active = false;
        }
    }
}
bool encoder_update_user(uint8_t index, bool clockwise) {
    switch (get_highest_layer(layer_state)) {
        case _trns:
        case _qwer:
            if (index == 1) {
                if (clockwise) {
                    tap_code(KC_RIGHT);
                } else {
                    tap_code(KC_LEFT);
                }
            } else if (index == 0) { // Encoder on(slave) side
                if (clockwise) {
                    tap_code(KC_DOWN);
                } else {
                    tap_code(KC_UP);
                }
            }
            break;
        case _nr:
            if (index == 1) {
                if (clockwise) {
                    tap_code(KC_MPRV);
                } else {
                    tap_code(KC_MNXT);
                }
            } else if (index == 0) { // Encoder on(slave) side
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
            }
            break;
        case _nav:
        case _fn:
            // Switch between windows on Windows with alt tab.
            if (index == 0) {
                if (clockwise) {
                    if (!is_alt_tab_active) {
                        is_alt_tab_active = true;
                        register_code(KC_LALT);
                    }
                    alt_tab_timer = timer_read();
                    tap_code16(KC_TAB);
                } else {
                    tap_code16(S(KC_TAB));
                }
            }
            break;
        }
        return false;
}
//OLED
//Orientation of the oled screen
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

static void masterOled(void) {
    oled_clear();
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("Fishrya      V:1.6.2"),false);
    oled_set_cursor(0, 1);
    oled_write("Code and Design by: ",false);
    oled_set_cursor(0, 2);
    oled_write("Scy Marshall Ltd.",false);
    oled_set_cursor(0,3);
    oled_write("Currently active: ",false);
    switch (get_highest_layer(layer_state)) {
        case _trns:
            oled_write_P(PSTR("TRNS"), false);
            break;
        case _qwer:
            oled_write_P(PSTR("Game"), false);
            break;
        case _nr:
            oled_write_P(PSTR("Tech"), false);
            break;
        case _fn:
            oled_write_P(PSTR("Func"), false);
            break;
        case _nav:
            oled_write_P(PSTR("Nav"), false);
            break;
        default:
        break;
    }
    oled_set_cursor(0, 4);
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.caps_lock   ? PSTR("CAPSLOCK ") : PSTR(""), false);
    oled_set_cursor(0,5);
    oled_write("Words per Minute: ", false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
}

static void slaveOled(void) {
    switch (get_highest_layer(layer_state)) {
    case _trns:
    oled_write_raw_P(Gay64,sizeof(Gay64));
        break;
    case _qwer:
        oled_write_raw_P(Game64,sizeof(Game64));
        break;
    case _nr:
    oled_write_raw_P(Nerd64,sizeof(Nerd64));
        break;
    case _fn:
    oled_write_raw_P(Func64,sizeof(Func64));
        break;
    case _nav:
    oled_write_raw_P(Nav64,sizeof(Nav64));
        break;
    default:
        break;
    }
}

// Used to draw on to the oled screen
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        masterOled();
    } else {
        slaveOled();
    }
    return false;
}



 /*,-----------------------------------------------.               VOU LAYOUT                ,----------------------------------------------.
 * | ESC   |   V   |   .   |   O   |   U   |   Ä   |                                         |   Q   |   G   |   L   |   H   |   F   |   J   |
 * |-------+-------+-------+-------+-------+-------|                                         |-------+-------+-------+-------+-------+-------|
 * | TAB   |   C   |   A   |  E    |   I   |   Y   |                                         |   B   |   T   |   R   |   N   |   S   |   ß   |
 * |-------+-------+-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------+-------+-------|
 * | LSFT  |   Z   |   X   |   ,   |   Ü   |   Ö   |   nr  |       |         |  qwer |   fn  |   P   |   D   |   W   |   M   |   K   |  RSFT |
 * `-----------------------+-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------+-----------------------'
 *                         |OPY    |  ALT  |SUPER  | CTRL  | SPACE |         | ENTER | BSPC  |  DEL  |   fn  | GAY   |
 *                         `---------------------------------------'         `---------------------------------------'*/
  /*  [_vou] = LAYOUT(
    KC_ESC,  DE_V, DE_DOT, DE_O,    DE_U,    DE_ADIA,                                               DE_Q,   DE_G,   DE_L, DE_H, DE_F, DE_J,
    KC_TAB,  DE_C, DE_A,   DE_E,    DE_I,    DE_Y,                                                  DE_B,   DE_T,   DE_R, DE_N, DE_S, LT(_nr,KC_MINS),
    KC_LSFT, DE_Z, DE_X,   DE_COMM, DE_ODIA, DE_UDIA, MO(_nr), XXXXXXX,     TG(_qwer), MO(_fn), DE_P,   DE_D,   DE_W, DE_M, DE_K, KC_RSFT,
                           KC_TRNS, KC_LALT, KC_LGUI, KC_LCTL,   KC_SPC,    KC_ENT,    KC_BSPC, KC_DEL, MO(_fn),TG(_gay)), */
/*,-----------------------------------------------.                          OPY LAYOUT                          ,-----------------------------------------------.
* | (NAV) |   Q   |   Z   |   O   |   P   |   Y   |                                                              |   W   |   C   |   M   |   V   |   X   | (gay) |
* |-------+-------+-------+-------+-------+-------|                                                              |-------+-------+-------+-------+-------+-------|
* |  , ;  |(NR) H |(ALT)A |(CTRL)E|   I   |   U   |                                                              |   D   |   T   |(CTRL)N|(ALT)S |(NR) R |  . :  |
* |-------+-------+-------+-------+-------+-------+-------+-------.                              ,-------+-------+-------+-------+-------+-------+-------+-------|
* |   !   |(FN)J  |   Ö   |   Ä   |   K   |   Ü   |  COPY | PASTE |                              | SHOT  |  TAB  |   B   |   G   |   L   |  ß $  |(FN) F |   ?   |
* `-----------------------+-------+-------+-------+-------+-------|                              |-------+-------+-------+-------+-------+-----------------------'
*                         |  vou  |  META |  ESC  |C/SHIFT|   TAB |                              |  ENTER| SPACE |  BSPC |   DEL |   GAY |
*                         `---------------------------------------'                              `---------------------------------------'*/
 /*   [_opy] = LAYOUT(
    MO(_nav),   DE_Q,         DE_Z,        DE_O,        DE_P,    DE_Y,                                            DE_W,    DE_C,   DE_M,        DE_V,        DE_X,         XXXXXXX,
    TD(TD_C_S), LT(_nr,DE_H), ALT_T(DE_A), CTL_T(DE_E), DE_I,    DE_U,                                            DE_D,    DE_T,   CTL_T(DE_N), ALT_T(DE_S), LT(_nr,DE_R), TD(TD_D_C),
    DE_EXLM,    LT(_fn,DE_J), DE_ODIA,     DE_ADIA,     DE_K,    DE_UDIA, KC_COPY, KC_PASTE,  SHOT,   KC_TAB, DE_B,    DE_G,   DE_L,        TD(TD_S_D),  LT(_fn,DE_F), DE_QUOT,
                                           QK_LOCK,     KC_LGUI, KC_ESC,  KC_LSFT, KC_TAB,    KC_ENT, KC_SPC, KC_BSPC, KC_DEL, KC_TRNS),*/

//-----------------------------------------------------------------------WRITING--LAYOUTS---------------------------------------------------------------------------------------------------
/*,-----------------------------------------------.                       GAY LAYOUT                             ,-----------------------------------------------.
* |     Q |   J   |   Z   |   Y   |   .:  |   Ü   |                                                              |   X   |   M   |   D   |   F   |   K   |   ß   |
* |-------+-------+-------+-------+-------+-------|                                                              |-------+-------+-------+-------+-------+-------|
* |   !   |(NR) G |(ALT)A |(CTRL)E|   I   |   O   |                                                              |   R   |   N   |(CTRL)S|(ALT)T |(NR) H |   ?   |
* |-------+-------+-------+-------+-------+-------+-------+-------.                              ,-------+-------+-------+-------+-------+-------+-------+-------|
* |  TAB  |(FN)C  |   Ä   |   Ö   |   U   |   ,;  | (nav)#| ENTER |                              |  SHOT |   -_  |   W   |   L   |   V   |   B   |(FN) P | SHIFT |
* `-----------------------+-------+-------+-------+-------+-------|                              |-------+-------+-------+-------+-------+-----------------------'
*                         |  qwer |  META |  ESC  |C/SHIFT| SPACE |                              | ENTER | SPACE |  BSPC |   DEL |   OPY |
*                         `---------------------------------------'                              `---------------------------------------'*/
 /*   [_gay] = LAYOUT(
    DE_Q,    DE_J,         DE_Z,        DE_Y,        TD(TD_D_C), DE_UDIA,                                                       DE_X,    DE_M,   DE_D,        DE_F,        DE_K,         KC_MINS,
    DE_EXLM, LT(_nr,DE_G), ALT_T(DE_A), CTL_T(DE_E), DE_I,       DE_O,                                                          DE_R,    DE_N,   CTL_T(DE_S), ALT_T(DE_T), LT(_nr,DE_H), DE_QUES,
    KC_TAB,  LT(_fn,DE_C), DE_ADIA,     DE_ODIA,     DE_U,       TD(TD_C_S), LT(_nav,DE_HASH), KC_ENT,  SHOT,   TD(TD_M_L), DE_W,    DE_L,   DE_V,        DE_B,        LT(_fn,DE_P), KC_RSFT,
                                        TG(_qwer) ,  KC_LGUI,    KC_ESC,     KC_LSFT, KC_SPC,           KC_ENT, KC_SPC,     KC_BSPC, KC_DEL, TG(_qwer)),  */

  /*
     case _opy:
    oled_write_raw_P(opy64,sizeof(opy64));
        break;
    case _vou:
        oled_write_raw_P(vou64,sizeof(vou64));
        break;

    case _opy:
        oled_write_P(PSTR("OPY"), false);
        break;
    case _vou:
        oled_write_P(PSTR("vou"), false);
        break;


        */
