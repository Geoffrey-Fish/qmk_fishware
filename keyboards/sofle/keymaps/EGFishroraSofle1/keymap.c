#include <stdio.h>
#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "graphics.c"

//special definitions
#define UHR 0x27F3    // ⟳
#define QLA 0x203A    // ›
#define QRA 0x2039    // ‹
#define HI1 0x00B9    // ¹
#define HI2 0x00B2    // ²
#define HI3 0x00B3    // ³
#define EUR 0x20AC   //EURO
//French stuff
#define CEDL 0x00E7 // ç
#define AEFFL 0x00e6 // æ
#define OEFFL 0x0153 // œ

//This is the code for the aurora
//Custom defined layer names
enum sofle_layers {
    _vou = 0,
    _Nerd,
    _Light,
    _Game,
    _FKEY,
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

const uint16_t PROGMEM
keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// @formatter:off

/* vou
* ,----------------------------------------------.                     ,-----------------------------------------------.
* |  ESC |   1   |   2   |   3   |   4   |   5   |                     |   6   |   7   |   8   |   9   |   0   |QWERTZ |
* |------+-------+-------+-------+-------+-------|                     |-------+-------+-------+-------+-------+-------|
* |TB/FKY|   v   |   .   |   o   |   u   |   ä   |                     |   q   |   g   |   l   |   h   |   f   |  j    |
* |------+-------+-------+-------+------+--------|                     |-------+-------+-------+-------+-------+-------|
* |  LV3 |   c   |   a   |   e   |   i   |   y   |                     |   b   |   t   |   r   |   n   |   s   |  LV3  |
* |------+-------+-------+-------+-------+-------+-------.     .-------+-------+-------+-------+-------+-------+-------|
* |SHIFT |   z   |   x   |   ,   |   ö   |   ü   |FKEY   |     |XXXXXXX|   p   |   d   |   w   |   m   |   k   |SHIFT  |
* `--------------+-------+-------+-------+-------+-------|     |-------+-------+-------+-------+-------+---------------'
*                |QKLOCK | LAlt  | LGUI  |LCTRL  |Space  |     |Enter  |BSPC   |DEL    | LV4   | SHOT  |
*                '---------------------------------------'     '---------------------------------------'
*/
[_vou] =LAYOUT(
        KC_ESC,           DE_1, DE_2,    DE_3,    DE_4,    DE_5,                                DE_6,    DE_7,   DE_8,       DE_9, DE_0, TG(_Game),
        LT(_FKEY,KC_TAB), DE_V, DE_DOT,  DE_O,    DE_U,    DE_ADIA,                             DE_Q,    DE_G,   DE_L,       DE_H, DE_F, DE_J,
        TT(_Nerd),        DE_C, DE_A,    DE_E,    DE_I,    DE_Y,                                DE_B,    DE_T,   DE_R,       DE_N, DE_S, LT(_Nerd,KC_MINS),
        KC_LSFT,          DE_Z, DE_X,    DE_COMM, DE_ODIA, DE_UDIA, TT(_FKEY),         XXXXXXX, DE_P,    DE_D,   DE_W,       DE_M, DE_K, KC_RSFT,
                                QK_LOCK, KC_LALT, KC_LGUI, KC_LCTL, KC_SPC,            KC_ENT,  KC_BSPC, KC_DEL, MO(_Light), SHOT
),

/* Nerd
 * ,-----------------------------------------------.                     ,------------------------------------------------.
 * |   ⟳   |   ¹   |   ²   |   ³   |   ›   |   ‹   |                     |   ç   |   œ   |   æ   |grav   | acut  | circum|
 * |-------+-------+-------+-------+-------+-------|                     |-------+-------+-------+-------+-------+-------|
 * |  TAB  |   ^   |   _   |   {   |   }   |   @   |                     |   !   |   <   |   >   |    =  |   &   |    %  |
 * |-------+-------+-------+-------+-------+-------|                     |-------+------+--------+-------+-------+-------|
 * |  LV3  |   \   |   /   |   (   |   )   |   *   |                     |   ?   |   :   |   ;   |   -   |   :   |  LV3  |
 * |-------+-------+-------+-------+-------+-------|-------.     .-------|-------+------+--------+-------+-------+-------|
 * | CAPS  |   #   |   ~   |   [   |   ]   |   $   |FKEY   |     |JIGGLE |   +   |   "   |   '   |   |   |   €   |SHIFT  |
 * `---------------+-------+-------+-------+-------+-------|     |-------+-------+-------+-------+-------+---------------'
 *                 |QKLOCK | LAlt  | LGUI  |LCTRL  |Space  |     |Enter  |BSPC   |DEL    | LV4   | SHOT  |
 *                 `---------------------------------------'     '--------------------------------------'
 */
[_Nerd] =LAYOUT (
        UC(UHR), UC(HI1), UC(HI2), UC(HI3), UC(QLA), UC(QRA),                     UC(CEDL), UC(OEFFL), UC(AEFFL), DE_GRV,  DE_ACUT, DE_CIRC,
        KC_TAB,  DE_CIRC, DE_UNDS, DE_LCBR, DE_RCBR, DE_AT,                       DE_EXLM,  DE_LABK,   DE_RABK,   DE_EQL,  DE_AMPR, DE_PERC,
        KC_TRNS, DE_BSLS, DE_SLSH, DE_LPRN, DE_RPRN, DE_ASTR,                     DE_QUES,  DE_COLN,   DE_SCLN,   DE_MINS, DE_COLN, KC_TRNS,
        KC_CAPS, DE_HASH, DE_TILD, DE_LBRC, DE_RBRC, DE_DLR, KC_TRNS,    JIGGLE,  DE_PLUS,  DE_DQUO,   DE_QUOT,   DE_PIPE, UC(EUR), KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS
),
/* Light
 * ,-----------------------------------------------.                     ,-----------------------------------------------.
 * | SHRUG |LENNYF |FLIP   | LOREM |POMO   |LOGIN  |                     |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|
 * |-------+-------+-------+-------+-------+-------|                     |-------+-------+-------+-------+-------+-------|
 * |VALUP  |SATUP  |HUEUP  |SPEEDUP|RGBNXT |RGB IO |                     |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|
 * |-------+-------+-------+-------+-------+-------|                     |-------+-------+-------+-------+-------+-------|
 * |VALDWN |SATDWN |HUEDWN |SPEEDWN|RGBLST |XXXXXXX|                     |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|
 * |-------+-------+-------+-------+-------+-------|-------.     .-------|-------+-------+-------+-------+-------+-------|
 * |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|FKEY   |     |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|
 * `---------------+-------+-------+-------+-------+-------|     --------+-------+-------+-------+-------+---------------'
 *                 |QKLOCK | LAlt  | LGUI  |LCTRL  |Space  |     |Enter  |BSPC   |DEL    | LV4   | SHOT  |
 *                 '--------------------------------------'      '---------------------------------------'
     */
[_Light] =LAYOUT(
        SHRUG,   LENNYF,  FLIP,    P_LOREM, XXXXXXX,  LOGIN,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_VAI, RGB_SAI, RGB_HUI, RGB_SPI, RGB_MOD,  RGB_TOG,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RGB_VAD, RGB_SAD, RGB_HUD, RGB_SPD, RGB_RMOD, XXXXXXX ,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                          KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),

/* FKEY
 * ,-----------------------------------------------.                     ,-------------------------------------------------.
 * |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |                     |  F7  |  F8   |  F9   |  F10   |  F11   |  F12   |
 * |-------+-------+-------+-------+-------+-------|                     |------+-------+-------+--------+--------+--------|
 * |XXXXXXX|XXXXXXX| UP    |XXXXXXX|POMO   |LOGIN  |                     |   *  |   7   |   8   |   9    |    -   |XXXXXXX |
 * |-------+-------+-------+-------+-------+-------|                     |------+-------+-------+--------+--------+--------|
 * |XXXXXXX| LEFT  | DOWN  | RIGHT |XXXXXXX|XXXXXXX|                     |   /  |   4   |   5   |   6    |    +   |    -   |
 * |-------+-------+-------+-------+-------+-------|-------.     .-------|------+-------+-------+--------+--------+--------|
 * |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|FKEY   |     |XXXXXXX|   0  |   1   |   2   |   3    |   =    |   .    |
 * `---------------+-------+-------+-------+-------+-------|     |-------+-------+-------+--------+------+-----------------'
 *                 |QKLOCK | LAlt  | LGUI  |LCTRL  |Space  |     |Enter  |BSPC   |DEL    | LV4   | SHOT  |
 *                 `--------------------------------------'      '---------------------------------------'
 */
[_FKEY] =LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX,  XXXXXXX, LOGIN,                     KC_PAST, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, XXXXXXX,
        XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,                   KC_PSLS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_TILD,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_TRNS, KC_TRNS, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, KC_KP_DOT,
                          XXXXXXX, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
/* Game
 * ,---------------------------------------------.                      ,----------------------------------------------.
 * | ESC   |   1   |   2   |   3   |   4   |   5  |                     |   6   |   7   |   8   |   9   |   0   |  vou |
 * |-------+-------+-------+-------+-------+------|                     |-------+-------+-------+-------+-------+------|
 * | Tab   |   Q   |   W   |   E   |   R   |   T  |                     |   Z   |   U   |   I   |   O   |   P   |  Ü   |
 * |-------+-------+-------+-------+-------+------|                     |-------+-------+-------+-------+-------+------|
 * |CAPS   |   A   |   S   |   D   |   F   |   G  |                     |   H   |   J   |   K   |   L   |   Ö   |  Ä   |
 * |-------+-------+-------+-------+-------+------|-------.     .-------|-------+-------+-------+-------+-------+------|
 * |SHIFT  |   Y   |   X   |   C   |   V   |   B  |FKEY   |     |XXXXXXX|   N   |   M   |   ,   |   .   |   -   |RShift|
 * `--------------+-------+-------+-------+-------+-------|     |-------+-------+-------+-------+-------+--------------'
 *                |QKLOCK | LAlt  | LGUI  |LCTRL  |Space  |     |Enter  |BSPC   |DEL    | LV4   | SHOT  |
 *                '---------------------------------------'     '---------------------------------------'
 */
[_Game] =LAYOUT(
        KC_ESC,     DE_1,   DE_2,   DE_3,   DE_4,   DE_5, 				        DE_6,     DE_7, DE_8,    DE_9,   DE_0,    KC_TRNS,
        KC_TAB,     DE_Q,   DE_W,   DE_E,   DE_R,   DE_T, 				        DE_Y,     DE_U, DE_I,    DE_O,   DE_P,    DE_UDIA,
        KC_CAPS,    DE_A,   DE_S,   DE_D,   DE_F,   DE_G, 				        DE_H,     DE_J, DE_K,    DE_L,   DE_ODIA, DE_ADIA,
        KC_LSFT,    DE_Z,   DE_X,   DE_C,   DE_V,   DE_B, KC_TRNS, 	   KC_TRNS, DE_N,     DE_M, DE_COMM, DE_DOT, DE_MINS, KC_RSFT,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
)};
//@formatter:on

