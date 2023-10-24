#include QMK_KEYBOARD_H

#define BLINK_TIMEOUT 250
#define LOCK_TIMEOUT 5000
#define TABBING_TIMEOUT 1000
#define LED GP25

// Can probably get rid of most of these because they are DVORAK mods

#define MOD_LOPT MOD_LALT
#define MOD_LCMD MOD_LGUI
#define MOD_ROPT MOD_RALT
#define MOD_RCMD MOD_RGUI




uint16_t lock_timeout(void);
void do_panic(void);
void do_tabbing(uint16_t kc);
void release_locks(void);

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data);
void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data);

enum layer_names {
	L_BASE,
	L_SYMBOLS,
	L_NAV,
	L_SYSTEM, 
	L_NUMBERS
};

void symbols_on(void);
void symbols_off(void);
void nav_on(void);
void nav_off(void);
void sys_on(void);
void sys_off(void);
void numbers_on(void);
void numbers_off(void);

typedef enum  {
	LOCK_NONE,
	LOCK_SYMBOLS,
	LOCK_NAV,
	LOCK_TABBING,
	LOCK_NUMBERS
} lock_type_t;

typedef enum {
	NONE,
	TAP,
	HOLD
} tap_dance_tap_hold_state_t;

typedef struct {
	uint16_t tap;
	uint16_t hold;
	tap_dance_tap_hold_state_t state;
	void (*onHold)(void);
	void (*onUp)(void);
} tap_dance_tap_hold_t;

enum tap_dances {
	D_PANIC,
	D_TAB,
	D_SPACE,
	D_RETURN,
	D_SYSTEM,
	D_TILD,
	D_PIPE,
	D_LPRN,
	D_RPRN
};

enum key_codes {
	M_PANIC = SAFE_RANGE,
	M_WINL,
	M_WINR,
	M_APPL,
	M_APPR
};

#define TAP_DANCE_TAP_ACTIONS(tap, hold, onHold, onUp)\
	{\
		.fn = { NULL, tap_dance_tap_hold_finished, tap_dance_tap_hold_reset },\
		.user_data = (void *)&((tap_dance_tap_hold_t){ tap, hold, NONE, onHold, onUp })\
	}

// Shared mode lock timers.
uint16_t lock_timer = 0;
uint16_t lock_toggle = 0;
bool lock_highlight = false;
bool lock_interrupt = false;
lock_type_t lock_type = LOCK_NONE;

tap_dance_action_t tap_dance_actions[] = {
	[D_PANIC] = TAP_DANCE_TAP_ACTIONS(M_PANIC, KC_LCTL, NULL, NULL),
	[D_TAB] = TAP_DANCE_TAP_ACTIONS(KC_TAB, 0, &numbers_on, &numbers_off),
	[D_SPACE] = TAP_DANCE_TAP_ACTIONS(KC_SPC, 0, &symbols_on, &symbols_off),
	[D_RETURN] = TAP_DANCE_TAP_ACTIONS(KC_ENT, 0, &nav_on, &nav_off),
	[D_SYSTEM] = TAP_DANCE_TAP_ACTIONS(M_PANIC, 0, &sys_on, &sys_off),
	[D_TILD] = TAP_DANCE_TAP_ACTIONS(KC_TILD, KC_LSFT, NULL, NULL),
	[D_PIPE] = TAP_DANCE_TAP_ACTIONS(KC_PIPE, KC_LCTL, NULL, NULL),
	[D_LPRN] = TAP_DANCE_TAP_ACTIONS(KC_LPRN, KC_LOPT, NULL, NULL),
	[D_RPRN] = TAP_DANCE_TAP_ACTIONS(KC_RPRN, KC_LCMD, NULL, NULL)
};

#define THL_3 TD(D_PANIC)
#define THL_2 LT(L_NUMBERS, KC_TAB)
#define THL_1 KC_LGUI

#define THR_1 LT(L_SYMBOLS, KC_SPC)
#define THR_2 LT(L_NAV, KC_ENT)
#define THR_3 KC_BSPC

