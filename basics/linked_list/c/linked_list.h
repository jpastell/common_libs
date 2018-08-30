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
 * @file link_list.h
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
} data;

/**
 * @brief typedef node, linked list node.
 *
 * contains data for a linked list node.
 */
typedef struct sNode {
	data value;	/**< data stored in the node*/
	void* next;	/**< reference for the next node*/
} node;


/**
 * @brief typedef linked list, linked data type.
 *
 * contains head node pointer and size of the linked list.
 */

typedef struct sLinkedList {
	node* head;
	unsigned int size;
} linked_list;

/*
 *Prototype definition
 */
void delete_data(data* data_ptr);
data* new_data(void* data_ptr, size_t size);


#endif /* _LINKED_LIST_H */








