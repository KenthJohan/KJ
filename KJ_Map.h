#pragma once

#include <assert.h>

//uint_8
#include <stdint.h>

//size_t
#include <sys/types.h>

int KJ_Map_int (int X, int A0, int A1, int B0, int B1)
{
   if (X < A0) {return B0;}
   if (X > A1) {return B1;}
   int DA;
   int DB;
   DA = A1 - A0;
   DB = B1 - B0;
   if (DA > DB) {DA = DA + 1; DB = DB + 1;}
   // X = (X-A0) * ((DB + K) / (DA + K)) + B0
   X = X - A0;
   X = X * DB; //Scale up before scale down is important for intergers.
   if (DA == 0) {return B1;};
   X = X / DA; //Scale down
   X = X + B0;
   assert (X <= B1);
   assert (X >= B0);
   return X;
}


void KJ_Map_u16v 
(
   uint16_t const * X, 
   uint16_t * Y, 
   size_t Count, 
   int A0, int A1, int B0, int B1
)
{
   for (size_t I = 0; I < Count; I = I + 1)
   {
      Y [I] = KJ_Map_int (X [I], A0, A1, B0, B1);
   }
}

float KJ_Map_float (float X, float A0, float A1, float B0, float B1)
{
   if (X < A0) {return B0;}
   if (X > A1) {return B1;}
   float DA;
   float DB;
   DA = A1 - A0;
   DB = B1 - B0;
   // X = (X-A0) * ((DB + K) / (DA + K)) + B0
   X = X - A0;
   X = X * DB; //Scale up before scale down is important for intergers.
   if (DA == 0) {return B1;};
   X = X / DA; //Scale down
   X = X + B0;
   return X;
}

int KJ_Map_Index2D_Asserted
(
   unsigned int Width,
   unsigned int Height,
   unsigned int X,
   unsigned int Y
)
{
   assert ((X >= 0) || (Y >= 0) || (X < Width) || (Y < Height));
   int Index;
   Index = X + Width * Y;
   assert (Index < (Width * Height));
   return Index;
}


