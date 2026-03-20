#ifndef INC_LIS2MDL_H_
#define INC_LIS2MDL_H_

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

#define I2C_ADDR 0b0011110

#define LIS2MDL_MAGNETIC_SENSITIVITY 1.5f
#define LIS2MDL_TEMPERATURE_SENSITIVITY 8.0f

/* Configuration Register A */
typedef enum {
    LIS2MDL_TEMP_COMP_DISABLE = 0,
    LIS2MDL_TEMP_COMP_ENABLE  = 1
} lis2mdl_temp_comp_t;

typedef enum {
    LIS2MDL_NORMAL = 0,
    LIS2MDL_REBOOT_ENABLE  = 1
} lis2mdl_reboot_t;

typedef enum {
    LIS2MDL_SOFT_RESET_DISABLE = 0,
    LIS2MDL_SOFT_RESET_ENABLE  = 1
} lis2mdl_soft_reset_t;

typedef enum {
    LIS2MDL_HIGH_RES = 0,
    LIS2MDL_LOW_POWER    = 1
} lis2mdl_power_mode_t;

typedef enum {
    LIS2MDL_ODR_10HZ  = 0,
    LIS2MDL_ODR_20HZ  = 1,
    LIS2MDL_ODR_50HZ  = 2,
    LIS2MDL_ODR_100HZ = 3
} lis2mdl_odr_t;

typedef enum {
    LIS2MDL_MODE_CONTINUOUS = 0,
    LIS2MDL_MODE_SINGLE     = 1,
    LIS2MDL_MODE_IDLE       = 2
} lis2mdl_mode_t;

/* Configuration Register B */
typedef enum {
		LIS2MDL_SINGLE_MODE_OFFSET_CANC_DISABLE = 0,
    LIS2MDL_SINGLE_MODE_OFFSET_CANC_ENABLE  = 1
   
} lis2mdl_offset_canc_one_shot_t;

typedef enum {
    LIS2MDL_INT_DATA_OFF_DISABLE = 0,
    LIS2MDL_INT_DATA_OFF_ENABLE  = 1
} lis2mdl_int_data_off_t;

typedef enum {
    LIS2MDL_SET_FREQ_ODR_2  = 0,
    LIS2MDL_SET_FREQ_ODR_4 = 1
} lis2mdl_set_freq_t;

typedef enum {
    LIS2MDL_OFFSET_CANC_DISABLE = 0,
    LIS2MDL_OFFSET_CANC_ENABLE  = 1
} lis2mdl_off_canc_t;

typedef enum {
    LIS2MDL_LPF_DISABLE = 0,
    LIS2MDL_LPF_ENABLE  = 1
} lis2mdl_lpf_t;

/* Configuration Register C */
typedef enum {
    LIS2MDL_INT_ON_DISABLE  = 0,
    LIS2MDL_INT_ON_DRDY_PIN = 1
} lis2mdl_int_pin_t;

typedef enum {
    LIS2MDL_I2C_ENABLE  = 0,
    LIS2MDL_I2C_DISABLE = 1
} lis2mdl_i2c_disable_t;

typedef enum {
    LIS2MDL_BDU_DISABLE = 0,
    LIS2MDL_BDU_ENABLE     = 1
} lis2mdl_bdu_t;

typedef enum {
    LIS2MDL_LSB_FIRST = 0,
    LIS2MDL_MSB_FIRST = 1
} lis2mdl_ble_t;

typedef enum {
    LIS2MDL_SPI_3WIRE = 0,
    LIS2MDL_SPI_4WIRE = 1
} lis2mdl_spi_mode_t;

typedef enum {
    LIS2MDL_SELF_TEST_DISABLE = 0,
    LIS2MDL_SELF_TEST_ENABLE  = 1
} lis2mdl_self_test_t;

typedef enum {
    LIS2MDL_DRDY_DISABLE = 0,
    LIS2MDL_DRDY_ENABLE  = 1
} lis2mdl_drdy_t;

/* Interrupt Control Register */
typedef enum{
	LIS2MDL_AXIS_INTERRUPT_DISABLE = 0,
	LIS2MDL_AXIS_INTERRUPT_ENABLE = 1,
}lis2mdl_axis_int_t;

typedef enum {
    LIS2MDL_INT_ACTIVE_LOW  = 0,
    LIS2MDL_INT_ACTIVE_HIGH = 1
} lis2mdl_int_polarity_t;

typedef enum {
    LIS2MDL_INT_PULSED = 0,
    LIS2MDL_INT_LATCHED = 1
} lis2mdl_int_latch_t;

typedef enum {
    LIS2MDL_INT_DISABLE = 0,
    LIS2MDL_INT_ENABLE  = 1
} lis2mdl_int_enable_t;

typedef struct lis2mdl_t
{
    HAL_StatusTypeDef (*write)(struct lis2mdl_t *dev,uint8_t reg, uint8_t *data, uint16_t len);
    HAL_StatusTypeDef (*read)(struct lis2mdl_t *dev,uint8_t reg, uint8_t *data, uint16_t len);
	
		SPI_HandleTypeDef *hspi;
    GPIO_TypeDef *cs_port;
    uint16_t cs_pin;
	
		I2C_HandleTypeDef *hi2c;
    GPIO_TypeDef *i2c_int_port;
    uint16_t i2c_int_pin;

} lis2mdl_t;

typedef struct{
		lis2mdl_temp_comp_t temp_comp;
    lis2mdl_reboot_t reboot;
    lis2mdl_soft_reset_t soft_reset;
    lis2mdl_power_mode_t power;
    lis2mdl_odr_t odr;
    lis2mdl_mode_t mode;
	
		lis2mdl_offset_canc_one_shot_t one_shot;
		lis2mdl_int_data_off_t interrupt;
		lis2mdl_set_freq_t freq;
    lis2mdl_off_canc_t offset_canc;
    lis2mdl_lpf_t lpf;
	
	  lis2mdl_int_pin_t int_drdy;
		lis2mdl_i2c_disable_t i2c_dis;
    lis2mdl_bdu_t bdu;
		lis2mdl_ble_t end;
    lis2mdl_spi_mode_t spi_mode;
	  lis2mdl_self_test_t self_test;
		lis2mdl_drdy_t drdy;
} lis2mdl_cfg_t;

typedef struct
{
    lis2mdl_axis_int_t x_enable;
    lis2mdl_axis_int_t y_enable;
    lis2mdl_axis_int_t z_enable;

    lis2mdl_int_polarity_t polarity;
    lis2mdl_int_latch_t latch;

    lis2mdl_int_enable_t global_enable;

} lis2mdl_int_cfg_t;

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