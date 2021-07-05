#include "GpioExpanderPi.h"
#include <wiringPiI2C.h>

bool GpioExpanderPi::begin(uint8_t i2cAddress) {
	int fd = wiringPiI2CSetup(i2cAddress);
	if (fd == -1)
		return false;
	_fd = fd;
	return true;
}

void GpioExpanderPi::digitalWrite(int pin, bool value) {
	uint16_t sendData = reverseUInt16(0x0001 << pin);
	wiringPiI2CWriteReg16(_fd, value ? GPIO_EXPANDER_DIGITAL_WRITE_HIGH : GPIO_EXPANDER_DIGITAL_WRITE_LOW, sendData);
}

bool GpioExpanderPi::digitalRead(int pin) {
	return (_digitalReadPort() & (0x0001 << pin)) ? 1 : 0;
}

uint16_t GpioExpanderPi::_digitalReadPort() {
	return reverseUInt16(wiringPiI2CReadReg16(_fd, GPIO_EXPANDER_DIGITAL_READ));
}

uint16_t GpioExpanderPi::analogRead(int pin) {
	wiringPiI2CWriteReg16(_fd, GPIO_EXPANDER_ANALOG_READ, pin);
	return reverseUInt16(wiringPiI2CReadReg16(_fd, GPIO_EXPANDER_DIGITAL_READ));
}

void GpioExpanderPi::analogWrite(int pin, uint8_t value) {
	uint16_t sendData = (pin & 0xff) | ((value & 0xff) << 8);
	wiringPiI2CWriteReg16(_fd, GPIO_EXPANDER_ANALOG_WRITE, sendData);
}

void GpioExpanderPi::changeAddr(uint8_t i2cAddress) {
	wiringPiI2CWriteReg16(_fd, GPIO_EXPANDER_CHANGE_I2C_ADDR, i2cAddress);
}

void GpioExpanderPi::saveAddr() {
	wiringPiI2CWrite(_fd, GPIO_EXPANDER_SAVE_I2C_ADDR);
}

void GpioExpanderPi::pwmFreq(uint16_t freq) {
	wiringPiI2CWriteReg16(_fd, GPIO_EXPANDER_PWM_FREQ, reverseUInt16(freq));
}

void GpioExpanderPi::adcSpeed(uint8_t speed) {
	wiringPiI2CWriteReg8(_fd, GPIO_EXPANDER_ADC_SPEED, speed);
}

void GpioExpanderPi::pinMode(int pin, GpioExpanderPinMode mode) {
	uint16_t sendData = reverseUInt16(0x0001 << pin);
	uint8_t portModeRegister;
	if (mode == GPIO_PIN_INPUT)
		portModeRegister = GPIO_EXPANDER_PORT_MODE_INPUT;
	else if (mode == GPIO_PIN_INPUT_PULLUP)
		portModeRegister = GPIO_EXPANDER_PORT_MODE_PULLUP;
	else if (mode == GPIO_PIN_INPUT_PULLDOWN)
		portModeRegister = GPIO_EXPANDER_PORT_MODE_PULLDOWN;
	else if (mode == GPIO_PIN_OUTPUT)
		portModeRegister = GPIO_EXPANDER_PORT_MODE_OUTPUT;
	wiringPiI2CWriteReg16(_fd, portModeRegister, sendData);
}

void GpioExpanderPi::shutdown() {
	for (uint8_t i = 0; i < 8; i++) {
		pinMode(i, GPIO_PIN_OUTPUT);
		digitalWrite(i, false);
	}
}
