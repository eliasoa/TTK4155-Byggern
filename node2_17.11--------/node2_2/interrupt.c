#include "interrupt.h"

#include <stdio.h>
#include "sam.h"
#include "printf-stdarg.h"


void TC0_Handler( void ){
	printf("TC0 trigget");
}