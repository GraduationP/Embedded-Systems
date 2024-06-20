/*
 * NMEA.h
 *
 *  Created on: Jan 28, 2024
 *      Author: wegz
 */

#ifndef INC_NMEA_H_
#define INC_NMEA_H_
#include "main.h"

#define bufsize 350
char GGA[100];
uint8_t rx_databuffer[bufsize];


typedef struct{
	int hour;
	int min;
	int sec;
}TIME;
typedef struct{
	float latitude;
	char ns;
	float longitude;
	char ew;
}LOCATION;
typedef struct{
	float altitude;
	char unit;
}ALTITUDE;
typedef struct{
	int day;
	int mon ;
	int yr;	
}DATE;
typedef struct{
	LOCATION lcation;
	TIME tim;
	int isValid;
	ALTITUDE alt;
	int numofsat;
}GGASTRUCT;
typedef struct{
	DATE date;
	float speed;
	float course;
	int isValid;
}RMCSTRUCT;
typedef struct{
	GGASTRUCT ggastruct;
	char rmcstruct;
}GPSSTRUCT;

GPSSTRUCT gpsdata;

int decodeGGA (char *GGAbuffer, GGASTRUCT *gga);

int decodeRMC (char *RMCbuffer, GGASTRUCT *rmc);

void dma_uart(DMA_HandleTypeDef *hdma ,UART_HandleTypeDef *huart ,GPSSTRUCT *gpsdata ,char *GGA, uint8_t *rx_databuffer);

#endif /* INC_NMEA_H_ */
