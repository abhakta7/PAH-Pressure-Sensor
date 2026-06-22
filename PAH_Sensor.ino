#include <Wire.h>
#include <string>
#include "pressure_converter.h"

const uint8_t ADDRESS = 0x28;    // contains the I2C address of the Honeywell HSCMANV160MG2A3
const int DELAY_INTERVAL = 1000; // sets that the sensor should read a value every 1000 ms
const int INTERVAL = 1;          // defines that each interval will be 1 s
int numberOfSeconds = 0;         // counts how many seconds the sensor has been active for

/**
 * @brief Initializes the connection to the sensor and Serial, and waits for Serial connection to be established.
 *
 */
void setup()
{
  Wire.begin();       // intializes connection to the sensor
  Serial.begin(9600); // establishes connection to Serial

  while (!Serial)
  {
    Serial.println("Waiting for Serial connection");
  }
}

/**
 * @brief Reads the sensor value every second, converts it to mmHg, and prints the pressure value and time elapsed to Serial.
 */
void loop()
{
  uint8_t bytesRecieved = Wire.requestFrom(ADDRESS, 2); // requests 2 bytes of data from the sensor and saves the number of bytes received

  if (bytesRecieved == 2)
  {
    uint8_t msb = Wire.read(); // saves the first byte from the sensor
    uint8_t lsb = Wire.read(); // saves the second byte from the sensor

    uint16_t sensorValue = (msb << 8) | lsb; // combines the two bytes into a 16-bit integer
    sensorValue = sensorValue & 0x3FFF;      // applies a bitmask to the sensor value to ignore the status bits

    float pressureValue = getPressure(sensorValue); // converts the sensor value to a pressure value in millibars
    pressureValue = convertPressure(pressureValue); // converts the pressure value from millibars to mmHg

    numberOfSeconds += INTERVAL; // increments the number of seconds the sensor has been active for by the defined interval

    // prints the pressure value and time elapsed to Serial
    Serial.print("Pressure: ");
    Serial.print(pressureValue);
    Serial.print("      ");
    Serial.print("Time: ");
    Serial.println(numberOfSeconds);
  }
  else
  {
    Serial.print("Failed to read sensor."); // prints an error message to Serial if the sensor value could not be read
  }

  delay(DELAY_INTERVAL); // waits for the defined delay interval before reading the sensor value again
}
