/* Copyright 2023 Brian Low
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#define TAPPING_TERM_PER_KEY

#define MASTER_RIGHT

#define RGB_MATRIX_SLEEP     // turn off effects when suspended

#define SPLIT_TRANSPORT_MIRROR             // If LED_MATRIX_KEYPRESSES or LED_MATRIX_KEYRELEASES is enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_LEADER

#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100  // limits maximum brightness of LEDs (max 255). Higher may cause the controller to crash.

// Only single key -> no timeout
#define LEADER_NO_TIMEOUT
#define LEADER_TIMEOUT 1
#define LEADER_PER_KEY_TIMING

// https://docusaurus.qmk.fm/tap_hold
#define HOLD_ON_OTHER_KEY_PRESS

// touchpad
//#define POINTING_DEVICE_ROTATION_90
//#define POINTING_DEVICE_INVERT_X
//#define POINTING_DEVICE_INVERT_Y
#define CIRQUE_PINNACLE_DIAMETER_MM 35
#define CIRQUE_PINNACLE_CURVED_OVERLAY

#define CIRQUE_PINNACLE_ATTENUATION EXTREG__TRACK_ADCCONFIG__ADC_ATTENUATE_3X

#define CIRQUE_PINNACLE_POSITION_MODE CIRQUE_PINNACLE_ABSOLUTE_MODE

#define CIRQUE_PINNACLE_TAP_ENABLE
// #define POINTING_DEVICE_GESTURES_SCROLL_ENABLE
#define POINTING_DEVICE_GESTURES_CURSOR_GLIDE_ENABLE

// mouse layer
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 8
