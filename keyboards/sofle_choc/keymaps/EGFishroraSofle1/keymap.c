#include <stdio.h>
#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "lib/graphics.c"
#include "timer.h"
#define ANIM_FRAME_TIME 250
#define ANIM_FRAME_WIDTH 8
#define BOUNCE_HEIGHT 4
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
char wpm_str[10];
// Jiggler tracking token (global) - accessible in all functions
deferred_token token = INVALID_DEFERRED_TOKEN;
//Layer Names
enum layers {
    _vou = 0,
    _Nerd,
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

const uint16_t PROGMEM
keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// @formatter:off

/* vou
* ,----------------------------------------------.                                                ,-----------------------------------------------.
* |  ESC |   1   |   2   |   3   |   4   |   5   |                                                |   6   |   7   |   8   |   9   |   0   |QWERTZ |
* |------+-------+-------+-------+-------+-------|                                                |-------+-------+-------+-------+-------+-------|
* |TB/FKY|   v   |   .   |   o   |   u   |   ä   |                                                |   q   |   g   |   l   |   h   |   f   |  j    |
* |------+-------+-------+-------+------+--------|                                                |-------+-------+-------+-------+-------+-------|
* |  LV3 |   c   |   a   |   e   |   i   |   y   |                                                |   b   |   t   |   r   |   n   |   s   |  LV3  |
* |------+-------+-------+-------+-------+-------+-------.                                .-------+-------+-------+-------+-------+-------+-------|
* |SHIFT |   z   |   x   |   ,   |   ö   |   ü   |FKEY   |                                |  OPY  |   p   |   d   |   w   |   m   |   k   |SHIFT  |
* `--------------+-------+-------+-------+-------+-------|                                |-------+-------+-------+-------+-------+---------------'
*                |QKLOCK | LAlt  | LGUI  |LCTRL  |Space  |                                |Enter  |BSPC   |DEL    | LV4   | SHOT  |
*                '---------------------------------------'                                '---------------------------------------'
*/
    [_vou] =LAYOUT(
    KC_ESC,           DE_1, DE_2,    DE_3,    DE_4,    DE_5,                              DE_6,    DE_7,   DE_8,       DE_9, DE_0, TG(_Game),
    LT(_FKEY,KC_TAB), DE_V, DE_DOT,  DE_O,    DE_U,    DE_ADIA,                           DE_Q,    DE_G,   DE_L,       DE_H, DE_F, DE_J,
    TT(_Nerd),        DE_C, DE_A,    DE_E,    DE_I,    DE_Y,                              DE_B,    DE_T,   DE_R,       DE_N, DE_S, LT(_Nerd,KC_MINS),
    KC_LSFT,          DE_Z, DE_X,    DE_COMM, DE_ODIA, DE_UDIA, TT(_FKEY),      DF(_opy), DE_P,    DE_D,   DE_W,       DE_M, DE_K, KC_RSFT,
                            QK_LOCK, KC_LALT, KC_LGUI, KC_LCTL, KC_SPC,         KC_ENT,   KC_BSPC, KC_DEL, MO(_Light), SHOT
    ),

/* Nerd
 * ,-----------------------------------------------.                                    ,-----------------------------------------------.
 * |   ⟳   |   ¹   |   ²   |   ³   |   ›   |   ‹   |                                   |   ç   |   œ   |   æ   |grav   | acut  | circum|
 * |-------+-------+-------+-------+-------+-------|                                    |-------+-------+-------+-------+-------+-------|
 * |  TAB  |   ^   |   _   |   {   |   }   |   @   |                                    |   !   |   <   |   >   |    =  |   &   |    %  |
 * |-------+-------+-------+-------+-------+-------|                                    |-------+------+--------+-------+-------+-------|
 * |  LV3  |   \   |   /   |   (   |   )   |   *   |                                    |   ?   |   :   |   ;   |   -   |   :   |  LV3  |
 * |-------+-------+-------+-------+-------+-------|-------.                    .-------|-------+------+--------+-------+-------+-------|
 * | CAPS  |   #   |   ~   |   [   |   ]   |   $   |FKEY   |                    |JIGGLE |   +   |   "   |   '   |   |   |   €   |SHIFT  |
 * `---------------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+---------------'
 *                 |QKLOCK | LAlt  | LGUI  |LCTRL  |Space  |                    |Enter  |BSPC   |DEL    | LV4   | SHOT  |
 *                 `---------------------------------------'                    '--------------------------------------'
 */
    [_Nerd] =LAYOUT (
    UC(UHR), UC(HI1), UC(HI2), UC(HI3), UC(QLA), UC(QRA),                       UC(CEDL), UC(OEFFL), UC(AEFFL), DE_GRV,  DE_ACUT, DE_CIRC,
    KC_TAB,  DE_CIRC, DE_UNDS, DE_LCBR, DE_RCBR, DE_AT,                         DE_EXLM,  DE_LABK,   DE_RABK,   DE_EQL,  DE_AMPR, DE_PERC,
    KC_TRNS, DE_BSLS, DE_SLSH, DE_LPRN, DE_RPRN, DE_ASTR,                       DE_QUES,  DE_COLN,   DE_SCLN,   DE_MINS, DE_COLN, KC_TRNS,
    KC_CAPS, DE_HASH, DE_TILD, DE_LBRC, DE_RBRC, DE_DLR, KC_TRNS,      JIGGLE,  DE_PLUS,  DE_DQUO,   DE_QUOT,   DE_PIPE, UC(EUR), KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS
    ),
/* Light
 * ,-----------------------------------------------.                                     ,-----------------------------------------------.
 * | SHRUG |LENNYF |FLIP   | LOREM |POMO   |LOGIN  |                                     |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|
 * |-------+-------+-------+-------+-------+-------|                                     |-------+-------+-------+-------+-------+-------|
 * |VALUP  |SATUP  |HUEUP  |SPEEDUP|RGBNXT |RGB IO |                                     |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|
 * |-------+-------+-------+-------+-------+-------|                                     |-------+-------+-------+-------+-------+-------|
 * |VALDWN |SATDWN |HUEDWN |SPEEDWN|RGBLST |XXXXXXX|                                     |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|
 * |-------+-------+-------+-------+-------+-------|-------.                     .-------|-------+-------+-------+-------+-------+-------|
 * |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|FKEY   |                     |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|
 * `---------------+-------+-------+-------+-------+-------|                     |-------+-------+-------+-------+-------+---------------'
 *                 |QKLOCK | LAlt  | LGUI  |LCTRL  |Space  |                     |Enter  |BSPC   |DEL    | LV4   | SHOT  |
 *                 '--------------------------------------'                      '---------------------------------------'
     */
    [_Light] =LAYOUT(
    SHRUG,   LENNYF,  FLIP,    P_LOREM, XXXXXXX,  LOGIN,                         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_VAI, RGB_SAI, RGB_HUI, RGB_SPI, RGB_MOD,  RGB_TOG,                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    RGB_VAD, RGB_SAD, RGB_HUD, RGB_SPD, RGB_RMOD, XXXXXXX ,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,     XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),

/* FKEY
 * ,-----------------------------------------------.                                        ,-------------------------------------------------.
 * |  F1   |  F2   |  F3   |  F4   |  F5   |  F6   |                                        |  F7  |  F8   |  F9   |  F10   |  F11   |  F12   |
 * |-------+-------+-------+-------+-------+-------|                                        |------+-------+-------+--------+--------+--------|
 * |XXXXXXX|XXXXXXX| UP    |XXXXXXX|POMO   |LOGIN  |                                        |   *  |   7   |   8   |   9    |    -   |XXXXXXX |
 * |-------+-------+-------+-------+-------+-------|                                        |------+-------+-------+--------+--------+--------|
 * |XXXXXXX| LEFT  | DOWN  | RIGHT |XXXXXXX|XXXXXXX|                                        |   /  |   4   |   5   |   6    |    +   |    -   |
 * |-------+-------+-------+-------+-------+-------|-------.                        .-------|------+-------+-------+--------+--------+--------|
 * |XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|XXXXXXX|FKEY   |                        |XXXXXXX|   0  |   1   |   2   |   3    |   =    |   .    |
 * `---------------+-------+-------+-------+-------+-------|                        |-------+-------+-------+--------+------+-----------------'
 *                 |QKLOCK | LAlt  | LGUI  |LCTRL  |Space  |                        |Enter  |BSPC   |DEL    | LV4   | SHOT  |
 *                 `--------------------------------------'                         '---------------------------------------'
 */
    [_FKEY] =LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    XXXXXXX, XXXXXXX, KC_UP,   XXXXXXX,  XXXXXXX, LOGIN,                        KC_PAST, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, XXXXXXX,
    XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX,                      KC_PSLS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_TILD,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_TRNS,    KC_TRNS, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, KC_KP_DOT,
                      XXXXXXX, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
/* Game
 * ,---------------------------------------------.                                     ,----------------------------------------------.
 * | ESC   |   1   |   2   |   3   |   4   |   5  |                                    |   6   |   7   |   8   |   9   |   0   |  vou |
 * |-------+-------+-------+-------+-------+------|                                    |-------+-------+-------+-------+-------+------|
 * | Tab   |   Q   |   W   |   E   |   R   |   T  |                                    |   Z   |   U   |   I   |   O   |   P   |  Ü   |
 * |-------+-------+-------+-------+-------+------|                                    |-------+-------+-------+-------+-------+------|
 * |CAPS   |   A   |   S   |   D   |   F   |   G  |                                    |   H   |   J   |   K   |   L   |   Ö   |  Ä   |
 * |-------+-------+-------+-------+-------+------|-------.                    .-------|-------+-------+-------+-------+-------+------|
 * |SHIFT  |   Y   |   X   |   C   |   V   |   B  |FKEY   |                    |XXXXXXX|   N   |   M   |   ,   |   .   |   -   |RShift|
 * `--------------+-------+-------+-------+-------+-------|                    |-------+-------+-------+-------+-------+--------------'
 *                |QKLOCK | LAlt  | LGUI  |LCTRL  |Space  |                    |Enter  |BSPC   |DEL    | LV4   | SHOT  |
 *                '---------------------------------------'                    '---------------------------------------'
 */
    [_Game] =LAYOUT(
    KC_ESC,  DE_1, DE_2,    DE_3,    DE_4,    DE_5, 				         DE_6,    DE_7,    DE_8,    DE_9,   DE_0,    KC_TRNS,
    KC_TAB,  DE_Q, DE_W,    DE_E,    DE_R,    DE_T, 				         DE_Y,    DE_U,    DE_I,    DE_O,   DE_P,    DE_UDIA,
    KC_CAPS, DE_A, DE_S,    DE_D,    DE_F,    DE_G, 				         DE_H,    DE_J,    DE_K,    DE_L,   DE_ODIA, DE_ADIA,
    KC_LSFT, DE_Z, DE_X,    DE_C,    DE_V,    DE_B,    KC_TRNS,     KC_TRNS, DE_N,    DE_M,    DE_COMM, DE_DOT, DE_MINS, KC_RSFT,
                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  	KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/* OPY
 * ,----------------------------------------------.                                             ,-----------------------------------------------.
 * |  ESC  |   1   |   2   |   3   |   4   |   5   |                                            |   6   |   7   |   8   |   9   |   0   |QWERTZ |
 * |-------+-------+-------+-------+-------+-------|                                            |-------+-------+-------+-------+-------+-------|
 * | (NAV) |   Q   |   Z   |   O   |   P   |   Y   |                                            |   W   |   C   |   M   |   V   |   X   | (nav) |
 * |-------+-------+-------+-------+-------+-------|                                            |-------+-------+-------+-------+-------+-------|
 * |  , ;  |(NR) H |(ALT)A |(CTRL)E|   I   |   U   |                                            |   D   |   T   |(CTRL)N|(ALT)S |(NR) R |  . :  |
 * |-------+-------+-------+-------+-------+-------+-------.                            ,-------+-------+-------+-------+-------+-------+-------|
 * |       |(FN)J  |   Ö   |   Ä   |   K   |   Ü   | PASTE |                            | VOU   |   B   |   G   |   L   |  ß $  |(FN) F |       |
 * `---------------+-------+-------+-------+-------+-------|                            |-------+-------+-------+-------+-------+---------------'
 *                 |  LOCK |  META |  ESC  |C/SHIFT|   TAB |                            | ENTER | SPACE |  BSPC |   DEL |       |
 *                 `---------------------------------------'                            `---------------------------------------'
 */
    [_opy] = LAYOUT(
    KC_ESC,          DE_1,        DE_2,        DE_3,        DE_4,   DE_5,                         DE_6,   DE_7,    DE_8,        DE_9,          DE_0,         TG(_Game),
    MO(_navi),       DE_Q,        DE_Z,        DE_O,        DE_P,   DE_Y,                         DE_W,   DE_C,    DE_M,        DE_V,          DE_X,         MO(_navi),
    TD(TD_COM_SEM), LT(_nr,DE_H), ALT_T(DE_A), CTL_T(DE_E), DE_I,   DE_U,                         DE_D,   DE_T,    CTL_T(DE_N), ALT_T(DE_S),   LT(_nr,DE_R), TD(TD_DOT_COL),
    XXXXXXX,        LT(_fn,DE_J), DE_ODIA,     DE_ADIA,     DE_K,   DE_UDIA, XXXXXXX,    DF(_vou),DE_B,   DE_G,    DE_L,        TD(TD_SZ_DOL), LT(_fn,DE_F), XXXXXXX,
                                  QK_LOCK,     KC_LGUI,     KC_ESC, KC_LSFT, KC_TAB,     KC_ENT,  KC_SPC, KC_BSPC, KC_DEL,      XXXXXXX
    ),
/*number and symbols layer
 * ,-----------------------------------------.                                                ,-----------------------------------------.
 * |  ⟳   |   ¹  |   ²  | ³   |   ›  |   ‹  |                                                |   ç  |   œ  |   æ  | grav | acut | circ |
 * |------+------+------+------+------+------|                                                |------+------+------+------+------+------|
 * |   @  |   |  |   €  |  {   |   }  |   <  |                                                |   *  |   7  |  8   |   9  |   ^  |   %  |
 * |------+------+------+------+------+------|                                                |------+------+------+------+------+------|
 * |   "  |   \  |   /  |  (   |   )  |   >  |                                                |  - _ |   4  |  5   |   6  |   =  |   &  |
 * |------+------+------+------+------+------+------.                                  ,------+------+------+------+------+------+------|
 * |   '  |  #   |   ~  |   [  |   ]  |  ! ? |      |                                  |      |   +  |   1  |  2   |   3  |   0  |      |
 * `--------------------+------+------+------+------|                                  |------+------+------+------+------+-------------'
 *               |      |      |      |      |      |                                  |      |      |      |      |      |
 *               `----------------------------------'                                  `----------------------------------'
 */
    [_nr] = LAYOUT(
    UC(UHR), UC(HI1), UC(HI2), UC(HI3), UC(QLA), UC(QRA),                               UC(CEDL),       UC(OEFFL), UC(AEFFL), DE_GRV, DE_ACUT, DE_CIRC,
    DE_AT,   DE_PIPE, UC(EUR), DE_LCBR, DE_RCBR, DE_LABK,                               DE_ASTR,        KC_P7,     KC_P8,     KC_P9,  DE_CIRC, DE_PERC,
    DE_DQUO, DE_BSLS, DE_SLSH, DE_LPRN, DE_RPRN, DE_RABK,                               TD(TD_MIN_LOW), KC_P4,     KC_P5,     KC_P6,  DE_EQL,  DE_AMPR,
    DE_QUOT, DE_HASH, DE_TILD, DE_LBRC, DE_RBRC, TD(TD_EXC_QUE), XXXXXXX,      XXXXXXX, DE_PLUS,        KC_P1,     KC_P2,     KC_P3,  KC_P0,   XXXXXXX,
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,        XXXXXXX,      XXXXXXX, XXXXXXX,        XXXXXXX,   XXXXXXX,   XXXXXXX
    ),

/*nav and punctuation layer
 * ,-------------------------------------------.                                        ,------------------------------------------.
 * |  F1    |  F2  |  F3  |  F4  |  F5  |  F6  |                                        |  F7  |  F8  |  F9  |  F10 |  F11 |  F12  |
 * |--------+------+------+------+------+------|                                        |------+------+------+------+------+-------|
 * |        |      |      |      |      |      |                                        |  LB  | home |   up | pgup |      |       |
 * |--------+------+------+------+------+------|                                        |------+------+------+------+------+-------|
 * |        |      |      |      |      |      |                                        |  MB  |   <- |lock  |  ->  |INSERT| PRINT |
 * |--------+------+------+------+------+------+------.                          ,------+------+------+------+------+------+-------|
 * |        |      |      |      |      |      |      |                          |      |  RB  | end  |  dwn | pgdn |      |       |
 * `----------------------+------+------+------+------|                          |------+------+------+------+---------------------'
 *                 |      |      |      |      |      |                          |      |      |      |      |      |
 *                 `----------------------------------'                          `----------------------------------'
 */
    [_navi] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,   KC_F6,                          KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         MS_BTN1, KC_HOME, KC_UP,   KC_PGUP, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                         MS_BTN2, KC_LEFT, KC_SCRL, KC_RGHT, KC_INS,  KC_PSCR,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, MS_BTN3, KC_END,  KC_DOWN, KC_PGDN, XXXXXXX, XXXXXXX,
                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
/*function layer
 * ,----------------------------------------------.                                      ,------------------------------------------.
 * |  F1  |  F2   |  F3   |  F4   |  F5   |  F6   |                                      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12  |
 * |------+-------+-------+-------+-------+-------|                                      |------+------+------+------+------+-------|
 * |VALUP |SATUP  |HUEUP  |SPEEDUP|RGBNXT |RGB IO |                                      | laut |  F7  |  F8  |  F9  | F10  | SHRUG |
 * |------+-------+-------+-------+-------+-------|                                      |------+------+------+------+------+-------|
 * |VALDWN|SATDWN |HUEDWN |SPEEDWN|RGBLST |XXXXXXX|                                      | mute |  F4  |  F5  |  F6  | F11  |  FLIP |
 * |------+-------+-------+-------+-------+-------+------.                        ,------+------+------+------+------+------+-------|
 * |      |       |       |       |       |       |      |                        |ZOMBIE| leise|  F1  |  F2  |  F3  | F12  |LENNYF |
 * `----------------------+-------+-------+-------+------|                        |------+------+------+------+---------------------'
 *                        |       |       |      |       |                        |      |      |      |      |      |
 *                        `------------------------------'                        `----------------------------------'
 */
    [_fn] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,    KC_F6,                           KC_F7,   KC_F8,   KC_F9,   KC_F10, KC_F11, KC_F12,
    RGB_VAI, RGB_SAI, RGB_HUI, RGB_SPI, RGB_MOD,  RGB_TOG,                         KC_VOLU, KC_F7,   KC_F8,   KC_F9,  KC_F10, SHRUG,
    RGB_VAD, RGB_SAD, RGB_HUD, RGB_SPD, RGB_RMOD, XXXXXXX,                         KC_MUTE, KC_F4,   KC_F5,   KC_F6,  KC_F11, FLIP,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,       P_LOREM, KC_VOLD, KC_F1,   KC_F2,   KC_F3,  KC_F12, LENNYF,
                      XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
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
        return OLED_ROTATION_270;
}
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
            oled_write_P(PSTR("nerd"), false);
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
    oled_set_cursor(0, 2);
    led_t led_state = host_keyboard_led_state();
    oled_write_ln_P(led_state.caps_lock   ? PSTR("CAPSLOCK ") : PSTR(" "), false);
    oled_set_cursor(0,3);
    oled_write("WPM: ", false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
    oled_set_cursor(0,4);
}

static void slaveOled(void) {
    switch (get_highest_layer(layer_state)) {
    case _vou:
        oled_write_raw_P(vou32,sizeof(vou32));
        break;
    case _Nerd:
        oled_write_raw_P(nerd32,sizeof(nerd32));
        break;
    case _Light:
        oled_write_raw_P(light32,sizeof(light32));
        break;
    case _Game:
        oled_write_raw_P(game32,sizeof(game32));
        break;
    case _FKEY:
        oled_write_raw_P(func32,sizeof(func32));
        break;
    case _opy:
    oled_write_raw_P(opy32,sizeof(opy32));
        break;
    case _nr:
    oled_write_raw_P(opyNerd32,sizeof(opyNerd32));
        break;
    case _navi:
    oled_write_raw_P(opyNavi32,sizeof(opyNavi32));
        break;
    case _fn:
    oled_write_raw_P(opyFunc32,sizeof(opyFunc32));
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



