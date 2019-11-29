#include "dbgIssam.h"
#include "usartIssam.h"
#include <stdarg.h>
#include <stdio.h>




/*

@author de cette fonction Issam 

*/
void _printf(const char *fmt, ...) {
	static char buf[CHUNK];
	va_list args;
	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	printChars(buf);
	va_end(args);
}
