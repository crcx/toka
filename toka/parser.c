/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: parser.c
 *|F|
 *
 * Copyright (c) 2006 - 2009  Charles R. Childers
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
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <memory.h>

#include "toka.h"
extern VM_STACK data, address, alternate;




/******************************************************
 *|F| Variables:
 *|F|   FILE *input[]
 *|F|   Current file stream to parse from. Setup as
 *|F|   an array of 8 inputs.
 *|F|
 *|F|   long isp
 *|F|   Pointer to the most recent input source in the array
 *|F|
 *|F|   long base
 *|F|   Holds the current numeric base
 *|F|
 *|F|   long parser
 *|F|   When ON (TRUE), system parsing words will parse. When
 *|F|   OFF (FALSE), they will take a string from the stack.
 *|F|
 *|F|   long escapes
 *|F|   When ON (TRUE), escape sequences will be handled
 *|F|   by the parser. When OFF (FALSE), they will be ignored.
 *|F|
 *
 *|G| base     ( -a )      Variable containg the current
 *|G|                      numeric base
 *|G| parser   ( -a )      Variable holding current parser
 *|G|                      mode.
 *|G| escape-sequences ( -a)  Variable determining if
 *|G|                         escape sequences are used.
 ******************************************************/
FILE *input[8];
long base=10;
long isp=0;
long parser=TRUE;
long escapes=TRUE;


/******************************************************
 *|G| >number  ( a-nf )    Attempt to convert a string
 *|G|                      to a number
 *
 *|F| to_number()
 *|F| Attempt to convert a string (on TOS) to a number.
 *|F| This accepts a format of:
 *|F|   [prefix][-]number
 *|F| If successful, it leaves the number and a flag of
 *|F| TRUE on the stack. Otherwise, it leaves the original
 *|F| string, and a flag of FALSE.
 *|F|
 ******************************************************/
void to_number()
{
  char *s, *t;
  long flag, old_base;

  s = (char *)TOS; DROP;
  t = s;
  flag = TRUE;
  old_base = base;

  if (*t == '%')
  {
    base = 2;
    t++; s++;
  }
  if (*t == '&')
  {
    base = 8;
    t++; s++;
  }
  if (*t == '#')
  {
    base = 10;
    t++; s++;
  }
  if (*t == '$')
  {
    base = 16;
    t++; s++;
  }

  if (*t == '-')
    t++;

  for (; *t; t++)
  {
     if (base <= 10)
     {
       if (!isdigit(*t))
       {
         flag = FALSE;
         break;
       }
     }
     else
     {
       if (!isxdigit(*t))
       {
         flag = FALSE;
         break;
       }
     }
  }

  if (flag == TRUE)
    vm_push(strtol(s, (char **)NULL, base));
  else
    vm_push((long)s);

  vm_push(flag);
  base = old_base;
}



/******************************************************
 *|G| >string  ( n-a )     Convert a number to a string
 *
 *|F| to_string()
 *|F| Convert a number (on TOS) to a string.
 *|F|
 ******************************************************/
void to_string()
{
  char *s;
  s = gc_alloc(128, sizeof(char), GC_MEM);
  switch (base)
  {
    case  8: snprintf(s, 128, "%lo", TOS); break;
    case 16: snprintf(s, 128, "%lx", TOS); break;
    default: snprintf(s, 128, "%li", TOS); break;
  }
  TOS = (long)s;
}



/******************************************************
 *|G| parse    ( d-a )     Parse until the character
 *|G|                      represented by 'd' is found.
 *|G|                      Return a pointer to the string
 *
 *|F| parse()
 *|F| Parse the input buffer until the character passed
 *|F| on TOS is found, or until the end of the line is
 *|F| encountered. Return a pointer to the resulting
 *|F| string on the stack.
 *|F|
 ******************************************************/
void parse()
{
  long delim;
  char *s;

  delim = TOS; DROP;
  s = gc_alloc(4096, sizeof(char), GC_MEM);
  get_token(s, delim);
}



/******************************************************
 *|F| get_token(char *s, long delim)
 *|F| Return a string (in "s") up to the specified
 *|F| delimiter. This also puts the resulting string
 *|F| on the stack.
 *|F|
 ******************************************************/
void get_token(char *s, long delim)
{
  char *t;
  long c;

  t = s;

  while (1)
  {
    if ((c = getc(input[isp])) == EOF && input[isp] != stdin)
    {
      fclose(input[isp]);
      isp--;
      break;
    }
    if (c == EOF && input[isp] == stdin)
    {
      exit(0);
    }

    if (c == '\\' && escapes == TRUE)
    {
      c = getc(input[isp]);
      if (c == 'n')
      {
        *t++ = 10;
        c = 1;
      }
      if (c == 'r')
      {
        *t++ = 13;
        c = 1;
      }
      if (c == '"')
      {
        *t++ = (char)c;
        c = 1;
      }
      if (c == '^')
      {
        *t++ = 27;
        c = 1;
      }
    }

    if (delim == 10 || delim == 32)
    {
      if (c == 10 || c == 13)
      {
        break;
      }
    }

    if (c == delim)
      break;
    if (c >= 32 || c == 10 || c == 13)
      *t++ = (char)c;
  }
  *t++ = 0;
  vm_push((long)s);
}



/******************************************************
 *|F| long include_file(char *s)
 *|F| Attempt to open a file ("s") and add it to the
 *|F| top of the input stack.
 *|F|
 ******************************************************/
long include_file(char *s)
{
  FILE *file;
  long flag;

  file = fopen(s, "r");
  flag = FALSE;

  if (file)
  {
    isp++;
    input[isp] = file;
    flag = TRUE;
  }

  return flag;
}



/******************************************************
 *|G| include   ( "- )     Attempt to open a file and
 *|G|                      add it to the input stack.
 *|G|           ( $- )     Non-parsing form
 *
 *|F| include()
 *|F| Take a filename off the stack, attempt to open
 *|F| it and add it to the input stream if successful.
 *|F|
 ******************************************************/
void include()
{
  char *s;

  if (PARSING)
  {
    s = gc_alloc(256, sizeof(char), GC_TEMP);
    get_token(s, 32); DROP;
  }
  else
  {
    s = (char *)TOS; DROP;
  }

  include_file(s);
}



/******************************************************
 *|G| needs     ( "- )     Attempt to include a file
 *|G|                      from the library (normally
 *|G|                      /usr/share/toka/library)
 *|G|           ( $- )     Non-parsing form
 *
 *|F| needs()
 *|F| Take a filename off the stack. Attempt to open it
 *|F| from the library, and add it to the input stream 
 *|F| if successful.
 *|F|
 ******************************************************/
void needs()
{
  char *s;
  char *d;

  d = gc_alloc(384, sizeof(char), GC_TEMP);
  strcpy(d, LIBRARY);

  if (PARSING)
  {
    s = gc_alloc(256, sizeof(char), GC_TEMP);
    get_token(s, 32); DROP;
  }
  else
  {
    s = (char *)TOS; DROP;
  }

  strcat(d, s);
  include_file(d);
}


/******************************************************
 *|G| end.      ( - )      Remove the current file from
 *|G|                      the input stack
 *
 *|F| force_eof()
 *|F| Remove the current file from the input stack. This
 *|F| can be used to abort an include.
 *|F|
 ******************************************************/
void force_eof()
{
  if (isp > 0)
  {
    fclose(input[isp]);
    isp--;
  }
  else
  {
    error(ERROR_CLOSE_STDIN);
  }
}
