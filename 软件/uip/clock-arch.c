#include "clock-arch.h"
#include <stdint.h>

extern int32_t g_RunTime;

/*---------------------------------------------------------------------------*/
clock_time_t
clock_time(void)
{
	return g_RunTime;
}
/*---------------------------------------------------------------------------*/
