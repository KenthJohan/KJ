#pragma once

#include "KJ_Pixel.h"

#include <time.h>
#include <stdlib.h>

void KJ_Pixel_Random_Fill_ABGR8888
(
   struct KJ_Pixel_ABGR8888 * Pixmap, 
   size_t Pixmap_Count
)
{
   for (size_t I = 0; I < Pixmap_Count; I = I + 1)
   {
      Pixmap [I].R = (uint8_t) rand () % 256;
      Pixmap [I].G = (uint8_t) rand () % 256;
      Pixmap [I].B = (uint8_t) rand () % 256;
      Pixmap [I].A = (uint8_t) 255;
   }
}


void KJ_Pixel_Random_Fill_G16
(
   struct KJ_Pixel_Grayscale16 * Pixmap, 
   size_t Pixmap_Count
)
{
   for (size_t I = 0; I < Pixmap_Count; I = I + 1)
   {
      Pixmap [I].A = (uint16_t) rand () % UINT16_MAX;
   }
}
