#ifndef INC_LIS2MDL_H_
#define INC_LIS2MDL_H_

#include "lis2mdl_config.h"

#if defined(STM32F412Vx) || defined(STM32F446xx)
    #include "stm32f4xx_hal.h"

#elif defined(STM32G030xx) || defined(STM32G0B0xx) || defined(STM32G070xx)
    #include "stm32g0xx_hal.h"

#elif defined(STM32G431xx)
    #include "stm32g4xx_hal.h"

#else
    #error "MCU not supported. Please contact for platform support."
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define LIS2MDL_OFFSET_X_REG_L         0x45U
#define LIS2MDL_OFFSET_X_REG_H         0x46U
#define LIS2MDL_OFFSET_Y_REG_L         0x47U
#define LIS2MDL_OFFSET_Y_REG_H         0x48U
#define LIS2MDL_OFFSET_Z_REG_L         0x49U
#define LIS2MDL_OFFSET_Z_REG_H         0x4AU

#define LIS2MDL_WHO_AM_I               0x4FU
#define LIS2MDL_WHO_AM_I_VALUE         0x40U

#define LIS2MDL_CFG_REG_A              0x60U
#define LIS2MDL_CFG_REG_B              0x61U
#define LIS2MDL_CFG_REG_C              0x62U

#define LIS2MDL_INT_CTRL_REG           0x63U
#define LIS2MDL_INT_SOURCE_REG         0x64U
#define LIS2MDL_INT_THS_L_REG          0x65U
#define LIS2MDL_INT_THS_H_REG          0x66U

#define LIS2MDL_STATUS_REG             0x67U

#define LIS2MDL_OUTX_L_REG             0x68U
#define LIS2MDL_OUTX_H_REG             0x69U
#define LIS2MDL_OUTY_L_REG             0x6AU
#define LIS2MDL_OUTY_H_REG             0x6BU
#define LIS2MDL_OUTZ_L_REG             0x6CU
#define LIS2MDL_OUTZ_H_REG             0x6DU

#define LIS2MDL_TEMP_OUT_L_REG         0x6EU
#define LIS2MDL_TEMP_OUT_H_REG         0x6FU

#define LIS2MDL_MAGNETIC_SENSITIVITY 1.5f
#define LIS2MDL_TEMPERATURE_SENSITIVITY 8.0f

#define LIS2MDL_I2C_TIMEOUT_MS    5U
#define LIS2MDL_SPI_TIMEOUT_MS 	  1U

#define LIS2MDL_I2C_ADDR 0b0011110

typedef enum {
    LIS2MDL_BUS_I2C,
    LIS2MDL_BUS_SPI
} lis2mdl_bus_t;

typedef struct lis2mdl_t
{
    HAL_StatusTypeDef (*write)(struct lis2mdl_t *dev,uint8_t reg, uint8_t *data, uint16_t len);
    HAL_StatusTypeDef (*read)(struct lis2mdl_t *dev,uint8_t reg, uint8_t *data, uint16_t len);

    lis2mdl_bus_t bus;
	
    union {
    #if defined(HAL_I2C_MODULE_ENABLED)
            struct {
                I2C_HandleTypeDef *hi2c;
                GPIO_TypeDef      *int_port;
                uint16_t           int_pin;
            } i2c;
    #endif

    #if defined(HAL_SPI_MODULE_ENABLED)
            struct {
                SPI_HandleTypeDef *hspi;
                GPIO_TypeDef      *cs_port;
                uint16_t           cs_pin;
            } spi;
    #endif
    } bus_cfg;
} lis2mdl_t;

HAL_StatusTypeDef LIS2MDL_Init(lis2mdl_t *dev);
HAL_StatusTypeDef LIS2MDL_Config(lis2mdl_t *dev, lis2mdl_cfg_t *cfg);

HAL_StatusTypeDef LIS2MDL_Read_Config(lis2mdl_t *dev, uint8_t *cfg_a, uint8_t *cfg_b, uint8_t *cfg_c, uint8_t *cfg_int);

HAL_StatusTypeDef LIS2MDL_Interrupt_Config(lis2mdl_t *dev, lis2mdl_int_cfg_t *int_cfg);
HAL_StatusTypeDef LIS2MDL_Read_INT_Source_Register(lis2mdl_t *dev, uint8_t *data);
HAL_StatusTypeDef LIS2MDL_Set_Interrupt_Threshold(lis2mdl_t *dev, uint16_t threshold);
HAL_StatusTypeDef LIS2MDL_Read_Interrupt_Threshold(lis2mdl_t *dev, uint16_t *threshold);

HAL_StatusTypeDef LIS2MDL_Set_Hard_Iron_Registers(lis2mdl_t *dev, float offset_x, float offset_y, float offset_z);
HAL_StatusTypeDef LIS2MDL_Read_Hard_Iron_Registers(lis2mdl_t *dev, float *offset_x, float *offset_y, float *offset_z);

HAL_StatusTypeDef LIS2MDL_Read_Status_Register(lis2mdl_t *dev, uint8_t *data);

HAL_StatusTypeDef LIS2MDL_Read_Magnetic_Data(lis2mdl_t *dev, float *x, float *y, float *z);
HAL_StatusTypeDef LIS2MDL_Read_Temperature(lis2mdl_t *dev, float *temp);
#ifdef __cplusplus
}
#endif

#endif
