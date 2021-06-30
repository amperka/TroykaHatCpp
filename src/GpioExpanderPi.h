#ifndef __GPIOEXPANDERPI_H__
#define __GPIOEXPANDERPI_H__

#include <stdint.h>

constexpr uint8_t GPIO_EXPANDER_DEFAULT_I2C_ADDRESS = 0X2A;
constexpr uint8_t GPIO_EXPANDER_WHO_AM_I = 0x00;
constexpr uint8_t GPIO_EXPANDER_RESET = 0x01;
constexpr uint8_t GPIO_EXPANDER_CHANGE_I2C_ADDR = 0x02;
constexpr uint8_t GPIO_EXPANDER_SAVE_I2C_ADDR = 0x03;
constexpr uint8_t GPIO_EXPANDER_PORT_MODE_INPUT = 0x04;
constexpr uint8_t GPIO_EXPANDER_PORT_MODE_PULLUP = 0x05;
constexpr uint8_t GPIO_EXPANDER_PORT_MODE_PULLDOWN = 0x06;
constexpr uint8_t GPIO_EXPANDER_PORT_MODE_OUTPUT = 0x07;
constexpr uint8_t GPIO_EXPANDER_DIGITAL_READ = 0x08;
constexpr uint8_t GPIO_EXPANDER_DIGITAL_WRITE_HIGH = 0x09;
constexpr uint8_t GPIO_EXPANDER_DIGITAL_WRITE_LOW = 0x0A;
constexpr uint8_t GPIO_EXPANDER_ANALOG_WRITE = 0x0B;
constexpr uint8_t GPIO_EXPANDER_ANALOG_READ = 0x0C;
constexpr uint8_t GPIO_EXPANDER_PWM_FREQ = 0x0D;
constexpr uint8_t GPIO_EXPANDER_ADC_SPEED = 0x0E;

enum GpioExpanderPinMode {
	GPIO_PIN_INPUT,
	GPIO_PIN_OUTPUT,
	GPIO_PIN_INPUT_PULLUP,
	GPIO_PIN_INPUT_PULLDOWN,
};

class GpioExpanderPi {
public:
	bool begin(uint8_t i2cAddress = GPIO_EXPANDER_DEFAULT_I2C_ADDRESS);

	void pinMode(int pin, GpioExpanderPinMode mode);
	void digitalWrite(int pin, bool value);
	bool digitalRead(int pin);
	uint16_t analogRead(int pin);
	void analogWrite(int pin, uint8_t value);

	void changeAddr(uint8_t i2cAddress);
	void saveAddr();

	void pwmFreq(uint16_t freq);
	void adcSpeed(uint8_t speed);

	void shutdown();

	inline uint16_t reverseUInt16(uint16_t data) {
		return ((data & 0xff) << 8) | ((data >> 8) & 0xff);
	}

private:
	int _fd;

	uint16_t _digitalReadPort();
};

#endif //__GPIOEXPANDERPI_H__
