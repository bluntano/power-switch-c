#include "common.h"

int switch_on_off(int relayPin, int delayInSec)
{
	delayInSec = delayInSec * 1000;
	if (wiringPiSetup() == -1)
	{ // when initialize wiringPi failed, print message to screen
		printf("setup wiringPi failed!\n");
		return 1;
	}
	
	pinMode(relayPin, OUTPUT);
	digitalWrite(relayPin, LOW);
	while (1)
	{
		digitalWrite(relayPin, HIGH);
		delay(delayInSec);
		digitalWrite(relayPin, LOW);
		break;
	}
	return 0;
}