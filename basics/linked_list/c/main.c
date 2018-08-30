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
		*data_iter = new_data((void*)&data_random,sizeof(data_random));		
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



int main(int argc, const char * argv[]){
	test_data_generation(1000);
	return 0;
}


