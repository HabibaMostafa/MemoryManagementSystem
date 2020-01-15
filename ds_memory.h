/**************************************************************************
 Habiba Mostafa
 1070307
 mostafah@uoguelph.ca
 *************************************************************************/

#ifndef DS_MEMORY
#define DS_MEMORY

#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 4096

/*Defining appropriate structs required for Memory
  Management System c files*/
struct ds_counts_struct{
    int reads;
    int writes;
};

struct ds_blocks_struct{
    long start;
    long length;
    char alloced;
};

struct ds_file_struct{
    FILE *fp;
    struct ds_blocks_struct block[MAX_BLOCKS];
};

/* Defining apprpriate function protoypes required for Memory
  Management System c files */
int ds_create( char *filename, long size );
int ds_init( char *filename );
void ds_test_init();
long ds_malloc( long amount );
void ds_free( long start );
void *ds_read( void *ptr, long start, long bytes );
long ds_write( long start, void *ptr, long bytes );
int ds_finish();

#endif


