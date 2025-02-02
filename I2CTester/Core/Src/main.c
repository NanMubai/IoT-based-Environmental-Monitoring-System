/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include "bme280.h"
//#include "bme280_support.c"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//#define BME280_I2C_ADDRESS 0x76 << 1

//#define BME280_REG_CONFIG 0xF5
//#define BME280_REG_CTRL_MEAS 0xF4
//#define BME280_REG_CTRL_HUM 0xF2

//#define BME280_REG_PRESS_MSB 0xF7
//#define BME280_REG_PRESS_LSB 0xF8
//#define BME280_REG_PRESS_XLSB 0xF9

//#define BME280_REG_TEMP_MSB 0xFA
//#define BME280_REG_TEMP_LSB 0xFB
//#define BME280_REG_TEMP_XLSB 0xFC

//#define BME280_REG_HUM_MSB 0xFD
//#define BME280_REG_HUM_LSB 0xFE




/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void send_data_via_uart(float imp_temp, float imp_press, float imp_humi, float dewpt);
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif

PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

GETCHAR_PROTOTYPE
{
  uint8_t ch = 0;

  /* Clear the Overrun flag just before receiving the first character */
  __HAL_UART_CLEAR_OREFLAG(&huart2);

  /* Wait for reception of a character on the USART RX line and echo this
   * character on console */
  HAL_UART_Receive(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
  return ch;
}

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

//static void BME280_Init(void);
//void BME280_WriteReg(uint8_t reg_addr, uint8_t value);
//uint8_t BME280_ReadReg(uint8_t reg_addr);
//void BME280_ReadRegs(uint8_t reg_addr, uint8_t *data, uint16_t len);
//int32_t BME280_ReadTemp();
//void SendSensorDataUART(int32_t temperature, int32_t pressure, int32_t humidity);
//void BME280_ReadData(int32_t *temperature, int32_t *pressure, int32_t *humidity);








#define BME280_API
/*Enable the macro BME280_API to use this support file */
/*----------------------------------------------------------------------------*
*  The following functions are used for reading and writing of
*	sensor data using I2C or SPI communication
*----------------------------------------------------------------------------*/
#ifdef BME280_API
/*	\Brief: The function is used as I2C bus read
 *	\Return : Status of the I2C read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of byte of data to be read
 */
s8 BME280_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
 /*	\Brief: The function is used as I2C bus write
 *	\Return : Status of the I2C write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */
s8 BME280_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
/*	\Brief: The function is used as SPI bus write
 *	\Return : Status of the SPI write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */
s8 BME280_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
/*	\Brief: The function is used as SPI bus read
 *	\Return : Status of the SPI read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of byte of data to be read */
s8 BME280_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
/*
 * \Brief: SPI/I2C init routine
*/
s8 I2C_routine(void);
s8 SPI_routine(void);
#endif


void BME280_delay_msek(u32 msek);
/* This function is an example for reading sensor data
 *	\param: None
 *	\return: communication result
 */
s32 bme280_data_readout_template(void);
/*----------------------------------------------------------------------------*
 *  struct bme280_t parameters can be accessed by using bme280
 *	bme280_t having the following parameters
 *	Bus write function pointer: BME280_WR_FUNC_PTR
 *	Bus read function pointer: BME280_RD_FUNC_PTR
 *	Delay function pointer: delay_msec
 *	I2C address: dev_addr
 *	Chip id of the sensor: chip_id
 *---------------------------------------------------------------------------*/
struct bme280_t bme280;
/* This function is an example for reading sensor data
 *	\param: None
 *	\return: communication result
 */
s32 bme280_data_readout_template(void)
{
	/* The variable used to assign the standby time*/
	u8 v_stand_by_time_u8 = BME280_INIT_VALUE;
	/* The variable used to read uncompensated temperature*/
	s32 v_data_uncomp_temp_s32 = BME280_INIT_VALUE;
	/* The variable used to read uncompensated pressure*/
	s32 v_data_uncomp_pres_s32 = BME280_INIT_VALUE;
	/* The variable used to read uncompensated pressure*/
	s32 v_data_uncomp_hum_s32 = BME280_INIT_VALUE;
	/* The variable used to read compensated temperature*/
	s32 v_comp_temp_s32[2] = {BME280_INIT_VALUE, BME280_INIT_VALUE};
	/* The variable used to read compensated pressure*/
	u32 v_comp_press_u32[2] = {BME280_INIT_VALUE, BME280_INIT_VALUE};
	/* The variable used to read compensated humidity*/
	u32 v_comp_humidity_u32[2] = {BME280_INIT_VALUE, BME280_INIT_VALUE};

	/* result of communication results*/
	s32 com_rslt = ERROR;

 /*********************** START INITIALIZATION ************************/
  /*	Based on the user need configure I2C or SPI interface.
  *	It is example code to explain how to use the bme280 API*/
 	#ifdef BME280_API
	I2C_routine();
	//SPI_routine();
	#endif
/*--------------------------------------------------------------------------*
 *  This function used to assign the value/reference of
 *	the following parameters
 *	I2C address
 *	Bus Write
 *	Bus read
 *	Chip id
*-------------------------------------------------------------------------*/
	com_rslt = bme280_init(&bme280);

	/*	For initialization it is required to set the mode of
	 *	the sensor as "NORMAL"
	 *	data acquisition/read/write is possible in this mode
	 *	by using the below API able to set the power mode as NORMAL*/
	/* Set the power mode as NORMAL*/
	com_rslt += bme280_set_power_mode(BME280_FORCED_MODE);
	/*	For reading the pressure, humidity and temperature data it is required to
	 *	set the OSS setting of humidity, pressure and temperature
	 * The "BME280_CTRLHUM_REG_OSRSH" register sets the humidity
	 * data acquisition options of the device.
	 * changes to this registers only become effective after a write operation to
	 * "BME280_CTRLMEAS_REG" register.
	 * In the code automated reading and writing of "BME280_CTRLHUM_REG_OSRSH"
	 * register first set the "BME280_CTRLHUM_REG_OSRSH" and then read and write
	 * the "BME280_CTRLMEAS_REG" register in the function*/
	com_rslt += bme280_set_oversamp_humidity(BME280_OVERSAMP_1X);

	/* set the pressure oversampling*/
	com_rslt += bme280_set_oversamp_pressure(BME280_OVERSAMP_1X);
	/* set the temperature oversampling*/
	com_rslt += bme280_set_oversamp_temperature(BME280_OVERSAMP_1X);
/*--------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*
************************* START GET and SET FUNCTIONS DATA ****************
*---------------------------------------------------------------------------*/
	/* This API used to Write the standby time of the sensor input
	 *	value have to be given
	 *	Normal mode comprises an automated perpetual cycling between an (active)
	 *	Measurement period and an (inactive) standby period.
	 *	The standby time is determined by the contents of the register t_sb.
	 *	Standby time can be set using BME280_STANDBYTIME_125_MS.
	 *	Usage Hint : bme280_set_standbydur(BME280_STANDBYTIME_125_MS)*/
	com_rslt += bme280_set_standby_durn(BME280_STANDBY_TIME_1_MS);

	/* This API used to read back the written value of standby time*/
	//com_rslt += bme280_get_standby_durn(&v_stand_by_time_u8);
/*-----------------------------------------------------------------*
************************* END GET and SET FUNCTIONS ****************
*------------------------------------------------------------------*/

/************************* END INITIALIZATION *************************/

/*------------------------------------------------------------------*
************ START READ UNCOMPENSATED PRESSURE, TEMPERATURE
AND HUMIDITY DATA ********
*---------------------------------------------------------------------*/

	/* API is used to read the uncompensated humidity*/
	com_rslt += bme280_read_uncomp_humidity(&v_data_uncomp_hum_s32);

	/* API is used to read the uncompensated temperature*/
	com_rslt += bme280_read_uncomp_temperature(&v_data_uncomp_temp_s32);

	/* API is used to read the uncompensated pressure*/
	com_rslt += bme280_read_uncomp_pressure(&v_data_uncomp_pres_s32);
	HAL_Delay(10);
	/* API is used to read the uncompensated temperature,pressure
	and humidity data */
	com_rslt += bme280_read_uncomp_pressure_temperature_humidity(
	&v_data_uncomp_temp_s32, &v_data_uncomp_pres_s32, &v_data_uncomp_hum_s32);

/*--------------------------------------------------------------------*
************ END READ UNCOMPENSATED PRESSURE AND TEMPERATURE********
*-------------------------------------------------------------------------*/

/*------------------------------------------------------------------*
************ START READ COMPENSATED PRESSURE, TEMPERATURE
AND HUMIDITY DATA ********
*---------------------------------------------------------------------*/
	/* API is used to compute the compensated temperature*/
	v_comp_temp_s32[0] = bme280_compensate_temperature_int32(
			v_data_uncomp_temp_s32);

	/* API is used to compute the compensated pressure*/
	v_comp_press_u32[0] = bme280_compensate_pressure_int32(
			v_data_uncomp_pres_s32);

	/* API is used to compute the compensated humidity*/
	v_comp_humidity_u32[0] = bme280_compensate_humidity_int32(
			v_data_uncomp_hum_s32);

	/* API is used to read the compensated temperature, humidity and pressure*/
	com_rslt += bme280_read_pressure_temperature_humidity(
	&v_comp_press_u32[1], &v_comp_temp_s32[1],  &v_comp_humidity_u32[1]);

	//float imp_temp = ((float)(v_comp_temp_s32[1])/100)*1.8+32;		// convert to fahrenheit
	float temp = ((float)v_comp_temp_s32[1]/100);
	//float imp_press = ((float)(v_comp_press_u32[1])/100)*.0295300; 	// convert to inches of mercury
	float press = ((float)(v_comp_press_u32[1])/100);
	float imp_humi = ((float)(v_comp_humidity_u32[1])/1024);		// relative humidity
	float dewpt = ((float)v_comp_temp_s32[1]/100) - ((100 - imp_humi) / 5. );
	dewpt = dewpt * 1.8 + 32;
//	printf("Temp: %.f DegF,  Press: %.2f inHg,  Humi: %.f%% rH,  DewPt: %.f DegF\r\n",
//								imp_temp,
//								imp_press,
//								imp_humi,
//								dewpt);
	send_data_via_uart(temp, press, imp_humi, dewpt);
/*--------------------------------------------------------------------*
************ END READ COMPENSATED PRESSURE, TEMPERATURE AND HUMIDITY ********
*-------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------*
************************* START DE-INITIALIZATION ***********************
*-------------------------------------------------------------------------*/
	/*	For de-initialization it is required to set the mode of
	 *	the sensor as "SLEEP"
	 *	the device reaches the lowest power consumption only
	 *	In SLEEP mode no measurements are performed
	 *	All registers are accessible
	 *	by using the below API able to set the power mode as SLEEP*/
	 /* Set the power mode as SLEEP*/
	com_rslt += bme280_set_power_mode(BME280_SLEEP_MODE);
/*---------------------------------------------------------------------*
************************* END DE-INITIALIZATION **********************
*---------------------------------------------------------------------*/
return com_rslt;
}

#ifdef BME280_API
#define SPI_READ	0x80
#define SPI_WRITE	0x7F
#define BME280_DATA_INDEX	1
#define BME280_ADDRESS_INDEX	2
/*--------------------------------------------------------------------------*
*	The following function is used to map the I2C bus read, write, delay and
*	device address with global structure bme280
*-------------------------------------------------------------------------*/
s8 I2C_routine(void) {
/*--------------------------------------------------------------------------*
 *  By using bme280 the following structure parameter can be accessed
 *	Bus write function pointer: BME280_WR_FUNC_PTR
 *	Bus read function pointer: BME280_RD_FUNC_PTR
 *	Delay function pointer: delay_msec
 *	I2C address: dev_addr
 *--------------------------------------------------------------------------*/
	bme280.bus_write = BME280_I2C_bus_write;
	bme280.bus_read = BME280_I2C_bus_read;
	bme280.dev_addr = BME280_I2C_ADDRESS1;
	bme280.delay_msec = BME280_delay_msek;

	return BME280_INIT_VALUE;
}

/*---------------------------------------------------------------------------*
 * The following function is used to map the SPI bus read, write and delay
 * with global structure bme280
 *--------------------------------------------------------------------------*/
//s8 SPI_routine(void) {
///*--------------------------------------------------------------------------*
// *  By using bme280 the following structure parameter can be accessed
// *	Bus write function pointer: BME280_WR_FUNC_PTR
// *	Bus read function pointer: BME280_RD_FUNC_PTR
// *	Delay function pointer: delay_msec
// *--------------------------------------------------------------------------*/

//	bme280.bus_write = BME280_SPI_bus_write;
//	bme280.bus_read = BME280_SPI_bus_read;
//	bme280.delay_msec = BME280_delay_msek;

///*--------------------------------------------------------------------------*
// *  Drop the chip select pin to low - this tells the BME280 to
// *  use SPI mode. It will not respond to I2C commands until you
// *  reset the power to it.
// */
//	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_Pin, GPIO_PIN_RESET);
//	HAL_Delay(10);
//	HAL_GPIO_WritePin(GPIOB, SPI2_CS1_Pin, GPIO_PIN_SET);

//	return BME280_INIT_VALUE;
//}

/************** I2C/SPI buffer length ******/

#define	I2C_BUFFER_LEN 28
#define SPI_BUFFER_LEN 28

/*-------------------------------------------------------------------*
*	This is a sample code for read and write the data by using I2C/SPI
*	Use either I2C or SPI based on your need
*	The device address defined in the bme280.h file
*-----------------------------------------------------------------------*/
 /*	\Brief: The function is used as I2C bus write
 *	\Return : Status of the I2C write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */
s8 BME280_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    HAL_StatusTypeDef status = HAL_OK;
	s32 iError = BME280_INIT_VALUE;

	while (HAL_I2C_IsDeviceReady(&hi2c1, (uint8_t)(dev_addr<<1), 3, 100) != HAL_OK) {}

    status = HAL_I2C_Mem_Write(&hi2c1,						// i2c handle
    						  (uint8_t)(dev_addr<<1),		// i2c address, left aligned
							  (uint8_t)reg_addr,			// register address
							  I2C_MEMADD_SIZE_8BIT,			// bme280 uses 8bit register addresses
							  (uint8_t*)(&reg_data),		// write returned data to reg_data
							  cnt,							// write how many bytes
							  100);							// timeout

	if (status != HAL_OK)
    {
        // The BME280 API calls for 0 return value as a success, and -1 returned as failure
    	iError = (-1);
    }
	return (s8)iError;
}

 /*	\Brief: The function is used as I2C bus read
 *	\Return : Status of the I2C read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of data byte of to be read
 */
