#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"

int h31(int x)
{
  int h = 1;
  int next;
  while(1)
  {
    next = 3*h + 1;
    if (next >= x) return h;
    h = next;
  }
}

long *Generate_2p3q_Seq(int n, int *seq_size)
{
  *seq_size = 0;
  long* sequence = ( long * ) malloc( sizeof( long ) * n );

  if ( !sequence || ( n < 2 ) )
  {
    return NULL;
  }

  int two_index = 0;
  int three_index = 0;
  int two_prod;
  int three_prod;

  sequence[0] = 1;

  for ( int i = 1; i < n; i++ )
  {
    two_prod = 2 * sequence[two_index];
    three_prod = 3 * sequence[three_index];
    sequence[i] = (two_prod < three_prod) ? two_prod : three_prod;

    if ( sequence[i] > n )
    {
      sequence[i] = 0;
      ( *seq_size ) = i;
      return sequence;
    }

    two_index += (two_prod <= three_prod);
    three_index += (two_prod >= three_prod);

  }

  return sequence;
}