#define TD_SYS TD(D_SYSTEM)
#define TD_TILD TD(D_TILD)
#define TD_PIPE TD(D_PIPE)
#define TD_LPRN TD(D_LPRN)
#define TD_RPRN TD(D_RPRN)

#define MT_A MT(MOD_LSFT, KC_A)
#define MT_S MT(MOD_LCTL, KC_S)
#define MT_D MT(MOD_LOPT, KC_D)
#define MT_F MT(MOD_LCMD, KC_F)

#define MT_J MT(MOD_RCMD, KC_J)
#define MT_K MT(MOD_ROPT, KC_K)
#define MT_L MT(MOD_RCTL, KC_L)
#define MT_SCLN MT(MOD_RSFT, KC_SCLN)

#define MT_4 MT(MOD_RCMD, KC_4)
#define MT_5 MT(MOD_ROPT, KC_5)
#define MT_6 MT(MOD_RCTL, KC_6)
#define MT_QUOT MT(MOD_RSFT, KC_QUOT)

#define CTL_A LCTL(KC_A)
#define CTL_E LCTL(KC_E)
#define DK_APPS LCMD(LOPT(KC_ESC))
#define DK_LOCK LCMD(LCTL(KC_Q))
#define DK_TABL LCMD(LSFT(KC_LBRC))
#define DK_TABR LCMD(LSFT(KC_RBRC))

// Alternative to tap dance
#define SFT_ESC LSFT_T(KC_ESC)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/*
	 * Layer: Default
	 * ┌───┬───┬───┬───┬───┐ ┌───┬───┬───┬───┬───┐
	 * │ Q │ W │ E │ R │ T │ │ Y │ U │ I │ O │ P │
	 * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
	 * │ A │ S │ D │ F │ G │ │ H │ J │ K │ L │ ; │
	 * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
	 * │ Z │ X │ C │ V │ B │ │ N │ M │ , │ . │ / │
	 * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
	 * │ ⎋ │   │ ‼︎ │ ⇥ │ ⌫ │ │ ␣ │   │ ⍟ │   │ ⏎ │
	 * └───┴───┴───┴───┴───┘ └───┴───┴───┴───┴───┘
	 */
	[L_BASE] = LAYOUT_ortho_4x10(
		KC_Q, 	KC_W, 	KC_E, 	KC_R,	KC_T,	KC_Y,	KC_U,   KC_I,    KC_O,    KC_P,
		KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,    KC_L,    KC_SCLN,
		KC_Z, 	KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_SLSH,
		SFT_ESC, XXXXXXX,THL_3,  THL_2,  THL_1,  THR_1,  THR_2,  THR_3,   XXXXXXX, TD_SYS
	),
	/*
	 * Layer: Symbols
	 */
	[L_SYMBOLS] = LAYOUT_ortho_4x10(
		KC_GRV,  KC_QUOT, KC_LCBR, KC_RCBR, KC_BSLS, KC_PLUS, KC_7,    KC_8,    KC_9,    KC_MINS,
		KC_TILD, KC_PIPE, KC_LPRN, KC_RPRN, KC_SLSH, KC_EQL,  KC_4,    KC_5,    KC_6,    KC_QUOT,
		KC_COLN, KC_SCLN, KC_LBRC, KC_RBRC, KC_UNDS, KC_0,    KC_1,    KC_2,    KC_3,    KC_SLSH,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______
	),
	/*
	 * Layer: Navigation
	 */
	
	[L_NAV] = LAYOUT_ortho_4x10(
		HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E),  HYPR(KC_R),  HYPR(KC_T), KC_VOLU, KC_HOME, KC_UP,   KC_END,  KC_PGUP,
		HYPR(KC_A), HYPR(KC_S),   HYPR(KC_D), HYPR(KC_F), HYPR(KC_G), KC_VOLD, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
		HYPR(KC_Z), HYPR(KC_X),   HYPR(KC_C), HYPR(KC_V), HYPR(KC_B), KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______
	),
	/*
	 * Layer: Numbers
	 */
	[L_NUMBERS] = LAYOUT_ortho_4x10(
		KC_1, 		KC_2, 		KC_3,  		KC_4,  		KC_5, 	KC_6, 	KC_7, 	KC_8,    KC_9,    KC_0,
		KC_EXLM, 	KC_AT,  	KC_HASH,	KC_DLR, 	KC_PERC, KC_CIRC, KC_AMPR,    KC_ASTR,    KC_LPRN, KC_RPRN,
		QK_BOOT, 	XXXXXXX,   	LALT(KC_3), M_APPL,  	M_APPR,  KC_MUTE, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
		_______, _______, _______ , _______, _______, _______, _______, _______,_______, _______
	),
	/*
	 * Layer: System
	 */
	[L_SYSTEM] = LAYOUT_ortho_4x10(
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
		KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,
		KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RSFT,
		KC_ESC,  XXXXXXX, KC_LCTL, KC_LOPT, KC_LCMD, KC_RCMD, KC_ROPT, KC_RCTL, XXXXXXX, M_PANIC
	)
};

