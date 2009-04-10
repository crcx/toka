/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: interpret.c
 *|F|
 *
 * Copyright (c) 2006-2009  Charles R. Childers
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


extern Inst *heap;
extern ENTRY dictionary[];
extern VM_STACK data, address, alternate;



/******************************************************
 *|F| Variables:
 *|F|   long compiler
 *|F|   When set to FALSE, interpret; when set to TRUE,
 *|F|   compile. This is checked by the various word
 *|F|   classes defined in class.c
 *|F|
 *|F|   char *scratch
 *|F|   Temporary holding area used by the parser and
 *|F|   other routines.
 *|F|
 *|F|   char *tib
 *|F|   Pointer to the text input buffer.
 *|F|
 *
 *|G| heap     ( -a )      Variable pointing to the top
 *|G|                      of the local heap
 *|G| compiler ( -a )      Variable holding the compiler
 *|G|                      state
 ******************************************************/
long compiler=0;
char *scratch;
char *tib;



/******************************************************
 *|F| interpret()
 *|F| Accept and process input.
 *|F|
 ******************************************************/
void interpret()
{
  Inst class;
  long flag;

  scratch = calloc(1024, sizeof(char));

  while (1)
  {
    flag = FALSE; class = 0;
    fflush(stdout);
    vm_stack_check();
    get_token(scratch, 32);
    find_word();
    flag = TOS; DROP;
    if (flag == FALSE)
    {
      if (strlen(scratch) != 0)
      {
        vm_push((long)scratch);
        to_number();
        flag = TOS; DROP;
        if (flag == TRUE)
          data_class();
        else
          error(ERROR_WORD_NOT_FOUND);
      }
    }
    else
    {
      class = (Inst)TOS; DROP;
      ((class)());
    }
  }
}
