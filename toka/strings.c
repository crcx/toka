/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: strings.c
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
#include <string.h>
#include <strings.h>

#include "toka.h"


extern VM_STACK data, address, alternate;



void string_getLength()
{
   char *x;
   x = (char *)TOS;
   vm_push((long)strlen(x));
}


void string_grow()
{
  long x;
  char *src;
  x = TOS; data.sp--;
  string_getLength();
  TOS += x + sizeof(char);
  x = TOS; data.sp--;
  src = (char *)TOS; data.sp--;
  vm_push((long)gc_alloc(x, sizeof(char), GC_KEEP));
  strcpy((char *)TOS, src);
}


void string_append()
{
  char *src, *dest;
  src = (char *)TOS; data.sp--;
  string_getLength();
  TOS += (sizeof(char)*2);
  string_grow();
  dest = (char *)TOS; data.sp-- ;
  strcat(dest, src);
  vm_push((long)dest);
}

void string_compare()
{
  char *src, *dest;
  src  = (char *)TOS; data.sp--;
  dest = (char *)TOS; data.sp--;
  if (strcmp(src, dest) == 0)
    vm_push(TRUE);
  else
    vm_push(FALSE);
}
