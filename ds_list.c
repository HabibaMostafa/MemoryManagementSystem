/**************************************************************************
 Habiba Mostafa
 1070307
 mostafah@uoguelph.ca
 *************************************************************************/

#include "ds_list.h"
#include "ds_memory.h"


/* Creating a list by initializing the file and allocating space for the first long
   It then writes the allocated variable into the file and closes the file */

void ds_create_list(){

    long listValue = 0;
    ds_init("list.bin");
    ds_malloc(sizeof(listValue));
    listValue = -1;
    ds_write(0, &listValue, sizeof(long));
    ds_finish();

}


/* This function opens and initializes the given file, reading its contents into the 
   global variable ds_file.block */

int ds_init_list(){

    ds_init("list.bin");

    return 0;

}


/* This finds an element within the list at a given index. traverses the linked list 
   accordingly and replaces it by the given value */

int ds_replace( int value, long index ){

    struct ds_list_item_struct previous;
    struct ds_list_item_struct remove;
    
    long freeLocation;
    long previous_location = 0;
    long i;

    ds_read(&previous.next, 0, sizeof(long));
    
    for(i = index; i >= 0; i--){
        if(previous.next == -1){
            return -1;
        } else {
            previous_location = previous.next;
            ds_read(&previous, previous.next, sizeof(struct ds_list_item_struct));
        }
    }
    /* Assinging the value to the previous item struct variable to update it */
    previous.item = value;
    ds_write(previous_location, &previous, sizeof(struct ds_list_item_struct));

    return 0;

}


/* This function allows inserting a new element to the existing linked list at a 
   specific index by traversing the list as necessessary as long as -1 isn't reached 
   i.e. the end of the list */

int ds_insert( int value, long index ){

    struct ds_list_item_struct previous;
    struct ds_list_item_struct new;
    
    long previous_location = 0;
    long i;

    ds_read(&previous.next, 0, sizeof(long));
    
    for(i = index; i > 0; i--){
        if(previous.next == -1){
            return -1;
        } else {
            previous_location = previous.next;
            ds_read(&previous, previous.next, sizeof(struct ds_list_item_struct));
        }
    }

    new.next = previous.next;
    new.item = value;

    previous.next = ds_malloc(sizeof(struct ds_list_item_struct));    

    ds_write(previous.next, &new, sizeof(struct ds_list_item_struct));

    if(previous_location == 0){
        ds_write(0, &previous.next, sizeof(long));
    } else {
        ds_write(previous_location, &previous, sizeof(struct ds_list_item_struct));
    }
 
    return 0;

}


/* Additional function to print the contents of the list and test functionality */

int print_list(){

    long loc = 0;

    struct ds_list_item_struct li;

    ds_read(&li.next, 0, sizeof(long));

    printf("LOCATION | ITEM | NEXT\n");

    while(li.next != -1){
        loc = li.next;
        ds_read(&li, loc, sizeof(struct ds_list_item_struct));
        printf("%3ld | %3d | %3ld\n", loc, li.item, li.next);
    }

    return 0;

}


/* This function deletes an elements from the list as it traverses to a certain index */

int ds_delete( long index ){

    struct ds_list_item_struct previous;
    struct ds_list_item_struct remove;
    
    long freeLocation;
    long previous_location = 0;
    long i;

    ds_read(&previous.next, 0, sizeof(long));
    
    for(i = index; i > 0; i--){
        if(previous.next == -1){
            return -1;
        } else {
            previous_location = previous.next;
            ds_read(&previous, previous.next, sizeof(struct ds_list_item_struct));
        }
    }

    freeLocation = previous.next;
    
    ds_read(&remove, previous.next, sizeof(struct ds_list_item_struct));
    
    previous.next = remove.next;
    
    ds_write(previous_location, &previous, sizeof(struct ds_list_item_struct));

    ds_free(freeLocation);

    return 0;
}


int ds_swap( long index1, long index2){

    return 0;
}


long ds_find( int target ){

    return 0;
}

/* This function accesses a file and scans the integers stored in the file to input them
   into the current list accordingly */

int ds_read_elements( char * filename){

    int value = 0;
    int index = 0;

    FILE * fptr = fopen(filename, "r");

    if(fptr == NULL){
        printf("Error - could not open file");
        return 1;
    }

    while(fscanf(fptr, "%d", &value) == 1){
        ds_insert(value, index);
        index++;
    }

    fclose(fptr);

    return 0;
}


/* Calling ds_finish from the memory.c file to perform appropriate writes and close the file */

int ds_finish_list(){

    if(ds_finish() == 1){
        return 0;
    } else {
        return 1;
    }

}



