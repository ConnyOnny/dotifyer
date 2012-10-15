/*
 * error.h
 *
 *  Created on: Sep 5, 2012
 *      Author: connyonny
 */

#ifndef ERROR_H_
#define ERROR_H_

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#ifdef __GNUC__
#define ERROR(format, args...) \
	do {\
		fprintf (stderr, "ERROR in file %s in line %d:\n", __FILE__, __LINE__); \
		fprintf (stderr, format, ## args); \
		raise (SIGABRT);\
		exit (1); /* this is never executed but needed for less warnings */ \
	} while (0)
#endif // __GNUC__

#ifdef _MSC_VER
#define ERROR(...) \
	do {\
		fprintf (stderr, "ERROR in file %s in line %d:\n", __FILE__, __LINE__); \
		fprintf (stderr, __VA_ARGS__); \
		raise (SIGABRT);\
		exit (1); \
	} while (0)
#endif // _MSC_VER

#ifndef ERROR
#error Vararg-Macro support needed and only implemented for gcc and msvc
#endif


#endif /* ERROR_H_ */
