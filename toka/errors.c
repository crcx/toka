/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: errors.c
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
#include <string.h>

#include "toka.h"
extern Inst *heap, *ip;
extern VM_STACK data, address, alternate;



/******************************************************
 *|F| error(long code)
 *|F| Display a given error by code
 *|F|
 ******************************************************/
void error(long code)
{
  long fatal;

  fatal = FALSE;

  printf("E%li: ", code);
  switch (code)
  {
    case ERROR_WORD_NOT_FOUND:
         printf("'%s' is not a word or a number.\n", (char *)TOS);
         DROP;
         break;
    case ERROR_NO_MEM:
         printf("Out of memory\n");
         fatal = TRUE;
         break;
    case ERROR_FFI_ARGUMENTS:
         printf("Too many arguments to alien function.\n");
         break;
    case ERROR_FFI_LIBRARY_NOT_FOUND:
         printf("Unable to open library '%s'.\n", (char *)TOS);
         DROP;
         break;
    case ERROR_FFI_FUNCTION_NOT_FOUND:
         printf("Lookup of symbol '%s' failed.\n", (char *)TOS);
         DROP;
         break;
    case ERROR_STACK:
         printf("Stack problem: ");
         if (data.sp < 0)
         {
           printf("data stack underflow\n");
           data.sp = 0;
           TOS = 0;
         }
         if (data.sp > MAX_DATA_STACK)
         {
           printf("data stack overflow\n");
           data.sp = 0;
           TOS = 0;
         }
         if (address.sp < 0)
         {
           printf("return stack underflow\n");
           fatal = TRUE;
         }
         if (address.sp > MAX_RETURN_STACK)
         {
           printf("return stack overflow\n");
           fatal = TRUE;
         }
         if (alternate.sp < 0)
         {
           printf("alternate stack underflow\n");
           alternate.sp = 0;
           TOAS = 0;
         }
         if (alternate.sp > MAX_DATA_STACK)
         {
           printf("alternate stack overflow\n");
           alternate.sp = 0;
           TOAS = 0;
         }
         break;
    case ERROR_CLOSE_STDIN:
         printf("Attempt to close stdin!\n");
         fatal = TRUE;
         break;
    case ERROR_QUOTE_TOO_BIG:
         printf("Maximum quote length exceeded!\n");
         fatal = TRUE;
         break;
  }
  if (fatal == TRUE)
  {
    printf("Unable to recover; will abort...\n\n");
    exit(1);
  }
}
