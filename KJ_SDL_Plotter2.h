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
   SDL_Point * Points;
   SDL_Rect Rectangle [1];
   int Scale_X;
};

void KJ_SDL_Plot_Construct (struct KJ_SDL_Plot * Plot, SDL_Rect * Rectangle, int Scale_X)
{
   Plot->Scale_X = Scale_X;
   Plot->Rectangle->x = Rectangle->x;
   Plot->Rectangle->y = Rectangle->y;
   Plot->Rectangle->w = Rectangle->w;
   Plot->Rectangle->h = Rectangle->h;
   Plot->Index = 0;
   Plot->Points = malloc (Plot->Rectangle->w * sizeof (SDL_Point));
   assert (Plot->Points != NULL);
   //for (size_t I = 0; I < Plot->Rectangle->w; I = I + 1)
   {
      
   };
};

void KJ_SDL_Plot_Destruct (struct KJ_SDL_Plot * Plot)
{
   assert (Plot->Points != NULL);
   free (Plot->Points);
   Plot->Points = NULL;
};

void KJ_SDL_Plot_Append (struct KJ_SDL_Plot * Plot, int Y, int A0, int A1)
{
   assert (Plot->Index < Plot->Rectangle->w);
   Y = KJ_Map_int (Y, A0, A1, Plot->Rectangle->y, Plot->Rectangle->y + Plot->Rectangle->h);
   Plot->Points [Plot->Index].x = Plot->Rectangle->x + Plot->Index * Plot->Scale_X;
   Plot->Points [Plot->Index].y = Y;
   
   //printf ("(%i %i)\n", Plot->Rectangle->x, Plot->Rectangle->y);
   printf ("(%i %i)\n", Plot->Points [Plot->Index].x, Plot->Points [Plot->Index].y);
   
   Plot->Index = Plot->Index + 1;
   if (Plot->Index >= (Plot->Rectangle->w / Plot->Scale_X))
   {
      Plot->Index = 0;
      memset (Plot->Points, 0, Plot->Rectangle->w * sizeof (SDL_Point));
   }
   assert (Plot->Index < Plot->Rectangle->w);
}

void KJ_SDL_Plot_Render (struct KJ_SDL_Plot * Plot, SDL_Renderer * Renderer)
{
   SDL_RenderDrawLines (Renderer, Plot->Points, Plot->Index);
}

void KJ_SDL_Plot_Render_Center (struct KJ_SDL_Plot * Plot, SDL_Renderer * Renderer)
{
   int AX = Plot->Rectangle->x;
   int AY = Plot->Rectangle->y + Plot->Rectangle->h / 2;
   int BX = Plot->Rectangle->x + Plot->Rectangle->w;
   int BY = Plot->Rectangle->y + Plot->Rectangle->h / 2;
   SDL_RenderDrawLine (Renderer, AX, AY, BX, BY);
}

