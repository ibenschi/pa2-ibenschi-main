#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char *argv[])
{
  
   
  int size;
  long n = 0;

  if (argc != 4)
  {
    printf("\n ERROR: argc should equal 4\n");
    return EXIT_FAILURE;
  }
  
  if (argv[1][1] == 'a')
  {
    long* FileArray = Array_Load_From_File( argv[2], &size );
  
    if (!FileArray)
    {
      free(FileArray);
      printf("ERROR: invalid file\n");
      return EXIT_FAILURE;
    }
  
    Array_Shellsort( FileArray, size, &n );
    Array_Save_To_File( argv[3], FileArray, size );
    printf("Value of n: %ld\n", n);
    free( FileArray ); 
  }
  
  if (argv[1][1] == 'l')
  {
    Node* head = List_Load_From_File(argv[2]);
    if (!head)
    {
      printf("\nERROR: invalid file\n");
      return EXIT_FAILURE;
    }
    head = List_Shellsort(head, &n); 
    printf("%ld\n", n);
    List_Save_To_File(argv[3], head);
  } 
  return EXIT_SUCCESS;
}

