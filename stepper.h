
#ifndef stepper_h
#define	stepper_h

// all distances (positions) in 16X microsteps
//    1/80 mm (a "ustep"), INT16 => +- 400 mm
// all times in 12 MHz ticks 
//    83.333 ns (a "tick"), UINT32 => 5.9 mins
// all speeds in ticks/ustep
// sample head speed (real range is 30 to 150 mm/sec) ...
//    75, (16 usteps every 1200 ticks, 10k pps, 2000 mm/sec)
//   
//     0 defined as zero speed
#define ms1  0b000
#define ms2  0b100
#define ms4  0b010
#define ms8  0b110
#define ms16 0b111

#define stepFwd 1

#define rc_step_mask 0b11001000
#define rcms1  0b00000000
#define rcms2  0b10000000
#define rcms4  0b01000000
#define rcms8  0b11000000
#define rcms16 0b11001000
UINT8 rcStepCode[] = {rcms1, rcms2, rcms4, rcms8, rcms16};

#define ra_step_mask 0b00010000
#define rams1   0b00000000
#define rams2   0b00010000
#define rams4   0b00000000
#define rams8   0b00010000
#define rams16  0b00010000
UINT8 raStepCode[] = {rams1, rams2, rams4, rams8, rams16};

#define rb_step_mask 0b00110000
#define rbms1   0b00000000
#define rbms2   0b00000000
#define rbms4   0b00010000
#define rbms8   0b00010000
#define rbms16  0b00110000
UINT8 rbStepCode[] = {rbms1, rbms2, rbms4, rbms8, rbms16};

UINT8 pwr2m1[] = {0b0000, 0b0001, 0b0011, 0b0111, 0b1111};

#define ustepsPerMm (200*16)/40          /* usteps/rev over mm/rev (80) */
#define maxUstepsH (330 * ustepsPerMm)   /* 13"     */
#define maxUstepsV (308 * ustepsPerMm)   /* 12 1/8" */

void initSteppers();
void setUstepH(UINT8 ustep);
void setUstepV(UINT8 ustep);
BOOL isUstepCompat(INT16 pos, UINT8 ustep);
void setStepDirH(UINT8 dir);
void setStepDirV(UINT8 dir);
void stepPulseH();
void stepPulseV();
void resetSteppers();

#endif
