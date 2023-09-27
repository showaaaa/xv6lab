#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  
  if(argc != 1){
    fprintf(2, "Usage: countsys\n");
    exit(1);
  }

  int number = countsys();

  printf("%d\n", number);
  exit(0);
}