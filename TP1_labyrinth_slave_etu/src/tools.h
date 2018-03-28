/*
 * Name        : tools.h
 * Author      : VP
 * Date        : 23.10.2017
 * Description : utility functions to draw the labyrinth and to test object collisions
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdint.h>

#define MAX_RADIUS 15		// maximum radius of an object
#define WALL_WIDTH 3		// labyrinth wall width
#define END_OF_LINE -1		// 'x' coordinate of labyrinth indicating the end of a wall
#define END_OF_WALLS -2		// ^y' coordinate of labyrinth indicating the end of the point table

// constants used to build the collision vector (see function test_collision)
enum {
	NO_COLLISION=0,
	TOUCH_LEFT=(1<<2),
	TOUCH_RIGHT=(1<<0),
	TOUCH_UP=(1<<1),
	TOUCH_DOWN=(1<<3),
};

typedef struct
{
	float x;
	float y;
} coord_t;

typedef struct
{
	int x;
	int y;
} coord_fx_t;

// defines a "squared" object. "pos" defines the position of the center of the object
// and radius is the number of pixels considered around pos in x and y directions
typedef struct
{
	coord_t pos;
	coord_t speed;
	uint8_t radius;
	uint16_t color;
	uint16_t period;			// display period [ms]
} object_t;

typedef struct {
	int ball_id;
	coord_fx_t ball_coord;
	uint16_t color;
	uint8_t radius;
	int8_t winner;
	//uint32_t dbg_cptr;
} master_tx_t;

// rounds a float on an integer, whatever its sign
int round(float x);


/* draw the labyrinth. The wall description is an array of points. 2 successive points must have at least
 * one common coordinate, either x or y since only vertical or horizontal lines are allowed. To end a line,
 * END_OF_LINE must replace the x coordinate, while feeding y with the line color of the next line. The end of the array
 * is marked with the point {END_OF_WALLS,END_OF_WALLS}
 * Parameter: labyrinth_points: pointer on the array of points
 * */
void draw_labyrinth(coord_fx_t *labyrinth_points);

/* detect all collisions among all objects in every direction.
 * Parameter: object: object that tests collisions
 * Return: collision vector index or NO_COLLISION. The vector is a bit vector indicating where the object touched
 * an obstacle. Example of value returned: TOUCH_RIGHT | TOUCH_UP.
 */
int test_collision(object_t *object);

#endif /* TOOLS_H_ */
