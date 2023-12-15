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

#define BACKSPACE 0x100
#define C(x)  ((x)-'@')  // Control-x

// //
// // send one character to the uart.
// //
// void
// consputc(int c)
// {
//   extern volatile int panicked; // from printf.c

//   if(panicked){
//     for(;;)
//       ;
//   }

//   if(c == BACKSPACE){
//     // if the user typed backspace, overwrite with a space.
//     uartputc('\b'); uartputc(' '); uartputc('\b');
//   } else {
//     uartputc(c);
//   }
// }

struct {
  struct spinlock lock;
  
  // input
#define INPUT_BUF 128
  char buf[INPUT_BUF];
  uint r;  // Read index
  uint w;  // Write index
  uint e;  // Edit index
} null;

//
// user write()s to the console go here.
//
int
nullwrite(struct file *f, int user_src, uint64 src, int n)
{
//   int i;

//   acquire(&cons.lock);
//   for(i = 0; i < n; i++){
//     char c;
//     if(either_copyin(&c, user_src, src+i, 1) == -1)
//       break;
//     consputc(c);
//   }
//   release(&cons.lock);

  return n;
}

//
// user read()s from the console go here.
// copy (up to) a whole input line to dst.
// user_dist indicates whether dst is a user
// or kernel address.
//
int
nullread(struct file *f, int user_dst, uint64 dst, int n)
{
  
  
//   char cbuf;

  
//   acquire(&null.lock);
//   cbuf = C('D');
//   either_copyout(user_dst, dst, &cbuf, 1);
      

//   release(&null.lock);

  return 0;
}

//
// the console input interrupt handler.
// uartintr() calls this for input character.
// do erase/kill processing, append to cons.buf,
// wake up consoleread() if a whole line has arrived.
//
// void
// consoleintr(int c)
// {
//   acquire(&cons.lock);

//   switch(c){
//   case C('P'):  // Print process list.
//     procdump();
//     break;
//   case C('U'):  // Kill line.
//     while(cons.e != cons.w &&
//           cons.buf[(cons.e-1) % INPUT_BUF] != '\n'){
//       cons.e--;
//       consputc(BACKSPACE);
//     }
//     break;
//   case C('H'): // Backspace
//   case '\x7f':
//     if(cons.e != cons.w){
//       cons.e--;
//       consputc(BACKSPACE);
//     }
//     break;
//   default:
//     if(c != 0 && cons.e-cons.r < INPUT_BUF){
//       c = (c == '\r') ? '\n' : c;

//       // echo back to the user.
//       consputc(c);

//       // store for consumption by consoleread().
//       cons.buf[cons.e++ % INPUT_BUF] = c;

//       if(c == '\n' || c == C('D') || cons.e == cons.r+INPUT_BUF){
//         // wake up consoleread() if a whole line (or end-of-file)
//         // has arrived.
//         cons.w = cons.e;
//         wakeup(&cons.r);
//       }
//     }
//     break;
//   }
  
//   release(&cons.lock);
// }

void
nullinit(void)
{
  initlock(&null.lock, "null");

  //uartinit();

  // connect read and write system calls
  // to consoleread and consolewrite.
  devsw[NULL].read = nullread;
  devsw[NULL].write = nullwrite;
}