s8 BME280_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
    HAL_StatusTypeDef status = HAL_OK;
	s32 iError = BME280_INIT_VALUE;
	u8 array[I2C_BUFFER_LEN] = {BME280_INIT_VALUE};
	u8 stringpos = BME280_INIT_VALUE;
	array[BME280_INIT_VALUE] = reg_addr;

	while (HAL_I2C_IsDeviceReady(&hi2c1, (uint16_t)(dev_addr<<1), 3, 100) != HAL_OK) {}

    status = HAL_I2C_Mem_Read(&hi2c1,						// i2c handle
    						  (uint8_t)(dev_addr<<1),		// i2c address, left aligned
							  (uint8_t)reg_addr,			// register address
							  I2C_MEMADD_SIZE_8BIT,			// bme280 uses 8bit register addresses
							  (uint8_t*)(&array),			// write returned data to this variable
							  cnt,							// how many bytes to expect returned
							  100);							// timeout

    if (status != HAL_OK)
    {
    	// The BME280 API calls for 0 return value as a success, and -1 returned as failure
    	iError = (-1);
    }
	for (stringpos = BME280_INIT_VALUE; stringpos < cnt; stringpos++) {
		*(reg_data + stringpos) = array[stringpos];
	}

	return (s8)iError;
}

/*	\Brief: The function is used as SPI bus read
 *	\Return : Status of the SPI read
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, will data is going to be read
 *	\param reg_data : This data read from the sensor, which is hold in an array
 *	\param cnt : The no of byte of data to be read
 */


