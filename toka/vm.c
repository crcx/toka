/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: vm.c
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

#include "toka.h"


/******************************************************
 *|F| Variables:
 *|F|   Inst *heap
 *|F|   Pointer into the current heap
 *|F|
 *|F|   Inst *ip
 *|F|   The instruction pointer
 *|F|
 *|F|   VM_STACK data, address, alternate
 *|F|   The data, address, and return stacks
 *|F|
 ******************************************************/
Inst *heap, *ip;
VM_STACK data, address, alternate;


/******************************************************
 *|F| vm_init()
 *|F| Prepare the virtual machine. This sets up the
 *|F| stacks, and any other things that need to be
 *|F| initialized.
 *|F|
 ******************************************************/
void vm_init()
{
  data.stack = gc_alloc(MAX_DATA_STACK, sizeof(long), GC_KEEP);
  address.stack = gc_alloc(MAX_DATA_STACK, sizeof(long), GC_KEEP);
  alternate.stack = gc_alloc(MAX_DATA_STACK, sizeof(long), GC_KEEP);

  data.sp = 0;
  address.sp = 0;
  alternate.sp = 0;
}


/******************************************************
 *|F| vm_run(Inst)
 *|F| Run through a list of instructions
 *|F| Side effects:
 *|F|   modifes *ip
 *|F|
 ******************************************************/
void vm_run(Inst prog[])
{
  ip = prog;
  while (*ip != 0)
  {
    vm_stack_check();
    ((*ip++)());
  }
}


/******************************************************
 *|F| vm_stack_check()
 *|F| Check for over/underflow and reset if detected
 *|F| If the return stack over/underflows, exit Toka
 *|F| 
 ******************************************************/
void vm_stack_check()
{
  if (data.sp < 0 || data.sp > MAX_DATA_STACK)
    error(ERROR_STACK);
  if ((address.sp < 0 || address.sp > MAX_RETURN_STACK) || (alternate.sp < 0 || alternate.sp > MAX_DATA_STACK))
    error(ERROR_STACK);
}


/******************************************************
 *|F| vm_push(long a)
 *|F| Push a number to the stack.
 *|F|
 ******************************************************/
void vm_push(long a)
{
  data.sp++; TOS = a;
}


/******************************************************
 *|F| vm_lit()
 *|F| Push the value in the following memory location
 *|F| to the stack
 *|F|
 ******************************************************/
void vm_lit()
{
  vm_push((long)*ip++);
}


/******************************************************
 *|F| vm_quote_lit()
 *|F| Push the value in the following memory location
 *|F| to the stack
 *|F|
 ******************************************************/
void vm_quote_lit()
{
  vm_push((long)*ip++);
}


/******************************************************
 *|F| vm_string_lit()
 *|F| Push the pointer in the following memory location
 *|F| to the stack. This is a helper function for 
 *|F| strings.
 *|F|
 ******************************************************/
void vm_string_lit()
{
  vm_push((long)*ip++);
}


/******************************************************
 *|F| vm_primitive()
 *|F| Invoke the primitive id # specified in the 
 *|F| following cell.
 ******************************************************/
void vm_primitive()
{
  Inst xt;
  xt = (Inst )*ip++;
  ((xt)());
}
