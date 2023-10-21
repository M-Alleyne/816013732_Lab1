//Michael Alleyne
//816013732

#include "stdio.h"
#include "ctype.h"
#include "unistd.h"
#include "sys/times.h"

#include "sam.h"
#include "Clock_Control.h"
#include "Definitions.h"
#include "FreeRTOS_SAMD21.h"

#define SLOTX	4
#define CYCLEX	5
#define SLOT_T	5000
#define SERIAL	SerialUSB


	int tps, cycle=0, slot=0;
	clock_t now, then;
	struct tms n;
	
	void myDelayMs(int ms)
	{
		vTaskDelay( (ms * 1000) / portTICK_PERIOD_US );
	}
	
	static void one(void) 
	{
		SERIAL.println("task 1 running\n");
		SERIAL.flush();
		myDelayMs(100);
		sleep(1);
	}
	
	static void two(void)
	{
		SERIAL.println("task 2 running\n");
		SERIAL.flush();
		myDelayMs(100);
		sleep(2);
	}
	
	static void three(void)
	{
		SERIAL.println("task 3 running\n");
		SERIAL.flush();
		myDelayMs(100);
		sleep(3);
	}
	
	static void four(void)
	{
		SERIAL.println("task 4 running\n");
		SERIAL.flush();
		myDelayMs(100);
		sleep(4);
	}
	
	static void five(void)
	{
		SERIAL.println("task 5 running\n");
		SERIAL.flush();
		myDelayMs(100);
		sleep(5);
	}
	
	static void burn(void)
	{
		clock_t bstart = times (&n);
		
		while ( ((now=times(&n))-then) < SLOT_T*tps/1000)
		{
			/* burn time here */
		}
		SERIAL.println("burn time = %2.2dms\n\n", (times(&n)-bstart)*1000/tps);
		then = now;
		cycle = CYCLEX;
	}
	
	void (*ttable [SLOTX][CYCLEX])() =
	{
		
		{one,  two,   burn,  burn,  burn},
		{one,  three, burn,  burn,  burn},
		{one,  four,  burn,  burn,  burn},
		{burn, burn,  burn,  burn,  burn}
	};
	
	main()
	{
		SystemInit();
		clocks.Clock_Init();
		
		tps = sysconf(SysTick);
		SERIAL.println("clock ticks/sec = %d\n\n", tps);
		while (1)
		{
			
			for(slot=0; slot<SLOTX; slot++)
				for(cycle=0; cycle<CYCLEX; cycle++)
					(*ttable[slot][cycle])();
		}
	}