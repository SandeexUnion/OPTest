# include <stdio.h>
# include <assert.h>

# include "bitset.h"

 int bitset_checkValue ( bitset *a , unsigned value ) {
     return value >= 0 && value <= a -> maxValue ;
     }

 bitset bitset_create ( unsigned setMaxValue ) {
     assert ( setMaxValue < 32) ;
     return ( bitset ) {0 , setMaxValue };
     }
 bitset bitset_intersection ( bitset set1 , bitset set2 ) {
     assert ( set1 . maxValue == set2 . maxValue ) ;
     return ( bitset ) { set1 . values & set2 . values , set1 . maxValue };
     }
 void bitset_print ( bitset set ) {
     printf ("{") ;
     int isEmpty = 1;
     for (int i = 0; i <= set . maxValue ; ++ i ) {
         if ( bitset_in ( set , i ) ) {
             printf ("%d, ", i ) ;
             isEmpty = 0;
             }
         }
     if ( isEmpty )
         printf ("}\n") ;
     else
     printf ("\b\b}\n") ;
     }

 // ...