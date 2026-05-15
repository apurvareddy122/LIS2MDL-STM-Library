/*
 * lis2mdl_config.h
 *
 *  Created on: May 15, 2026
 *      Author: apurvaa
 */

#ifndef INC_LIS2MDL_CONFIG_H_
#define INC_LIS2MDL_CONFIG_H_

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

#endif /* INC_LIS2MDL_CONFIG_H_ */
