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
    _vou = 0,
    _Nerd,
    _NUMP,
    _Light,
    _FKEY,
    _Game,
    _opy,
    _nr,
    _navi,
    _fn
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
    TD_DOT_COL,
    TD_COM_SEM,
    TD_SZ_DOL,
    TD_EXC_QUE,
    TD_MIN_LOW
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
// @formatter:off
 /* Vou
 * ,-----------------------------------------------.                                          ,----------------------------------------------.
 * | ESC   |   V   |   .   |   O   |   U   |   Ä   |                                         |   Q   |   G   |   L   |   H   |   F   |   J   |
 * |-------+-------+-------+-------+-------+-------|                                         |-------+-------+-------+-------+-------+-------|
 * | TAB   |   C   |   A   |  E    |   I   |   Y   |                                         |   B   |   T   |   R   |   N   |   S   |   ß   |
 * |-------+-------+-------+-------+-------+-------+-------+-------.         ,-------+-------+-------+-------+-------+-------+-------+-------|
 * | LSFT  |   Z   |   X   |   ,   |   Ü   |   Ö   | NUMPAD|       |         |  GAME | FKEY  |   P   |   D   |   W   |   M   |   K   |  RSFT |
 * `-----------------------+-------+-------+-------+-------+-------|         |-------+-------+-------+-------+-------+-----------------------'
 *                         |QKLOCK |  ALT  |SUPER  | CTRL  | SPACE |         | ENTER | BSPC  |  DEL  | LIGHT | OPY   |
 *                         `---------------------------------------'         `---------------------------------------'
 */
    [_vou] = LAYOUT(
    KC_ESC,  DE_V, DE_DOT, DE_O,    DE_U,    DE_ADIA,                                             DE_Q,   DE_G,      DE_L, DE_H, DE_F, DE_J,
    KC_TAB,  DE_C, DE_A,   DE_E,    DE_I,    DE_Y,                                                DE_B,   DE_T,      DE_R, DE_N, DE_S, LT(_Nerd,KC_MINS),
    KC_LSFT, DE_Z, DE_X,   DE_COMM, DE_ODIA, DE_UDIA, TT(_NUMP), XXXXXXX,   TG(_Game), TT(_FKEY), DE_P,   DE_D,      DE_W, DE_M, DE_K, KC_RSFT,
                           QK_LOCK, KC_LALT, KC_LGUI, KC_LCTL,   KC_SPC,    KC_ENT,    KC_BSPC,   KC_DEL, TT(_Light),TG(_opy)
    ),
