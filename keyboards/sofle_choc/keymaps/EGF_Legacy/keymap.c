#include <stdio.h>

#include QMK_KEYBOARD_H
#include "keymap_german.h"

#define BOB 0x00B7    // ·
#define ENDASH 0x2013 // – en dash
#define SCRL 0x2113   // ℓ
#define LOW9 0x201E   // „
#define HIG6 0x201C   // “
#define HIG9 0x201D   // ”
#define EMDASH 0x2014 // — em dash
#define SSS 0x00DF    // ß
#define UHR 0x27F3    // ⟳
#define CUHR 0x27F2   // ⟲
#define LSQ 0x201A    // ‚
#define HSQ 0x2018    // ‘
#define RSQ 0x2019    // ’
#define QLA 0x203A    // ›
#define QRA 0x2039    // ‹
#define CENT 0x00A2   // ¢
#define YEN 0x00A5    // ¥
#define REQ 0x00BB    // »
#define LEQ 0x00AB    // «
#define HI1 0x00B9    // ¹
#define HI2 0x00B2    // ²
#define HI3 0x00B3    // ³


     /*    ///////template sofle layout map
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  28  |  21  |  20  |  11  |  10  |   0  |                    |  35  |  45  |  46  |  55  |  56  |  63  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  27  |  22  |  19  |  12  |   9  |   1  |                    |  36  |  44  |  47  |  54  |  57  |  62  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  26  |  23  |  18  |  13  |   8  |   2  |-------.    ,-------|  37  |  43  |  48  |  53  |  58  |  61  |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * |  25  |  24  |  17  |  14  |   7  |   3  |-------|    |-------|  38  |  42  |  49  |  52  |  59  |  60  |
     * `-----------------------------------------/      /     \      \------------------------------------------'
     *            |   16  |   15 |  6  |    5   /   4  /       \  39  \  |  40  |  41  |  50  |  51   |
     *            |       |      |     |       /      /         \      \ |      |      |      |       |
     *           ------------------------------------'           '------''----------------------------'
     */
/*
// Design custom lights for the layers
#define INDICATOR_BRIGHTNESS 30
#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

// Light combinations
#define SET_INDICATORS(hsv) \
	{26, 2, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {50, 1, hsv},\
    {60,2,hsv},\
    {63,1,hsv}

#define QWERTZ_INDICATOR(hsv)\
    {63,1,HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}


#define SET_LAYER_ID(hsv) \
	{0, 3, hsv},\
    {35, 3, hsv}

#define SET_NUMPAD(hsv) \
	{35+15, 5, hsv},\
	{35+22, 3, hsv},\
	{35+27, 3, hsv}

#define SET_ARROWKEYS(hsv)\
    {18, 2, hsv}, \
    {23, 1, hsv}, \
    {13, 1, hsv}

#define SET_LIGHT_MODES(hsv)\
    {35, 3, hsv}, \
    {44, 4, hsv}

#define SET_LIGHT_VALUES(hsv)\
    {48, 2, hsv}, \
    {52, 2, hsv}, \
    {58, 2, hsv}

#define SET_LIGHT_BUTTONS(hsv)\
    {42, 2, hsv}

#define SET_LIGHT_SPECIAL(hsv)\
    {63, 1, hsv}

#define SET_TOP_ROW(hsv) \
	{28, 1, hsv}, \
    {20, 2, hsv}, \
	{10, 2, hsv}, \
    {0, 1, hsv}, \
	    {35, 1, hsv}, \
	    {45, 2, hsv}, \
	    {55, 2, hsv}, \
	    {63, 1, hsv}
*/
//Custom defined layer names
enum sofle_layers {
    _vou =0,
    _VOU,
    _LEVEL3,
    _LEVEL4,
    _QWERTZ,
    _FKEY,
};

//custom defined special key codes
enum custom_keycodes {
    P_LOREM = SAFE_RANGE,
    LENNYF,
    FLIP,
    SHRUG,
    DCOM,
    SHOT,
    CONSOL
};

