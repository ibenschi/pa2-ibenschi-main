#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "sequence.h"
#include "shell_array.h"

long *Array_Load_From_File(char *filename, int *size)
{
  FILE* input = fopen(filename, "r");
  if ( !input )
  {
    return NULL;
  }

  
  long* array =  ( long * ) malloc( sizeof(long) * INT_MAX );
  
  *size = 0;
  int x;

  do
  {
    x = fread( array + *size, sizeof( long ), 1, input );
    *size += x;
  } while(x);
  
  fclose(input);
  return array;
}

int Array_Save_To_File(char *filename, long *array, int size)
{
  FILE* output = fopen(filename, "w");
  int count = 0;

  if (!output)
  {
    fclose(output);
    return -1;
  }

  for ( int i = 0; i < size; i++ )
  {
    count += fwrite( array + i , 1 , sizeof(long) , output );
  }

  fclose( output );

  return count;
}


void Array_Shellsort(long *array, int size, long *n)
{
  int seq_size = 0;
  long* sequence = Generate_2p3q_Seq( size, &seq_size );
  for (long gap = h31(size); gap > 0; gap = (gap -  1)/3)
  {
    //long gap = sequence[x];

    for (long i = gap; i < size; i++)
    {
      long temp = array[i];
      long j;  

      for (j = i; j >= gap && array[j - gap] > temp; j -= gap)
      {
        (*n)++;
        array[j] = array[j - gap];
      }

      if ( (j >= gap) && !(array[j - gap] > temp) ) (*n)++;

      array[j] = temp;
    }
  }

  free( sequence );
  return;
}