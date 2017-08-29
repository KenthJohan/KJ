#pragma once

#include <stdio.h>
#include <assert.h>
#include <time.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>



void KJ_SDL_Init_Try ()
{
   int Result;
   Result = SDL_Init (SDL_INIT_VIDEO);
   assert (Result == 0 && "Unable to initialize SDL");
}

void KJ_IMG_Init_Try ()
{
   int IMG_Flags = IMG_INIT_PNG;
   int Result;
   Result = IMG_Init (IMG_Flags);
   assert (Result & IMG_Flags);
}

void KJ_TTF_Init_Try ()
{
   int Result;
   Result = TTF_Init ();
   assert (Result == 0 && "Unable to initialize SDL TTF");
}

TTF_Font * KJ_TTF_OpenFont_Try (char const * Path, int Size)
{
   TTF_Font * Font;
   Font = TTF_OpenFont (Path, Size);
   assert (Font != NULL);
   return Font;
}

SDL_Window * KJ_SDL_CreateWindow_Try (char const * Title, SDL_DisplayMode * Display_Mode)
{
   SDL_Window * Window;
   Window = SDL_CreateWindow (Title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Display_Mode->w, Display_Mode->h, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);
   assert (Window != NULL && "Unable to create window");
   return Window;
}

SDL_Renderer * KJ_SDL_CreateRenderer_Try (SDL_Window * Window)
{
   SDL_Renderer * Renderer;
   Renderer = SDL_CreateRenderer (Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   assert (Renderer != NULL && "Unable to create a renderer");
   SDL_SetRenderDrawColor (Renderer, 0, 0, 0, 255);
   SDL_RenderPresent (Renderer);
   return Renderer;
}

SDL_Texture * KJ_SDL_CreateTexture_Try (SDL_Renderer * Renderer, int Format, size_t Width, size_t Height)
{
   SDL_Texture * Texture;
   Texture = SDL_CreateTexture (Renderer, Format, SDL_TEXTUREACCESS_STREAMING, Width, Height);
   assert (Texture != NULL && "Unable to create texture");
   SDL_SetTextureBlendMode (Texture, SDL_BLENDMODE_BLEND);
   return Texture;
}

void KJ_SDL_CreateTexture_Array_Try 
(
   SDL_Renderer * Renderer, 
   int Format, 
   size_t Width, 
   size_t Height, 
   SDL_Texture * Texture_Array [], 
   size_t Count
)
{
   for (size_t I = 0; I < Count; I = I + 1)
   {
      Texture_Array [I] = KJ_SDL_CreateTexture_Try (Renderer, Format, Width, Height);
   }
}

void KJ_SDL_DestroyTexture_Array (SDL_Texture * Texture_Array [], size_t Count)
{
   for (size_t I = 0; I < Count; I = I + 1)
   {
      SDL_DestroyTexture (Texture_Array [I]);
   }
}

void KJ_Get_Display_Info_Try (SDL_DisplayMode * Display, SDL_PixelFormat * Format, SDL_Rect * Boundary)
{
   int Result;
   size_t Count = SDL_GetNumVideoDisplays ();
   SDL_PixelFormat * Dynamic_Format;
   for (size_t I = 0; I < Count; I = I + 1)
   {
      Result = SDL_GetCurrentDisplayMode (I, Display);
      if (Result == 0)
      {
         Dynamic_Format = SDL_AllocFormat (Display->format);
         memcpy (Format, Dynamic_Format, sizeof (SDL_PixelFormat));
         SDL_FreeFormat (Dynamic_Format);
         Boundary->x = 0;
         Boundary->y = 0;
         Boundary->w = Display->w;
         Boundary->h = Display->h;
      }
      else
      {
         printf ("Could not get display mode for video display #%d: %s\n", I, SDL_GetError ());
      }
   }
}


void KJ_SDL_Render_Time (SDL_Renderer * Renderer, TTF_Font * Font, struct timespec * Time, SDL_Rect * Rectangle)
{
   struct tm * ptm;
   char Text [40] = {'\0'};
   SDL_Surface * Surface;
   SDL_Texture * Texture;
   SDL_Color Color = {0, 220, 100};

   ptm = localtime (&(Time->tv_sec));
   strftime (Text, sizeof (Text), "%Y-%m-%d %H:%M:%S", ptm);
   sprintf (Text, "%s.%03ld", Text, Time->tv_nsec/1000000);

   Surface = TTF_RenderText_Solid (Font, Text, Color);
   assert (Surface != NULL);
   
   Texture = SDL_CreateTextureFromSurface (Renderer, Surface);
   assert (Texture != NULL);

   SDL_RenderCopy (Renderer, Texture, NULL, Rectangle);
   SDL_FreeSurface (Surface);
   SDL_DestroyTexture (Texture);
}


void KJ_SDL_Render_Text (SDL_Renderer * Renderer, TTF_Font * Font, SDL_Rect * Rectangle, char const * Text)
{
   SDL_Surface * Surface;
   SDL_Texture * Texture;
   SDL_Color Color = {0, 220, 100};
   
   Surface = TTF_RenderText_Solid (Font, Text, Color);
   assert (Surface != NULL);
   
   Texture = SDL_CreateTextureFromSurface (Renderer, Surface);
   assert (Texture != NULL);

   SDL_RenderCopy (Renderer, Texture, NULL, Rectangle);
   SDL_FreeSurface (Surface);
   SDL_DestroyTexture (Texture);
}


FILE * KJ_SDL_Open_FFmpeg_Pipe (SDL_DisplayMode * Display, SDL_PixelFormat * Format, char const * Path, size_t FPS)
{
   char Command [300] = {'\0'};
   size_t const Thread_Count = 2;
   char const * Format_Out = "yuv420p";
   char const * Format_In = "rgb32";
   char const * Format_File = "mp4";
   char const * Codec = "h264";
   FILE * File;
   sprintf (Command, "ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt %s -s %i*%i -r %i -i -", Format_In, Display->w, Display->h, FPS);
   sprintf (Command, "%s -threads %i -preset ultrafast -f %s -an -pix_fmt %s -vcodec %s", Command, Thread_Count, Format_File, Format_Out, Codec);
   sprintf (Command, "%s %s 2>/dev/null", Command, Path);
   printf ("\n\n%s\n\n", Command);
   File = NULL;
   //File = popen (Command, "w");
   assert (File != NULL);
   return NULL;
}

void KJ_SDL_Center_Scale (SDL_Rect * Rectangle, int X, int Y)
{
   Rectangle->x = Rectangle->x - X;
   Rectangle->w = Rectangle->w + (2 * X);
   Rectangle->y = Rectangle->y - Y;
   Rectangle->h = Rectangle->h + (2 * Y);
}


void KJ_SDL_Generate_Grid
(
   SDL_Rect * Rectangle, 
   int Width, 
   int Height, 
   int Columns, 
   int Rows,
   int I
)
{
   Rectangle->w = Width;
   Rectangle->h = Height;
   Rectangle->x = Width * (I % Columns);
   Rectangle->y = Height * (I / Columns);
}

void KJ_SDL_Generate_Grid_Inside
(
   SDL_Rect * Rectangle, 
   int Width, 
   int Height, 
   int Columns, 
   int Rows,
   int I
)
{
   Rectangle->w = Width / Columns;
   Rectangle->h = Height / Rows;
   Rectangle->x = (Width / Columns) * (I % Columns);
   Rectangle->y = (Height / Rows) * (I / Columns);
}



void KJ_SDL_Generate_Grid_Boundary 
(
   struct SDL_Rect * Rectangle, 
   SDL_Rect * Boundary, 
   int Columns, 
   int Rows,
   int I
)
{
   Rectangle->w = Boundary->w;
   Rectangle->h = Boundary->h;
   Rectangle->x = Boundary->x + (Boundary->w * (I % Columns));
   Rectangle->y = Boundary->y + (Boundary->h * (I / Columns));
}

void KJ_SDL_Generate_Grid_Inside_Boundary 
(
   struct SDL_Rect * Rectangle, 
   SDL_Rect * Boundary, 
   int Columns, 
   int Rows,
   int I
)
{
   Rectangle->w = Boundary->w / Columns;
   Rectangle->h = Boundary->h / Rows;
   Rectangle->x = Boundary->x + ((Boundary->w / Columns) * (I % Columns));
   Rectangle->y = Boundary->y + ((Boundary->h / Rows) * (I / Columns));
}






struct KJ_SDL_Context
{
   char              *    Name;
   SDL_Window        *    Window;
   SDL_Renderer      *    Renderer;
   TTF_Font          *    Font;
   SDL_DisplayMode        Display_Mode [1];
   SDL_PixelFormat        Pixel_Format [1];
   SDL_Rect               Screen_Boundary [1];
   SDL_Event              Event [1];
   int                    Pending_Event;
   void              *    Frame;
   size_t                 Frame_Size;
};


void KJ_SDL_Context_Allocate_Frame (struct KJ_SDL_Context * Item)
{
   int Width        = Item->Display_Mode->w;
   int Height       = Item->Display_Mode->h;
   int Depth        = Item->Pixel_Format->BytesPerPixel;
   Item->Frame_Size = Width * Height * Depth;
   Item->Frame      = malloc (Item->Frame_Size);
   assert (Item->Frame != NULL);
}

void KJ_SDL_Context_Construct (struct KJ_SDL_Context * Item)
{
   KJ_SDL_Init_Try ();
   KJ_IMG_Init_Try ();
   KJ_TTF_Init_Try ();
   KJ_Get_Display_Info_Try (Item->Display_Mode, Item->Pixel_Format, Item->Screen_Boundary);
   Item->Window = KJ_SDL_CreateWindow_Try ("Test SDL 2", Item->Display_Mode);
   Item->Renderer = KJ_SDL_CreateRenderer_Try (Item->Window);
   //Item->Font = KJ_TTF_OpenFont_Try ("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 40);
   Item->Font = KJ_TTF_OpenFont_Try ("/usr/share/fonts/truetype/freefont/FreeMonoBold.ttf", 40);
   KJ_SDL_Context_Allocate_Frame (Item);
}

void KJ_SDL_Context_Print_Info (struct KJ_SDL_Context * Item)
{
   printf ("Display width:                %i\n", Item->Display_Mode->w);
   printf ("Display height:               %i\n", Item->Display_Mode->h);
   printf ("Display refresh_rate:         %i\n", Item->Display_Mode->refresh_rate);
   printf ("Display format:               %s\n", SDL_GetPixelFormatName (Item->Display_Mode->format));
   printf ("Display bytes per pixels:     %i\n", Item->Pixel_Format->BytesPerPixel);   
}

void KJ_SDL_Context_Destruct (struct KJ_SDL_Context * Item)
{
   printf ("My_Application_Destruct begin\n");
   free (Item->Frame);
   TTF_CloseFont (Item->Font);
   SDL_DestroyRenderer (Item->Renderer);
   SDL_DestroyWindow (Item->Window);
   TTF_Quit ();
   IMG_Quit ();
   SDL_Quit ();
   printf ("My_Application_Destruct end\n");
}



int KJ_SDL_Scancode_Check (struct KJ_SDL_Context * Item, SDL_Scancode Scancode)
{
   uint8_t const * State = SDL_GetKeyboardState (NULL);
   return State [Scancode] == 1;
}


SDL_Keycode KJ_SDL_Scancode_Event (struct KJ_SDL_Context * Item)
{
   SDL_Scancode Scancode;
   //SDL_Keycode Key;
   //Key = Item->Event->key.keysym.sym;
   Scancode = Item->Event->key.keysym.scancode;
   return Scancode;
}


int KJ_SDL_Key_Pressing (struct KJ_SDL_Context * Item)
{
   return Item->Pending_Event && (Item->Event->type == SDL_KEYDOWN);
}


int KJ_SDL_Key_Pressed (struct KJ_SDL_Context * Item)
{
   return Item->Pending_Event && (Item->Event->key.type == SDL_KEYDOWN) && (Item->Event->key.state == SDL_PRESSED) && (Item->Event->key.repeat == 0);
}

int KJ_SDL_Key_Pressed1 (struct KJ_SDL_Context * Item)
{
   return Item->Pending_Event && (Item->Event->key.type == SDL_KEYDOWN) && (Item->Event->key.state == SDL_PRESSED);
}

void KJ_SDL_Update (struct KJ_SDL_Context * Item)
{
   //SDL_RenderClear (Application->Renderer);
   Item->Pending_Event = SDL_PollEvent (Item->Event);
   if (Item->Pending_Event)
   {
      switch (Item->Event->type)
      {
         case SDL_QUIT:
         break;
      }
   }
}


void KJ_SDL_Frame_Capture (struct KJ_SDL_Context * Item)
{
   int Result;
   int Pitch = Item->Pixel_Format->BytesPerPixel * Item->Display_Mode->w;
   int Format = SDL_PIXELFORMAT_RGB888;
   Result = SDL_RenderReadPixels (Item->Renderer, Item->Screen_Boundary, Format, Item->Frame, Pitch);
   //fprintf (stderr, "Failed to read pixel data from SDL_Renderer object. SDL_GetError() - %s\n", SDL_GetError());
   assert (Result == 0);
}


void KJ_SDL_Frame_Save_BMP (struct KJ_SDL_Context * Item, char const * Path)
{
   int Width = Item->Display_Mode->w;
   int Height = Item->Display_Mode->h;
   int Depth = Item->Pixel_Format->BytesPerPixel;
   int Pitch = Item->Pixel_Format->BytesPerPixel * Item->Display_Mode->w;
   int Format = SDL_PIXELFORMAT_RGB888;
   SDL_Surface * Surface;
   Surface = SDL_CreateRGBSurfaceWithFormatFrom (Item->Frame, Width, Height, Depth, Pitch, Format);
   assert (Surface != NULL);
   //fprintf (stderr, "Couldn't create SDL_Surface from renderer pixel data. SDL_GetError() - %s\n", SDL_GetError());
   SDL_SaveBMP (Surface, Path);
   SDL_FreeSurface (Surface);
}


int KJ_SDL_Frame_Write_File (struct KJ_SDL_Context * Item, FILE * File)
{
   size_t N = fwrite (Item->Frame, Item->Frame_Size, 1, File);
   //printf ("N %i\n", N);
   assert (N == 1);
   fflush (File);
   return 1;
}
