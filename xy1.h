
#ifndef xy1_h
#define	xy1_h

#include <xc.h>

#define _XTAL_FREQ 48000000
 
#define INT8    int8_t
#define INT16   int16_t
#define INT24   int24_t
#define INT32   int32_t
#define UINT8  uint8_t
#define UINT16 uint16_t
#define UINT24 uint24_t
#define UINT32 uint32_t
#define PTR    uintptr_t
#define BOOL   uint8_t
#define FALSE  0
#define TRUE   1

#define hms1  LATBbits.LB2
#define hms2  LATBbits.LB3
#define hms3  LATAbits.LA7
#define hstep LATCbits.LC0
#define hdir  LATCbits.LC1

#define hms1TRIS  TRISBbits.RB2
#define hms2TRIS  TRISBbits.RB3
#define hms3TRIS  TRISAbits.RA7
#define hstepTRIS TRISCbits.RC0
#define hdirTRIS  TRISCbits.RC1

#define vms1  LATAbits.LA0
#define vms2  LATAbits.LA1
#define vms3  LATAbits.LA6
#define vstep LATAbits.LA4
#define vdir  LATAbits.LA5

#define vms1TRIS  TRISAbits.RA0
#define vms2TRIS  TRISAbits.RA1
#define vms3TRIS  TRISAbits.RA6
#define vstepTRIS TRISAbits.RA4
#define vdirTRIS  TRISAbits.RA5

#define led          LATCbits.LC6
#define stepperReset LATAbits.LA3

#define ledTRIS          TRISCbits.RC6
#define stepperResetTRIS TRISAbits.RA3

#define hlim   PORTBbits.RB4
#define vlim   PORTBbits.RB5
#define enable PORTCbits.RC7

#define hlimioc   IOCBbits.IOCB4
#define vlimioc   IOCBbits.IOCB5
#define enableioc IOCCbits.IOCC7

#define hlimTRIS         TRISBbits.RB4
#define vlimTRIS         TRISBbits.RB5
#define enableTRIS       TRISCbits.RC7

#endif