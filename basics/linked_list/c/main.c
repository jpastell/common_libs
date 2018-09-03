//    
//    link_list.h
//
//    Main file for generic link list in c. Main runs multiple
//    test used for commits.
//
//    Created by Juan Pablo Castellanos on 26/8/18
//    Copyright © 2018 Juan Pablo Castellanos. All rights reserved.
//

//API to be tested
#include "linked_list.h"

//STD libraries used for testing
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int test_data_generation(size_t vector_test_length)
{
	//iterator index
	int iterator=0;
	int data_random;
	int error=0;
	//Define seed values for randomization
	unsigned seed = (unsigned)time(NULL);
	printf("Using seed %d for randomization\n",seed);
	//Setting seed value
	srand(seed);
	//Iterator elements
	data** data_iter;
	int* int_iter;
	//Data containers
	data** data_head = (data**)malloc(sizeof(data*)*vector_test_length);
	int* int_head = (int*)malloc(sizeof(int)*vector_test_length);
	//populate the memory allocated
	for(iterator=0;iterator<vector_test_length;iterator++){
		data_random = rand();
		//Adjust pointers
		data_iter = data_head + iterator;
		int_iter = int_head + iterator;
 		//Populate the data
		*data_iter = new_data((void*)&data_random,sizeof(data_random),NULL);		
		*int_iter = data_random;			
	}
	//Verify the data matches
	for(iterator=0;iterator<vector_test_length;iterator++){
		data_iter = data_head + iterator;
		int_iter = int_head + iterator;
		if(*int_iter !=  *((int*)((*data_iter)->data_ptr))){
			printf("Error at iteration %d,:\n",iterator);
			printf("Data received: %d, ", *((int*)((*data_iter)->data_ptr)));
			printf("Data expected: %d\n", *int_iter);
			error += 1;
		}
		//Release any data allocated in the array
		delete_data(*data_iter);

	}
	//Release memory
	free((void*)data_head);
	free((void*)int_head);
	return error;
}

void print_int(void * data){
	printf("Value : %d\n",*((int*)data));
}

int test_linked_list_creation(void (*pfunc) (void*)){
	//Define seed values for randomization
	unsigned seed = (unsigned)time(NULL);
	printf("Using seed %d for randomization\n",seed);
	//Setting seed value
	srand(seed);
	//Create empty linked list
	linked_list* ll_pointer;
        ll_pointer = new_linked_list(NULL);
	if(ll_pointer->head != NULL ) {
		printf("Invalid head for empty linked list\n");
		delete_linked_list(ll_pointer);
		return -1;
	}
	if(get_size(ll_pointer) != 0) {
		printf("Invalid size for empty linked list\n");
		delete_linked_list(ll_pointer);
		return -2;
	}
	delete_linked_list(ll_pointer);


	//Create a non empty linked list
	int data_test =rand();	
	ll_pointer =  new_linked_list(new_data((void*)(&data_test),sizeof(data_test),pfunc));
	
	if(ll_pointer->head != NULL ) {
		//Get the index 0 value
		data* test;
		test = get_data(ll_pointer,0);
		if(data_test != *((int*)(test->data_ptr))){
			delete_linked_list(ll_pointer);
			return -3;
		}
	} else {
		printf("NULL is not epected for initilized linke dlist\n");
		delete_linked_list(ll_pointer);
		return -4;
	}

	if(get_size(ll_pointer) != 1) {
		printf("Invalid size for non empty linked list\n");
		delete_linked_list(ll_pointer);

		return -5;
	}
	print_linked_list(ll_pointer);
	delete_linked_list(ll_pointer);
	return 0;
}

