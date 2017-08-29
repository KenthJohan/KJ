#pragma once

#include <assert.h>

//uint_8
#include <stdint.h>

//size_t
#include <sys/types.h>

//abs
#include <stdlib.h>


void KJ_LPIR_u16
(
   uint16_t const * Input,
   uint16_t * Background,
   uint16_t * Output,
   size_t Count,
   int K
)
{
   float B;
   for (size_t I = 0; I < Count; I = I + 1)
   {
      B = ((float)Input [I] / (float)K) + (float)Background [I] - ((float)Background [I] / (float)K);
      Background [I] = (int)B;
      //Background [I] = Input [I];
      Output [I] =  abs (Input [I] - Background [I]);
   }
}

void KJ_LPIR_Offset_u16
(
   uint16_t const * Input,
   uint16_t * Background,
   uint16_t * Output,
   size_t Count,
   int K,
   float Offset
)
{
   float B;
   for (size_t I = 0; I < Count; I = I + 1)
   {
      B = ((float)Input [I] / (float)K) + (float)Background [I] - ((float)Background [I] / (float)K);
      Background [I] = (int)B;
      //Background [I] = Input [I];
      Output [I] =  abs (Input [I] - Background [I] + Offset);
   }
}
