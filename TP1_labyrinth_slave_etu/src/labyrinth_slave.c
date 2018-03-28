/*
===============================================================================
 Name        : labyrinth_slave.c
 Author      : V. Pilloux
 Date	     : 23.10.2017
 Description : TP1 Labyrinth solution, slave code. The slave only transmits
               the accelerometer data to the master and displays the balls at
               the positions given by the master.
               The Ethernet interrupt is masked when the data has to be used
               in the main to avoid an overriding during the variables use.
===============================================================================
*/

#include "LPC17xx.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <cr_section_macros.h>
#include "lcd.h"
#include "accelerometer.h"
#include "ethernet_mgt.h"
#include "tools.h"

#define NUMBER_OF_BALLS  5 				// min 1
#define BALL_DISP_PERIOD 20				// ms
#define BALL_RADIUS 5
#define LCD_YELLOW (LCD_GREEN | LCD_RED)
#define NONE  -1

#define GOAL_H_WALL (LCD_MAX_WIDTH-(2*BALL_RADIUS+1+WALL_WIDTH))
#define GOAL_V_WALL (LCD_MAX_HEIGHT-(2*BALL_RADIUS+1+WALL_WIDTH)-1)


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


/* Description: Callback of ethernet module. This function is called when a message is received.
 * Each ball of the master send its own coordinates that are saved here.
 * Parameters: data: pointer on data received
 *             len: length of the data [bytes]
 */
void master_info_rx(void *data, int len)
{
	// receive master_tx structure
}

//init ball
int init_struct_ball(object_t*ball,int X, int Y, int Radius, int Color){
		if(Radius > MAX_RADIUS){
			return -1;
		}
		ball->pos.x = X;
		ball->pos.y = Y;
		ball->radius = Radius;
		ball->speed.x = 0;
		ball->speed.y = 0;
		ball->period = 20;
		ball->color = Color;

		return 0;
}

//update speed of ball
void update_struct_ball_accel(object_t *ball,accel_t *accel_ball){
	ball->speed.x = round(accel_ball->accel_x);
	ball->speed.y = round(accel_ball->accel_y);
}


//clean LCD and display new laby and balls
void update_game(object_t*ball){
	clear_screen(LCD_BLACK);
	draw_labyrinth(labyrinth_points);
	lcd_circle(ball->pos.x, ball->pos.y, ball->radius , ball->color);
}


int main(void)
{
	accel_t accel_slave;
	object_t slave_ball;
	init_lcd();
	if(accel_init() != 0)
	{
		printf("Accelerometer initialization failed!\n");
		return 1;
	}
	//ethernet_init(master_info_rx);

	//init game for the first time
	draw_labyrinth(labyrinth_points);
	if(init_struct_ball(&slave_ball,10,10,5,LCD_YELLOW) != 0){
		printf("Bad parameter(s)!\n");
		return 1;
	}

	lcd_circle(slave_ball.pos.x, slave_ball.pos.y, slave_ball.radius, slave_ball.color);

	if(accel_read(&accel_slave) != 0){
		printf("Accelerometer accel_read failed!\n");
		return 1;
	}

	//implementation of test_collision
	//if collision , 10% of speed loss and x,y speed inverse
	switch(test_collision(&slave_ball)){
	case NO_COLLISION:
		printf("NO_COLLISION\n");
		break;
	case TOUCH_LEFT:
		printf("TOUCH_LEFT\n");
		slave_ball.speed.x = slave_ball.speed.x-((slave_ball.speed.x*10)/100);
		slave_ball.speed.y = slave_ball.speed.y-((slave_ball.speed.y*10)/100);
		break;
	case TOUCH_RIGHT:
		printf("TOUCH_RIGHT\n");
		slave_ball.speed.x = slave_ball.speed.x-((slave_ball.speed.x*10)/100);
		slave_ball.speed.y = slave_ball.speed.y-((slave_ball.speed.y*10)/100);
		break;
	case TOUCH_UP:
		printf("TOUCH_UP\n");
		slave_ball.speed.x = slave_ball.speed.x-((slave_ball.speed.x*10)/100);
		slave_ball.speed.y = slave_ball.speed.y-((slave_ball.speed.y*10)/100);
		break;
	case TOUCH_DOWN:
		printf("TOUCH_DOWN\n");
		slave_ball.speed.x = slave_ball.speed.x-((slave_ball.speed.x*10)/100);
		slave_ball.speed.y = slave_ball.speed.y-((slave_ball.speed.y*10)/100);
		break;
	}

	while(1)
	{

	}
}

