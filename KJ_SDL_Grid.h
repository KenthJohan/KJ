#pragma once

#include <stdio.h>
#include <assert.h>
#include <time.h>

#include <SDL2/SDL.h>



void KJ_SDL_Grid_Generate_Inside 
(
   struct SDL_Rect * Rectangle, 
   size_t Count, 
   int X, 
   int Y, 
   int W,
   int H, 
   int Columns, 
   int Rows,
   int Offset
)
{
   for (size_t I = 0; I < Count; I = I + 1)
   {
      Rectangle [I].w = W / Columns;
      Rectangle [I].h = H / Rows;
      Rectangle [I].x = X + ((W / Columns) * ((I + Offset) % Columns));
      Rectangle [I].y = Y + ((H / Rows) * ((I + Offset) / Columns));
   }
}