void keyboard_post_init_user(void) {
	//debug_enable = true;
	//debug_matrix = true;
	//debug_keyboard = true;
	//debug_mouse = true;
	setPinOutput(LED);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	bool pressed = record->event.pressed;
	tap_dance_action_t *action;

	// Check keycodes during tabbing or command lock.
	if (lock_type == LOCK_TABBING) {
		switch (keycode) {
		// Permissive keys during cmd+tab lock.
		case M_WINL:
		case M_WINR:
		case M_APPL:
		case M_APPR:
		case KC_Q:
		case KC_LSFT:
		case KC_RSFT:
			break;
		// End tabbing for all other cases.
		default:
			dprint("Lock interrupt.\n");
			lock_interrupt = true;
			return false;
		}
	}

	// Other keycode cases.
	switch (keycode) {
	case TD(D_PANIC):
		action = &tap_dance_actions[TD_INDEX(keycode)];
		if (pressed || !action->state.count || action->state.finished) {
			break;
		}
		dprint("TD PANIC!\n");
		// fallthough
	case M_PANIC:
		do_panic();
		break;
	case M_APPL:
		if (pressed) { do_tabbing(LSFT(KC_TAB)); }
		break;
	case M_APPR:
		if (pressed) { do_tabbing(KC_TAB); }
		break;
	case M_WINL:
		if (pressed) { do_tabbing(LSFT(KC_GRV)); }
		break;
	case M_WINR:
		if (pressed) { do_tabbing(KC_GRV); }
		break;
	case TD(D_SPACE):
	case TD(D_TAB):
	case TD(D_RETURN):
	case TD(D_TILD):
	case TD(D_PIPE):
	case TD(D_LPRN):
	case TD(D_RPRN):
		action = &tap_dance_actions[TD_INDEX(keycode)];
		if (!pressed && action->state.count && !action->state.finished) {
			tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)action->user_data;
			dprint("TD tapping.\n");
			tap_code16(tap_hold->tap);
		}
		break;
	case TD(D_SYSTEM):
		if (IS_LAYER_ON(L_SYMBOLS)) {
			lock_type = LOCK_SYMBOLS;
		} else if (IS_LAYER_ON(L_NAV)) {
			lock_type = LOCK_NAV;
		}
		break;
	}

	if (record->event.pressed && lock_timeout()) {
		dprint("Resetting lock timer.\n");
		lock_timer = timer_read();
	}

	return true;
}

uint16_t lock_timeout(void) {
	switch (lock_type) {
	case LOCK_NONE: return 0;
	case LOCK_TABBING: return TABBING_TIMEOUT;
	default: break;
	}
	return LOCK_TIMEOUT;
}

void matrix_scan_user(void) {
	if (lock_type != LOCK_NONE && timer_elapsed(lock_toggle) > BLINK_TIMEOUT) {
		lock_toggle = timer_read();
		lock_highlight = !lock_highlight;
		if (lock_highlight) {
			writePinHigh(LED);
		} else {
			writePinLow(LED);
		}
	}

	bool check_locks = lock_interrupt || lock_timeout() != 0;
	if (check_locks && timer_elapsed(lock_timer) > lock_timeout()) {
		dprint("Release locks\n");
		release_locks();
	}
}

