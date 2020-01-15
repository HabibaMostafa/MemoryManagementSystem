/**************************************************************************
 Habiba Mostafa
 1070307
 mostafah@uoguelph.ca
 *************************************************************************/

/* Global variable initialized */

long elements;

/* Creating an array by initializing its length and the file that it belongs to. */

int ds_create_array(){

    long arrayLength = 0;
    elements = 0;
    arrayLength = 256 * 4;

    ds_init("array.bin");
    
    ds_malloc(sizeof(long)); 
    
    ds_malloc(arrayLength);
    
    ds_write(0, &elements, sizeof(long));
    
    ds_finish();

    /* Checking for ds_create_array functionality */
    if ((ds_init("array.bin") != 0) || (ds_malloc(sizeof(long)) != -1) || (ds_finish() == 1)){
        return -1;
    } else {
        return 0;
    }
}


/* Additional function to print the contents of the array and test functionality of other functions */

int print_array(){

    int i;
    int value = 0;
    long fileLocation = 0;
    
    printf("Array:\n");

    for(i = 0; i < elements; i++){
        fileLocation = (i * sizeof(int)) + sizeof(elements);
        ds_read(&value, fileLocation, sizeof(int));
        printf("array [%d] is %d \n", i, value);
    }

    return 0;

}

int ds_init_array(){

    ds_init("array.bin");
    ds_read(&elements, 0, sizeof(long));
    printf("elements at init %ld\n", elements);

    if((ds_init("array.bin") != 0) || ds_read(&elements, 0, sizeof(int)) == NULL){
        return 1;
    } else {
        return 0;

    }
}


/* This finds an element within the array at a given index. traverses the linked list 
   accordingly and replaces it by the given value */

int ds_replace( int value, long index ){

    long fileLocation = 0;

    fileLocation = (index * sizeof(int)) + sizeof(elements);

    if(index < elements){
        ds_write(fileLocation, &value, sizeof(int));
        return 0;
    } else {
        return -1;
    }

}

/* This function allows inserting a new element to the existing array at a specific index */

int ds_insert( int value, long index ){

    int tempOld = 0; 
    int tempNew = value;
    long fileLocation = 0;
    long i = 0;

    for(i = index; i <= elements; i++){

        /* Setting the correct offset file location according to the index and the elements */        
        fileLocation = (i * sizeof(int)) + sizeof(elements);

        if(i == elements){
            ds_write(fileLocation, &value, sizeof(int));
            break;
        } else {
           ds_read(&tempOld, fileLocation, sizeof(int));
           ds_write(fileLocation, &tempNew, sizeof(int));

           tempNew = tempOld;
        }
    }
    elements++;

    return 0;
}


/* This function deletes an elements from the array at a given index */

int ds_delete( long index ){
    
    long i = 0;
    long fileLocation = 0;
    int prevValue = 0;
    int currValue = 0;

    for(i = (elements - 1); i >= index; i--){

        fileLocation = (i * sizeof(int)) + sizeof(elements);

        if(i == (elements - 1)){
            ds_read(&prevValue, fileLocation, sizeof(long));
        } else {
            ds_read(&prevValue, fileLocation, sizeof(int));
            ds_write(fileLocation, &currValue, sizeof(int));
        }
        currValue = prevValue;
    }
    elements --;

    return 0;
}


int ds_swap( long index1, long index2 ){
    
    long fileLocation1 = 0;
    long fileLocation2 = 0;
    int value1 = 0;
    int value2 = 0;

    fileLocation1 = (index1 * sizeof(int)) + sizeof(elements);
    fileLocation2 = (index2 * sizeof(int)) + sizeof(elements);

    ds_read(&value1, fileLocation1, sizeof(int));
    ds_read(&value2, fileLocation2, sizeof(int));

    ds_write(fileLocation1, &value2, sizeof(int));
    ds_write(fileLocation2, &value1, sizeof(int));

    return 0;
}


long ds_find( int target ){

    long i = 0; 
    int value = 0;
    long fileLocation = 0;

    for(i = 0; i < elements; i++){
        fileLocation = (i * sizeof(int)) + sizeof(elements);
        ds_read(&value, fileLocation, sizeof(int));
        if(value == target){
            return i;
        }
    }

    return -1;
}


int ds_read_elements( char *filename ){

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


int ds_finish_array(){

    ds_write(0, &elements, sizeof(long));
    
    printf("elements: %ld\n", elements);
    
    ds_finish();

    return 0;

}


