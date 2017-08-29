#pragma once

#include <assert.h>

//uint_8
#include <stdint.h>

//size_t
#include <sys/types.h>

//NULL
#include <stddef.h>

struct KJ_Range_int
{
   int A;
   int B;
};


void KJ_Range_int_Init (struct KJ_Range_int * Range)
{
   Range->A = INT32_MAX;
   Range->B = INT32_MIN;
}

void KJ_Range_Relax_GT (int * Max, int Value)
{
   if (Value > *Max)
   {
      *Max = Value;
   }
}

void KJ_Range_Relax_LT (int * Min, int Value)
{
   if (Value < *Min)
   {
      *Min = Value;
   }
}

void KJ_Range_Primitive_Find_int
(
   int const * Data, 
   size_t Count, 
   int * Min, 
   int * Max
)
{
   assert ((Count > 0 && Data != NULL) || (Count == 0));
   for (size_t I = 0; I < Count; I = I + 1)
   {
      KJ_Range_Relax_GT (Max, Data [I]);
      KJ_Range_Relax_LT (Min, Data [I]);
   }
   assert (*Max >= *Min);
}


void KJ_Range_Find_int (int const * Data, size_t Count, struct KJ_Range_int * Range)
{
   KJ_Range_Primitive_Find_int (Data, Count, &(Range->A), &(Range->B));
}


void KJ_Range_Primitive_Find_u16
(
   uint16_t const * Data, 
   size_t Count, 
   int * Min, 
   int * Max
)
{
   assert ((Count > 0 && Data != NULL) || (Count == 0));
   for (size_t I = 0; I < Count; I = I + 1)
   {
      KJ_Range_Relax_GT (Max, Data [I]);
      KJ_Range_Relax_LT (Min, Data [I]);
   }
   assert (*Max >= *Min);
}


void KJ_Range_Find_u16 (uint16_t const * Data, size_t Count, struct KJ_Range_int * Range)
{
   KJ_Range_Primitive_Find_u16 (Data, Count, &(Range->A), &(Range->B));
}
