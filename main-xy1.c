/*
 * File:   main-xy1.c
 * Author: eridien, mark hahn
 *
 * Created on December 9, 2016, 11:20 PM
 *  PROCESSOR: PIC18F25K50
 * 
 * eridien XY firmware
 * github.com/mark-hahn/sw-xy
 */


#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "xy1.h"
#include "stepper.h"

// global state
BOOL homed = FALSE;
INT16 lastPosH, lastPosV;
INT16 posH = 0, posV = 0;

void pwrOff(){
  led = 0;
  T0CONbits.TMR0ON = 0; // timer 0 off
  lostPos();
}

void pwrOn(){
  led = 1;
}

void atHomeH() {
  homedH = TRUE;
  stopMoveH();
  lastPosH = posH;
  posH = 0;
}

void atHomeV() {
  homedV = TRUE;
  stopMoveV();
  lastPosV = posV;
  posV = 0;
}

void lostPos() {
  homed = FALSE;
  posH = posV = 0;
  resetSteppers();
}

// state during move
BOOL moving = FALSE, homingH = FALSE;
INT16 tgtPosH, tgtPosV;
UINT16 speedH, speedV;
UINT32 moveElapsedTime;

void startMove(INT16 h, INT16 v, UINT16 speed, BOOL relative) {
  tgtPosH = h + (relative ? posH : 0);
  tgtPosV = v + (relative ? posV : 0);
  moveElapsedTime = 0;
  moving = TRUE;
}

void stopMove() {
  moving = FALSE;
}

UINT8 timerVal = 0xa5; // debug
void stepperInt() {
 led = !led;           // debug, shows 5.9 KHz
  timerVal = TMR0L;    // debug, time elapsed since rollover happened
}

UINT8 iocPortB, iocPortC;

void chkHlim() {
  if(!homed && !hlim && !vlim)
    atHome();
}
void chkVlim(){
  if(!homed && !hlim && !vlim)
    atHome();  
}
void chkEnable(){
  if(enable) {
    pwrOn();
  } else {
    pwrOff();
  }
}
 
void interrupt all_ints(void) {
  if (TMR0IF) {
    TMR0IF = 0;
    stepperInt();
  }
  if(IOCIF) {
    volatile UINT8 iocDelay;
    iocPortB = PORTB; iocPortC = PORTC;
    iocDelay = 0; // can't clr IOCIF until one instr has passed
    IOCIF = 0;
    chkHlim();
    chkVlim();
    chkEnable();
  }
}

// Stepper vref = 4.096 * (DACR/32) - 0.7
// Stepper current in amps = stepper vref/0.8
// max value is 2.55 amps (255)
void setStepperAmps(UINT8 ampsTimes100) {
  VREFCON2bits.DACR = ((UINT16)65*ampsTimes100)/1000+5;
}

void main(void) {
  OSCCONbits.IRCF = 7; // hf int osc 16 MHz
   
  stepperReset = 0;    // disable stepper during init
  
  // DAC output
  VREFCON0bits.FVRS   = 3; // vref = 4V
  VREFCON0bits.FVREN  = 1; // enable vref module
  VREFCON1bits.DACPSS = 2; // fixed voltage reference top
  VREFCON1bits.DACNSS = 0; // ground reference bottom
  VREFCON1bits.DACEN  = 1; // apply top & bottom source voltages
  setStepperAmps(100);     // default is 1 amp
  VREFCON1bits.DACOE  = 1; // enable DAC output pin
  
  initSteppers();
  
  // timer 0 config   48 MHz/4/4/256 => 11.72 KHz
  T0CONbits.T0PS   = 1; // 4x scaling, 2 ^ (T0PS+1)
  T0CONbits.PSA    = 0; // prescaler on
  T0CONbits.T0CS   = 0; // timer, internal fosc/4
  T0CONbits.T08BIT = 1; // 8-bit
  T0CONbits.TMR0ON = 1; // timer 0 on
  TMR0IF = 0;
  TMR0IE = 1;
     
  // interrupt on change
  hlimTRIS = vlimTRIS = enableTRIS = 1;
  hlimioc  = vlimioc  = enableioc = 1;
  IOCIF = 0;
  IOCIE = 1;
          
  // enable all interrupts
  RCONbits.IPEN = 0;  // don't use interrupt priorities
  PEIE = 1; // enable peripheral ints
  GIE = 1;  // global enable
  
  ledTRIS = 0; // power light and debug
  
  setUstepH(4); // debug

  while (TRUE) {
    __delay_ms(1);
    stepPulseH(); // debug
  }
}
