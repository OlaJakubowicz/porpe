/*
* Document-macros: Errors | Warnings
*
* Variadic macros for signalizing errors and warnings ;)  
* Variadic macros ANSI C99 preprocessor standard, gcc 4.0.1+
* file: Errors.h
* author: JO
*/

#ifndef __ERRORS_H_VARIADIC_FEAR__
#define __ERRORS_H_VARIADIC_FEAR__

#include <stdio.h>
#include <stdlib.h>

#define PANIC(_rcode,...) ( {fprintf(stderr, "Fatal: "); fprintf(stderr, __VA_ARGS__ ) ; exit(_rcode); })
#define FEAR(...) ({fprintf(stderr, "Warning: "); fprintf(stderr,  __VA_ARGS__ ); })
//empty line (warning: no newline at end of file)

#endif