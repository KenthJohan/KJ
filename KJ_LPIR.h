#pragma once

#include <assert.h>

//uint_8
#include <stdint.h>

//size_t
#include <sys/types.h>

//abs
#include <stdlib.h>

//floatf
#include <math.h>

#include "KJ_Map.h"

void KJ_LPIR_u16
(
   uint16_t const * Input,
   uint16_t * Background,
   uint16_t * Output,
   size_t Count,
   float K
)
{
   for (size_t I = 0; I < Count; I = I + 1)
   {
      Background [I] = K * (float) Input [I] + (1.0f - K) * (float) Background [I];
      Output [I] =  abs ((float) Input [I] - (float) Background [I]);
   }
}


void KJ_LPIR1_u16
(
   uint16_t const * Input,
   uint16_t * Background,
   uint16_t * Output,
   size_t Count,
   float K
)
{
   for (size_t I = 0; I < Count; I = I + 1)
   {
      Output [I] =  abs ((float) Input [I] - Background [I]);
      float G;
      G = KJ_Map_float (Output [I], 0.0f, 255.0f, 0.0f, 1.0f);
      Background [I] = G * (float) Background [I] + (1.0f - G) * (float) Input [I];
   }
}




void KJ_LPIR_float
(
   float const * Input,
   float * Background,
   float * Output,
   size_t Count,
   float K
)
{
   for (size_t I = 0; I < Count; I = I + 1)
   {
      Output [I] =  abs (Input [I] - Background [I]);
      Background [I] = K * Input [I] + (1.0f - K) * Background [I];
   }
}

void KJ_LPIR1_float
(
   float const * Input,
   float * Background,
   float * Output,
   size_t Count
)
{
   float G;
   for (size_t I = 0; I < Count; I = I + 1)
   {
      Output [I] =  abs (Input [I] - Background [I]);
      G = KJ_Map_float (Output [I], -255.0f, 50.0f, 0.01f, 0.99f);
      Background [I] = G * Background [I] + (1.0f - G) * Input [I];
   }
}


void KJ_LPIR3_float
(
   float const * Input,
   float * Background,
   float * Momentum,
   float * Output,
   size_t Count
)
{
   float G;
   float B;
   for (size_t I = 0; I < Count; I = I + 1)
   {
      Output [I] = abs (Input [I] - Background [I]);
      G = KJ_Map_float (Output [I], -255.0f, 50.0f, 0.01f, 0.99f);
      B = G * Background [I] + (1.0f - G) * Input [I];
      Momentum [I] = Momentum [I] + (B - Background [I]);
      Momentum [I] = Momentum [I] * 0.8;
      Background [I] = B + Momentum [I];
   }
}



void KJ_LPIR2_float
(
   float const * Input,
   float * Mean,
   float * Variance2,
   float * Output,
   size_t Count,
   float P,
   float K
)
{
   for (size_t I = 0; I < Count; I = I + 1)
   {
      if ((Output [I] / sqrtf (Variance2 [I])) <= K)
      {
         Mean [I] = P * Input [I] + (1.0f - P) * Mean [I];
      }
      Output    [I] = abs (Input [I] - Mean [I]);
      Variance2 [I] = (Output [I] * Output [I]) * P + (1.0f - P) * Variance2 [I];
   }
}


