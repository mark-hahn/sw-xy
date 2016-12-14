/*
 * File:   stepper.c
 * Author: mark hahn @ eridien
 *
 * Created on December 11, 2016, 10:53 AM
 */

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "xy1.h"
#include "stepper.h"

void initSteppers() {
  hstep = vstep = 1;
  hms1TRIS = hms2TRIS = hms3TRIS = hdirTRIS = hstepTRIS = 0;
  vms1TRIS = vms2TRIS = vms3TRIS = vdirTRIS = vstepTRIS = 0;
  stepperResetTRIS = 0;
  resetSteppers();
}

void setUstepH(UINT8 ustep) {
  UINT8 x, latc=LATC, TRISc=TRISC, portc=PORTC, code=rcStepCode[ustep];
  LATC = x = (LATC & !rc_step_mask) | rcStepCode[ustep];
  latc=LATC, TRISc=TRISC, portc=PORTC, code=rcStepCode[ustep];
}

void setUstepV(UINT8 ustep) {
  PORTA = (LATA & !ra_step_mask) | raStepCode[ustep];
  PORTB = (LATB & !rb_step_mask) | rbStepCode[ustep];
}

BOOL isUstepCompat(INT16 pos, UINT8 ustep) {
  return !(pos & pwr2m1[ustep]);
}

void setStepDirH(UINT8 dir) {
  hdir = dir;
}

void setStepDirV(UINT8 dir) {
  vdir = dir;
}

void stepPulseH() {
  hstep = 0;
  __delay_us(1);
  hstep = 1;
}

void stepPulseV() {
  vstep = 0;
  __delay_us(1);
  vstep = 1;
}

void resetSteppers() {
  stepperReset = 0;
  __delay_us(10);
  stepperReset = 1;
  __delay_ms(10);
}