// Tap Dance declarations
enum custom_tapdance{
     TD_ENT_SPC = 0
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // vou
     /*
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |QWERTZ|
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |TB/FKY|   v  |   .  |   o  |   u  |   ä  |                    |   q  |   g  |   l  |   h  |   f  |  j   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  LV3 |   c  |   a  |   e  |   i  |   y  |-------.    ,-------|   b  |   t  |   r  |   n  |   s  |  LV3 |
     * |------+------+------+------+------+------|FKEYLOCK|   | SHOT  |------+------+------+------+------+------|
     * |SHIFT |   z  |   x  |   ,  |   ö  |   ü  |-------|    |-------|   p  |   d  |   w  |   m  |   k  | LV2  |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *           | PGDOWN| LAlt | LGUI |LCTRL | /Space  /       \Enter \  |BSPC  |DEL   | LV4  | PGUP  |
     *           |       |      |      |      |/       /         \      \ |      |      |      |       |
     *           ------------------------------------'           '------''----------------------------'
     */

    [_vou] = LAYOUT(
        KC_ESC,    DE_1,   DE_2,    DE_3,    DE_4,    DE_5,                                      DE_6,    DE_7,   DE_8,        DE_9,    DE_0, TG(_QWERTZ),
        LT(_FKEY, KC_TAB), DE_V,    DE_DOT,  DE_O,    DE_U,    DE_ADIA,                          DE_Q,    DE_G,   DE_L,        DE_H,    DE_F, DE_J,
        MO(_LEVEL3),       DE_C,    DE_A,    DE_E,    DE_I,    DE_Y,                             DE_B,    DE_T,   DE_R,        DE_N,    DE_S, TT(_LEVEL3),
        KC_LSFT,           DE_Z,    DE_X,    DE_COMM, DE_ODIA, DE_UDIA, TG(_FKEY),        SHOT,  DE_P,    DE_D,   DE_W,        DE_M,    DE_K, TT(_VOU),
                                    KC_PGDN, KC_LALT, KC_LGUI, KC_LCTL, KC_SPC,  TD(TD_ENT_SPC), KC_BSPC, KC_DEL, TT(_LEVEL4), KC_PGUP
    ),
    /* VOU
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |   ̌Uhr|   °  |   §  |   ℓ  |   »  |  «   |                    |   $  |   €  |   „  |   ”  |  “   |  ß   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  TAB |   V  |   •  |   O  |   U  |   Ä  |                    |   Q  |   G  |   L  |   H  |  F   |  J   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  LV3 |   C  |   A  |   E  |   I  |   Y  |-------.    ,-------|   B  |   T  |   R  |   N  |  S   |  LV3 |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * | SHIFT|   Z  |   X  |   –  |  Ö   |   Ü  |-------|    |-------|   P  |   D  |   W  |   M  |  K   |  LV2 |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *             | nr5 | LAlt | LGUI |LCTRL | /Space  /       \Enter \  |Back  |DEL   | LV4  | nr5  |
     *             |     |      |      |      |/       /         \      \ |      |      |      |      |
     *             `----------------------------------'           '------''---------------------------'
     */
    [_VOU] = LAYOUT(
        UC(CUHR), DE_DEG,  DE_SECT, UC(SCRL),   UC(REQ),    UC(LEQ),                          DE_DLR,  DE_EURO, UC(LOW9), UC(HIG6), UC(HIG9), KC_MINS,
        KC_TRNS,  S(DE_V), UC(BOB), S(DE_O),    S(DE_U),    S(DE_ADIA),                       S(DE_Q), S(DE_G), S(DE_L),  S(DE_H),  S(DE_F),  S(DE_J),
        KC_TRNS,  S(DE_C), S(DE_A), S(DE_E),    S(DE_I),    S(DE_Y),                          S(DE_B), S(DE_T), S(DE_R),  S(DE_N),  S(DE_S),  KC_TRNS,
        KC_TRNS,  S(DE_Z), S(DE_X), UC(ENDASH), S(DE_ODIA), S(DE_UDIA), KC_TRNS,     KC_TRNS, S(DE_P), S(DE_D), S(DE_W),  S(DE_M),  S(DE_K),  KC_TRNS,
                           KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS
    ),
    /* LEVEL3
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  ⟳   |   ¹  |   ²  |  ³   |  ›   |   ‹  |                    |   ¢  |   ¥  |   ‚  |  ‘   |  ’   |  -   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  TAB |   ^  |   _  |  {   |   }  |   @  |                    |   !  |   <  |   >  |   =  |   &  |  %   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  LV3 |   \  |   /  |  (   |   )  |   *  |-------.    ,-------|   ?  |   :  |   ;  |   -  |   :  |  LV3 |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * | SHIFT|   #  |   ~  |  [   |   ]  |   $  |-------|    |-------|   +  |   "  |   '  |   |  |   +  |  LV2 |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *             | nr5 | LAlt | LGUI |LCTRL | /Space  /       \Enter \  |Back  |DEL   | LV4  | nr5  |
     *             |     |      |      |      |/       /         \      \ |      |      |      |      |
     *             `----------------------------------'           '------''---------------------------'
     */

