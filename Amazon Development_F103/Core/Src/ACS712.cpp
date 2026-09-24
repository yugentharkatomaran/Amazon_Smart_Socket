/*
 * ACS712.cpp
 *
 *  Created on: 22-Sept-2026
 *      Author: yugi
 */

#include "ACS712.h"
#include <math.h>

#define ADC_MAX_VALUE       4095.0f
#define ADC_REFERENCE       3.3f

#define SAMPLE_COUNT        1000

/*
 * Set this according to your hardware.
 *
 * If ZMCT103 OUT is connected DIRECTLY to STM32 ADC:
 *      VOLTAGE_FACTOR = 1.0
 *
 * If you are using a 1:1 voltage divider:
 *      VOLTAGE_FACTOR = 2.0
 */
#define VOLTAGE_FACTOR      1.0f
/*
 * Noise threshold.
 * Your no-load ADC is around 23 and varies slightly.
 * RMS below this threshold is treated as zero current.
 *
 * Tune later if required.
 */
#define NOISE_THRESHOLD     2.0f

/*
 * Calibration factor.
 *
 * We will determine this experimentally.
 *
 * current = rmsVoltage * CURRENT_CALIBRATION
 *
 * Start with 1.0.
 */
#define CURRENT_CALIBRATION 1.0f

void ACS712::adcInit()
{

	HAL_ADC_Start(&hadc1);

}

void ACS712::adcRead()
{
    uint64_t sum = 0;
    uint64_t sumSquare = 0;

    uint32_t adcValue;

    uint32_t adcMin = 4095;
    uint32_t adcMax = 0;

    /*
     * Take many samples because ZMCT103 output
     * represents an AC waveform.
     */
    for (uint32_t i = 0; i < SAMPLE_COUNT; i++)
    {
        HAL_ADC_Start(&hadc1);

        if (HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
        {
            adcValue = HAL_ADC_GetValue(&hadc1);

            sum += adcValue;

            sumSquare +=
                ((uint64_t)adcValue * (uint64_t)adcValue);

            if (adcValue < adcMin)
            {
                adcMin = adcValue;
            }

            if (adcValue > adcMax)
            {
                adcMax = adcValue;
            }
        }

        HAL_ADC_Stop(&hadc1);
    }


    /*
     * Calculate DC offset / centre point.
     *
     * In your case this may be around:
     *
     *      20 - 25 ADC counts
     */
    float adcAverage =
        (float)sum / (float)SAMPLE_COUNT;


    /*
     * Calculate:
     *
     * RMS = sqrt(E[x²] - E[x]²)
     *
     * This automatically removes the DC offset.
     */
    float meanSquare =
        (float)sumSquare / (float)SAMPLE_COUNT;

    float rmsSquare =
        meanSquare - (adcAverage * adcAverage);

    if (rmsSquare < 0)
    {
        rmsSquare = 0;
    }

    float adcRms = sqrtf(rmsSquare);


    /*
     * Convert RMS ADC counts into RMS voltage.
     */
    float voltageRms =
        adcRms *
        (ADC_REFERENCE / ADC_MAX_VALUE) *
        VOLTAGE_FACTOR;


    /*
     * Remove very small no-load noise.
     */
    if (adcRms < NOISE_THRESHOLD)
    {
        current = 0.0f;
    }
    else
    {
        current =
            voltageRms * CURRENT_CALIBRATION;
    }


    /*
     * Existing variables:
     *
     * readValue  = average ADC value
     * rawVoltage = AC RMS voltage
     * current    = calculated AC RMS current
     */
    readValue = (uint32_t)adcAverage;
    rawVoltage = voltageRms;
}
