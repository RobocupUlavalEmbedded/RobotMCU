/*
 * led.c
 *
 *  Created on: 2016-11-17
 *      Author: Gagnon
 *
 *      Handles communication with LED driver : IS31FL3199
 */

#include "led.h"

static uint8_t led_CTRL1_value = 0x00;
static uint8_t led_CTRL2_value = 0x00;

void led_init(void) {
	uint8_t data = 0x01; //On
	I2C_write(LED_ADDRESS, LED_REG_SHUTDOWN, &data, 1); //Turn on device

	data = LED_PWM;
	uint16_t i = 0;
	for(i = 0; i < 9; i++) {
		const uint16_t reg = (uint16_t)(LED_REG_PWM + i);
		I2C_write(LED_ADDRESS, reg, &data, 1);
	}

	I2C_write(LED_ADDRESS, LED_REG_CTRL1, &led_CTRL1_value, 1); //LED off
	I2C_write(LED_ADDRESS, LED_REG_CTRL2, &led_CTRL2_value, 1); //LED off

	data = 0x00;
	I2C_write(LED_ADDRESS, LED_REG_LOAD_DATA, &data, 1);

	data = LED_CS_10mA; //Current select
	I2C_write(LED_ADDRESS, LED_REG_CONFIG2, &data, 1);

}

void led_swipingLedTest(void) {
	//Testing LEDs
	uint8_t j = 0;
	for(j = 0; j <= 9; j++) {
		led_turnOn(j);
		HAL_Delay(100);
		led_turnOff(j);
	}
}

void led_turnOn(uint8_t ledId) {
	if(ledId >= 0 && ledId <= 2) {
		const uint8_t bitOfLed = (uint8_t)(1 << ledId);
		led_CTRL1_value |= bitOfLed;
		I2C_write(LED_ADDRESS, LED_REG_CTRL1, &led_CTRL1_value, 1);
	} else if(ledId >= 3 && ledId <= 5) {
		const uint8_t bitOfLed = (uint8_t)(1 << (ledId + 1));
		led_CTRL1_value |= bitOfLed;
		I2C_write(LED_ADDRESS, LED_REG_CTRL1, &led_CTRL1_value, 1);
	} else if(ledId <= 8) {
		const uint8_t bitOfLed =  (uint8_t)(1 << (ledId-6));
		led_CTRL2_value |= bitOfLed;
		I2C_write(LED_ADDRESS, LED_REG_CTRL2, &led_CTRL2_value, 1);
	}
	uint8_t data = 0x00;
	I2C_write(LED_ADDRESS, LED_REG_LOAD_DATA, &data, 1);
}

void led_turnOff(uint8_t ledId) {
	if(ledId >= 0 && ledId <= 2) {
		const uint8_t mask = (uint8_t)(1 << ledId);
		led_CTRL1_value &= (uint8_t)~mask;
		I2C_write(LED_ADDRESS, LED_REG_CTRL1, &led_CTRL1_value, 1);
	} else if(ledId >= 3 && ledId <= 5) {
		const uint8_t mask = (uint8_t)(1 << (ledId + 1));
		led_CTRL1_value &= (uint8_t)~mask;
		I2C_write(LED_ADDRESS, LED_REG_CTRL1, &led_CTRL1_value, 1);
	} else if(ledId <= 8) {
		const uint8_t mask = (uint8_t)(1 << (ledId-6));
		led_CTRL2_value &= (uint8_t)~mask;
		I2C_write(LED_ADDRESS, LED_REG_CTRL2, &led_CTRL2_value, 1);
	}
	uint8_t data = 0x00;
	I2C_write(LED_ADDRESS, LED_REG_LOAD_DATA, &data, 1);
}