    [_LEVEL3] = LAYOUT(
        UC(UHR), UC(HI1), UC(HI2), UC(HI3), UC(QLA), UC(QRA),                     UC(CENT), UC(YEN), UC(LSQ), UC(HSQ), UC(RSQ), DE_MINS,
        KC_TAB,  DE_CIRC, DE_UNDS, DE_LCBR, DE_RCBR, DE_AT,                       DE_EXLM,  DE_LABK, DE_RABK, DE_EQL,  DE_AMPR, DE_PERC,
        KC_TRNS, DE_BSLS, DE_SLSH, DE_LPRN, DE_RPRN, DE_ASTR,                     DE_QUES,  DE_COLN, DE_SCLN, DE_MINS, DE_COLN, KC_TRNS,
        KC_TRNS, DE_HASH, DE_TILD, DE_LBRC, DE_RBRC, DE_DLR, KC_TRNS,    KC_TRNS, DE_PLUS,  DE_DQUO, DE_QUOT, DE_PIPE, DE_PLUS, KC_TRNS,
                          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
    ),


       /* LEVEL4
        * ,-----------------------------------------.                    ,-----------------------------------------.
        * | Lorem|lenny |FLIP  |SHRUG |Console|     |                    |      |      |      |      |      |Velocikey|
        * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
        * | .com | pgup |  up  | pgdn | pos1 |      |                    |      |      |      |      |      |      |
        * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
        * |  LV3 |  lft |  dwn |  rgt |  ende|  Mute|-------.    ,-------|  HEAT|RGB ON| HUE+ | SAT+ | VAL+ |  LV3 |
        * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
        * | SHIFT|      |      |      |      |      |-------|    |-------|  MODEREV| MODE | HUE- | SAT- | VAL- |  LV2 |
        * `-----------------------------------------/       /     \      \-----------------------------------------'
        *             | nr5 | LAlt | LGUI |LCTRL | /Space  /       \Enter \  |Back  |DEL   | LV4  | nr5  |
        *             |     |      |      |      |/       /         \      \ |      |      |      |      |
        *             `----------------------------------'           '------''---------------------------'
        */
       [_LEVEL4] = LAYOUT(
           P_LOREM, LENNYF,  FLIP,    SHRUG,    CONSOL, XXXXXXX,                    XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, VK_TOGG,
           DCOM,    KC_PGUP, KC_UP,   KC_PGDN,  KC_HOME, XXXXXXX,                   XXXXXXX,  XXXXXXX,  XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,
           KC_TRNS, KC_LEFT, KC_DOWN, KC_RIGHT, KC_END,  KC_KB_MUTE,                XXXXXXX,  RGB_TOG,  RGB_HUI,  RGB_SAI, RGB_VAI, KC_TRNS,
           KC_TRNS, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, KC_NO,   KC_TRNS, RGB_RMOD,  RGB_MOD,  RGB_HUD,  RGB_SAD, RGB_VAD, KC_TRNS,
           KC_TRNS, KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
           ),

    /* QWERTZ
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  vou |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Z  |   U  |   I  |   O  |   P  |  Ü   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |CAPS  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   Ö  |  Ä   |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * |SHIFT |   Y  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   -  |RShift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *             | nr5 | LAlt | LGUI |LCTRL | /Space  /       \Enter \  |Back  |DEL   | LV4  | nr5  |
     *             |     |      |      |      |/       /         \      \ |      |      |      |      |
     *             `----------------------------------'           '------''---------------------------'
     */

