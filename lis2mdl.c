#include "lis2mdl.h"

/*SPI Functions*/
static HAL_StatusTypeDef LIS2MDL_SPI_Write(lis2mdl_t *dev, uint8_t reg, uint8_t *data, uint16_t len)
{
	HAL_StatusTypeDef ret;

	uint8_t header = (reg & 0x7F) << 1;

	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
	
	ret = HAL_SPI_Transmit(dev->hspi, &header, 1, 1000);
	if (ret != HAL_OK){
		HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
		return ret;
	}
	
	ret = HAL_SPI_Transmit(dev->hspi, data, len, 1000);
	if (ret != HAL_OK){
		HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
		return ret;
	}
	
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
	
	return HAL_OK;
}

static HAL_StatusTypeDef LIS2MDL_SPI_Read(lis2mdl_t *dev, uint8_t reg, uint8_t *data, uint16_t len)
{
	HAL_StatusTypeDef ret;
	uint8_t header = ((reg & 0x7F) << 1) | 0x01;
	
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_RESET);
	
	ret = HAL_SPI_Transmit(dev->hspi, &header, 1, 1000);
	if (ret != HAL_OK){
		HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
		return ret;
	}
	
	ret = HAL_SPI_Receive(dev->hspi, data, len, 1000);
	if (ret != HAL_OK){
		HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
		return ret;
	}
	
	HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
	
	return HAL_OK;
}

static HAL_StatusTypeDef LIS2MDL_SPI_Init(lis2mdl_t *dev)
{

	dev->read = LIS2MDL_SPI_Read;
	dev->write = LIS2MDL_SPI_Write;
	
	return HAL_OK;
}

/*I2C Functions*/
static HAL_StatusTypeDef LIS2MDL_I2C_Write(lis2mdl_t *dev,uint8_t reg, uint8_t *data, uint16_t len)
{
	HAL_StatusTypeDef ret;
	ret = HAL_I2C_Mem_Write(dev->hi2c,I2C_ADDR << 1,reg,I2C_MEMADD_SIZE_8BIT,data,len,1000);
	if (ret != HAL_OK) return ret;
	
	return HAL_OK;
}

static HAL_StatusTypeDef LIS2MDL_I2C_Read(lis2mdl_t *dev,uint8_t reg, uint8_t *data, uint16_t len)
{
	HAL_StatusTypeDef ret;
	
	ret = HAL_I2C_Mem_Read(dev->hi2c,I2C_ADDR << 1,reg,I2C_MEMADD_SIZE_8BIT,data,len,1000);
	if (ret != HAL_OK) return ret;
	
	return HAL_OK;
}

static HAL_StatusTypeDef LIS2MDL_I2C_Init(lis2mdl_t *dev)
{
	
	
	dev->read = LIS2MDL_I2C_Read;
	dev->write = LIS2MDL_I2C_Write;
	
	if(dev->hi2c && dev->cs_port)
	{
		HAL_GPIO_WritePin(dev->cs_port, dev->cs_pin, GPIO_PIN_SET);
	}
	
	return HAL_OK;
}

static HAL_StatusTypeDef LIS2MDL_Read(lis2mdl_t *dev, uint8_t reg, uint8_t *data,uint16_t len)
{
    if (dev == NULL || dev->read == NULL || data == NULL) return HAL_ERROR;

    return dev->read(dev, reg, data, len);
}

static HAL_StatusTypeDef LIS2MDL_Write(lis2mdl_t *dev, uint8_t reg, uint8_t *data,uint16_t len)
{
    if (dev == NULL || dev->write == NULL || data == NULL) return HAL_ERROR;
		
		if((reg >= 0x4B && reg <= 0x4C) || (reg >= 0x50 && reg <= 0x5F) || (reg == 0x4F || reg == 0x64) || (reg >= 0x67 && reg <= 0x6F)) return HAL_ERROR;

    return dev->write(dev, reg, data, len);
}

HAL_StatusTypeDef LIS2MDL_Init(lis2mdl_t *dev)
{
	HAL_StatusTypeDef ret;
	uint8_t who;
	
	if(dev == NULL) return HAL_ERROR;
	
	if (dev->hi2c && dev->hspi) return HAL_ERROR;
	if(!dev->hi2c && !dev->hspi) return HAL_ERROR;
	
	if(dev->hi2c){
		ret = LIS2MDL_I2C_Init(dev);
		if(ret!=HAL_OK) return ret;
	} else if (dev->hspi){
		ret = LIS2MDL_SPI_Init(dev);	
		if(ret!=HAL_OK) return ret;		
	}
	
	ret = LIS2MDL_Read(dev, LIS2MDL_WHO_AM_I, &who, 1);
	if (ret != HAL_OK || who != LIS2MDL_WHO_AM_I_VALUE) return HAL_ERROR;
	
	return HAL_OK;
}	 

