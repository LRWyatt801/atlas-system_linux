#include "laps.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>



/**
 * create_car - creates a car_node in BST
 * @car_id - unique id for car node
 *
 * Return - pointer to new node
**/

car_node_t *create_car(int car_id)
{
	car_node_t *new_car;

	new_car = malloc(sizeof(car_node_t));
	if (!new_car)
		return (NULL);
	new_car->car_id = car_id;
	new_car->lap_num = 0;
	new_car->car_left = new_car->car_right = NULL;
	printf("Car %d joined the race\n", car_id);
	return new_car;
}

/**
 * car_update - checks each id and updates lap if exists,
 *				otherwise adds id to BST
 * @car_id: identification of car
 * @root: pointer to root of BST
 *
 * Return: n/a
**/

car_node_t *car_update(int car_id, car_node_t *root)
{
	if (root == NULL)
		return create_car(car_id);
	
	if (car_id == root->car_id)
	{
		root->lap_num++;
		return root;
	}
	else if (car_id < root->car_id)
		root->car_left = car_update(car_id, root->car_left);
	else if (car_id > root->car_id)
		root->car_right = car_update(car_id, root->car_right);
	
	return root;
}

/**
 * print_race - prints all cars and laps
 * @root: pointer to car
 *
 * Return: n/a
**/

void print_race(car_node_t *root)
{
	if (root != NULL)
	{
		print_race(root->car_left);
		printf("Car %d [%d laps]\n", root->car_id, root->lap_num);
		print_race(root->car_right);
	}
}

/**
 * free_bst - frees a binary search tree
 * @root: pointer to root node
 *
 * Return: n/a
**/

void free_bst(car_node_t *root)
{
	if (root != NULL)
	{
		free_bst(root->car_left);
		free(root);
		free_bst(root->car_right);
	}
}

/**
 * race_state - keeps track of a race between several cars
 * @id: pointer to an array of car identifiers
 * @size: size of array for id
 *
 * Return: n/a
**/

void race_state(int *id, size_t size)
{
	size_t i = 0;
	static car_node_t *root;

	/* if size is 0 then free tree */
	if (size == 0)
	{
		free_bst(root);
		exit(0);
	}

	/* iterate through id list */
	for (i = 0; i < size; i++)
	{
		root = car_update(id[i], root);
	}
	printf("Race state:\n");
	print_race(root);
}
