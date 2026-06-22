const float PRESSURE_MAX = 160.0f;
const float PRESSURE_MIN = 0.0f;

/**
 * @brief Get the pressure value from the sensor reading in millibars.
 *
 * @param sensorValue the two bytes read from the sensor combined into a 16-bit integer
 * @return float the pressure value in millibars
 */
float getPressure(uint16_t sensorValue)
{
  float pressureApplied = 0.0f;
  float output = (float)sensorValue / 16383.0;
  pressureApplied = ((output - 0.1) * (PRESSURE_MAX - PRESSURE_MIN)) / (0.8) + PRESSURE_MIN;

  return pressureApplied;
}

/**
 * @brief Convert the pressure value from millibars to mmHg.
 *
 * @param pressure the pressure value in millibars
 * @return float the pressure value in mmHg
 */
float convertPressure(float pressure)
{
  float convertedPressure = 0.0f;
  convertedPressure = pressure * 0.750062f;

  return convertedPressure;
}