HAL_StatusTypeDef LIS2MDL_Config(lis2mdl_t *dev, lis2mdl_cfg_t *cfg)
{
	HAL_StatusTypeDef ret;
	
	if (dev == NULL || cfg == NULL) return HAL_ERROR;
	
	if ((cfg->int_drdy == LIS2MDL_INT_ON_DRDY_PIN) && (cfg->drdy == LIS2MDL_DRDY_ENABLE)) return HAL_ERROR;
	
	if(dev->hi2c)
	{
		if ((cfg->spi_mode == LIS2MDL_SPI_4WIRE)||(cfg->i2c_dis == LIS2MDL_I2C_DISABLE)) return HAL_ERROR;
	}
	uint8_t data[3];
	
	data[0] = (((cfg->temp_comp & 0x01) << 7) | ((cfg->reboot & 0x01) << 6) | ((cfg->soft_reset & 0x01) << 5) | ((cfg->power & 0x01) << 4) | ((cfg->odr & 0x03) << 2) | (cfg->mode & 0x03));
	data[1] = (((cfg->one_shot & 0x01) << 4) | ((cfg->interrupt & 0x01) << 3) | ((cfg->freq & 0x01) << 2) | ((cfg->offset_canc & 0x01) << 1) | (cfg->lpf & 0x01));
	data[2] = (((cfg->int_drdy & 0x01) << 6) | ((cfg->i2c_dis & 0x01) << 5) | ((cfg->bdu & 0x01) << 4) | ((cfg->end & 0x01) << 3) | ((cfg->spi_mode & 0x01) << 2) | ((cfg->self_test & 0x01) << 1) | (cfg->drdy & 0x01));
	
	ret = LIS2MDL_Write(dev, LIS2MDL_CFG_REG_A, data, 3);
	if (ret != HAL_OK) return ret;
	
	return HAL_OK;
}

HAL_StatusTypeDef LIS2MDL_Interrupt_Config(lis2mdl_t *dev, lis2mdl_int_cfg_t *int_cfg)
{
	HAL_StatusTypeDef ret;
	uint8_t data;
	
	if (dev == NULL || int_cfg == NULL) return HAL_ERROR;
	
	if(dev->hi2c && int_cfg->global_enable && dev->i2c_int_port == NULL) return HAL_ERROR;
	
	data = (((int_cfg->x_enable & 0x01) << 7) | ((int_cfg->y_enable & 0x01) << 6) | ((int_cfg->z_enable& 0x01) << 5) | ((int_cfg->polarity & 0x01) << 2) | ((int_cfg->latch & 0x01) << 1) | (int_cfg->global_enable & 0x01));
	
	ret = LIS2MDL_Write(dev, LIS2MDL_INT_CTRL_REG , &data, 1);
	if (ret != HAL_OK) return ret;
	
	return HAL_OK;
}

HAL_StatusTypeDef LIS2MDL_Read_Config(lis2mdl_t *dev, uint8_t *cfg_a, uint8_t *cfg_b, uint8_t *cfg_c, uint8_t *cfg_int)
{
	HAL_StatusTypeDef ret;
	uint8_t data[4];
	
	if (dev == NULL) return HAL_ERROR;
	
	ret = LIS2MDL_Read(dev, LIS2MDL_CFG_REG_A, data, 4);
	if (ret != HAL_OK) return ret;
	
	*cfg_a = data[0];
	*cfg_b = data[1];
	*cfg_c = data[2];
	*cfg_int = data[3];
	
	return HAL_OK;
}