//s8 BME280_SPI_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
//{
//	HAL_StatusTypeDef status = HAL_OK;
//	s32 iError=BME280_INIT_VALUE;
//	u8 txarray[SPI_BUFFER_LEN]={0,};
//	u8 rxarray[SPI_BUFFER_LEN] = {0,};
//	u8 stringpos;
//	/*	For the SPI mode only 7 bits of register addresses are used.
//	The MSB of register address is declared the bit what functionality it is
//	read/write (read as 1/write as BME280_INIT_VALUE)*/
//	txarray[BME280_INIT_VALUE] = reg_addr|SPI_READ;/*read routine is initiated register address is mask with 0x80*/

//	HAL_GPIO_WritePin( GPIOB, SPI2_CS1_Pin, GPIO_PIN_RESET );
//	status = HAL_SPI_TransmitReceive( &hspi2, (uint8_t *)(&txarray), (uint8_t *)(&rxarray), cnt+1, 5);
//	while( hspi2.State == HAL_SPI_STATE_BUSY ) {};
//	HAL_GPIO_WritePin( GPIOB, SPI2_CS1_Pin, GPIO_PIN_SET );
//	HAL_Delay(5); // since i can't find a buffer flushing command
//	for (stringpos = BME280_INIT_VALUE; stringpos < cnt; stringpos++) {
//		*(reg_data + stringpos) = rxarray[stringpos+BME280_DATA_INDEX];
//	}

