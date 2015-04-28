/*
#include <cstdio>
#include <cstdlib>
extern "C" 
{
	#include <mpsse.h>
}
using namespace std;

void test(struct mpsse_context *io, int pin) {
	char * name;
	switch (pin) {
		case GPIOL0:
			name = "GPIOL0";
			break;
		case GPIOL1:
			name = "GPIOL1";
			break;
		case GPIOL2:
			name = "GPIOL2";
			break;
		case GPIOL3:
			name = "GPIOL3";
			break;
		case GPIOH0:
			name = "GPIOH0";
			break;
		case GPIOH1:
			name = "GPIOH1";
			break;
		case GPIOH2:
			name = "GPIOH2";
			break;
		case GPIOH3:
			name = "GPIOH3";
			break;
		case GPIOH4:
			name = "GPIOH4";
			break;
		case GPIOH5:
			name = "GPIOH5";
			break;
		case GPIOH6:
			name = "GPIOH6";
			break;
		case GPIOH7:
			name = "GPIOH7";
			break;
		default:
			name = "Unknown";
			printf("%d\n", pin);
	}
	int write;
	write = PinHigh(io, pin);
	printf("%s State: %d / %d\n", name ,PinState(io, pin, -1), write);
	sleep(1);
	write = PinLow(io, pin);
	printf("%s State: %d / %d\n", name ,PinState(io, pin, -1), write);
	//sleep(1);
}

int main(void)
{
	struct mpsse_context *io = NULL;
	int i = 0, retval = EXIT_FAILURE;

	io = MPSSE(GPIO, 0, 0);
	
	printf("Start\n");
	
	if (io) {
		printf("IO pass\n");
	} else {
		printf("IO not pass\n");
	}
	
	if (io->open) {
		printf("IO open\n");
	} else {
		printf("IO not open\n");
	}

	//if(io && io->open)
	if (io)
	{
		for(i=0; i<4; i++)
		{
			test(io, i);
			/*
			test(io, GPIOL0);
			test(io, GPIOL1);
			test(io, GPIOL2);
			test(io, GPIOL3);
			
			test(io, GPIOH0);
			test(io, GPIOH1);
			test(io, GPIOH2);
			test(io, GPIOH3);
			
			test(io, GPIOH7);
			
			test(io, GPIO1);
			* /
		}
	
		retval = EXIT_SUCCESS;
	}
	else
	{
		printf("Failed to open MPSSE: %s\n", ErrorString(io));
	}
		
	Close(io);

	return retval;
}
*/