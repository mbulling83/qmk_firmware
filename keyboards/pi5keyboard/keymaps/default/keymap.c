#include QMK_KEYBOARD_H
#include "keymap_extras/keymap_dvorak.h"

#define BLINK_TIMEOUT 250
#define LOCK_TIMEOUT 5000
#define TABBING_TIMEOUT 1000
#define LED GP25

#define DV_SPC KC_SPC
#define DV_TAB KC_TAB
#define DV_ESC KC_ESC
#define DV_RET KC_ENT
#define DV_DELL KC_BSPC
#define DV_DELR KC_DEL
#define DV_LSFT KC_LSFT
#define DV_LCTL KC_LCTL
#define DV_LOPT KC_LOPT
#define DV_LCMD KC_LCMD
#define DV_RCMD KC_RCMD
#define DV_ROPT KC_ROPT
#define DV_RCTL KC_RCTL
#define DV_RSFT KC_RSFT
#define MOD_LOPT MOD_LALT
#define MOD_LCMD MOD_LGUI
#define MOD_ROPT MOD_RALT
#define MOD_RCMD MOD_RGUI

uint16_t lock_timeout(void);
void do_panic(void);
void do_tabbing(uint16_t kc);
void release_locks(void);

void tap_dance_tap_hold_finished(qk_tap_dance_state_t *state, void *user_data);
void tap_dance_tap_hold_reset(qk_tap_dance_state_t *state, void *user_data);

enum layer_names {
	L_BASE,
	L_SYMBOLS,
	L_NAV,
	L_SYSTEM
};

void symbols_on(void);
void symbols_off(void);
void nav_on(void);
void nav_off(void);
void sys_on(void);
void sys_off(void);

