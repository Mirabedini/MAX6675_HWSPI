#include <SPI.h>

#define MAX6675_Settings (SPISettings(1000000, MSBFIRST, SPI_MODE1))
#define MAX6675_THERMOCOUPLE_OPEN_BIT 0x04
#define MAX6675_THERMOCOUPLE_OPEN -1.0
#define MAX6675_READ_PERIOD 250
#define MAX6675_CONVERSION_RATIO 0.25

class MAX6675
{
private:
	uint32_t _lastCallTime;
	int16_t _SSPin;
	uint16_t _incomingMessage;
	float _currentTemp;
	SPIClass _SPI;

public:
	MAX6675(int16_t SSPin);
	MAX6675(int16_t SSPin, SPIClass &SSPI);
	float readTempC();
	float readTempF();
};