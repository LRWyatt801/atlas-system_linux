#include <stddef.h>

#ifndef LAPS_H
#define LAPS_H

/* Struct */

/**
 * struct carnode_s - node in binary search tree
 * @car_id: identification for car node
 * @lap_num: number of laps car has done
 * @car_left: pointer to left child/node
 * @car_right: pointer to right child/node
 *
 * Description: This struct is to be used in conjuction with race_state.
 *              It will store information about each car in a race and
 *              what lap said car is on.
**/

typedef struct carnode_s
{
	int car_id;
	int lap_num;
	struct carnode_s *car_left;
	struct carnode_s *car_right;
} car_node_t;

/* Prototypes */

void race_state(int *id, size_t size);
car_node_t *create_car(int car_id);
car_node_t *car_update(int car_id, car_node_t *root);
void print_race(car_node_t *root);
void free_bst(car_node_t *root);

#endif
