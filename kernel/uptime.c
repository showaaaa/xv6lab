//
// Console input and output, to the uart.
// Reads are line at a time.
// Implements special input characters:
//   newline -- end of line
//   control-h -- backspace
//   control-u -- kill line
//   control-d -- end of file
//   control-p -- print process list
//

#include <stdarg.h>

#include "types.h"
#include "param.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "file.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"
#include "proc.h"

#include <stdint.h>

#define BACKSPACE 0x100
#define C(x)  ((x)-'@')  // Control-x


struct {
  struct spinlock lock;
  
  // input
#define INPUT_BUF 128
  char buf[INPUT_BUF];
  uint r;  // Read index
  uint w;  // Write index
  uint e;  // Edit index
} uptime;

//
// user write()s to the console go here.
//
int
uptimewrite(struct file *f, int user_src, uint64 src, int n)
{

  return n;
}

//
// user read()s from the console go here.
// copy (up to) a whole input line to dst.
// user_dist indicates whether dst is a user
// or kernel address.
//
int
uptimeread(struct file *f, int user_dst, uint64 dst, int n)
{
  
  if(f->off != 0){
      f->off = 0;
    
      return 0;
    }
  char cbuf;
  uint tmp = ticks;
  char buffer[n];
  int idx = 0;
  while(tmp > 0){
    int cur = tmp % 10;
    buffer[idx++] = cur + '0';
    tmp = tmp / 10;
  }
 int res = idx;
  acquire(&uptime.lock);
  idx--;
    while(idx >= 0){
        cbuf = buffer[idx--];
        either_copyout(user_dst, dst, &cbuf, 1);
        dst++;
    }
    cbuf = '\n';
    either_copyout(user_dst, dst, &cbuf, 1);
    
      
    f->off = 1;
  release(&uptime.lock);

  return res+1;
}



void
uptimeinit(void)
{
  initlock(&uptime.lock, "uptime");

  //uartinit();

  // connect read and write system calls
  // to consoleread and consolewrite.
  devsw[UPTIME].read = uptimeread;
  devsw[UPTIME].write = uptimewrite;
}