typedef enum  {
	LOCK_NONE,
	LOCK_SYMBOLS,
	LOCK_NAV,
	LOCK_TABBING
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

qk_tap_dance_action_t tap_dance_actions[] = {
	[D_PANIC] = TAP_DANCE_TAP_ACTIONS(M_PANIC, 0, NULL, NULL),
	[D_TAB] = TAP_DANCE_TAP_ACTIONS(DV_TAB, 0, &symbols_on, &symbols_off),
	[D_SPACE] = TAP_DANCE_TAP_ACTIONS(DV_SPC, 0, &symbols_on, &symbols_off),
	[D_RETURN] = TAP_DANCE_TAP_ACTIONS(DV_RET, 0, &nav_on, &nav_off),
	[D_SYSTEM] = TAP_DANCE_TAP_ACTIONS(M_PANIC, 0, &sys_on, &sys_off),
	[D_TILD] = TAP_DANCE_TAP_ACTIONS(DV_TILD, DV_LSFT, NULL, NULL),
	[D_PIPE] = TAP_DANCE_TAP_ACTIONS(DV_PIPE, DV_LCTL, NULL, NULL),
	[D_LPRN] = TAP_DANCE_TAP_ACTIONS(DV_LPRN, DV_LOPT, NULL, NULL),
	[D_RPRN] = TAP_DANCE_TAP_ACTIONS(DV_RPRN, DV_LCMD, NULL, NULL)
};

#define THL_3 TD(D_PANIC)
#define THL_2 TD(D_TAB)
#define THL_1 DV_DELL
#define THR_1 TD(D_SPACE)
#define THR_2 TD(D_RETURN)
#define THR_3 DV_DELR

#define TD_SYS TD(D_SYSTEM)
#define TD_TILD TD(D_TILD)
#define TD_PIPE TD(D_PIPE)
#define TD_LPRN TD(D_LPRN)
#define TD_RPRN TD(D_RPRN)

#define MT_A MT(MOD_LSFT, DV_A)
#define MT_O MT(MOD_LCTL, DV_O)
#define MT_E MT(MOD_LOPT, DV_E)
#define MT_U MT(MOD_LCMD, DV_U)

#define MT_H MT(MOD_RCMD, DV_H)
#define MT_T MT(MOD_ROPT, DV_T)
#define MT_N MT(MOD_RCTL, DV_N)
#define MT_S MT(MOD_RSFT, DV_S)

#define MT_4 MT(MOD_RCMD, DV_4)
#define MT_5 MT(MOD_ROPT, DV_5)
#define MT_6 MT(MOD_RCTL, DV_6)
#define MT_DOT MT(MOD_RSFT, DV_DOT)

#define CTL_A LCTL(DV_A)
#define CTL_E LCTL(DV_E)
#define DK_APPS LCMD(LOPT(DV_ESC))
#define DK_LOCK LCMD(LCTL(DV_Q))
#define DK_TABL LCMD(LSFT(DV_LBRC))
#define DK_TABR LCMD(LSFT(DV_RBRC))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/*
	 * Layer: Default
	 * ┌───┬───┬───┬───┬───┐ ┌───┬───┬───┬───┬───┐
	 * │ ' │ , │ . │ P │ Y │ │ F │ G │ C │ R │ L │
	 * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
	 * │ A │ O │ E │ U │ I │ │ D │ H │ T │ N │ S │
	 * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
	 * │ ; │ Q │ J │ K │ X │ │ B │ M │ W │ V │ Z │
	 * ├───┼───┼───┼───┼───┤ ├───┼───┼───┼───┼───┤
	 * │ ⎋ │   │ ‼︎ │ ⇥ │ ⌫ │ │ ␣ │ ⏎ │ ⍟ │   │ ⚙ │
	 * └───┴───┴───┴───┴───┘ └───┴───┴───┴───┴───┘
	 */
	[L_BASE] = LAYOUT_ortho_4x10(
		DV_QUOT, DV_COMM, DV_DOT,  DV_P,    DV_Y,    DV_F,    DV_G,    DV_C,    DV_R,    DV_L,
		MT_A,    MT_O,    MT_E,    MT_U,    DV_I,    DV_D,    MT_H,    MT_T,    MT_N,    MT_S,
		DV_SCLN, DV_Q,    DV_J,    DV_K,    DV_X,    DV_B,    DV_M,    DV_W,    DV_V,    DV_Z,
		DV_ESC,  XXXXXXX, THL_3,   THL_2,   THL_1,   THR_1,   THR_2,   THR_3,   XXXXXXX, TD_SYS
	),
	/*
	 * Layer: Symbols
	 */
	[L_SYMBOLS] = LAYOUT_ortho_4x10(
			DV_GRV,  _______, DV_LCBR, DV_RCBR, DV_BSLS, DV_PLUS, DV_7,    DV_8,    DV_9,    DV_MINS,
			TD_TILD, TD_PIPE, TD_LPRN, TD_RPRN, DV_SLSH, DV_EQL,  MT_4,    MT_5,    MT_6,    MT_DOT,
			DV_COLN, DV_SCLN, DV_LBRC, DV_RBRC, DV_UNDS, DV_0,    DV_1,    DV_2,    DV_3,    DV_SLSH,
			_______, _______, _______, _______, _______, _______, _______, _______, _______, _______
	),
	/*
	 * Layer: Navigation
	 */
	[L_NAV] = LAYOUT_ortho_4x10(
		DK_APPS, DK_LOCK, M_WINL,  M_WINR,  XXXXXXX, KC_VOLU, KC_HOME, KC_UP,   KC_END,  KC_PGUP,
		CTL_A,   CTL_E,   DK_TABL, DK_TABR, XXXXXXX, KC_VOLD, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,
		XXXXXXX, XXXXXXX, M_APPL,  M_APPR,  XXXXXXX, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX,
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______
	),
	/*
	 * Layer: System
	 */
	[L_SYSTEM] = LAYOUT_ortho_4x10(
		KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,
		KC_F11,  KC_F12,  KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,
		DV_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DV_RSFT,
		DV_ESC,  XXXXXXX, DV_LCTL, DV_LOPT, DV_LCMD, DV_RCMD, DV_ROPT, DV_RCTL, XXXXXXX, M_PANIC
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
	qk_tap_dance_action_t *action;

	// Check keycodes during tabbing or command lock.
	if (lock_type == LOCK_TABBING) {
		switch (keycode) {
		// Permissive keys during cmd+tab lock.
		case M_WINL:
		case M_WINR:
		case M_APPL:
		case M_APPR:
		case DV_Q:
		case DV_LSFT:
		case DV_RSFT:
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
		if (pressed) { do_tabbing(LSFT(DV_TAB)); }
		break;
	case M_APPR:
		if (pressed) { do_tabbing(DV_TAB); }
		break;
	case M_WINL:
		if (pressed) { do_tabbing(LSFT(DV_GRV)); }
		break;
	case M_WINR:
		if (pressed) { do_tabbing(DV_GRV); }
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

void tap_dance_tap_hold_finished(qk_tap_dance_state_t *state, void *user_data) {
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

void tap_dance_tap_hold_reset(qk_tap_dance_state_t *state, void *user_data) {
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

void symbols_on(void) { layer_on(L_SYMBOLS); }
void symbols_off(void) {
	if (lock_type == LOCK_SYMBOLS) { return; }
	layer_off(L_SYMBOLS);
}

void nav_on(void) { layer_on(L_NAV); }
void nav_off(void) {
	if (lock_type == LOCK_NAV) { return; }
	layer_off(L_NAV);
}

void sys_on(void) {
	if (lock_type != LOCK_NONE) { return; }
	layer_on(L_SYSTEM);
}
void sys_off(void) { layer_off(L_SYSTEM); }

void do_tabbing(uint16_t kc) {
	lock_timer = timer_read();
	if (!(get_mods() & MOD_BIT(DV_LCMD))) {
		dprint("Beginning tabbing.\n");
		lock_type = LOCK_TABBING;
		clear_mods();
		register_code16(DV_LCMD);
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
		unregister_code16(DV_LCMD);
	case LOCK_SYMBOLS:
		dprint("Releasing symbol lock.");
		layer_off(L_SYMBOLS);
	case LOCK_NAV:
		dprint("Releasing nav lock.");
		layer_off(L_NAV);
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
