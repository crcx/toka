/************************************************************
 * Copyright (c) 2006, 2007  Charles R. Childers
 *
 * Permission to use, copy, modify, and distribute this 
 * software for any purpose with or without fee is hereby 
 * granted, provided that the above copyright notice and 
 * this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR 
 * DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE 
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY 
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE 
 * FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL 
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS 
 * OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF 
 * CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING 
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 
 * OF THIS SOFTWARE.
 ************************************************************/

#include <stdio.h>
#include <asm/ioctls.h>
#include <pty.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <termios.h>

struct termios new_termios, old_termios;

long console_size_x() 
{
  struct winsize win;
  int fd;

  fd = open(ttyname(0), O_RDWR);
  if (fd == -1 || ioctl(fd, TIOCGWINSZ, &win) == -1)
  {
    close(fd);
    return 0;
  }
  close(fd);
  return (long)win.ws_col;
}


long console_size_y()
{
  struct winsize win;
  int fd;

  fd = open(ttyname(0), O_RDWR);
  if (fd == -1 || ioctl(fd, TIOCGWINSZ, &win) == -1)
  {
    close(fd);
    return 0;
  }
  close(fd);
  return (long)win.ws_row;
}


void console_init() 
{
  tcgetattr(0, &old_termios);
  new_termios = old_termios;
  new_termios.c_iflag &= ~(BRKINT+ISTRIP+IXON+IXOFF +ICRNL+INLCR);
  new_termios.c_iflag |= (IGNBRK+IGNPAR);
  new_termios.c_lflag &= ~(ICANON+ISIG+IEXTEN+ECHO);
  new_termios.c_cc[VMIN] = 1;
  new_termios.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &new_termios);
}


void console_cleanup() {
  tcsetattr(0, TCSANOW, &old_termios);
}


#define ALT(c)  (256+c)   // ex: ALT('a') = 353
#define CTL(c)  (c&31)    // ex: CTL('a') = 1

#define K_BS    127
#define K_F(c)  (127+c)   // F1 thru F12
#define K_UP    140
#define K_DOWN  141
#define K_RIGHT 142
#define K_LEFT  143
#define K_HOME  144
#define K_INS   145
#define K_DEL   146
#define K_END   147
#define K_PGUP  148
#define K_PGDN  149

int getkey() 
{
//
// Get a keystroke & translate to 1-byte keycodes:
//  0-31     Control keys (no translation) .................. CTL('a') macro
//  32-127   Regular keys (no translation) .................. 'a' etc.
//  128-159  Function/Keypad keys (arbitrary translation) ... F(x) and K_ macros
//  160-255  Alt-keys (translate Alt-A -> 128+'a') .......... ALT('a') macro
//
  char s[3];
  int i=0;
  int c = getchar();
  if (c!=27)               // Regular key
    return c;
  c = getchar();
  if (c!='[')              // Alt+key
    return ALT(c);
  else 
  {                   // Function keys & Keypad
    c = getchar();
    if (c>='A' && c<='D')                // Arrows
      return K_UP + c - 'A';
    if (c=='[')                          // F1-F5
      return K_F(1) + getchar() - 'A';
    while (c!='~' && i<3) 
    {
      s[i++]= c;
      c = getchar();
    }
    s[i]=0;
    i = atoi(s);
    if (i>=1 && i<=6)                    // Home/Ins/Del/End/Pgup/Pgdn
      return K_HOME + i - 1;
    if (i>=17 && i<=21)                  // F6-F10
      return K_F(6) + i - 17;
    if (i>=23 && i<=24)                  // F11-F12
      return K_F(11) + i - 23;
  }
  return 0;
}
