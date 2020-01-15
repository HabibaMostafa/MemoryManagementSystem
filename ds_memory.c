/**************************************************************************
 Habiba Mostafa
 1070307
 mostafah@uoguelph.ca
 *************************************************************************/
#include "ds_memory.h"


/* Defining global variables */

struct ds_file_struct ds_file;
struct ds_counts_struct ds_counts;


/* This function creates a file consisting of a header that represents the block array */

int ds_create( char *filename, long size ){
    
    int i;
    char byte;
    int fwriteReturn = 0;

    FILE* fptr = fopen (filename, "wb+");

    if(fptr == NULL){
        printf("Error - could not open file");
        return 1;
    }
    
    /* Initializing the file header variables inside the global variable ds_file */
    ds_file.block[0].start = 0;
    ds_file.block[0].length = size;
    ds_file.block[0].alloced = 0;

    /* Looping through all elements of the block array and initializing them to zero */
    for(i = 1; i < MAX_BLOCKS; i++){
        ds_file.block[i].start = 0;
        ds_file.block[i].length = 0;
        ds_file.block[i].alloced = 0;
    }

    /* Writing header to the file */
    fwriteReturn = fwrite(ds_file.block, sizeof(struct ds_blocks_struct), MAX_BLOCKS, fptr);

    for(i = 0; i < size; i ++){
        fwrite(&byte, sizeof(byte), 1, fptr);
    }
    
    fclose(fptr);

    /* Checking for successful function run */
    if (fptr == NULL){
        printf("Error - could not close file");
        return 1;
    }
    if (( fptr == NULL) || (fwriteReturn != MAX_BLOCKS)){
        return 1;
    } else {
        return 0;
    }

}


/* This function opens and initializes the given file, reading its contents into the global variable ds_file.block */
int ds_init( char *filename ){

    ds_file.fp = fopen(filename, "rb+");

    if(ds_file.fp == NULL){
        printf("Error - could not open file");
        return 1;
    }

    /* Checking for successful function run */
    if (fread(ds_file.block, sizeof(struct ds_blocks_struct), MAX_BLOCKS, ds_file.fp) == 0 ){
        return 1;
    }

    /* Initializing counts of reads and writes */
    ds_counts.reads = 0;
    ds_counts.writes = 0;

    return 0;

}


/* This is a test function to display the layout and contents of all blocks */
void ds_test_init(){

    int i;
    
    /* Looping through elements of the block to initialize variables accordingly */
    for(i = 0; i < MAX_BLOCKS; i++){
        printf("%d\t", i);
        printf("%ld\t", ds_file.block[i].start);
        printf("%ld\t", ds_file.block[i].length);
        printf("%d\n", (int)ds_file.block[i].alloced);
    }

    printf("reads: %d\n", ds_counts.reads);
    printf("writes: %d\n", ds_counts.writes);

    return;

}


/* This function allocates space for the long amount specified, declaring an alloced value accordingly */
long ds_malloc( long amount ){

    int i;
    int j;
    long start = 0;

    for(i = 0; i < MAX_BLOCKS; i++){
        long original_length = ds_file.block[i].length;

        /* Checking for occupied blocks, filling it in and allocating space accordingly */
        if((ds_file.block[i].length >= amount) && ((int)ds_file.block[i].alloced == 0)){
            ds_file.block[i].length = amount;
            ds_file.block[i].alloced = 1;
            start = ds_file.block[i].start;

            for(j = 0; j < MAX_BLOCKS; j++){
                if(ds_file.block[j].length == 0){
                    ds_file.block[j].start = ds_file.block[i].start + amount;
                    ds_file.block[j].length = original_length - amount;
                    ds_file.block[j].alloced = 0;
                    break;
                }
            }
            return start;
        }
    }

    return -1;

}


/* This function distinguishes between an avaialable block and an alloced one by iteration through all blocks */

void ds_free( long start ){

    int i;

    for(i = 0; i < MAX_BLOCKS; i++){
        if(ds_file.block[i].start == start){
            ds_file.block[i].alloced = 0; 
       }
    }

    return;
}


/* ds_finish writes the block array into the header at the beginning of the file and closes the file */

int ds_finish(){

    int fwriteReturnValue = 0;
 
    /* Reaching the beginning of the file */
    fseek(ds_file.fp, 0, SEEK_SET);
        
    fwriteReturnValue = fwrite(ds_file.block, sizeof(struct ds_blocks_struct), MAX_BLOCKS, ds_file.fp);
    
    ds_counts.writes++;

    printf("reads: %d \n", ds_counts.reads);
    printf("writes: %d \n", ds_counts.writes);

    fclose(ds_file.fp);
    
    if(fwriteReturnValue != 0){
        return 1;
    } else {
        return 0;
    }

}


/* This function reads from the file and returns a non zero value upon success */

void *ds_read( void *ptr, long start, long bytes ){

    int readReturnValue = 0;

    fseek(ds_file.fp, (sizeof(struct ds_blocks_struct) * MAX_BLOCKS + start), SEEK_SET);

    readReturnValue = fread(ptr, bytes, 1, ds_file.fp);

    if (readReturnValue != 0){
        ds_counts.reads++;
        return ptr;
    } 
    else {
        return NULL;
    }

}


/* This function sets the start position of the file - offset by the length of the header and writes bytes
   to the file, incrementing the writes and reads counts accordingly.  */

long ds_write( long start, void *ptr, long bytes ){

    int writeReturnValue = 0;
    long position = 0;
    
    /* Calculating the offset position according to the length of the header */
    position = (sizeof(struct ds_blocks_struct) * MAX_BLOCKS) + start;

    fseek(ds_file.fp, position, SEEK_SET);

    writeReturnValue = fwrite(ptr, bytes, 1, ds_file.fp);
    
    /* Checking for successful writing to the binary file */
    if (writeReturnValue != 0){
        ds_counts.writes ++;
        return start;
    }
    else {
        return -1;
    }

}