    [_QWERTZ] = LAYOUT(
         KC_ESC,  DE_1, DE_2, DE_3, DE_4, DE_5,                  DE_6, DE_7, DE_8, DE_9, DE_0, KC_TRNS,
         KC_TAB,  DE_Q, DE_W, DE_E, DE_R, DE_T,                  DE_Z, DE_U, DE_I, DE_O, DE_P, DE_UDIA,
         KC_CAPS, DE_A, DE_S, DE_D, DE_F, DE_G,                  DE_H, DE_J, DE_K, DE_L, DE_ODIA, DE_ADIA,
         KC_LSFT, DE_Y, DE_X, DE_C, DE_V, DE_B, KC_TRNS,    SHOT, DE_N, DE_M, DE_COMM, DE_DOT, DE_MINS, KC_RSFT,
         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,           KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    ),
    /* FKEY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  | F10  | F11  | F12  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      | .com |      |      |unicode mode changer              |   *  |   7  |   8  |   9  |   -  |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------.    ,-------|   /  |   4  |   5  |   6  |   +  |   -  |
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------|    |-------|   0  |   1  |   2  |   3  |   =  |   .  |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *             | nr5 | LAlt | LGUI |LCTRL | /Space  /       \Enter \  |Back  |DEL   | LV4  | nr5  |
     *             |     |      |      |      |/       /         \      \ |      |      |      |      |
     *             `----------------------------------'           '------''---------------------------'
     */
    [_FKEY] = LAYOUT(
         KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,                        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
         _______, DCOM,    _______, _______, UC_PREV, UC_NEXT,                      KC_PAST, KC_KP_7, KC_KP_8, KC_KP_9, KC_PMNS, KC_NO,
         _______, _______, _______, _______, _______, _______,                      KC_PSLS, KC_KP_4, KC_KP_5, KC_KP_6, KC_PPLS, KC_TILD,
         _______, _______, _______, _______, _______, _______, _______,    KC_TRNS, KC_KP_0, KC_KP_1, KC_KP_2, KC_KP_3, KC_PENT, KC_KP_DOT,
                            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
    )
};

// Tap Dance code
tap_dance_action_t tap_dance_actions[] = {
    [TD_ENT_SPC] = ACTION_TAP_DANCE_DOUBLE(KC_ENT, KC_SPC)// Enter or space
};


