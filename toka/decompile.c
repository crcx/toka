/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: decompile.c
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

#include "toka.h"
extern ENTRY dictionary[];
extern long last;
extern VM_STACK data, address, alternate;



/******************************************************
 *|F| long resolve_name(Inst xt)
 *|F| Search for a name in the dictionary that corresponds
 *|F| to 'xt'. Display it if found, and return a flag.
 *|F|
 ******************************************************/
long resolve_name(Inst xt)
{
  long flag, a;

  flag = FALSE;
  for (a = last; a > 0; a--)
  {
     if (dictionary[a].xt == xt && flag == 0)
     {
       printf("%s ", dictionary[a].name);
       flag = TRUE;
     }
  }
  return flag;
}


/******************************************************
 *|F| decompile(Inst *xt)
 *|F| Decompile a quote and its children and display the
 *|F| result on the screen.
 *|F|
 ******************************************************/
void decompile(Inst *xt)
{
  Inst this;
  long flag;
  char *string;

  printf("[ ");

  while (1) {
    this = (Inst)*xt++;
    resolve_name(this);
    if (this == (Inst)0)
    {
      printf("] ");
      return;
    }
    if (this == &vm_primitive)
    {
      this = (Inst)*xt++;
      printf("<primitive: %li> ", (long)this);
    }
    if (this == (Inst)1)
    {
      this = (Inst)*xt++;
      if (resolve_name(this) == FALSE)
        printf("<vm:int %li> ", (long)this);
    }
    if (this == (Inst)27)
    {
      printf("<vm:dec %li> ", (long)this);
    }
    if (this == &vm_lit)
    {
      this = (Inst)*xt++;
      if (resolve_name(this) == FALSE)
        printf("vm_lit:%li ", (long)this);
    }
    if (this == &vm_quote_lit)
    {
      printf("` ");
      this = (Inst)*xt++;
      if (resolve_name(this) == FALSE)
        printf("%li ", (long)this);
    }
    if (this == &vm_string_lit)
    {
      string = (char *)*xt++;
      putchar('"');
      putchar(' ');
      for (; *string; string++)
      {
        switch (*string)
        {
          case 27: printf("\\^"); break;
          case 10: printf("\\n"); break;
          case 13: printf("\\r"); break;
          case 92: printf("\\"); break;
          case 34: printf("\\\""); break;
          default: putchar(*string);
        }
      }
      putchar('"');
      putchar(' ');
    }
    if (this == &qlit)
    {
      this = (Inst)*xt++;
      decompile((Inst *)this);
    }
    if (this == &quote_class)
    {
      this = (Inst)*xt++;
      flag = resolve_name(this);
      if (flag == FALSE)
      {
        decompile((Inst *)this);
        printf("invoke ");
      }
    }
    if (this == &ffi_invoke)
      printf("<ffi> ");
  }
}


/******************************************************
 *|G| :see     (  a- )     Decompile the specified quote
 *
 *|F| see()
 *|F| Decompile the quote on the stack.
 *|F|
 ******************************************************/
void see()
{
  decompile((Inst *)TOS);
  DROP;
  putchar('\n');
}
