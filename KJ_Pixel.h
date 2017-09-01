#pragma once

//uint8_t
#include <stdint.h>

enum KJ_Pixel_Kind 
{
   KJ_Pixel_Kind_RGBA8888,
   KJ_Pixel_Kind_ABGR8888
};

struct __attribute__((__packed__)) KJ_Pixel_RGBA8888
{
   union
   {
      struct
      {
         uint8_t R;
         uint8_t G;
         uint8_t B;
         uint8_t A;
      };
      uint8_t Data [4];
   };
};

struct __attribute__((__packed__)) KJ_Pixel_ABGR8888
{
   union
   {
      struct
      {
         uint8_t A;
         uint8_t B;
         uint8_t G;
         uint8_t R;
      };
      uint8_t Data [4];
   };
};

struct __attribute__((__packed__)) KJ_Pixel_Grayscale16
{
   union
   {
      struct
      {
         uint16_t A;
      };
      uint16_t Data [1];
   };
};


void KJ_Pixel_Grayscale16_To_ABGR8888 
(
   struct KJ_Pixel_Grayscale16 const * Source, 
   struct KJ_Pixel_ABGR8888 * Destination, 
   size_t Pixmap_Count, 
   struct KJ_Pixel_ABGR8888 const * Colormap,
   size_t Color_Count
)
{
   for (size_t I = 0; I < Pixmap_Count; I = I + 1)
   {
      assert (Source [I].A < Color_Count);
      Destination [I].R = Colormap [Source [I].A].R;
      Destination [I].G = Colormap [Source [I].A].G;
      Destination [I].B = Colormap [Source [I].A].B;
      Destination [I].A = 255;
   }
}




void KJ_Pixel_float_To_ABGR8888 
(
   float const * Source, 
   struct KJ_Pixel_ABGR8888 * Destination, 
   size_t Pixmap_Count, 
   struct KJ_Pixel_ABGR8888 const * Colormap,
   size_t Color_Count
)
{
   for (size_t I = 0; I < Pixmap_Count; I = I + 1)
   {
      assert (Source [I] >= 0);
      assert (Source [I] < Color_Count);
      Destination [I].R = Colormap [(size_t) Source [I]].R;
      Destination [I].G = Colormap [(size_t) Source [I]].G;
      Destination [I].B = Colormap [(size_t) Source [I]].B;
      Destination [I].A = 255;
   }
}
