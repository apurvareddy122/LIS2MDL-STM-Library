# LIS2MDL-STM-Library
C driver for the STMicroelectronics LIS2MDL 3-axis digital magnetic sensor.

### Sample Usage (I2C Example)
```
#include "lis2mdl.h"

lis2mdl_t mg_dev;
lis2mdl_cfg_t mg_cfg;

void System_Init(void) {

    mg_dev.bus = LIS2MDL_BUS_I2C;
    mg_dev.bus_cfg.i2c.hi2c = &hi2c2;

    if (LIS2MDL_Init(&mg_dev) != HAL_OK) {
        Error_Handler();
    }

    mg_cfg.mode = LIS2MDL_MODE_CONTINUOUS;
    mg_cfg.odr = LIS2MDL_ODR_50HZ;
    mg_cfg.power = LIS2MDL_HIGH_RES;
    mg_cfg.temp_comp = LIS2MDL_TEMP_COMP_ENABLE;
    mg_cfg.bdu = LIS2MDL_BDU_ENABLE;

    LIS2MDL_Config(&mg_dev, &mg_cfg);
}

void Loop(void) {
    float x, y, z;
    if (LIS2MDL_Read_Magnetic_Data(&mg_dev, &x, &y, &z) == HAL_OK) {

        printf(" X: %.2fmG, Y: %.2fmG, Z: %.2fmG\r\n", x, y, z);
    }
    HAL_Delay(20);
}
```
### Hard - Iron Compensation
Hard-iron distortion is caused by permanent magnets or magnetized steel near the sensor. This shifts the magnetic "sphere" away from the origin.
##### Calibration:
1. Collect Data: Rotate your device in 3D space while logging raw $x, y, z$ values.
2. Identify the maximum and minimum values recorded for each axis.
3. **Offest = (maximum + minimum)/2** for each axis.
4. Store the offsets in hard iron registers, use the **LIS2MDL_Set_Hard_Iron_Registers** API.
