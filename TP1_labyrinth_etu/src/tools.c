/*
 * tools.c
 *
 *  Created on: 22 oct. 2017
 *      Author: vince
 */

#include <math.h>
#include "tools.h"
#include "lcd.h"

int round(float x)
{
	if (x>=.5)
		return (int)ceil(x);
	if (x<=-.5)
		return (int)floor(x);
	return 0;
}


void draw_labyrinth(coord_fx_t *labyrinth_points)
{
	int i=0, color=LCD_WHITE;

	clear_screen(LCD_BLACK);
	do {
		while (labyrinth_points[++i].x>=0)
		{
			lcd_filled_rectangle(
					labyrinth_points[i-1].x>labyrinth_points[i].x?labyrinth_points[i-1].x+WALL_WIDTH-1:labyrinth_points[i-1].x,
					labyrinth_points[i-1].y>labyrinth_points[i].y?labyrinth_points[i-1].y+WALL_WIDTH-1:labyrinth_points[i-1].y,
					labyrinth_points[i-1].x==labyrinth_points[i].x?labyrinth_points[i].x+WALL_WIDTH-1:labyrinth_points[i].x,
					labyrinth_points[i-1].y==labyrinth_points[i].y?labyrinth_points[i].y+WALL_WIDTH-1:labyrinth_points[i].y,
					color);
		}
		color=labyrinth_points[i].y;
	} while (labyrinth_points[i++].x!=END_OF_WALLS);
}



/* detect all collisions among all object in every direction
 * Return: collision vector index or NO_COLLISION
 */
int test_collision(object_t *object)
{
	uint16_t tp[2*MAX_RADIUS+1], i, k;
	int offset_x, offset_y;
	int col_dir_idx=0; // keep track of collision points around max_dir
	coord_fx_t speed, pos;
	float speed_max;

	// test collision at next position of the object. ! to rounding !
	pos.x=round(object->pos.x+object->speed.x);
	pos.y=round(object->pos.y+object->speed.y);
	speed.x=pos.x-round(object->pos.x);
	speed.y=pos.y-round(object->pos.y);
	// test screen bounds:
	if (pos.x<object->radius)
		col_dir_idx|=TOUCH_LEFT;
	if (pos.x>LCD_MAX_WIDTH-object->radius-1)
		col_dir_idx|=TOUCH_RIGHT;
	if (pos.y<object->radius)
		col_dir_idx|=TOUCH_UP;
	if (pos.y>LCD_MAX_HEIGHT-object->radius-1)
		col_dir_idx|=TOUCH_DOWN;
	if (col_dir_idx)
		return col_dir_idx;

	speed_max=MAX(ABS(speed.x), ABS(speed.y));
	for (k=1; k<=speed_max; k++)		// test line by line if there is a collision, going forward of 1 pixel
	{
		pos.x=round(object->pos.x+object->speed.x*(float)k/speed_max);
		pos.y=round(object->pos.y+object->speed.y*(float)k/speed_max);
		speed.x=pos.x-round(object->pos.x);
		speed.y=pos.y-round(object->pos.y);
		offset_x=speed.x?1:0;			// to adjust size of the front detection line
		offset_y=speed.y?1:0;
		if (speed.y>0)		// test low horizontal line of pixel of the object width (on new position), except pixel on corner!
		{
			read_pixels((uint8_t)(pos.x-object->radius+offset_x), (uint16_t)(pos.y+object->radius),
					(uint8_t)(pos.x+object->radius-offset_x), (uint16_t)(pos.y+object->radius), tp);
			for (i=0; i<=2*(object->radius-offset_x); i++)
				if (tp[i])
				{
					col_dir_idx|=TOUCH_DOWN;
					break;
				}
		}
		if (speed.y<0)
		{
			read_pixels((uint8_t)(pos.x-object->radius+offset_x), (uint16_t)(pos.y-object->radius),
					(uint8_t)(pos.x+object->radius-offset_x), (uint16_t)(pos.y-object->radius), tp);
			for (i=0; i<=2*(object->radius-offset_x); i++)
				if (tp[i])
				{
					col_dir_idx|=TOUCH_UP;
					break;
				}
		}
		if (speed.x>0)		// test right vertical line of pixel of the object width (on new position) except corner pixel
		{
			read_pixels((uint8_t)(pos.x+object->radius), (uint16_t)(pos.y-object->radius+offset_y),
					(uint8_t)(pos.x+object->radius), (uint16_t)(pos.y+object->radius-offset_y), tp);
			for (i=0; i<=2*(object->radius-offset_y); i++)
				if (tp[i])
				{
					col_dir_idx|=TOUCH_RIGHT;
					break;
				}
		}
		if (speed.x<0)
		{
			read_pixels((uint8_t)(pos.x-object->radius), (uint16_t)(pos.y-object->radius+offset_y),
					(uint8_t)(pos.x-object->radius), (uint16_t)(pos.y+object->radius-offset_y), tp);
			for (i=0; i<=2*(object->radius-offset_y); i++)
				if (tp[i])
				{
					col_dir_idx|=TOUCH_LEFT;
					break;
				}
		}
		if (col_dir_idx)
			break;
	}
	return col_dir_idx;
}
