#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "sequence.h"
#include "shell_list.h"

void printList(Node* n)
{
    while (n != NULL) {
        printf("\n%ld ", n->value);
        n = n->next;
    }
}

Node* GetListElement(Node* head, int index)
{
  Node* node = head;
  if (index < 0) return NULL;
  for (int i = 0; i < index; i++) 
    {
      if (!node) return NULL;
      node = node -> next;
    }

  return  node;
}

long GetListLong(Node* head, int index)
{
  Node* node = head;
  for (int i = 0; i < index; i++) node = node -> next;
  return  node -> value;
}

Node *List_Load_From_File(char *filename)
{
  FILE* input = fopen(filename, "r");

  if ( !input ) return NULL;

  Node* head = ( Node* ) malloc( sizeof( Node ) );
  head -> next = NULL;
  Node* current = head;

  long val = 0;

  int x = fread( &val, sizeof( long ), 1, input );
  while(x)
  {
    current -> value = val;
    if ( ( x = fread( &val, sizeof( long ), 1, input ) ) )
    {
      Node* next = ( Node* ) malloc( sizeof( Node ) );
      current -> next = next;
      current = current -> next;
      current -> next = NULL;
    }
  }
  fclose(input);
  return head;
}

int List_Save_To_File(char *filename, Node *list)
{
  FILE* output = fopen(filename, "w");
  Node* current = list;
  Node* ToFree = NULL;

  int count = 0;

  if (!output) fclose(output);

  while(current)
  {
    //printf("%ld\n", current -> value);
    count += output && fwrite( &(current -> value) , 1 , sizeof(long) , output );
    ToFree = current;
    current = current -> next;
    free(ToFree);
  }

  fclose( output );
  return count;
}

Node *List_Shellsort(Node *list, long *n)
{
  int size = 0;
  Node* listCopy = list;
  while(listCopy)
  {
    size++;
    listCopy = listCopy -> next;
  }

  for (int gap = h31(size); gap > 0; gap /= 3)
  {
    Node* LeftX_ = NULL; 
    Node* LeftY = NULL;
    Node* LeftY_ = GetListElement(list, gap - 1);
    for ( long i = 0; i < size - gap; i++)
    { 
      Node* LeftX = LeftX_;
      Node* xNode = list;
      LeftY = LeftY_; 
      Node* yNode = LeftY -> next;
      for ( long j = 0; (j < size - i - gap) && ++(*n); j+=gap )
      {
        if ( yNode -> value < xNode -> value ) 
        {
          list = SwapNodes(list, LeftX, LeftY);
          Node* temp = xNode;
          xNode = yNode;
          yNode = temp;
          if (xNode == LeftY_) LeftY_ = yNode;
          if (yNode == LeftY_) LeftY_ = xNode;
        }
        LeftX = xNode;
        xNode = xNode -> next;
        LeftY = yNode;
        yNode = yNode -> next;
        
      }
    }
  }
  return list;
}


Node* SwapNodes(Node* list, Node* LeftX, Node* LeftY)
{
  Node* xNode = LeftX ? LeftX -> next : list;
  Node* yNode = LeftY -> next;

  if ( (xNode == yNode) ) return list;

  if (xNode == list)
  {
    if ( xNode -> next == yNode )
    {
      Node* temp = yNode -> next;
      yNode -> next = xNode;
      xNode -> next = temp;
      return yNode;
    }

    Node* RightX = xNode -> next;
    Node* RightY = yNode -> next;
    LeftY -> next = xNode;
    xNode -> next = RightY;
    yNode -> next = RightX;
    return yNode;
  }

  LeftX -> next = SwapNodes(xNode, NULL, LeftY);
  return list;
}