//Shorts
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
        if (record->event.pressed) {
    static deferred_token token = INVALID_DEFERRED_TOKEN;
    static report_mouse_t report = {0};
    if (token) {
        // If jiggler is currently running, stop when any key is pressed.
        cancel_deferred_exec(token);
        token = INVALID_DEFERRED_TOKEN;
        report = (report_mouse_t){};  // Clear the mouse.
        host_mouse_send(&report);
        } else if (keycode == JIGGLE) {
            uint32_t jiggler_callback(uint32_t trigger_time, void* cb_arg) {
                // Deltas to move in a circle of radius 20 pixels over 32 frames.
                static const int8_t deltas[32] = {
                    0, -1, -2, -2, -3, -3, -4, -4, -4, -4, -3, -3, -2, -2, -1, 0,
                    0, 1, 2, 2, 3, 3, 4, 4, 4, 4, 3, 3, 2, 2, 1, 0};
                static uint8_t phase = 0;
                // Get x delta from table and y delta by rotating a quarter cycle.
                report.x = deltas[phase];
                report.y = deltas[(phase + 8) & 31];
                phase = (phase + 1) & 31;
                host_mouse_send(&report);
                return 16;  // Call the callback every 16 ms.
            }
        token = defer_exec(1, jiggler_callback, NULL);  // Schedule callback.
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
        case _vou:
        case _Game:
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
        case _Nerd:
        case _Light:
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
        case _FKEY:
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
static void masterOled(void) {
    oled_clear();
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("Fishy"), false);
    oled_set_cursor(0, 1);
    oled_write("Layer: ",false);
    switch (get_highest_layer(layer_state)) {
        case _vou:
            oled_write_P(PSTR("vou"), false);
            break;
        case _Nerd:
            oled_write_P(PSTR("\%?<*$"), false);
            break;
        case _Light:
            oled_write_P(PSTR("Light"), false);
            break;
        case _Game:
            oled_write_P(PSTR("Game"), false);
            break;
        case _FKEY:
            oled_write_P(PSTR("Function"), false);
            break;
        default:
        break;
    }
    oled_set_cursor(0, 2);
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.caps_lock   ? PSTR("CAPSLOCK ") : PSTR("       "), false);
    oled_set_cursor(0,3);
    oled_write("WPM: ", false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
    oled_set_cursor(0,4);
}

static void slaveOled(void) {
    switch (get_highest_layer(layer_state)) {
        case _vou:
            oled_write_raw_P(vou,sizeof(vou));
            break;
        case _Nerd:
            oled_write_raw_P(imperium_logo,sizeof(imperium_logo));
            break;
        case _Light:
            oled_write_raw_P(starTrek_logo,sizeof(starTrek_logo));
            break;
        case _Game:
            oled_write_raw_P(game_logo,sizeof(game_logo));
            break;
        case _FKEY:
            oled_write_raw_P(trooper_logo,sizeof(trooper_logo));
        default:
            break;
    }
}
//Orientation of the oled screen
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        return OLED_ROTATION_270;
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



