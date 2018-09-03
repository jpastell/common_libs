/****************************************************************************
 * Copyright © 2018, Juan Pablo Castellanos. All rights reserved.           *
 *                                                                          *
 * linked_list.c is part of common libs project                             *
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

#include "linked_list.h"
#include <stdio.h>

/** 
 * @file linked_list.c
 * @author Juan Pablo Castellanos Flores
 * @date 26/8/18
 * @brief Link list funtion implementation
 *    
 * Linked list implementation, data creation and linked methods
 */


/**
 * @brief static function used to copy data byte for bye.
 *
 * Copy data byte for byte from @p src into @p dest the function copy one byte
 * at a time until the size is completed, @p size is the size of the data to
 * be copied.
 * 
 * @param src char void pointer of the data to be copied.
 * @param dest char void pointer where the data will be copied.
 * @param size size_t varible that contain the size of the data to be
 * copied
 *
 * @return void.
 *
 */
static void copy_data(char* src, char* dest, size_t size){
	size_t iter;
	for(iter=0;iter<size;iter++){
		*dest=*src;
		dest++;
		src++;
	}	
}

/**
 * @brief new dynamic data constuctor.
 *
 * Creates a new data, dynamically allocates memory for data contarner and
 * the data to be copied. Once both memory regions are requested the funtion
 * copies byte per byte the data specidied in @p data_ptr and @p size.
 *  
 * @param data_ptr void pointer where the new data is going to copy from.
 * @param size size_t data of the size to be copied.
 * @param data type print function
 *
 * @return data* , data pointer with the new element copied
 *
 * @code
 * int element = 9;
 * data *new_data_ptr = new_data(element, sizeof(element));
 * @endcode
 *
 */
data* new_data(void* data_ptr, size_t size, void (*print) (void*))
{
	//Create the data data structure meory
	data* struct_ptr = (data*)malloc(sizeof(data));
	//Allocate the memory for the data copied
	void* data_ref = malloc(size);
	//Copy the data into the new memory alocated
	copy_data((char*)data_ptr,(char*)data_ref,size);
	//Update data pointer an the size
	struct_ptr->data_ptr=(void*)data_ref;
	struct_ptr->size=size;
	struct_ptr->print_data=print;
	//Return the reference for the data type created
	return struct_ptr;
}

/**
 * @brief Function used to free memory data
 *
 * Function used to free the memory used for the data cointainer and 
 * mwmory reserved for adta allocation.
 * 
 * @param data_ptr data pointer of the element to be free.
 *
 * @return void.
 *
 */

void delete_data(data* data_ptr)
{
	//Free the memory used for data
	free(data_ptr->data_ptr);
	//Free the memory for the data allocator
	free((void*)data_ptr);
}


node* new_node(data* data_ptr)
{
	node* head_ptr = (node*)malloc(sizeof(node));
	head_ptr->value_ptr = data_ptr;
	head_ptr->next = NULL;
	return head_ptr;
}

void delete_node(node* node_ptr){
	//Delete the pata embeded in the node
	delete_data(node_ptr->value_ptr);
	free((void*)node_ptr);
}

linked_list* new_linked_list(data* data_ptr)
{
	//Allocate the memory for link list
	linked_list* linked_list_ptr = (linked_list*)malloc(sizeof(linked_list));
	if(data_ptr == NULL){
		printf("Inserting NULL\n");
		//Since there is not data just initialize the list as empty list
		linked_list_ptr->head = NULL;
		linked_list_ptr->size = 0;
	} else {
		//Create a new node and attached to the list
		linked_list_ptr->head = new_node(data_ptr);
		linked_list_ptr->size = 1;
	}
	return linked_list_ptr;
}

