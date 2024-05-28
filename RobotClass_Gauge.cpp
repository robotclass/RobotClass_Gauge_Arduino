/*!
 *  @file RobotClass_Gauge.cpp
 *  QIIC Led Gauge library
 *  Written by Oleg Evsegneev for RobotClass (2024).
 *  e-mail: oleg.evsegneev@gmail.com
 */
#include "RobotClass_Gauge.h"

RobotClass_Gauge::RobotClass_Gauge(){
}

void RobotClass_Gauge::begin(uint8_t sda, uint8_t scl, uint8_t addr, TwoWire *wire){
	_wire = wire;
	_addr = addr;

	_wire->begin(sda, scl);
}

void RobotClass_Gauge::begin(uint8_t addr, TwoWire *wire){
	_wire = wire;
	_addr = addr;
	
	_wire->begin();
}

void RobotClass_Gauge::test(){
	uint8_t data[I2C_DATA_SIZE];
	write_bytes(CMD_RUN_TEST, data);
}

void RobotClass_Gauge::reset(){
	uint8_t data[I2C_DATA_SIZE];
	write_bytes(CMD_RESET, data);
}

uint8_t RobotClass_Gauge::getVersion(){
	uint8_t data[I2C_DATA_SIZE+1];
	uint8_t count = read_bytes(CMD_GET_VERSION, data);
	return data[0];
}

uint8_t RobotClass_Gauge::getState(uint16_t *position, uint8_t *button) {
	uint8_t data[I2C_DATA_SIZE+1];
	uint8_t count = read_bytes(CMD_GET_STATE, data);

	*position = data[0] | (data[1]<<8);
	*button = data[2];

	return count;
}

void RobotClass_Gauge::setMode(uint8_t mode){
	uint8_t data[I2C_DATA_SIZE];
	data[0] = mode;

	write_bytes(CMD_SET_MODE, data);
}

void RobotClass_Gauge::setColor(uint8_t r, uint8_t g, uint8_t b){
	uint8_t data[I2C_DATA_SIZE];
	data[0] = r;
	data[1] = g;
	data[2] = b;

	write_bytes(CMD_SET_COLOR, data);
}

void RobotClass_Gauge::setBrightness(uint8_t value){
	uint8_t data[I2C_DATA_SIZE];
	data[0] = value;

	write_bytes(CMD_SET_BRIGHTNESS, data);
}

void RobotClass_Gauge::setEncLimit(uint8_t value){
	uint8_t data[I2C_DATA_SIZE];
	data[0] = value;

	write_bytes(CMD_SET_ENC_LIMIT, data);
}

void RobotClass_Gauge::setEncMax(uint8_t value){
	uint8_t data[I2C_DATA_SIZE];
	data[0] = value;

	write_bytes(CMD_SET_ENC_MAX, data);
}

void RobotClass_Gauge::setPotLPF(uint8_t value){
	uint8_t data[I2C_DATA_SIZE];
	data[0] = value;

	write_bytes(CMD_SET_POT_LPF, data);
}

uint8_t RobotClass_Gauge::i2c_error() {
	return _status;
}

int8_t RobotClass_Gauge::read_bytes(const uint8_t reg, uint8_t* data) {
	_wire->beginTransmission(_addr);
	_wire->write(reg);
	_wire->write(0x00);
	_wire->write(0x00);
	_wire->write(0x00);
	_wire->endTransmission();
	_wire->requestFrom(_addr, I2C_DATA_SIZE+1);
	int8_t count = 0;
	while (_wire->available()) data[count++] = _wire->read();
	return count;
}

bool RobotClass_Gauge::write_bytes(const uint8_t reg, const uint8_t* data) {
	_wire->beginTransmission(_addr);
	_wire->write(reg);
	for (uint8_t i = 0; i < I2C_DATA_SIZE-1; i++) _wire->write(data[i]);
	_status = _wire->endTransmission();
	return (_status == 0);
}