void tap_dance_tap_hold_finished(tap_dance_state_t *state, void *user_data) {
	tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

	if (state->pressed) {
		if (state->count == 1
#ifndef PERMISSIVE_HOLD
			&& !state->interrupted
#endif
		) {
			if (tap_hold->hold) {
				dprint("TD holding.\n");
				register_code16(tap_hold->hold);
			}
			if (tap_hold->onHold) {
				dprint("TD hold call.\n");
				tap_hold->onHold();
			}
			tap_hold->state = HOLD;
		} else {
			dprint("TD tap.\n");
			register_code16(tap_hold->tap);
			tap_hold->state = TAP;
		}
	}
}

void tap_dance_tap_hold_reset(tap_dance_state_t *state, void *user_data) {
	tap_dance_tap_hold_t *tap_hold = (tap_dance_tap_hold_t *)user_data;

	if (tap_hold->state != NONE) {
		dprint("TD complete.\n");
		// Shortcut allowing locks to continue.
		if (tap_hold->state == TAP) {
			dprint("TD release tap.\n");
			unregister_code16(tap_hold->tap);
		} else {
			dprint("TD release hold.\n");
			if (tap_hold->hold) { unregister_code16(tap_hold->hold); }
			if (tap_hold->onUp) { tap_hold->onUp(); }
		}
		tap_hold->state = NONE;
	}
}

void symbols_on(void) { 
	layer_on(L_SYMBOLS); 

}

void symbols_off(void) {
	if (lock_type == LOCK_SYMBOLS) { return; }
	layer_off(L_SYMBOLS);
}

void nav_on(void) { 
	layer_on(L_NAV); 
}

void nav_off(void) {
	if (lock_type == LOCK_NAV) { return; }
	layer_off(L_NAV);
}

void sys_on(void) {
	if (lock_type != LOCK_NONE) { return; }
	layer_on(L_SYSTEM);
}

void sys_off(void) { 
	layer_off(L_SYSTEM); 
}

void numbers_on(void) {
	if (lock_type == LOCK_NUMBERS) { return; }
	layer_on(L_NUMBERS);
}
void numbers_off(void) { 
	layer_off(L_NUMBERS); }


void do_tabbing(uint16_t kc) {
	lock_timer = timer_read();
	if (!(get_mods() & MOD_BIT(KC_LCMD))) {
		dprint("Beginning tabbing.\n");
		lock_type = LOCK_TABBING;
		clear_mods();
		register_code16(KC_LCMD);
	}
	dprint("Doing tabbing.\n");
	tap_code16(kc);
}

void start_lock(lock_type_t type) {
	if (type == LOCK_NONE) {
		lock_highlight = false;
		writePinLow(LED);
	} else if (type != lock_type) {
		lock_toggle = timer_read();
		lock_highlight = false;
		writePinHigh(LED);
	}
}

void release_locks(void) {
	dprint("Releasing locks.\n");
	switch (lock_type) {
	case LOCK_NONE:
		dprint("No lock detected.\n");
		break;
	case LOCK_TABBING:
		dprint("Releasing command lock.\n");
		unregister_code16(KC_LCMD);
	case LOCK_SYMBOLS:
		dprint("Releasing symbol lock.");
		layer_off(L_SYMBOLS);
	case LOCK_NAV:
		dprint("Releasing nav lock.");
		layer_off(L_NAV);
	case LOCK_NUMBERS:
		dprint("Releasing number lock.");
		layer_off(L_NUMBERS);
	}
	lock_type = LOCK_NONE;
	lock_highlight = false;
	lock_interrupt = false;
	writePinLow(LED);
}

void do_panic(void) {
	dprint("DON'T PANIC!\n");
	release_locks();
	// Clear all pressed keys and reset the layer.
	clear_keyboard();
	layer_clear();
	layer_on(L_BASE);
}
