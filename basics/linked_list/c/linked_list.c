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
 *
 * @return data* , data pointer with the new element copied
 *
 * @code
 * int element = 9;
 * data *new_data_ptr = new_data(element, sizeof(element));
 * @endcode
 *
 */
data* new_data(void* data_ptr, size_t size)
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