//    if (status != HAL_OK)
//    {
//    	// The BME280 API calls for 0 return value as a success, and -1 returned as failure
//    	iError = (-1);
//    }
//	return (s8)iError;
//}

/*	\Brief: The function is used as SPI bus write
 *	\Return : Status of the SPI write
 *	\param dev_addr : The device address of the sensor
 *	\param reg_addr : Address of the first register, where data is to be written
 *	\param reg_data : It is a value hold in the array,
 *		will be used for write the value into the register
 *	\param cnt : The no of byte of data to be write
 */
//s8 BME280_SPI_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
//{
//	HAL_StatusTypeDef status = HAL_OK;
//	s32 iError = BME280_INIT_VALUE;
//	u8 array[SPI_BUFFER_LEN * BME280_ADDRESS_INDEX];
//	u8 stringpos = BME280_INIT_VALUE;
//	u8 index = BME280_INIT_VALUE;
//	for (stringpos = BME280_INIT_VALUE; stringpos < cnt; stringpos++) {
//		/* the operation of (reg_addr++)&0x7F done as per the
//		SPI communication protocol specified in the data sheet*/
//		index = stringpos * BME280_ADDRESS_INDEX;
//		array[index] = (reg_addr++) & SPI_WRITE;
//		//printf("%X ", array[stringpos]);
//		array[index + BME280_DATA_INDEX] = *(reg_data + stringpos);
//	}