int linked_list_insertion(void (*pfunc) (void*))
{
	//Define seed values for randomization
	unsigned seed = (unsigned)time(NULL);
	//Testing variables
	int data_test, status,compare;
	data* test;
	printf("Using seed %d for randomization\n",seed);
	//Setting seed value
	srand(seed);


	//[--] Create an empty linked list and add 1 item
	data_test = rand();
	linked_list* ll_pointer =  new_linked_list(NULL);
	//Insert invalid index
	status = insert_data(ll_pointer,new_data((void*)(&data_test),\
						sizeof(data_test),pfunc),1);
	if(status == 0){
		printf("We wre expecting and issue here\n");
		delete_linked_list(ll_pointer);
		return -1;
	}
	//Insert valid index
	status = insert_data(ll_pointer,new_data((void*)(&data_test),\
						sizeof(data_test),pfunc),0);
	if(status != 0){
		printf("Unable to insert data at index 0\n");
		delete_linked_list(ll_pointer);
		return -1;
	}
	print_linked_list(ll_pointer);
	//[--] Push data at index 0
	data_test =rand();
	test = get_data(ll_pointer,0);
	compare = *((int*)(test->data_ptr));

	status = insert_data(ll_pointer,new_data((void*)(&data_test),\
						sizeof(data_test),pfunc),0);
	if(status != 0){
		printf("Unable to insert data at index 0\n");
		delete_linked_list(ll_pointer);
		return -1;
	} else {
		test = get_data(ll_pointer,1);
		if(compare != *((int*)(test->data_ptr))){
			printf("Data inserted does not match\n");
			delete_linked_list(ll_pointer);
			return -1;
		}	
	}
	print_linked_list(ll_pointer);
	//[--] Setting data at the end
	data_test =rand();
	status = insert_data(ll_pointer,new_data((void*)(&data_test),\
						sizeof(data_test),pfunc),ll_pointer->size);
	if(status != 0){
		printf("Unable to insert data at the end\n");
		delete_linked_list(ll_pointer);
		return -3;
	} else {
		test = get_data(ll_pointer,(ll_pointer->size)-1);
		if(data_test != *((int*)(test->data_ptr))){
			printf("Data inserted at the end does not maches\n");
			delete_linked_list(ll_pointer);
			return -1;
		}
	}
	print_linked_list(ll_pointer);
	//[--] Setting data at the end-1	
	data_test =rand();
	status = insert_data(ll_pointer,new_data((void*)(&data_test),\
						sizeof(data_test),pfunc),(ll_pointer->size)-1);
	if(status != 0){
		printf("Unable to insert data at the end -1\n");
		delete_linked_list(ll_pointer);
		return -3;
	} else {
		test = get_data(ll_pointer,(ll_pointer->size)-2);
		if(data_test != *((int*)(test->data_ptr))){
			printf("Data inserted at the end does not maches\n");
			delete_linked_list(ll_pointer);
			return -1;
		}
	}
	print_linked_list(ll_pointer);
	delete_linked_list(ll_pointer);
	return 0;
}


int change_data_test(size_t iterations,void (*pfunc) (void*))
{
	//iterator index
	int iterator=0;
	int data_random;
	int* head_int;
	data* data_test;

	//Define seed values for randomization
	unsigned seed = (unsigned)time(NULL);
	printf("Using seed %d for randomization\n",seed);
	//Setting seed value
	srand(seed);
	//Linked list used for testing
	linked_list* ll_pointer =  new_linked_list(NULL);
	//Create an array of elemnts for testing
	head_int = (int*)malloc(sizeof(int)*iterations);
	//Iterate the list to populate the elements in the linked list
	//and reference data
	for(;iterator<iterations;iterator++){
		data_random = rand();
		*(head_int+iterator) = data_random;
		if(insert_data(ll_pointer,new_data((void*)(&data_random),\
						sizeof(data_random),pfunc),iterator)){
		
			//Free resources
			delete_linked_list(ll_pointer);
			free((void*)head_int);
			return -1;
		}
	}
	print_linked_list(ll_pointer);
	//Iterate the list from top to bottoom to compare the data
	for(iterator--;iterator>=0;iterator--){
		data_test = get_data(ll_pointer,iterator);
		data_random = *((int*)(data_test->data_ptr));
		data_random++;
		data_test = change_data(ll_pointer,\
				new_data((void*)(&data_random),sizeof(data_random),pfunc),
				iterator);
		delete_data(data_test);
		data_test = get_data(ll_pointer,iterator);
		if(((*(head_int+iterator))+1) != *((int*)(data_test->data_ptr))){
			printf("Error at %d\n",iterator);
			//Free resources
			delete_linked_list(ll_pointer);
			free((void*)head_int);
			return -2;
		}
	}
	print_linked_list(ll_pointer);
	delete_linked_list(ll_pointer);
	free((void*)head_int);
	return 0;
}

