#pragma once

#include <assert.h>

//uint_8
#include <stdint.h>

//size_t
#include <sys/types.h>

//FLT_MIN
#include <float.h>

//NULL
#include <stddef.h>

struct KJ_Range_int
{
   int A;
   int B;
};

struct KJ_Range_u16
{
   uint16_t A;
   uint16_t B;
};

struct KJ_Range_float
{
   float A;
   float B;
};


void KJ_Range_int_Init (struct KJ_Range_int * Range)
{
   Range->A = INT32_MAX;
   Range->B = INT32_MIN;
}

void KJ_Range_float_Init (struct KJ_Range_float * Range)
{
   Range->A = FLT_MAX;
   Range->B = FLT_MIN;
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
      if (Data [I] > *Max)
      {
         *Max = Data [I];
      }
      if (Data [I] < *Min)
      {
         *Min = Data [I];
      }
   }
   assert (*Max >= *Min);
}


void KJ_Range_Find_int (int const * Data, size_t Count, struct KJ_Range_int * Range)
{
   KJ_Range_Primitive_Find_int (Data, Count, &(Range->A), &(Range->B));
}


void KJ_Range0_Minmax_Shared_u16
(
   uint16_t const * Data, 
   size_t Count, 
   uint16_t * Min, 
   uint16_t * Max
)
{
   assert ((Count > 0 && Data != NULL) || (Count == 0));
   for (size_t I = 0; I < Count; I = I + 1)
   {
      if (Data [I] > *Max)
      {
         *Max = Data [I];
      }
      if (Data [I] < *Min)
      {
         *Min = Data [I];
      }
   }
   assert (*Max >= *Min);
}


void KJ_Range0_Minmax_Single_u16
(
   uint16_t const * Data, 
   size_t Count, 
   uint16_t * Min, 
   uint16_t * Max
)
{
   *Min = UINT16_MAX;
   *Max = 0;
   KJ_Range0_Minmax_Shared_u16 (Data, Count, Min, Max);
}

void KJ_Range_Minmax_Shared_u16 (uint16_t const * Data, size_t Count, struct KJ_Range_u16 * Range)
{
   KJ_Range0_Minmax_Shared_u16 (Data, Count, &(Range->A), &(Range->B));
}

void KJ_Range_Minmax_Single_u16 (uint16_t const * Data, size_t Count, struct KJ_Range_u16 * Range)
{
   KJ_Range0_Minmax_Single_u16 (Data, Count, &(Range->A), &(Range->B));
}


void KJ_Range_Primitive_Find_float
(
   float const * Data, 
   size_t Count, 
   float * Min, 
   float * Max
)
{
   assert ((Count > 0 && Data != NULL) || (Count == 0));
   for (size_t I = 0; I < Count; I = I + 1)
   {
      if (Data [I] > *Max)
      {
         *Max = Data [I];
      }
      if (Data [I] < *Min)
      {
         *Min = Data [I];
      }
   }
   assert (*Max >= *Min);
}


void KJ_Range_Find_float (float const * Data, size_t Count, struct KJ_Range_float * Range)
{
   KJ_Range_Primitive_Find_float (Data, Count, &(Range->A), &(Range->B));
}
