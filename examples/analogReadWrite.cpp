/** 
 * The analogReadWrite example.
 *
 * The program reads analog value of pin 2 in the range [0, 4095]
 * and send PWM value in the range [0, 255] to the pin 3.
 * 
 * Here is an example of using the shutdown function of the library.
 * At any normal or emergency shutdown of the program, all Troyka Hat expander pins switch to the 0 state.
 **/

#include <GpioExpanderPi.h>

#include <csignal>
#include <cstdlib>
#include <stdio.h>

constexpr uint8_t GPIO_EXPANDER_POT_PIN = 2;
constexpr uint8_t GPIO_EXPANDER_LED_PIN = 3;

GpioExpanderPi expander;

void programTerminate(int param) {
	printf("Program exit.\n");
	expander.shutdown();
	exit(1);
}

int main(void) {
	signal(SIGINT, programTerminate);
	signal(SIGABRT, programTerminate);
	signal(SIGTERM, programTerminate);
	signal(SIGTSTP, programTerminate);

	if (!expander.begin())
		printf("Failed to init I2C communication.\n");

	for (;;) {
		uint16_t pot_value = expander.analogRead(GPIO_EXPANDER_POT_PIN);

		uint8_t led_value = (float)pot_value / 4095.0 * 255.0;

		expander.analogWrite(GPIO_EXPANDER_LED_PIN, led_value);

		printf("Pot on pin %d has value %d and the led on pin %d is %d\n", GPIO_EXPANDER_POT_PIN, pot_value, GPIO_EXPANDER_LED_PIN, led_value);
	}
	return 0;
}