int delete_data_test(size_t iterations,void (*pfunc) (void*))
{
	//iterator index
	int iterator=0;
	int data_random;
	int* head_int;
	data* data_test;

	if(iterations >=3 ){
		//Define seed values for randomization
		unsigned seed = (unsigned)time(NULL);
		printf("Using seed %d for randomization\n",seed);
		//Setting seed value
		srand(seed);
		//Linked list used for testing
		linked_list* ll_pointer =  new_linked_list(NULL);
		//Create an array of elemnts for testing
		head_int = (int*)malloc(sizeof(int)*iterations);
		//Iterate the list to populate the elements in the linked list
		//and reference data
		for(;iterator<iterations;iterator++){
			data_random = rand();
			*(head_int+iterator) = data_random;
			if(insert_data(ll_pointer,new_data((void*)(&data_random),\
							sizeof(data_random),pfunc),iterator)){
		
				//Free resources
				delete_linked_list(ll_pointer);
				free((void*)head_int);
				return -1;
			}
		}
		print_linked_list(ll_pointer);
		//Erase elements in the list
		//Erase at the beginign
		printf("Erase at the befining\n");
		data_random = get_size(ll_pointer);
		data_test = delete_data_linked(ll_pointer,0);
		if(*head_int != *(int*)(data_test->data_ptr)){
			printf("Data erased mismatch\n");
			delete_data(data_test);
			delete_linked_list(ll_pointer);
			free((void*)head_int);
			return -1;
		}
		delete_data(data_test);
		if(--data_random != get_size(ll_pointer)){
			printf("Size mismatch\n");
			delete_linked_list(ll_pointer);
			free((void*)head_int);
			return -1;
		}
		print_linked_list(ll_pointer);
		//Erase at the end
		printf("Erase at the end\n");
		data_random = get_size(ll_pointer);
		data_test = delete_data_linked(ll_pointer,get_size(ll_pointer)-1);
		if(*(head_int+ (iterations-1)) != *(int*)(data_test->data_ptr)){
			printf("Data erased mismatch\n");
			delete_data(data_test);
			delete_linked_list(ll_pointer);
			free((void*)head_int);
			return -1;
		}
		delete_data(data_test);
		if(--data_random != get_size(ll_pointer)){
			printf("Size mismatch\n");
			delete_linked_list(ll_pointer);
			free((void*)head_int);
			return -1;
		}
		print_linked_list(ll_pointer);
		//Erase in the midle
		//Data at 0 and dat aat iteration-1 are gone
		//stratting at index 1 to iteration-2
		printf("Erase at the midle\n");
		int new_index  = get_size(ll_pointer)/2;
		data_random = get_size(ll_pointer);
		data_test = delete_data_linked(ll_pointer,new_index);
		//printf("Size = %d\n",data_random);
		if(*(head_int+(new_index+1)) != *(int*)(data_test->data_ptr)){
			printf("Data erased mismatch\n");
			delete_data(data_test);
			delete_linked_list(ll_pointer);
			free((void*)head_int);
			return -1;
		}
		print_linked_list(ll_pointer);
		delete_data(data_test);
		//printf("Size = %zu\n",get_size(ll_pointer));
		if(--data_random != get_size(ll_pointer)){
			printf("Size mismatch\n");
			delete_linked_list(ll_pointer);
			free((void*)head_int);
			return -1;
		}
		print_linked_list(ll_pointer);
		delete_linked_list(ll_pointer);
		free((void*)head_int);
		return 0;
	} else {
		printf("Minimum interation number is 2");
		return -2;
	}
}



int main(int argc, const char * argv[])
{
	int status;
	/*
	printf("Running test data gen: ");
	status = test_data_generation(1000);
	if(status == 0) {
		printf("Passed\n");
	} else {
		printf("Failed\n");
		return status;

	}
	printf("Linked list creation: ");
	status = test_linked_list_creation(&print_int);
	if(status == 0) {
		printf("Passed\n");
	} else {
		printf("Failed\n");
		return status;

	}
	printf("Linked list insertion: ");
	status = linked_list_insertion(&print_int);
	if(status == 0) {
		printf("Passed\n");
	} else {
		printf("Failed\n");
		return status;

	}
	*/


	/*
	change_data_test(8,&print_int);
	*/

	delete_data_test(8,&print_int);

	return 0;
}


