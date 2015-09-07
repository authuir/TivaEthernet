/*
 * Common.h
 *
 *  Created on: 2015-8-6
 *      Author: Authuir
 */

#ifndef COMMON_H_
#define COMMON_H_

#ifndef TARGET_IS_BLIZZARD_RA1
#define TARGET_IS_BLIZZARD_RA1
#endif
#ifndef PART_TM4C123GH6PM
#define PART_TM4C123GH6PM
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/timer.h"
#include "driverlib/systick.h"
#include "driverlib/rom.h"
#include "driverlib/pin_map.h"
#include "driverlib/uart.h"
#include "driverlib/ssi.h"

#include "UART.h"
#include "JDQ.h"
#include "NRF.h"
#include "TFT.h"

#endif /* COMMON_H_ */
