/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: files.c
 *|F|
 *
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
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "toka.h"

extern VM_STACK data, address, alternate;




/******************************************************
 *|G| file.open  ( $m-n )  Open a specified file with
 *|G|                      the specified mode.
 *
 *|F| file_open()
 *|F| Open a file using the specified mode. Modes are
 *|F| a direct map to the fopen() modes: "r", "r+", "w",
 *|F| "w+", "a", and "a+". Numeric values for these are
 *|F| 1 - 6, in that order.
 *|F|
 ******************************************************/
void file_open()
{
  long mode;
  char *s;
  FILE *f;

  f = 0;
  mode = TOS; DROP;
  s = (char *)TOS; DROP;
  
  switch (mode)
  {
    case R:     f = fopen(s, "r");  break;
    case RPLUS: f = fopen(s, "r+"); break;
    case W:     f = fopen(s, "w");  break;
    case WPLUS: f = fopen(s, "w+"); break;
    case A:     f = fopen(s, "a");  break;
    case APLUS: f = fopen(s, "a+"); break;
  }
  if (!f)
    vm_push(0);
  else
    vm_push((long)f);
}


/******************************************************
 *|G| file.close ( n- )    Close the specified file handle
 *
 *|F| file_close()
 *|F| This is just a simple wrapper over fclose().
 *|F|
 ******************************************************/
void file_close()
{
  FILE *f;
  f = (FILE *)TOS; DROP;
  fclose(f);
}


/******************************************************
 *|G| file.read  ( nbl-r ) Read 'l' bytes into buffer 'b'
 *|G|                      from file handle 'n'. Returns
 *|G|                      the number of bytes read.
 *
 *|F| file_read()
 *|F| This is just a simple wrapper over fread().
 *|F|
 ******************************************************/
void file_read()
{
  long length;
  char *buffer;
  FILE *f;

  length = TOS; DROP;
  buffer = (char *)TOS; DROP;
  f = (FILE *)TOS; DROP;

  vm_push((long)fread(buffer, sizeof(char), length, f));
}


/******************************************************
 *|G| file.write ( nbl-w ) Write 'l' bytes from buffer 'b'
 *|G|                      to file handle 'n'. Returns
 *|G|                      the number of bytes written.
 *
 *|F| file_write()
 *|F| This is just a simple wrapper over fwrite().
 *|F|
 ******************************************************/
void file_write()
{
  long length;
  char *buffer;
  FILE *f;

  length = TOS; DROP;
  buffer = (char *)TOS; DROP;
  f = (FILE *)TOS; DROP;

  vm_push((long)fwrite(buffer, sizeof(char), length, f));
}


/******************************************************
 *|G| file.size  ( n-s )   Return the size (in bytes)
 *|G|                      of the specified file.
 *
 *|F| file_size()
 *|F| This is just a simple wrapper over fstat() which
 *|F| returns the size of the file.
 *|F|
 ******************************************************/
void file_size()
{
  FILE *f;
  struct stat this;

  f = (FILE *)TOS; DROP;

  if (fstat(fileno(f), &this) != 0)
    vm_push(0);
  else
    vm_push((long)this.st_size);
}


/******************************************************
 *|G| file.seek  ( nom-a ) Seek a new position in the
 *|G|                      file. Valid modes are
 *|G|                      START, CURRENT, and END.
 *
 *|F| file_seek()
 *|F| This is just a simple wrapper over fseek().
 *|F|
 ******************************************************/
void file_seek()
{
  long mode, offset, a;
  FILE *f;

  a = 0;
  mode = TOS; DROP;
  offset = TOS; DROP;
  f = (FILE *)TOS; DROP;

  switch (mode) {
  case START:   a = fseek(f, offset, SEEK_SET);
                break;
  case CURRENT: a = fseek(f, offset, SEEK_CUR);
                break; 
  case END:     a = fseek(f, offset, SEEK_END);
                break;
  }
  vm_push(a);
}


/******************************************************
 *|G| file.pos   ( n-a )   Return a pointer to the current
 *|G|                      offset into the file.
 *
 *|F| file_pos()
 *|F| This is just a simple wrapper over ftell().
 *|F|
 ******************************************************/
void file_pos()
{
  FILE *f;
  f = (FILE *)TOS; DROP;
  vm_push(ftell(f));
}
