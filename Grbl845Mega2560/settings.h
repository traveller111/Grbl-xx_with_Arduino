/*
  settings.h - eeprom configuration handling
  Part of Grbl

  Copyright (c) 2009-2011 Simen Svale Skogsrud
  Copyright (c) 2011 Sungeun K. Jeon

  Grbl is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  Grbl is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with Grbl.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef settings_h
#define settings_h

#include <math.h>
#include <inttypes.h>
/// LETARTARE
#include "nuts_bolts.h"
#include "defaults.h"    // define  AXIS_T_TYPE

/// date of construction
#define GRBL_VERSION_BUILD "20140426"
/// version
#define GRBL_VERSION "0.845"

/// 845 : the axes  -> GRBL_AXIS
#if (AXIS_T_TYPE == LINEAR)
    #if AXIS_T == AXIS_U
		#define GRBL_AXIS  "(X, Y, Z, U)"
	#elif AXIS_T ==	AXIS_V
		#define GRBL_AXIS "(X, Y, Z, V)"
	#elif AXIS_T ==	AXIS_W
		#define GRBL_AXIS "(X, Y, Z, W)"
	#else
		#define GRBL_AXIS "(X, Y, Z)"
	#endif
#elif (AXIS_T_TYPE == ROTARY)
	#if AXIS_T == AXIS_A
		#define GRBL_AXIS "(X, Y, Z, A)"
	#elif AXIS_T ==	AXIS_B
		#define GRBL_AXIS "(X, Y, Z, B)"
	#elif AXIS_T ==	AXIS_C
		#define GRBL_AXIS "(X, Y, Z, C)"
	#else
		#define GRBL_AXIS "(X, Y, Z)"
	#endif
#else
	#define GRBL_AXIS "(X, Y, Z)"
#endif


// Version of the EEPROM data. Will be used to migrate existing data from older versions of Grbl
// when firmware is upgraded. Always stored in byte 0 of eeprom
#define SETTINGS_VERSION 5

// Current global settings (persisted in EEPROM from byte 1 onwards)
typedef struct {
/// 843 : 4 -> N_AXIS,  X, Y, Z, T
  double steps_per_mm[N_AXIS];  //  X, Y, Z, T in [U,V,W,A,B,C]
/// 844
  double steps_per_degree;  // rotary A or B or C
  uint8_t microsteps;
  uint8_t pulse_microseconds;
  double default_feed_rate;
  double default_seek_rate;
  uint8_t invert_mask_stepdir;
  uint8_t invert_mask_limit;
  double mm_per_arc_segment;
  double acceleration;
  double junction_deviation;
  uint8_t spindle_pwm;
  uint32_t default_spindle;
  double max_spindle;
} settings_t;
extern settings_t settings;


// Initialize the configuration subsystem (load settings from EEPROM)
void settings_init();

// Print current settings
void settings_dump();

// Handle settings command
uint8_t settings_execute_line(char *line);

// A helper method to set new settings from command line
void settings_store_setting(int parameter, double value);

#endif
