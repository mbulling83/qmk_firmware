#include QMK_KEYBOARD_H
#include "keymap_extras/keymap_dvorak.h"

enum layer_names {
	L_BASE,
	L_SYMBOLS,
	L_NUMBERS,
	L_SYSTEM
};

#define DV_SPC KC_SPC
#define DV_TAB KC_TAB
#define DV_ESC KC_ESC
#define DV_HYPR KC_HYPR
#define DV_RET KC_ENT
#define DV_DELL KC_BSPC
#define DV_DELR KC_DEL
#define MOD_LOPT MOD_LALT
#define MOD_LCMD MOD_LGUI
#define MOD_ROPT MOD_RALT
#define MOD_RCMD MOD_RGUI

#define MT_DV_A MT(MOD_LSFT, DV_A)
#define MT_DV_O MT(MOD_LCTL, DV_O)
#define MT_DV_E MT(MOD_LOPT, DV_E)
#define MT_DV_U MT(MOD_LCMD, DV_U)
#define MT_DV_H MT(MOD_RCMD, DV_H)
#define MT_DV_T MT(MOD_ROPT, DV_T)
#define MT_DV_N MT(MOD_RCTL, DV_N)
#define MT_DV_S MT(MOD_RSFT, DV_S)

#define MT_S_GV MT(MOD_LSFT, DV_GRV)
#define MT_S_LB MT(MOD_LCTL, DV_LBRC)
#define MT_S_LC MT(MOD_LOPT, DV_LCBR)
#define MT_S_LP MT(MOD_LCMD, DV_LPRN)
#define MT_S_RP MT(MOD_RCMD, DV_RPRN)
#define MT_S_RC MT(MOD_ROPT, DV_RCBR)
#define MT_S_RB MT(MOD_RCTL, DV_RBRC)
#define MT_S_MN MT(MOD_RSFT, DV_MINS)

#define MT_N_4 MT(MOD_RCMD, DV_4)
#define MT_N_5 MT(MOD_ROPT, DV_5)
#define MT_N_6 MT(MOD_RCTL, DV_6)
#define MT_N_DT MT(MOD_RSFT, DV_DOT)

#define SYM_RET LT(L_SYMBOLS, DV_RET)
#define NUM_SPC LT(L_NUMBERS, DV_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
		 * Layer: Default
     * ┌───┬───┬───┬───┬───┐ ┌───┬───┬───┬───┬───┐
     * │ ' │ , │ . │ P │ Y │ │ F │ G │ C │ R │ L │
     * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
     * │ A │ O │ E │ U │ I │ │ D │ H │ T │ N │ S │
     * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
     * │ ⇥ │ Q │ J │ K │ X │ │ B │ M │ W │ V │ Z │
     * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
     * │ ⎋ │   │ ‼︎ │ ❖ │ ⏎ │ │ ␣ │ ⌫ │ ⌦ │   │ ⚙ │
     * └───┴───┴───┴───┴───┘ └───┴───┴───┴───┴───┘
     */
    [L_BASE] = LAYOUT_ortho_4x10(
        DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,    DV_F,    DV_G,    DV_C,    DV_R,    DV_L,
        MT_DV_A, MT_DV_O, MT_DV_E, MT_DV_U, DV_I,    DV_D,    MT_DV_H, MT_DV_T, MT_DV_N, MT_DV_S,
        DV_TAB,  DV_Q,    DV_J,    DV_K,    DV_X,    DV_B,    DV_M,    DV_W,    DV_V,    DV_Z,
        DV_ESC,  XXXXXXX, DV_HYPR, TO(0),   SYM_RET, NUM_SPC, DV_DELL, DV_DELR, XXXXXXX, TT(L_SYSTEM)
    ),
    /*
		 * Layer: Symbols
     * ┌───┬───┬───┬───┬───┐ ┌───┬───┬───┬───┬───┐
     * │ ! │ @ │ # │ $ │ % │ │ ^ │ & │ * │   │   │
     * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
     * │ ` │ [ │ { │ ( │ ; │ │ = │ ) │ } │ ] │ - │
     * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
     * │ ⇥ │   │   │ \ │   │ │   │ / │   │   │   │
     * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
     * │ ⎋ │   │ ‼︎ │   │ ⏎ │ │ ␣ │ ⌫ │ ⌦ │   │   │
     * └───┴───┴───┴───┴───┘ └───┴───┴───┴───┴───┘
     */
		[L_SYMBOLS] = LAYOUT_ortho_4x10(
				DV_EXLM, DV_AT,   DV_HASH, DV_DLR,  DV_PERC, DV_CIRC, DV_AMPR, DV_ASTR, XXXXXXX, XXXXXXX,
				MT_S_GV, MT_S_LB, MT_S_LC, MT_S_LP, DV_SCLN, DV_EQL,  MT_S_RP, MT_S_RC, MT_S_RB, MT_S_MN,
				_______, XXXXXXX, XXXXXXX, DV_BSLS, XXXXXXX, XXXXXXX, DV_SLSH, XXXXXXX, XXXXXXX, XXXXXXX,
				_______, _______, _______, _______, DV_RET,  DV_SPC,  _______, _______, _______, _______
		),
    /*
		 * Layer: Numbers
     * ┌───┬───┬───┬───┬───┐ ┌───┬───┬───┬───┬───┐
     * │ ⤉ │ ⇱ │ ↑ │ ⇲ │ v+│ │ - │ 7 │ 8 │ 9 │ , │
     * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
     * │ ⤈ │ ← │ ↓ │ → │ v-│ │ = │ 4 │ 5 │ 6 │ . │
     * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
     * │ ⇥ │ <<│ |>│ >>│ v0│ │ 0 │ 1 │ 2 │ 3 │ / │
     * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
     * │ ⎋ │   │ ‼︎ │ ❖ │ ⏎ │ │ ␣ │ ⌫ │ ⌦ │   │ ⚙ │
     * └───┴───┴───┴───┴───┘ └───┴───┴───┴───┴───┘
     */
		[L_NUMBERS] = LAYOUT_ortho_4x10(
				KC_PGUP, KC_HOME, KC_UP,   KC_END,  KC_VOLU, DV_MINS, DV_7,    DV_8,    DV_9,    DV_COMM,
				KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD, DV_EQL,  MT_N_4,  MT_N_5,  MT_N_6,  MT_N_DT,
				_______, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, DV_0,    DV_1,    DV_2,    DV_3,    DV_SLSH,
				_______, _______, _______, _______, DV_RET,  DV_SPC,  _______, _______, _______, _______
		),
    /*
		 * Layer: System
     * ┌───┬───┬───┬───┬───┐ ┌───┬───┬───┬───┬───┐
     * │F1 │F2 │F3 │F4 │F5 │ │F6 │F7 │F8 │F9 │F10│
     * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
     * │   │   │   │CWD│   │ │PSC│BUP│BDN│CAP│   │
     * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
     * │   │   │   │   │   │ │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
     * │   │   │ ‼︎ │   │   │ │   │   │   │   │   │
     * └───┴───┴───┴───┴───┘ └───┴───┴───┴───┴───┘
     */
		[L_SYSTEM] = LAYOUT_ortho_4x10(
				KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
				XXXXXXX, XXXXXXX, XXXXXXX, CAPSWRD, XXXXXXX, KC_PSCR, KC_BRID, KC_BRIU, KC_CAPS, XXXXXXX,
				XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
				XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
		)
};
