/*
###############################################################################
# Copyright (c) 2017, PulseRain Technology LLC 
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License (LGPL) as 
# published by the Free Software Foundation, either version 3 of the License,
# or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
# or FITNESS FOR A PARTICULAR PURPOSE.  
# See the GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
###############################################################################
*/

#ifndef M10PWM_H
#define M10PWM_H

#include "Arduino.h"

#define PWM_SUB_ADDR_RESOLUTION_LOW     (0x0 << 4)
#define PWM_SUB_ADDR_RESOLUTION_HIGH    (0x1 << 4)
#define PWM_SUB_ADDR_REG_ON             (0x2 << 4)
#define PWM_SUB_ADDR_REG_OFF            (0x3 << 4)
#define PWM_SUB_ADDR_SYNC_RESET         (0x4 << 4)


typedef struct {
    void (*resolution) (uint8_t pwm_index, uint16_t pwm_resolution) __reentrant;
    void (*dutyCycle) (uint8_t pwm_index, uint8_t pwm_on, uint8_t pwm_off) __reentrant;
} PWM_STRUCT;

extern const PWM_STRUCT PWM;

#endif
