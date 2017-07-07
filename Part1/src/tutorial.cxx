// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "TutorialConfig.h"
#ifdef USE_MYMATH
#include "MathFunctions/MathFunctions.h"
#endif
#include "Test/test.h"

int main (int argc, char *argv[])
{

  if (argc < 2)
    {
    fprintf(stdout,"%s Version %d.%d\n",
            argv[0],
            Tutorial_VERSION_MAJOR,
            Tutorial_VERSION_MINOR);
    fprintf(stdout,"Usage: %s number\n",argv[0]);
    return 1;
    }
  double inputValue = atof(argv[1]);

test();

#ifdef USE_MYMATH
  double outputValue = mysqrt(inputValue);
  printf("own\n");
#else
  double outputValue = sqrt(inputValue);
  printf("math.h\n");
#endif

  fprintf(stdout,"The square root of %g is %g\n",
          inputValue, outputValue);
  return 0;
}