/* Nerd
 * ,-----------------------------------------------.                                              ,-----------------------------------------------.
 * |JIGGLE |   ^   |   _   |   {   |   }   |   @   |                                              |   !   |   <   |   >   |   =   |   &   |   %   |
 * |-------+-------+-------+-------+-------+-------|                                              |-------+------+--------+-------+-------+-------|
 * |CAPS   |   \   |   /   |   (   |   )   |   *   |                                              |   ?   |   :   |   ;   |   -   |   :   |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------.              .-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |   #   |   ~   |   [   |   ]   |   $   |       |SHOT   |              |       |SHOT   |   +   |   "   |   '   |   |   |   €   |       |
 * `-----------------------+-------+-------+-------+-------+-------|              |-------+-------+-------+-------+-------+-----------------------'
 *                         |QKLOCK |  ALT  |SUPER  | CTRL  | SPACE |              | ENTER | BSPC  |  DEL  | LIGHT | OPY   |
 *                         `---------------------------------------'              '---------------------------------------'
 */
    [_Nerd] = LAYOUT (
    JIGGLE,  DE_CIRC, DE_UNDS, DE_LCBR, DE_RCBR, DE_AT,                                             DE_EXLM, DE_LABK, DE_RABK, DE_EQL,  DE_AMPR, DE_PERC,
    KC_CAPS, DE_BSLS, DE_SLSH, DE_LPRN, DE_RPRN, DE_ASTR,                                           DE_QUES, DE_COLN, DE_SCLN, DE_MINS, DE_COLN, XXXXXXX,
    XXXXXXX, DE_HASH, DE_TILD, DE_LBRC, DE_RBRC, DE_DLR,  XXXXXXX, SHOT   ,       XXXXXXX, SHOT,    DE_PLUS, DE_DQUO, DE_QUOT, DE_PIPE, UC(EUR), XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
/*
 * Numpad, Media
 * ,----------------------------------------------.                                                 ,-----------------------------------------------.
 * |       |       |       | VolUp |       |      |                                                 |   /   |   7   |  8    |   9   |   -   |       |
 * |-------+-------+-------+-------+-------+------|                                                 |-------+-------+-------+-------+-------+-------|
 * |       |       | Prev  | Play  | Next  |      |                                                 |   *   |   4   |  5    |   6   |   ,   |   +   |
 * |-------+-------+-------+-------+-------+------+-------------.                   ,---------------+-------+-------+-------+-------+-------+-------|
 * |       |       |       | VolDn | Mute  |      |      |NUMPAD|                   |       |       |   0   | 1 !   |   2   |   3   |   =   |       |
 * `-----------------------+-------+-------+------+------+------|                   |-------+-------+------+------+------+--------------------------'
 *                         |       |       |      |      |      |                   |       |       |       |       |       |
 *                        `-------------------------------------'                   `---------------------------------------'
 */
    [_NUMP] = LAYOUT(
    XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, XXXXXXX, XXXXXXX,                                             KC_PSLS, KC_P7,    KC_P8,  KC_P9, KC_PMNS, XXXXXXX,
    XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,                                             KC_PAST, KC_P4,    KC_P5,  KC_P6, KC_PDOT, KC_PPLS,
    XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD, KC_MUTE, XXXXXXX, XXXXXXX, KC_TRNS,         XXXXXXX, XXXXXXX, KC_P0,    KC_P1,    KC_P2, KC_P3, KC_PEQL, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
/* Light
 * ,-----------------------------------------------.                                                ,-----------------------------------------------.
 * |VALUP  |SATUP  |HUEUP  |SPEEDUP|RGBNXT |RGB IO |                                                |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------|                                                |-------+-------+-------+-------+-------+-------|
 * |VALDWN |SATDWN |HUEDWN |SPEEDWN|RGBLST |       |                                                |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------.                .-------+-------|-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |                |       |       |       |       |       |       |       |       |
 * `-----------------------+-------+-------+-------+-------+-------|                |-------+-------+-------+-------+-------+-----------------------'
 *                         |       |       |       |       |       |                |       |       |       |       |       |
 *                         `---------------------------------------'                '---------------------------------------'
 */
    [_Light] = LAYOUT(
    RGB_VAI, RGB_SAI, RGB_HUI, RGB_SPI, RGB_MOD,  RGB_TOG,                                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_VAD, RGB_SAD, RGB_HUD, RGB_SPD, RGB_RMOD, XXXXXXX,                                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                               XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
/* FKEY
 * ,-----------------------------------------------.                                               ,-----------------------------------------------.
 * |   F1  |   F2  |   F3  |   F4  |   F5  |   F6  |                                               |  F7   |  F8   |  F9   |  F10  |  F11  |  F12  |
 * |-------+-------+-------+-------+-------+-------|                                               |-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |                                               |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------+-------+-------.               .-------+-------+-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |       |       |               |       |  FKEY |SHRUG  |LENNYF |FLIP   |LOREM  |POMO   |LOGIN  |
 * `-----------------------+-------+-------+-------+-------+-------|               |-------+-------+-------+-------+-------+-----------------------'
 *                         |       |       |       |       |       |               |       |       |       |       |       |
 *                         `---------------------------------------'               '---------------------------------------'
 */
    [_FKEY] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                                               KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                             XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,         XXXXXXX, XXXXXXX, SHRUG,   LENNYF,  FLIP,    P_LOREM, XXXXXXX, LOGIN,
                               XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
/* Game
 * ,-----------------------------------------------.                                              ,----------------------------------------------.
 * |ESC    |   Q   |   W   |   E   |   R   |   T   |                                             |   Y   |   U   |   I   |   O   |   P   |       |
 * |-------+-------+-------+-------+-------+-------|                                             |------+-------+-------+--------+--------+------|
 * |CAPS   |   A   |   S   |   D   |   F   |   G   |                                             |   H   |   J   |   K   |   L   |   Ö   |  Ä    |
 * |-------+-------+-------+-------+-------+-------+-------+-------.             .-------+-------+-------+-------+-------+-------+-------+-------|
 * |SHIFT  |   Y   |   X   |   C   |   V   |   B   | NUMPAD| SHOT  |             |   VOU | FKEY  |   C   |   V   |   N   |   M   |   ,   |   .   |
 * `-----------------------+-------+-------+-------+-------+-------|             |-------+-------+-------+-------+-------+-----------------------'
 *                         |QKLOCK |  ALT  |SUPER  | CTRL  | SPACE |             | ENTER | BSPC  |  DEL  | LIGHT |       |
 *                         `---------------------------------------'             '---------------------------------------'
 */
    [_Game] = LAYOUT(
    KC_ESC,  DE_Q,   DE_W, DE_E,    DE_R,    DE_T, 				                                     DE_Y,   DE_U,    DE_I,    DE_O,   DE_P,    DE_UDIA,
    KC_TAB,  DE_A,   DE_S, DE_D,    DE_F,    DE_G, 				                                     DE_H,   DE_J,    DE_K,    DE_L,   DE_ODIA, DE_ADIA,
    KC_LSFT, DE_Z,   DE_X, DE_C,    DE_V,    DE_B,    TT(_NUMP), SHOT,          KC_TRNS, TT(_FKEY), DE_N,   DE_M,    DE_COMM, DE_DOT, DE_MINS, KC_RSFT,
                           QK_LOCK, KC_LALT, KC_LGUI, KC_LCTL,   KC_SPC,        KC_ENT,   KC_BSPC,   KC_DEL, TT(_Light),XXXXXXX
    ),
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* OPY
* ,-----------------------------------------------.                                                              ,-----------------------------------------------.
* | (NAV) |   Q   |   Z   |   O   |   P   |   Y   |                                                              |   W   |   C   |   M   |   V   |   X   | (nav) |
* |-------+-------+-------+-------+-------+-------|                                                              |-------+-------+-------+-------+-------+-------|
* |  , ;  |(NR) H |(ALT)A |(CTRL)E|   I   |   U   |                                                              |   D   |   T   |(CTRL)N|(ALT)S |(NR) R |  . :  |
* |-------+-------+-------+-------+-------+-------+-------+-------.                              ,-------+-------+-------+-------+-------+-------+-------+-------|
* |       |(FN)J  |   Ö   |   Ä   |   K   |   Ü   |  COPY | PASTE |                              | SHOT  |       |   B   |   G   |   L   |  ß $  |(FN) F |       |
* `-----------------------+-------+-------+-------+-------+-------|                              |-------+-------+-------+-------+-------+-----------------------'
*                         |  LOCK |  META |  ESC  |C/SHIFT|   TAB |                              |  ENTER| SPACE |  BSPC |   DEL |   VOU |
*                         `---------------------------------------'                              `---------------------------------------'
*/
    [_opy] = LAYOUT(
    MO(_navi),       DE_Q,        DE_Z,        DE_O,        DE_P,    DE_Y,                                           DE_W,    DE_C,   DE_M,        DE_V,          DE_X,         MO(_navi),
    TD(TD_COM_SEM), LT(_nr,DE_H), ALT_T(DE_A), CTL_T(DE_E), DE_I,    DE_U,                                           DE_D,    DE_T,   CTL_T(DE_N), ALT_T(DE_S),   LT(_nr,DE_R), TD(TD_DOT_COL),
    XXXXXXX,        LT(_fn,DE_J), DE_ODIA,     DE_ADIA,     DE_K,    DE_UDIA, KC_COPY, KC_PASTE,   SHOT,    XXXXXXX, DE_B,    DE_G,   DE_L,        TD(TD_SZ_DOL), LT(_fn,DE_F), XXXXXXX,
                                               QK_LOCK,     KC_LGUI, KC_ESC,  KC_LSFT, KC_TAB,     KC_ENT,  KC_SPC,  KC_BSPC, KC_DEL, KC_TRNS
    ),
/*number and symbols layer
 * ,-----------------------------------------.                                                     ,-----------------------------------------.
 * |   @  |   |  |   €  |  {   |   }  |   <  |                                                     |   *  |   7  |  8   |   9  |   ^  |   %  |
 * |------+------+------+------+------+------|                                                     |------+------+------+------+------+------|
 * |   "  |   \  |   /  |  (   |   )  |   >  |                                                     |  - _ |   4  |  5   |   6  |   =  |   &  |
 * |------+------+------+------+------+------+-------------.                         ,-------------+------+------+------+------+------+------|
 * |   '  |  #   |   ~  |   [  |   ]  |  ! ? |      |      |                         |      |JIGGLE|   +  |   1  |  2   |   3  |   0  |      |
 * `--------------------+------+------+------+------+------|                         |------+------+------+------+------+--------------------'
 *                      |      |      |      |      |      |                         |      |      |      |      |      |
 *                      `----------------------------------'                         `----------------------------------'
 */
    [_nr] = LAYOUT(
    DE_AT,   DE_PIPE, UC(EUR), DE_LCBR, DE_RCBR, DE_LABK,                                               DE_ASTR,        KC_P7,    KC_P8,    KC_P9, DE_CIRC, DE_PERC,
    DE_DQUO, DE_BSLS, DE_SLSH, DE_LPRN, DE_RPRN, DE_RABK,                                               TD(TD_MIN_LOW), KC_P4,    KC_P5,    KC_P6, DE_EQL, DE_AMPR,
    DE_QUOT, DE_HASH, DE_TILD, DE_LBRC, DE_RBRC, TD(TD_EXC_QUE), XXXXXXX, XXXXXXX,    XXXXXXX, JIGGLE,  DE_PLUS,        KC_P1,    KC_P2,    KC_P3, KC_P0, XXXXXXX,
                               XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX, XXXXXXX
    ),
/*nav and punctuation layer
  * ,-------------------------------------------.                                                  ,-------------------------------------------.
  * |        |      |      |      |      |      |                                                  |  LB  | home |   up | pgup |      |        |
  * |--------+------+------+------+------+------|                                                  |------+------+------+------+------+--------|
  * |        |      |      |      |      |      |                                                  |  MB  |   <- |lock  |  ->  |INSERT| PRINT  |
  * |--------+------+------+------+------+------+-------------.                      ,-------------+------+------+------+------+------+--------|
  * |        |      |      |      |      |      |      |      |                      |      |      |  RB  | end  |  dwn | pgdn |      |        |
  * `----------------------+------+------+------+------+------|                      |------+------+------+------+------+----------------------'
  *                        |      |      |      |      |      |                      |      |      |      |      |      |
  *                        `----------------------------------'                      `----------------------------------'
  */
     [_navi] = LAYOUT(
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                           MS_BTN1, KC_HOME, KC_UP,   KC_PGUP, XXXXXXX, XXXXXXX,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                                           MS_BTN2, KC_LEFT, KC_SCRL, KC_RGHT, KC_INS,  KC_PSCR,
       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, MS_BTN3, KC_END,  KC_DOWN, KC_PGDN, XXXXXXX, XXXXXXX,
                                  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
     ),
/*function layer
  * ,-----------------------------------------------.                                           ,-------------------------------------------.
  * |VALUP  |SATUP  |HUEUP  |SPEEDUP|RGBNXT |RGB IO |                                           | laut |  F7  |  F8  |  F9  | F10  |  SHRUG |
  * |-------+-------+-------+-------+-------+-------|                                           |------+------+------+------+------+--------|
  * |VALDWN |SATDWN |HUEDWN |SPEEDWN|RGBLST |XXXXXXX|                                           | mute |  F4  |  F5  |  F6  | F11  |   FLIP |
  * |-------+-------+-------+-------+-------+-------+-------------.               ,-------------+------+------+------+------+------+--------|
  * |       |       |       |       |       |       |      |      |               | LOGIN|ZOMBIE| leise|  F1  |  F2  |  F3  | F12  | LENNYF |
  * `-----------------------+-------+-------+-------+------+------|               |------+------+------+------+------+----------------------'
  *                         |       |       |       |      |      |               |      |      |      |      |      |
  *                         `-------------------------------------'               `----------------------------------'
  */
    [_fn] = LAYOUT(
    RGB_VAI, RGB_SAI, RGB_HUI, RGB_SPI, RGB_MOD,  RGB_TOG,                                           KC_VOLU, KC_F7,   KC_F8,  KC_F9, KC_F10, SHRUG,
    RGB_VAD, RGB_SAD, RGB_HUD, RGB_SPD, RGB_RMOD, XXXXXXX,                                           KC_MUTE, KC_F4,   KC_F5,  KC_F6, KC_F11, FLIP,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,       LOGIN  , P_LOREM, KC_VOLD, KC_F1,   KC_F2,  KC_F3, KC_F12, LENNYF,
                               XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    )
};

//@formatter:on
//Tap Dances
tap_dance_action_t tap_dance_actions[]={
    [TD_DOT_COL] = ACTION_TAP_DANCE_DOUBLE(DE_COMM,DE_SCLN),
    [TD_COM_SEM] = ACTION_TAP_DANCE_DOUBLE(DE_DOT,DE_COLN),
    [TD_SZ_DOL] = ACTION_TAP_DANCE_DOUBLE(KC_MINS,KC_DLR),
    [TD_EXC_QUE] = ACTION_TAP_DANCE_DOUBLE(DE_EXLM,DE_QUES),
    [TD_MIN_LOW] = ACTION_TAP_DANCE_DOUBLE(DE_MINS,DE_UNDS)
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
        case _vou:
        case _Game:
        case _opy:
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
        case _NUMP:
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
        case _FKEY:
        case _navi:
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

// Frames for the bouncing dot animation
static const char bounce_frames[][8] = {
    {0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00}, // Bottom position
    {0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, // Mid-low position
    {0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}, // Top position
    {0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00}, // Mid-low position
};

// Function to render bouncing dot animation
static void oled_render_bounce_anim(void) {
    static uint32_t anim_timer = 0;
    static uint8_t current_frame = 0;

    if (timer_elapsed32(anim_timer) > ANIM_FRAME_TIME) {
        anim_timer = timer_read32();
        current_frame = (current_frame + 1) % (sizeof(bounce_frames) / 8);

        oled_clear();
        for (int i = 0; i < 8; i++) {
            oled_write_raw_byte(bounce_frames[current_frame][i], i * OLED_DISPLAY_WIDTH + 64);
        }
    }
}
static void masterOled(void) {
    oled_clear();
    oled_set_cursor(0, 0);
    oled_write_P(PSTR("Fishrya"), false);
    oled_set_cursor(0, 1);
    oled_write("Layer: ",false);
    oled_set_cursor(0,3);
    switch (get_highest_layer(layer_state)) {
        case _vou:
            oled_write_P(PSTR("vou"), false);
            break;
        case _Nerd:
            oled_write_P(PSTR("nerd"), false);
            break;
        case _NUMP:
            oled_write_P(PSTR("Numpad"),false);
            break;
        case _Light:
            oled_write_P(PSTR("Light"), false);
            break;
        case _FKEY:
            oled_write_P(PSTR("Function"), false);
            break;
        case _Game:
            oled_write_P(PSTR("Game"), false);
            break;
        case _opy:
            oled_write_P(PSTR("OPY"), false);
            break;
        case _nr:
            oled_write_P(PSTR("n3rD"), false);
            break;
        case _navi:
            oled_write_P(PSTR("navy"), false);
            break;
        case _fn:
            oled_write_P(PSTR("fn"), false);
            break;
        default:
        break;
    }
    oled_set_cursor(0, 4);
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.caps_lock   ? PSTR("CAPSLOCK ") : PSTR(""), false);
    oled_set_cursor(0,5);
    oled_write("WPM: ", false);
    oled_set_cursor(0,6);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
}

static void slaveOled(void) {
    switch (get_highest_layer(layer_state)) {
    case _vou:
        oled_write_raw_P(vou64,sizeof(vou64));
        break;
    case _Nerd:
        oled_write_raw_P(nerd64,sizeof(nerd64));
        break;
    case _NUMP:
        oled_write_raw_P(numpad64,sizeof(numpad64));
        break;
    case _Light:
        oled_write_raw_P(light64,sizeof(light64));
        break;
    case _Game:
        oled_write_raw_P(game64,sizeof(game64));
        break;
    case _FKEY:
        oled_write_raw_P(func64,sizeof(func64));
        break;
    case _opy:
    oled_write_raw_P(opy64,sizeof(opy64));
        break;
    case _nr:
    oled_write_raw_P(opyNerd64,sizeof(opyNerd64));
        break;
    case _navi:
    oled_write_raw_P(opyNavi64,sizeof(opyNavi64));
        break;
    case _fn:
    oled_write_raw_P(opyFunc64,sizeof(opyFunc64));
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
        if (token != INVALID_DEFERRED_TOKEN) {
        // Jiggler is active, show bouncing animation
            oled_render_bounce_anim();
        } else {
            slaveOled();
        }
    }
    return false;
}



