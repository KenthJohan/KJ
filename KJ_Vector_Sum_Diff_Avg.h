#pragma once

//uint16_t
#include <stdint.h>

float KJ_Vector_Sum_Diff_Avg 
(
   uint16_t const * Left, 
   uint16_t const * Right, 
   size_t Count
)
{
   float Sum = 0;
   for (size_t I = 0; I < Count; I = I + 1)
   {
      Sum = Sum + (float)(Left [I] - Right [I]);
   }
   Sum = Sum / Count;
   return Sum;
}
