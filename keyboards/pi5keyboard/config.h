// Copyright 2022 Luke Schutt (@luke-schutt)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define TAPPING_TERM 200
#define PERMISSIVE_HOLD

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define WS2812_DI_PIN 23
#define RGBLED_NUM 1
#define RGB_DI_PIN 23
#define RGB_MATRIX_LED_COUNT 1
#define DRIVER_LED_TOTAL 1