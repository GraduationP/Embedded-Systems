/*
 * NMEA.c
 *
 *  Created on: Jan 28, 2024
 *      Author: wegz
 */


#include "new_NMEA.h"
#include "stdint.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

int GMT = +530;
int inx, hr, min, day, mon, yr, daychange;


int decodeGGA (char *GGAbuffer, GGASTRUCT *gga)
{
	inx = 0;
	char buffer[12];
	int i = 0;
	while (GGAbuffer[inx] != ',') inx++;  // 1st ','
	inx++;
	while (GGAbuffer[inx] != ',') inx++;  // After time ','
	inx++;
	while (GGAbuffer[inx] != ',') inx++;  // after latitude ','
	inx++;
	while (GGAbuffer[inx] != ',') inx++;  // after NS ','
	inx++;
	while (GGAbuffer[inx] != ',') inx++;  // after longitude ','
	inx++;
	while (GGAbuffer[inx] != ',') inx++;  // after EW ','
	inx++;
	if ((GGAbuffer[inx] == '1') || (GGAbuffer[inx] == '2') || (GGAbuffer[inx] == '6'))   // 0 indicates no fix yet
	{
		gga->isValid = 1;   // fix available
		inx = 0;   // reset the index. We will start from the inx=0 and extract information now
	}
	else
	{
		gga->isValid = 0;   // If the fix is not available
		return 1;
	}
	while (GGAbuffer[inx] != ',') inx++;
	inx++;
	memset(buffer,'\0',12);
	i=0;
	while (GGAbuffer[inx] != ',')
	{
		buffer[i] = GGAbuffer[inx];
		i++;
		inx++;
	}
	hr = (atoi(buffer)/10000) + GMT/100;
	min = ((atoi(buffer)/100)%100) + GMT%100;

	if (min>59)
	{
		min = min-60;
		hr++;
	}
	if (hr<0)
	{
		hr =24+hr;
		daychange--;
	}
	if (hr>24)
	{
		hr =hr-24;
		daychange++;
	}
	gga->tim.hour = hr;
	gga->tim.min = min;
	gga->tim.sec = atoi(buffer)%100;

	//get latitude
	inx++;
	memset(buffer,'\0',12);
	i=0;
	while (GGAbuffer[inx] != ',')
	{
		buffer[i] = GGAbuffer[inx];
		i++;
		inx++;
	}
	if (strlen(buffer) <6) return 2;
	int16_t num = (atoi(buffer));
	int j = 0;
	while (buffer[j] != '.') j++;
	j++;
	int declen = (strlen(buffer))-j;
	int dec = atoi ((char*) buffer+j);
	float lat = (num / 100.0) + (dec/pow(10, (declen+2)));
	gga->lcation.latitude =lat;
	inx++;
	gga->lcation.ns = GGAbuffer[inx];


	//get longitude
	inx++;
	inx++;
	memset(buffer,'\0',12);
	i=0;
	while (GGAbuffer[inx] != ',')
	{
		buffer[i] = GGAbuffer[inx];
		i++;
		inx++;
	}
	num = (atoi(buffer));
	j = 0;
	while (buffer[j] != '.') j++;
	j++;
	declen = (strlen(buffer))-j;
	dec = atoi ((char*) buffer+j);
	lat = (num / 100.0) + (dec/pow(10, (declen+2)));
	gga->lcation.longitude =lat;
	inx++;
	gga->lcation.ew = GGAbuffer[inx];

	inx++;
	inx++;
	inx++;

	inx++;
	memset(buffer,'\0',12);
	i=0;
	while (GGAbuffer[inx] != ',')
	{
		buffer[i] = GGAbuffer[inx];
		i++;
		inx++;
	}
	gga->numofsat = atoi(buffer);

	inx++;
	while (GGAbuffer[inx] != ',') inx++;

	inx++;
	memset(buffer,'\0',12);
	i=0;
	while (GGAbuffer[inx] != ',')
	{
		buffer[i] = GGAbuffer[inx];
		i++;
		inx++;
	}
	num = (atoi(buffer));
	j = 0;
	while (buffer[j] != '.') j++;
	j++;
	declen = (strlen(buffer))-j;
	dec = atoi ((char*) buffer+j);
	lat = (num) + (dec/pow(10, (declen)));
	gga->alt.altitude =lat;
	inx++;
	gga->alt.unit = GGAbuffer[inx];
	return 1;
}

int decodeRMC (char *RMCbuffer, GGASTRUCT *rmc);


void dma_uart(DMA_HandleTypeDef *hdma ,UART_HandleTypeDef *huart ,GPSSTRUCT *gpsdata ,char *GGA, uint8_t *rx_databuffer)
{
	int index =0;

	for(int i =0; i<bufsize-3; i++)
	{
		if(rx_databuffer[i]=='G'&&rx_databuffer[i+1]=='G'&&rx_databuffer[i+2]=='A')
		{
			i+=3;
			memset(GGA,'\0',100);
			while (rx_databuffer[i] !='*')
			{
				GGA[index] = rx_databuffer[i];
				i++;
				index++;
			}
			break;
		}
	}
	decodeGGA(GGA, &gpsdata->ggastruct);

//	// 1. Disable the DMA channel
//	HAL_DMA_Abort(hdma);
//	// 2. Reset the memory address pointer to the start of the buffer
//	hdma->Instance->PAR = (uint32_t)&(hdma->Instance->M0AR); // Reset peripheral address
//	hdma->Instance->M0AR = (uint32_t)rx_databuffer; // Reset memory address pointer
//	// 3. Reconfigure the DMA channel with the updated memory address and desired transfer parameters
//	hdma->Instance->NDTR = bufsize; // Set the number of data items to transfer
//	hdma->Instance->CR &= ~DMA_SxCR_HTIE; // Disable half-transfer interrupt
//	hdma->Instance->CR |= DMA_SxCR_TCIE; // Enable transfer complete interrupt
//	hdma->Instance->CR |= DMA_SxCR_EN; // Enable the DMA channel
//	// 4. Enable the DMA channel to resume the transfer
//	HAL_DMA_Start(hdma, (hdma->Instance->M0AR),rx_databuffer, bufsize);
	// start receive again
	HAL_UART_Receive_DMA(huart, rx_databuffer, bufsize);



}

