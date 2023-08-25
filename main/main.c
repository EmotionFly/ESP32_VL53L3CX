
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "esp_log.h"
#include "i2cdev.h"
#include "vl53l1x.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

static VL53L1_Dev_t dev;

#define TAG "VL53L3CX"

static const I2cDef I2CConfig = {
    .i2cPort            = I2C_NUM_0,
    .i2cClockSpeed      = 400000,
    .gpioSCLPin         = 22,
    .gpioSDAPin         = 21,
    .gpioPullup         = GPIO_PULLUP_ENABLE,
};

I2cDrv i2cBus = {
    .def                = &I2CConfig,
};

VL53L1_Error status = VL53L1_ERROR_NONE;
VL53L1_RangingMeasurementData_t rangingData;
uint8_t dataReady = 0;
uint16_t range;

void app_main(void)
{
    if (vl53l1xInit(&dev, &i2cBus))
    {
        ESP_LOGI(TAG,"Lidar Sensor VL53L3CX [OK].");
    }
    else
    {
        ESP_LOGI(TAG,"Lidar Sensor VL53L3CX [FAIL].");
        return;
    }

    VL53L1_StopMeasurement(&dev);
    VL53L1_SetDistanceMode(&dev, VL53L1_DISTANCEMODE_LONG);
    VL53L1_SetMeasurementTimingBudgetMicroSeconds(&dev, 25000);

    while(1)
    {
        VL53L1_StartMeasurement(&dev);

        while (dataReady == 0)
        {
            status = VL53L1_GetMeasurementDataReady(&dev, &dataReady);
            vTaskDelay(pdMS_TO_TICKS(1));
        }

        status = VL53L1_GetRangingMeasurementData(&dev, &rangingData);
        range = rangingData.RangeMilliMeter;

        VL53L1_StopMeasurement(&dev);

        VL53L1_StartMeasurement(&dev);

        printf("VL53L3CX Distance:  %dmm\n",range);

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
