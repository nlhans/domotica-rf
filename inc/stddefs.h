#ifndef STDDEFS_H
#define STDDEFS_H

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

#ifdef _16F1508
    #include "bspPIC16.h"
#endif

#ifdef _16F1933
    #include "bspPIC16.h"
#endif

#endif