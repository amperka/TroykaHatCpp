/** 
 * The digitalWrite example.
 *
 * The program changes the state of pin 0 from 1 to 0 twice a second.
 **/

#include <GpioExpanderPi.h>
#include <stdio.h>
#include <wiringPi.h>

constexpr uint8_t GPIO_EXPANDER_LED_PIN = 0;

GpioExpanderPi expander;

int main(void) {
	if (!expander.begin())
		printf("Failed to init I2C communication.\n");

	expander.pinMode(GPIO_EXPANDER_LED_PIN, GPIO_PIN_OUTPUT);

	for (;;) {
		expander.digitalWrite(GPIO_EXPANDER_LED_PIN, HIGH);
		printf("LED on pin %d is ON\n", GPIO_EXPANDER_LED_PIN);
		delay(500);
		expander.digitalWrite(GPIO_EXPANDER_LED_PIN, LOW);
		printf("LED on pin %d is OFF\n", GPIO_EXPANDER_LED_PIN);
		delay(500);
	}
	return 0;
}
