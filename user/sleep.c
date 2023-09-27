#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  
  if(argc != 2){
    fprintf(2, "Usage: sleep [num]...\n");
    exit(1);
  }
//   printf("before atoi\n");
  int number = atoi(argv[1]);
//   printf("after atoi %d\n", number);
  sleep(number);

  exit(0);
}