//	HAL_GPIO_WritePin( GPIOB, SPI2_CS1_Pin, GPIO_PIN_RESET );
//	status = HAL_SPI_Transmit( &hspi2, (uint8_t*)(&array), cnt*2, 100);
//	while( hspi2.State == HAL_SPI_STATE_BUSY ) {};
//	HAL_GPIO_WritePin( GPIOB, SPI2_CS1_Pin, GPIO_PIN_SET );

//    if (status != HAL_OK)
//    {
//    	// The BME280 API calls for 0 return value as a success, and -1 returned as failure
//    	iError = (-1);
//    }
//	return (s8)iError;
//}

/*	Brief : The delay routine
 *	\param : delay in ms
*/
void BME280_delay_msek(u32 msek)
{
	/*Here you can write your own delay routine*/
	HAL_Delay(10*msek);
}
#endif









/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
//	BME280_Init();
	int32_t temperature, pressure, humidity;
	char *str = "Hello world";
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
//		BME280_ReadData(&temperature, &pressure, &humidity);
    //SendSensorDataUART(temperature, pressure, humidity);
		//HAL_UART_Transmit(&huart2, (uint8_t *)str, strlen(str), HAL_MAX_DELAY);
		bme280_data_readout_template();
		//printf("Hello");
    HAL_Delay(1000);

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */









