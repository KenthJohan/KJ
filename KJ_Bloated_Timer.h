//printf
#include <stdio.h>

//timerfd_create
#include <sys/timerfd.h>

//read
#include <unistd.h>

//errno
#include <errno.h>

//uint64_t
#include <stdint.h>

//strerror
#include <string.h>

struct KJ_Bloated_Timer
{
   int                 Handle;
   struct itimerspec   Specification;
   uint64_t            Count;
   int                 Result;
   int                 Error;
   char              * Error_Message;
};

void KJ_Bloated_Timer_Construct (struct KJ_Bloated_Timer * Timer)
{
   Timer->Handle = timerfd_create (CLOCK_MONOTONIC, 0);
   assert (Timer->Handle != -1);
   Timer->Specification.it_value.tv_sec = 1;
   Timer->Specification.it_value.tv_nsec = 0;
   Timer->Specification.it_interval.tv_sec = 1;
   Timer->Specification.it_interval.tv_nsec = 0;
   timerfd_settime (Timer->Handle, 0, &(Timer->Specification), NULL);
}

void KJ_Bloated_Timer_Read (struct KJ_Bloated_Timer * Timer)
{
   errno = 0;
   Timer->Result = read (Timer->Handle, &(Timer->Count), sizeof (uint64_t));
   Timer->Error = errno;
   Timer->Error_Message = strerror (errno);
}

void KJ_Bloated_Timer_Printf (struct KJ_Bloated_Timer * Timer)
{
   printf ("Result        %i \n", Timer->Result);
   printf ("Count         %lli \n", Timer->Count);
   printf ("Error         %i \n", Timer->Error);
   printf ("Error_Message %s\n", Timer->Error_Message);
}
