#ifndef STDDEFS_H
#define STDDEFS_H

#ifdef QT_CORE_LIB
#include <stdint.h>

#define MRF_DISABLE_INT
#define MRF_ENABLE_INT

#else
#include <xc.h>
#include <stdio.h>
#include <string.h>

#define strConcat(a,b) a##b

#ifdef __PIC24FJ64GB004__
#define PIC24GB
    #include "bspPIC24.h"
#define SERVER
#endif
#ifdef __dsPIC33FJ128GP804__
#define dsPIC33
    #include "bspPIC24.h"
#define SERVER
#endif
#ifdef __PIC24FJ64GA004__
#define PIC24GA
    #include "bspPIC24.h"
#define SERVER
#endif

#ifdef _16LF1508
    #include "bspPIC16.h"
#define PIC16_HW
#endif

#ifdef _16LF1509
    #include "bspPIC16.h"
#define PIC16_HW
#endif

#ifdef _16F1933
    #include "bspPIC16.h"
#endif
#endif

#ifndef bool
#define bool uint8_t
#endif

#ifndef true
#define true ((bool)1)
#endif

#ifndef false
#define false ((bool)0)
#endif

#ifndef NULL
#define NULL 0
#endif

#define AdcChannel_t uint8_t

#endif