void send_data_via_uart(float imp_temp, float imp_press, float imp_humi, float dewpt) {
    char buffer[100];


    sprintf(buffer, "Temp: %.f DegF,  Press: %.2f inHg,  Humi: %.f%% rH,  DewPt: %.f DegF\r\n",
                    imp_temp,
                    imp_press,
                    imp_humi,
                    dewpt);


    HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), HAL_MAX_DELAY);
}



//static void BME280_Init(void)
//{
//	BME280_WriteReg(BME280_REG_CONFIG, 0x40);
//	BME280_WriteReg(BME280_REG_CTRL_MEAS,0x7B);
//	BME280_WriteReg(BME280_REG_CTRL_HUM, 0x01);
//}

//void BME280_WriteReg(uint8_t reg_addr, uint8_t value)
//{
//	uint8_t data[2];
//  data[0] = reg_addr;
//  data[1] = value;
//  HAL_I2C_Master_Transmit(&hi2c1, BME280_I2C_ADDRESS, data, 2, HAL_MAX_DELAY);
//}

//uint8_t BME280_ReadReg(uint8_t reg_addr)
//{
//	uint8_t value = 0;
//	HAL_I2C_Mem_Read(&hi2c1, BME280_I2C_ADDRESS, reg_addr, 1, &value, 1, HAL_MAX_DELAY);
//  return value;
//}

//void BME280_ReadRegs(uint8_t reg_addr, uint8_t *data, uint16_t len)
//{
//	HAL_I2C_Mem_Read(&hi2c1, BME280_I2C_ADDRESS, reg_addr, I2C_MEMADD_SIZE_8BIT, data, len, HAL_MAX_DELAY);
//}

//int32_t BME280_ReadTemp()
//{
//	uint8_t data[3];
//	BME280_ReadRegs(BME280_REG_TEMP_MSB, data, 3);
//	int32_t temp = (int32_t)(((uint32_t)data[0] << 12) | ((uint32_t)data[1] << 4) | (data[2] >> 4));
//	return temp;
//}

//void SendTemperatureUART(int32_t temperature)
//{
//	char buffer[50];
//	int len = snprintf(buffer, sizeof(buffer), "Raw Temperature: %d\r\n", temperature);
//	HAL_UART_Transmit(&huart2, (uint8_t *)buffer, len, HAL_MAX_DELAY);
//}

//void BME280_ReadData(int32_t *temperature, int32_t *pressure, int32_t *humidity)
//{
//	uint8_t data[8];

//	BME280_ReadRegs(BME280_REG_PRESS_MSB, data, 8);

//	*pressure = (int32_t)(((uint32_t)data[0] << 12) | ((uint32_t)data[1] << 4) | (data[2] >> 4));
//	*temperature = (int32_t)(((uint32_t)data[3] << 12) | ((uint32_t)data[4] << 4) | (data[5] >> 4));
//	*humidity = (int32_t)(((uint32_t)data[6] << 8) | data[7]);
//}

//void SendSensorDataUART(int32_t temperature, int32_t pressure, int32_t humidity)
//{
//	char buffer[100];
//	int len = snprintf(buffer, sizeof(buffer), "Temperature: %d, Pressure: %d, Humidity: %d", temperature, pressure, humidity);
//	HAL_UART_Transmit(&huart2, (uint8_t *)buffer, len, HAL_MAX_DELAY);
//}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
