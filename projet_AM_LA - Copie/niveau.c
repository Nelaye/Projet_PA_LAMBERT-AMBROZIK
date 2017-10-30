#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void sleep (int seconde)

{

      int current_time_init = time(NULL);

      int current_time = time(NULL);

      while (current_time <= (current_time_init + seconde))

      {

             current_time = time(NULL);

       }

}
