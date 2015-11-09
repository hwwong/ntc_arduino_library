/*
  NTC.h - Library for temperture measurement.
  Created by HW Wong , November 8, 2015.
  Released into the public domain.
*/

#include "Arduino.h"
#include "NTC.h"

NTC::NTC(int pin)
{
	_pin = pin;
}

int16_t NTC::readTemperature()
{
	return NTC3435_LUT[analogRead(_pin) + LUT_OFFSET];
}
