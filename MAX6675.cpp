#include <MAX6675.h>

MAX6675::MAX6675(int16_t SSPin)
{
	MAX6675(SSPin, SPI);
}
MAX6675::MAX6675(int16_t SSPin, SPIClass &SSPI)
{
	_SSPin = SSPin;
	_SPI = SSPI;
	pinMode(_SSPin, OUTPUT);
	digitalWrite(_SSPin, HIGH);
	_SPI.begin();
	_lastCallTime = 0;
}

float MAX6675::readTempC()
{
	if (millis() - _lastCallTime >= MAX6675_READ_PERIOD)
	{
		_SPI.beginTransaction(MAX6675_Settings);
		digitalWrite(_SSPin, LOW);
		_incomingMessage = _SPI.transfer16(0x00);
		digitalWrite(_SSPin, HIGH);
		_SPI.endTransaction();
		_lastCallTime = millis();

		if (_incomingMessage & MAX6675_THERMOCOUPLE_OPEN_BIT)
			return MAX6675_THERMOCOUPLE_OPEN;
		_currentTemp = (_incomingMessage >> 3) * MAX6675_CONVERSION_RATIO;
		return _currentTemp;
	}
	return _currentTemp;
}

float MAX6675::readTempF()
{
	return readTempC() * 1.8 + 32;
}