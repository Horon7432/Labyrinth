/**
 * Name        : tp1_labyrinth.c
 * Author      : VP
 * Date        : 23.10.2017
 * Description : Labyrinth (TP1). Master implementation must contain:
 *               - 5 balls management, 1 of the master controlled by the local accelerometer
 *               - 1 ball controlled by the slave (accelerometer of the slave board)
 *               - 3 balls with random accelerations
 *               - FreeRTOS used in cooperative mode
 *               - use of global variables allowed
 *               Only the slave acceleration is given by the slave. All ball positions are
 *               managed by the master.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "lcd.h"
#include "accelerometer.h"
#include "ethernet_mgt.h"
#include "tools.h"
#include "custom_rand.h"
#include "traces_ref.h"

#define NUMBER_OF_BALLS  5 				// min 1
#define BALL_DISP_PERIOD 20				// ms
#define BOT1_BALL_DISP_PERIOD 30		// ms
#define BOT2_BALL_DISP_PERIOD 50		// ms
#define BOT3_BALL_DISP_PERIOD 45		// ms
#define SPEED_MAX 5.
#define BALL_RADIUS 5
#define BOT1_BALL_RADIUS 7
#define BOT2_BALL_RADIUS 8
#define BOT3_BALL_RADIUS 8
#define REBOUND_FACTOR 0.9				// speed ratio after a rebound
#define PI 3.141592
#define LCD_YELLOW (LCD_GREEN | LCD_RED)

#define GOAL_H_WALL (LCD_MAX_WIDTH-(2*BALL_RADIUS+1+WALL_WIDTH))
#define GOAL_V_WALL (LCD_MAX_HEIGHT-(2*BALL_RADIUS+1+WALL_WIDTH)-1)

// Ball identifiers
enum {
	NONE = -1,			// NONE is used if ball has reached the goal (winner field)
	MASTER_BALL,
	SLAVE_BALL,
	BOT1_BALL,
	BOT2_BALL,
	BOT3_BALL
};

// ball descriptor
typedef struct {
	int thread_id;
	object_t ball;
} ball_param_th_t;

static coord_fx_t labyrinth_points[]={
		{80,280},{40,280},{40,190},{END_OF_LINE,LCD_WHITE},
		{40,100},{150,100},{150,160},{70,160},{END_OF_LINE,LCD_WHITE},
		{0,160},{40,160},{END_OF_LINE,LCD_WHITE},
		{70,190},{180,190},{180,80},{END_OF_LINE,LCD_WHITE},
		{210,100},{238,100},{END_OF_LINE,LCD_WHITE},
		{180,220},{238,220},{END_OF_LINE,LCD_WHITE},
		{0,40},{100,40},{END_OF_LINE,LCD_WHITE},
		{140,40},{237,40},{END_OF_LINE,LCD_WHITE},
		{120,220},{120,300},{END_OF_LINE,LCD_GREEN},
		{GOAL_H_WALL-2*BALL_RADIUS,GOAL_V_WALL},{LCD_MAX_WIDTH-1,GOAL_V_WALL},{END_OF_LINE,LCD_GREEN},
		{GOAL_H_WALL-4*BALL_RADIUS-WALL_WIDTH-1,LCD_MAX_HEIGHT-WALL_WIDTH},{GOAL_H_WALL-4*BALL_RADIUS-WALL_WIDTH-1,GOAL_V_WALL},{END_OF_WALLS,END_OF_WALLS}
};


/* Description: Callback of ethernet module. This function is called when a message is received
 * Parameters: data: pointer on data received
 *             len: length of the data [bytes]
 */
void slave_info_rx(void *data, int len)
{
	// code executed when the slave sends an ethernet frame
}

int main(void)
{
	accel_t ball_accel;
	static ball_param_th_t ball_param_th[NUMBER_OF_BALLS]={			// balls description
		{MASTER_BALL,{{10,10}, {0, 0}, BALL_RADIUS, LCD_YELLOW, BALL_DISP_PERIOD}},
		{SLAVE_BALL,{{30,10}, {0, 0}, BALL_RADIUS, LCD_GREEN, BALL_DISP_PERIOD}},
		{BOT1_BALL,{{200,10}, {0, 0}, BOT1_BALL_RADIUS, LCD_RED| (LCD_BLUE>>2), BOT1_BALL_DISP_PERIOD}},
		{BOT2_BALL,{{70,70}, {0, 0}, BOT2_BALL_RADIUS, LCD_RED | (LCD_BLUE>>1), BOT2_BALL_DISP_PERIOD}},
		{BOT3_BALL,{{200,280}, {0, 0}, BOT3_BALL_RADIUS, LCD_RED | LCD_BLUE, BOT3_BALL_DISP_PERIOD}}
	};

	init_rnd32(0);			// initialise random generator
	init_lcd();				// initialise screen
	if(accel_init() != 0)	// initialise accelerometer
	{
		printf("Accelerometer initialisation failed!\n");
		return 1;
	}
	//ethernet_init(slave_info_rx); // initialise ethernet and determine its callback function

	draw_labyrinth(labyrinth_points);
	init_traces(115200, 1, true); // initialise traces. Line to be removed if you implement your own traces

	accel_read(&ball_accel);	 // example: reading of the accelerometer

	// creating tasks...
	// xTaskCreate(...);
	// vTaskStartScheduler();		// launch scheduler
	while(1);

	return 1;
}
