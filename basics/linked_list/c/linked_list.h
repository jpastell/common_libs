/****************************************************************************
 * Copyright © 2018, Juan Pablo Castellanos. All rights reserved.           *
 *                                                                          *
 * linked_list.h is part of common libs project                             *
 *                                                                          *
 *   Common lib projects is free software: you can redistribute it and/or   *
 *   modify it under the terms of the GNU Lesser General Public License as  *
 *   published by the Free Software Foundation, either version 3 of the     *
 *   License, or(at your option) any later version.                         *
 *                                                                          *
 *   common libs project is distributed in the hope that it will be useful, *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/** 
 * @file linked_list.h
 * @author Juan Pablo Castellanos Flores
 * @date 26/8/18
 * @brief File containing data types and prototyped for a generic linked list
 *    
 * Definition for data node and linked list data tytes and
 * funtions prototypes for the API.
 */

#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

#include <stdlib.h>

/**
 * @brief typedef data, data container for linked list.
 *
 * contains a pointer to the data and the size of the data stored.
 */
typedef struct sData {
	void* data_ptr;	/**< void ponter to the data stored. */
	size_t size;	/**< sise of the data. */
	void (*print_data) (void *);
} data;

/**
 * @brief typedef node, linked list node.
 *
 * contains data for a linked list node.
 */
typedef struct sNode {
	data* value_ptr;	/**< data stored in the node*/
	void* next;		/**< reference for the next node*/
} node;


/**
 * @brief typedef linked list, linked data type.
 *
 * contains head node pointer and size of the linked list.
 */

typedef struct sLinkedList {
	node* head;
	size_t size;
} linked_list;

/*
 *Prototype definition
 */
void delete_data(data* data_ptr);
data* new_data(void* data_ptr, size_t size,void (*print) (void *));
linked_list* new_linked_list(data* data_ptr);
int insert_data(linked_list* linked_list_ptr, data* data_ptr, size_t index);
void print_linked_list(linked_list* linked_list_ptr);
void delete_linked_list(linked_list* linked_list_ptr);
data* get_data(linked_list* linked_list_ptr, size_t index);
size_t get_size(linked_list* linked_list_ptr);
static node* get_node_by_index(linked_list* linked_list_ptr, size_t index);
data* delete_data_linked(linked_list* linked_list_ptr, size_t index);
data* change_data(linked_list* linked_list_ptr, data* data_ptr, size_t index);


#endif /* _LINKED_LIST_H */








