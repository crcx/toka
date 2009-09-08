/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: data.c
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
extern Inst *heap;
extern VM_STACK data, address, alternate;



/******************************************************
 *|G| #        ( n- )      Compile the number in TOS
 *|G|                      into a definition.
 *
 *|F| make_literal()
 *|F| Compile a call to lit() and then place TOS into
 *|F| the next memory location.
 *|F|
 ******************************************************/
void make_literal()
{
  gc_keep();
  *heap++ = (Inst)1;//&vm_lit;
  *heap++ = (Inst)TOS;
  DROP;
}


/******************************************************
 *|G| $#       ( n- )      Compile the string pointer in
 *|G|                      TOS into a definition.
 *
 *|F| make_string_literal()
 *|F| Compile a call to string_lit() and then place TOS
 *|F| into the next memory location.
 *|F|
 ******************************************************/
void make_string_literal()
{
  gc_keep();
  *heap++ = (Inst)1;//&vm_string_lit;
  *heap++ = (Inst)TOS;
  DROP;
}


/******************************************************
 *|G| @        ( a-n )     Fetch the value in memory
 *|G|                      location 'a'
 *
 *|F| fetch()
 *|F| Fetch the value in the memory location pointed to
 *|F| by TOS.
 *|F|
 ******************************************************/
void fetch()
{
  TOS = *(long *)TOS;
}


/******************************************************
 *|G| !        ( na- )     Store 'n' to memory location
 *|G|                      'a'
 *
 *|F| store()
 *|F| Store NOS into the memory location specified by
 *|F| TOS.
 *|F|
 ******************************************************/
void store()
{
  *(long *)TOS = NOS; DROP; DROP;
}


/******************************************************
 *|G| c@        ( a-n )    Fetch a byte from memory
 *|G|                      location 'a'
 *
 *|F| fetch_char()
 *|F| Fetch the value in the memory location pointed to
 *|F| by TOS. This version reads a single byte.
 *|F|
 ******************************************************/
void fetch_char()
{
  TOS = *(char *)TOS;
}


/******************************************************
 *|G| c!        ( na- )    Store byte 'n' to memory
 *|G|                      location 'a'
 *
 *|F| store_char()
 *|F| Store NOS into the memory location specified by
 *|F| TOS. This version stores a single byte.
 *|F|
 ******************************************************/
void store_char()
{
  *(char *)TOS = (char)NOS; DROP; DROP;
}


/******************************************************
 *|G| copy     ( sdc- )    Copy 'c' bytes from 's' to
 *|G|                      'd'
 *
 *|F| copy()
 *|F| Copies a block of memory from one location to
 *|F| another. They can overlap.
 *|F|
 ******************************************************/
void copy()
{
  long count, *dest, *source;
  count = TOS; DROP;
  dest = (long *)TOS; DROP;
  source = (long *)TOS; DROP;
  memmove(dest, source, count);
}


/******************************************************
 *|G| cell-size ( -n )     Return the size of a cell
 *
 *|F| cell_size()
 *|F| Push the size of a cell to the stack.
 *|F|
 ******************************************************/
void cell_size()
{
  vm_push((long)sizeof(long));
}


/******************************************************
 *|G| char-size ( -n )     Return the size of a char
 *
 *|F| char_size()
 *|F| Push the size of a char to the stack
 *|F|
 ******************************************************/
void char_size()
{
  vm_push((long)sizeof(char));
}
