#include "irobotTime.h"

#ifdef _WIN32
	#include <windows.h>
#elif defined(__unix__)
	#include <unistd.h>
#endif

void irobotDelayMs(const int32_t ms){
	#ifdef _WIN32
		Sleep(ms);
	#elif defined(__unix__)
		usleep((ms) * 1000);
	#endif
}
