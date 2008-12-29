/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: stack.c
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
extern VM_STACK data, address, alternate;

/******************************************************
 *|G| dup      ( n-nn )    Duplicate the TOS
 *
 *|F| stack_dup()
 *|F| Duplicate the TOS
 *|F|
 ******************************************************/
void stack_dup()
{
  vm_push(TOS);
}


/******************************************************
 *|G| drop     ( n- )      Drop the TOS
 *
 *|F| stack_drop()
 *|F| Drop the TOS
 *|F|
 ******************************************************/
void stack_drop()
{
  data.sp--;
}


/******************************************************
 *|G| swap     ( ab-ba )   Exchange the TOS and NOS
 *
 *|F| stack_swap()
 *|F| Exchange TOS and NOS
 *|F|
 ******************************************************/
void stack_swap()
{
  long a, b;
  a = TOS;    b = NOS;
  TOS = b;    NOS = a;
}


/******************************************************
 *|G| >r       ( n- )      Push TOS to return stack, DROP
 *
 *|F| stack_to_r()
 *|F| Push TOS to return stack, DROP TOS
 *|F|
 ******************************************************/
void stack_to_r()
{
  TOAS = TOS; DROP; alternate.sp++;
}


/******************************************************
 *|G| r>       ( -n )      Pop TORS to the data stack
 *
 *|F| stack_from_r()
 *|F| Pop TORS to the data stack
 *|F|
 ******************************************************/
void stack_from_r()
{
  alternate.sp--; stack_dup(); TOS = TOAS; 
}


/******************************************************
 *|G| depth    ( -n )      Return the number of items
 *|G|                      on the stack
 *
 *|F| stack_depth()
 *|F| Return the number of items on the stack
 *|F|
 ******************************************************/
void stack_depth()
{
  vm_push(data.sp);
}
