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

// Enabling this option changes the startup behavior to listen for an
// active USB communication to delegate which part is master and which
// is slave. With this option enabled and theres’s USB communication,
// then that half assumes it is the master, otherwise it assumes it
// is the slave.
//
// I've found this helps with some ProMicros where the slave does not boot
#define SPLIT_USB_DETECT

#define RGB_DISABLE_WHEN_USB_SUSPENDED     // turn off effects when suspended

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
