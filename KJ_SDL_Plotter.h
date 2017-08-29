#pragma once

#include <SDL.h>
#include <stdio.h>
#include <assert.h>
#include <stdio.h>
#include <time.h>
#include "KJ_SDL.h"
#include "KJ_Pixel.h"
#include "KJ_Map.h"

struct KJ_SDL_Plot
{
   size_t Index;
   SDL_Texture * Texture;
   SDL_Rect Rectangle [1];
   int Width;
   int Height;
   struct KJ_Pixel_ABGR8888 * Frame;
   uint8_t * Data;
};

void KJ_SDL_Plot_Construct (struct KJ_SDL_Plot * Plot, SDL_Renderer * Renderer, int Width, int Height)
{
   Plot->Index = 0;
   Plot->Width = Width;
   Plot->Height = Height;
   Plot->Texture = KJ_SDL_CreateTexture_Try (Renderer, SDL_PIXELFORMAT_RGBA8888, Plot->Width, Plot->Height);
   
   Plot->Frame = malloc (Plot->Width * Plot->Width * sizeof (struct KJ_Pixel_ABGR8888));
   assert (Plot->Frame != NULL);
   memset (Plot->Frame, 0, Plot->Width * Plot->Width * sizeof (struct KJ_Pixel_ABGR8888));
   Plot->Data = malloc (Plot->Width * sizeof (uint8_t));
   assert (Plot->Data != NULL);
   memset (Plot->Data, 0, Plot->Width * sizeof (uint8_t));
};

void KJ_SDL_Plot_Destruct (struct KJ_SDL_Plot * Plot)
{
   assert (Plot->Frame != NULL);
   free (Plot->Frame);
   Plot->Frame = NULL;
   assert (Plot->Data != NULL);
   free (Plot->Data);
   Plot->Data = NULL;
};

void KJ_SDL_Plot_Append (struct KJ_SDL_Plot * Plot, uint8_t Y)
{
   Plot->Index = Plot->Index + 1;
   if (Plot->Index >= Plot->Width)
   {
      Plot->Index = 0;
      memset (Plot->Data, 0, Plot->Width * sizeof (uint8_t));
      memset (Plot->Frame, 0, Plot->Width * Plot->Width * sizeof (struct KJ_Pixel_ABGR8888));
   }
   assert (Plot->Index < Plot->Width);
   Plot->Data [Plot->Index] = Y;
}

void KJ_SDL_Plot_Render (struct KJ_SDL_Plot * Plot, SDL_Renderer * Renderer)
{
   for (size_t I = 0; I < (Plot->Width * Plot->Height); I = I + 1)
   {
      Plot->Frame [I].A = 255;
   }
   
   for (size_t I = 0; I < Plot->Width; I = I + 1)
   {
      size_t Index;
      Index = KJ_Map_Index2D_Asserted (Plot->Width, Plot->Height, I, Plot->Height / 2);
      Plot->Frame [Index].B = 255;
   }
   
   for (size_t X = 0; X < Plot->Width; X = X + 1)
   {
      uint8_t Y;
      Y = Plot->Data [X];
      assert (Y < Plot->Height);
      for (size_t YY = 0; YY < Y; YY = YY + 1)
      {
         size_t Index;
         Index = KJ_Map_Index2D_Asserted (Plot->Width, Plot->Height, X, Plot->Height - 1 - YY);
         Plot->Frame [Index].R = 255;
      }
   }
   SDL_UpdateTexture (Plot->Texture, NULL, Plot->Frame, Plot->Width * 4);
   SDL_RenderCopy (Renderer, Plot->Texture, NULL, Plot->Rectangle);
   SDL_RenderDrawRects (Renderer, Plot->Rectangle, 1);
}
