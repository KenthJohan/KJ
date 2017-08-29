//gcc Test_KJ_Map.c -std=gnu11 -fdiagnostics-color -Wall -Wno-missing-braces && ./a.out

#include "KJ_Map.h"
#include <stdio.h>

int main (int argc, char * argv [])
{
   for (float I = -4.0f; I < 4.0f; I = I + 0.5f)
   {
      float Value1;
      Value1 = KJ_Map_float ((float) I, -2.0f, 2.0f, 0.0f, 255.0f);
      printf ("Value %f %f\n", I, Value1);
   }
}