/* Assign custom lightings for the layers*/
/*#ifdef RGBLIGHT_ENABLE
char layer_state_str[70];
// Now define the array of layers. Later layers take precedence

// _vou
// Light indicators
const rgblight_segment_t PROGMEM layer_vou_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_INDICATORS(HSV_ORANGE),
  SET_LAYER_ID(HSV_BLUE)
);

//_VOU
// Light indicators and layerId
const rgblight_segment_t PROGMEM layer_VOU_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_INDICATORS(HSV_ORANGE),
  SET_LAYER_ID(HSV_TEAL)
);

// _LEVEL3,
// Light layerId
const rgblight_segment_t PROGMEM layer_level3_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_GREEN)
);

// _LEVEL4,
// Light on layerId, Arrow keys, Lightmodes, lightvalues, lightbuttons, lightspecial
const rgblight_segment_t PROGMEM layer_level4_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_PURPLE),
    SET_ARROWKEYS(HSV_RED),
    SET_LIGHT_MODES(HSV_GREEN),
    SET_LIGHT_VALUES(HSV_BLUE),
    SET_LIGHT_BUTTONS(HSV_PINK),
    SET_LIGHT_SPECIAL(HSV_ORANGE)
    );

// _QWERTZ,
// Light only layerswitcher so far
const rgblight_segment_t PROGMEM layer_qwertz_lights[] = RGBLIGHT_LAYER_SEGMENTS(
 QWERTZ_INDICATOR(HSV_RED),
 SET_LAYER_ID(HSV_YELLOW)
);

//_FKEYS,
// Light on the numpad
const rgblight_segment_t PROGMEM layer_fkey_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_PINK),
    SET_TOP_ROW(HSV_GREEN)
    );

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

    layer_vou_lights,
	layer_VOU_lights,
	layer_level3_lights,
    layer_level4_lights,
	layer_qwertz_lights,
	layer_fkey_lights
);

layer_state_t layer_state_set_user(layer_state_t state) {
	rgblight_set_layer_state(0, layer_state_cmp(state, _vou) && layer_state_cmp(default_layer_state,_vou));
	rgblight_set_layer_state(1, layer_state_cmp(state, _VOU));
	rgblight_set_layer_state(2, layer_state_cmp(state, _LEVEL3));
	rgblight_set_layer_state(3, layer_state_cmp(state, _LEVEL4));
	rgblight_set_layer_state(4, layer_state_cmp(state, _QWERTZ));
    rgblight_set_layer_state(5, layer_state_cmp(state, _FKEY));
    return state;
}
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

	rgblight_mode(10);// haven't found a way to set this in a more useful way

}
#endif
*/
#ifdef OLED_ENABLE
static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {

    oled_write_ln_P(PSTR("Scy's"),false);
    oled_write_ln_P(PSTR("Sofle\n"), false);
    oled_write_ln_P(PSTR("Your"), false);
    oled_write_ln_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _vou:
            oled_write_ln_P(PSTR("vou"), false);
            break;
        case _VOU:
            oled_write_ln_P(PSTR("LOUD"), false);
            break;
        case _LEVEL3:
            oled_write_ln_P(PSTR("\%?<*$"), false);
            break;
        case _LEVEL4:
            oled_write_ln_P(PSTR("Light"), false);
            break;
        case _QWERTZ:
            oled_write_ln_P(PSTR("Normi"), false);
            break;
        case _FKEY:
            oled_write_ln_P(PSTR("FKEY"), false);
            break;
        default:
          break;
    }
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("WPM:"), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);

}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }//test this rotation offhand
    else{
        return OLED_ROTATION_180;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case P_LOREM:
            if (record->event.pressed){
                SEND_STRING("Sombie ipsum reversus ab viral inferno, nam rick grimes malum cerebro.\n De carne lumbering animata corpora quaeritis.\n De apocalypsi gorger omero undead survivor dictum mauris.\nHi mindless mortuis soulless creaturas, imo evil stalking monstra adventus resi dentevil vultus comedat cerebella viventium.\n Qui animated corpse, cricket bat max brucks terribilem incessu 5ombi.\n The voodoo sacerdos flesh eater,exe fiat Jeff becum suscitat mortuos comedere carnem virus.\n Yombi tattered for solum oculi eorum defunctis go lum cerebro.\n Nescio brains an Undead SOMBIES.Sicut malus putrid voodoo horror.\n Nigh tofth eliv ingdead.\n");
                return false;
            }
        case LENNYF:  // ( ͡° ͜ʖ ͡°)
            if (record->event.pressed){
                SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_L) SS_TAP(X_F) SS_UP(X_RALT));
                return false;
            }
        case FLIP:  // (ﾉಥ益ಥ）ﾉ彡┻━┻)
            if (record->event.pressed){
                SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_T) SS_TAP(X_F) SS_UP(X_RALT));
                return false;
            }
        case SHRUG:  // ¯\_(ツ)_/¯
            if (record->event.pressed){
                SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_S) SS_TAP(X_F) SS_UP(X_RALT));
                return false;
            }
        case DCOM:  // .COM
            if (record->event.pressed){
                SEND_STRING(SS_TAP(X_DOT) SS_TAP(X_C) SS_TAP(X_O) SS_TAP(X_M));
                return false;
            }
        case SHOT:  // screenshot
            if (record->event.pressed){
                SEND_STRING(SS_DOWN(X_LSFT) SS_DOWN(X_LGUI) SS_TAP(X_S) SS_UP(X_LGUI) SS_UP(X_LSFT));
                return false;
            }
        case CONSOL:
            if(record->event.pressed)
            {
            SEND_STRING("using static Szstem.Console");
            return false;
            }
    }
    return true;
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {  // Encoder on master side
        if (IS_LAYER_ON(_LEVEL3)) {
            if (clockwise) {
                tap_code(KC_VOLD);
            } else {
                tap_code(KC_VOLU);
            }
        } else {
            if (clockwise) {
                tap_code(KC_DOWN);
            } else {
                tap_code(KC_UP);
            }
        }
    } else if (index == 1) { // Encoder on slave side
        if (IS_LAYER_ON(_LEVEL3)) {
            if (clockwise) {
                tap_code(KC_BSPC);
            } else {
                tap_code(KC_DEL);
            }
        } else {
            if (clockwise) {
                tap_code(KC_RIGHT);
            } else {
                tap_code(KC_LEFT);
                }
        }
    }
    return true;
}
#endif