HAL_StatusTypeDef LIS2MDL_Set_Hard_Iron_Registers(lis2mdl_t *dev, float offset_x, float offset_y, float offset_z)
{
	HAL_StatusTypeDef ret;
	uint8_t data[6];
	
	if (dev == NULL) return HAL_ERROR;
	
	int16_t raw_x = (int16_t)(offset_x / LIS2MDL_MAGNETIC_SENSITIVITY);
	int16_t raw_y = (int16_t)(offset_y / LIS2MDL_MAGNETIC_SENSITIVITY);
	int16_t raw_z = (int16_t)(offset_z / LIS2MDL_MAGNETIC_SENSITIVITY);

	data[0] = (uint8_t)(raw_x & 0xFF);
	data[1] = (uint8_t)((raw_x >> 8) & 0xFF);
	data[2] = (uint8_t)(raw_y & 0xFF);
	data[3] = (uint8_t)((raw_y >> 8) & 0xFF);
	data[4] = (uint8_t)(raw_z & 0xFF);
	data[5] = (uint8_t)((raw_z >> 8) & 0xFF);
	
	ret = LIS2MDL_Write(dev, LIS2MDL_OFFSET_X_REG_L, data, 6);
	if (ret != HAL_OK) return ret;
	
	return HAL_OK;
}
HAL_StatusTypeDef LIS2MDL_Read_Hard_Iron_Registers(lis2mdl_t *dev, float *offset_x, float *offset_y, float *offset_z)
{
	HAL_StatusTypeDef ret;
	uint8_t data[6];
	
	if(dev == NULL) return HAL_ERROR;
	
	ret = LIS2MDL_Read(dev,LIS2MDL_OFFSET_X_REG_L,data,6);
	if (ret != HAL_OK) return ret;
	
	*offset_x = (int16_t)((data[1]<<8)|data[0]);
	*offset_y = (int16_t)((data[3]<<8)|data[2]);
	*offset_z = (int16_t)((data[5]<<8)|data[4]);
	
	*offset_x *= LIS2MDL_MAGNETIC_SENSITIVITY;
	*offset_y *= LIS2MDL_MAGNETIC_SENSITIVITY;
	*offset_z *= LIS2MDL_MAGNETIC_SENSITIVITY;
	
	return HAL_OK;
}
	
HAL_StatusTypeDef LIS2MDL_Read_INT_Source_Register(lis2mdl_t *dev, uint8_t *data)
{
	HAL_StatusTypeDef ret;
	
	if(dev == NULL) return HAL_ERROR;
	
	ret = LIS2MDL_Read(dev,LIS2MDL_INT_SOURCE_REG,data,1);
	if (ret != HAL_OK) return ret;
	
	return HAL_OK;
}

HAL_StatusTypeDef LIS2MDL_Set_Interrupt_Threshold(lis2mdl_t *dev, uint16_t threshold)
{
	HAL_StatusTypeDef ret;
	uint8_t ths[2];
	
	if(dev == NULL) return HAL_ERROR;
	
	ths[0] = (uint8_t)(threshold & 0xFF);
	ths[1] = (uint8_t)((threshold  >> 8)& 0xFF);
	
	ret = LIS2MDL_Write(dev, LIS2MDL_INT_THS_L_REG, ths, 2);
	if (ret != HAL_OK) return ret;
	
	return HAL_OK;
}

HAL_StatusTypeDef LIS2MDL_Read_Interrupt_Threshold(lis2mdl_t *dev, uint16_t *threshold)
{
	HAL_StatusTypeDef ret;
	uint8_t ths[2];
	
	if(dev == NULL) return HAL_ERROR;
	
	ret = LIS2MDL_Read(dev, LIS2MDL_INT_THS_L_REG, ths, 2);
	if (ret != HAL_OK) return ret;
	
	*threshold = (uint16_t)((ths[1]<<8) | ths[0]);
	
	return HAL_OK;
}

HAL_StatusTypeDef LIS2MDL_Read_Status_Register(lis2mdl_t *dev, uint8_t *data)
{
	HAL_StatusTypeDef ret;
	
	if(dev == NULL) return HAL_ERROR;
	
	ret = LIS2MDL_Read(dev,LIS2MDL_STATUS_REG,data,1);
	if (ret != HAL_OK) return ret;
	
	return HAL_OK;
}

HAL_StatusTypeDef LIS2MDL_Read_Magnetic_Data(lis2mdl_t *dev, float *x, float *y, float *z)
{
	HAL_StatusTypeDef ret;
	uint8_t data[6];
	int16_t raw;
	
	if(dev == NULL) return HAL_ERROR;
	
	ret = LIS2MDL_Read(dev,LIS2MDL_OUTX_L_REG,data,6);
	if (ret != HAL_OK) return ret;
	
	raw = (data[1]<<8)|data[0];
	*x = raw * LIS2MDL_MAGNETIC_SENSITIVITY;
	raw = (data[3]<<8)|data[2];
	*y = raw * LIS2MDL_MAGNETIC_SENSITIVITY;
	raw = (data[5]<<8)|data[4];
	*z = raw * LIS2MDL_MAGNETIC_SENSITIVITY;
	
	return HAL_OK;
}

HAL_StatusTypeDef LIS2MDL_Read_Temperature(lis2mdl_t *dev, float *temp)
{
	HAL_StatusTypeDef ret;
	uint8_t data[2];
	int16_t raw;
	
	if(dev == NULL) return HAL_ERROR;
	
	ret = LIS2MDL_Read(dev,LIS2MDL_TEMP_OUT_L_REG,data,2);
	if (ret != HAL_OK) return ret;
	
	raw = (data[1]<<8) | data[0];
	
	*temp = (float)raw/LIS2MDL_TEMPERATURE_SENSITIVITY;
	
	return HAL_OK;
}
	