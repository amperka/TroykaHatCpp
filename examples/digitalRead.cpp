/** 
 * The digitalRead example.
 *
 * The program continuously reads the pin 1 state and send the message on state change.
 **/

#include <GpioExpanderPi.h>
#include <stdio.h>

constexpr uint8_t GPIO_EXPANDER_BUTTON_PIN = 1;

GpioExpanderPi expander;

int main(void) {
	if (!expander.begin())
		printf("Failed to init I2C communication.\n");

	expander.pinMode(GPIO_EXPANDER_BUTTON_PIN, GPIO_PIN_INPUT);

	bool previousButtonState = true;

	for (;;) {
		bool state = expander.digitalRead(GPIO_EXPANDER_BUTTON_PIN);
		if (state != previousButtonState) {
			previousButtonState = state;
			printf("Button state on pin %d changed to %d\n", GPIO_EXPANDER_BUTTON_PIN, state);
		}
	}
	return 0;
}
