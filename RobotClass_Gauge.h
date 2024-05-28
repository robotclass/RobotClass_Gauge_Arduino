/*!
 *  @file RobotClass_Gauge.h
 *  QIIC Led Gauge library
 *  Written by Oleg Evsegneev for RobotClass (2024).
 *  e-mail: oleg.evsegneev@gmail.com
 */
 
#include <Arduino.h>
#include <Wire.h>

#define BASE_I2C_ADDR 0x30

#define I2C_DATA_SIZE 3

#define CMD_GET_VERSION 0xB0	// версия прошивки
#define CMD_GET_SRC 0xB1		// получение источника сигнала
#define CMD_GET_STATE 0xB2		// получение позиции энкодера 0..15
#define CMD_SET_MODE 0xC0		// установка режима
#define CMD_SET_COLOR 0xC1		// установка цвета RGB 0..255,0..255,0..255
#define CMD_SET_BRIGHTNESS 0xC2	// установка яркости 0..31
#define CMD_SET_POT_LPF 0xC3	// установка коэффициента ФНЧ для потенциометра 1..15
#define CMD_SET_ENC_LIMIT 0xC4	// установка предела энкодера
#define CMD_SET_ENC_MAX 0xC5	// установка диапазона энкодера
#define CMD_INIT 0xE0			// инициализация (сброс+обнуление настроек)
#define CMD_RESET 0xE1			// сброс счётчика
#define CMD_RUN_TEST 0xE2		// запуск теста

#define ENC_LIMIT_1 0
#define ENC_LIMIT_2 1
#define ENC_LIMIT_4 2
#define ENC_LIMIT_8 3
#define ENC_LIMIT_16 4
#define ENC_LIMIT_32 5
#define ENC_LIMIT_64 6

#define MODE_FLOOD 0
#define MODE_LEVEL 1
#define MODE_POINT 2

#define SRC_ENC 0
#define SRC_POT 1

class RobotClass_Gauge {
	TwoWire* _wire = NULL;
	uint8_t _addr = BASE_I2C_ADDR;

	uint8_t _status = 0x00;

public:
	RobotClass_Gauge();
	void begin(uint8_t sda, uint8_t scl, uint8_t addr = BASE_I2C_ADDR, TwoWire *wire = &Wire);
	void begin(uint8_t addr = BASE_I2C_ADDR, TwoWire *wire = &Wire);
	void test();
	void reset();
	uint8_t getVersion();
	uint8_t getState(uint16_t *position, uint8_t *button);
	void setMode(uint8_t mode);
	void setColor(uint8_t r, uint8_t g, uint8_t b);
	void setBrightness(uint8_t brightness);
	void setEncLimit(uint8_t value);
	void setEncMax(uint8_t value);
	void setPotLPF(uint8_t value);
	uint8_t i2c_error();

private:
    int8_t read_bytes(const uint8_t reg, uint8_t* data);
    bool write_bytes(const uint8_t reg, const uint8_t* data);
};