int insert_data(linked_list* linked_list_ptr, data* data_ptr, size_t index)
{
	size_t iterator = 1;
	node* node_ctr = new_node(data_ptr);
	node* node_iter = linked_list_ptr->head;
	node* node_iter_z_m1; 
	//If index higer than lint value throw an error
	if((0 == linked_list_ptr->size) && (0 != index)){
		printf("Invalid index %lu for empty list\n",index);
		return -1;	
	} else {
		if( index > linked_list_ptr->size){
			printf("Index can't be higher than linked list size\n");
			return -2;	
		} else {
			if (index == 0) {
				if(node_iter ==NULL){
					//Empty list just link the data
					linked_list_ptr->head = node_ctr;
				} else {
					//Not empy list
					node_ctr->next = (void*)node_iter;
					linked_list_ptr->head = node_ctr;
				}
			} else {
				//Move the pointer to th eindex where the data will be
				//inserted, we are stoping at NULL to inlcude the case
				//add a node at zise + 1 
				while(node_iter->next !=NULL && iterator<=index){
					iterator++;
					node_iter_z_m1 = node_iter;
					node_iter = (node*)node_iter->next;
				}
				if(linked_list_ptr->size == index){
					//Add ad size +1 insterted at the end
					node_iter->next = node_ctr; 
				} else {
					//Insert the new node at the index
					node_ctr->next=	(void*)node_iter;
					node_iter_z_m1->next = (void*)node_ctr;
				}
			}
			linked_list_ptr->size++;
			return 0;
		}
	}	
}


void print_linked_list(linked_list* linked_list_ptr)
{
	printf("--------------------\n");
	//Iterate the entire list
	node* node_iter = linked_list_ptr->head;
	while( node_iter->next != NULL ){
		//Call the print function
		(*(node_iter->value_ptr->print_data))(node_iter->value_ptr->data_ptr);
		//Move to the next element
		node_iter = (node*)node_iter->next;
	}
	//Printing the last element
	(*(node_iter->value_ptr->print_data))(node_iter->value_ptr->data_ptr);
	printf("--------------------\n");
}


void delete_linked_list(linked_list* linked_list_ptr)
{
	if (linked_list_ptr->head != NULL) {
		//Iterate the list
		node* node_iter = linked_list_ptr->head;
		while( node_iter->next != NULL ){
			//Delete the node
			delete_node(node_iter);
			//Move to the next element
			node_iter = (node*)node_iter->next;
		}
		//Deleting last item
		delete_node(node_iter);
	}
	free((void*)linked_list_ptr);
}

static node* get_node_by_index(linked_list* linked_list_ptr, size_t index)
{
	size_t iterator = 1;
	node* node_iter = linked_list_ptr->head;
	if(node_iter == NULL){
		return NULL;
	} else {
		if(index >= linked_list_ptr->size){
			return NULL;
		} else {
			//Iterate to the elment to move
			for(;iterator<=index;iterator++){
				node_iter = (node*)node_iter->next;
			}
			return node_iter;
		}
	}	
}

data* get_data(linked_list* linked_list_ptr, size_t index)
{
	node* node_iter = get_node_by_index(linked_list_ptr,index);
	if(node_iter == NULL){
		return NULL;
	} else {
		return node_iter->value_ptr;
	}	
}

data* change_data(linked_list* linked_list_ptr, data* data_ptr, size_t index)
{
	data* temp_data;
	node* node_iter = get_node_by_index(linked_list_ptr,index);
	if(node_iter == NULL){
		return NULL;
	} else {
		temp_data = node_iter->value_ptr;
		node_iter->value_ptr = data_ptr;
		return temp_data;
	}	
}

data* delete_data_linked(linked_list* linked_list_ptr, size_t index)
{
	size_t iterator = 1;
	data* temp_data = NULL;
	node* temp_node = NULL;
	node* node_iter = linked_list_ptr->head;
	node* node_iter_z_m1; 
	//If index higer than lint value throw an error
	if(0 != linked_list_ptr->size) {
		if ( index <= linked_list_ptr->size-1) {
			if (index == 0) {
				temp_node = linked_list_ptr->head;
				linked_list_ptr->head = (node*)temp_node->next;
			} else {
				//Move the pointer to the index where the data will be
				//deleted
				while(iterator<=index){
					iterator++;
					node_iter_z_m1 = node_iter;
					node_iter = (node*)node_iter->next;
				}
				temp_node = node_iter;
				if(temp_node->next == NULL){
					//Delete the current item
					node_iter_z_m1->next = NULL;
				} else {
					//Bypass current item
					node_iter_z_m1->next = temp_node->next;
				}
			}
			linked_list_ptr->size--;
			temp_data = temp_node->value_ptr;
			//Free temp node memory only
			free((void*)temp_node);
		}
	}
	return temp_data;
}

size_t get_size(linked_list* linked_list_ptr)
{
	return linked_list_ptr->size;
}


