/*
 * nrfDriver.h
 *
 *  Created on: Nov 18, 2016
 *      Author: znuxor
 */

#ifndef NRFDRIVER_NRFDRIVER_H_
#define NRFDRIVER_NRFDRIVER_H_

#include "stm32f4xx.h"

void nrfInit(const size_t packetSize);
void nrfSend(uint8_t * dataOut);
void nrfReceive(uint8_t * dataIn);
uint8_t nrfRetransmitCount(void);
uint8_t nrfGetStatus(void);

#endif /* NRFDRIVER_NRFDRIVER_H_ */
