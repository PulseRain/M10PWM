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

#include "M10PWM.h"

//----------------------------------------------------------------------------
// pwm_set_resolution()
//
// Parameters:
//      pwm_index : index for PWM channel 
//                  on Arduino UNO Rev3, the mapping from index to pins are:
//                  0 - pin 3
//                  1 - pin 5
//                  2 - pin 6
//                  3 - pin 9
//                  4 - pin 10
//                  5 - pin 11
//
//      pwm_resolution: resolution for PWM, which determines the base frequency
//          The base frequency is calculated as the following:
//          Assume the processor clock rate is C
//          The PWM frequency is C / (resolution + 1)
//     
// Return Value:
//      None
//
// Remarks:
//      Function to set the resolution/frequency for PWM channel. 
//----------------------------------------------------------------------------

static void pwm_set_resolution (uint8_t pwm_index, uint16_t pwm_resolution) __reentrant
{
  uint8_t t;

  t = (uint8_t)(pwm_resolution & 0xFF);
  PWM_DATA = t;
  PWM_CSR = (0x80 | pwm_index | PWM_SUB_ADDR_RESOLUTION_LOW);

  t = (uint8_t)((pwm_resolution >> 8) & 0xFF);
  PWM_DATA = t;
  PWM_CSR = (0x80 | pwm_index | PWM_SUB_ADDR_RESOLUTION_HIGH);
    
} // End of pwm_set_resolution()


//----------------------------------------------------------------------------
// pwm_set_duty_cycle()
//
// Parameters:
//      pwm_index : index for PWM channel 
//                  on Arduino UNO Rev3, the mapping from index to pins are:
//                  0 - pin 3
//                  1 - pin 5
//                  2 - pin 6
//                  3 - pin 9
//                  4 - pin 10
//                  5 - pin 11
//
//      pwm_on    : The number of base cycles (1 / base_frequency) to be on
//      pwm_off   : The number of base cycles (1 / base_frequency) to be off 
//     
// Return Value:
//      None
//
// Remarks:
//      Function to set the duty cycle of PWM channel. 
//----------------------------------------------------------------------------
static void pwm_set_duty_cycle (uint8_t pwm_index, uint8_t pwm_on, uint8_t pwm_off) __reentrant
{
  PWM_DATA = pwm_off;
  PWM_CSR = (0x80 | pwm_index | PWM_SUB_ADDR_REG_OFF);

  PWM_DATA = pwm_on;
  PWM_CSR = (0x80 | pwm_index | PWM_SUB_ADDR_REG_ON);

  PWM_CSR = (0x80 | pwm_index | PWM_SUB_ADDR_SYNC_RESET);
  
} // End of pwm_set_duty_cycle()


const PWM_STRUCT PWM = {
  .resolution = pwm_set_resolution,
  .dutyCycle = pwm_set_duty_cycle  
};
