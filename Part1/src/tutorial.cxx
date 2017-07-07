// A simple program that computes the square root of a number
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TutorialConfig.h"
#ifdef USE_MYMATH
#include "MathFunctions/MathFunctions.h"
#endif
#include "Test/test.h"

static int StringIsNumber(char * str);

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

  if(StringIsNumber(argv[1]) == 0)
  {
      fprintf(stdout,"Input must be an integer number!\n");
      return -1;
  }

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

static int StringIsNumber(char * str)
{
    int ret = 1;
    int cnt;
    for(cnt = 0; cnt < strlen(str); cnt++)
    {
        if(!(str[cnt] >= '0' && str[cnt] <= '9' || str[cnt] == '.' || str[cnt] == '-'))
        {
            ret = 0;
            break;
        }
    }
    return ret;
}
