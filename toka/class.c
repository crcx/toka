/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: class.c
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

#include "toka.h"

extern VM_STACK data, address, alternate;
extern long compiler, last;
extern Inst *heap;


/******************************************************
 *|F| data_class()
 *|F| If compiling, compile a call to lit() and then
 *|F| inline TOS into the following location. Otherwise
 *|F| leave TOS alone.
 *|F|
 ******************************************************/
void data_class()
{
  if (COMPILING) {
    *heap++ = (Inst)&vm_lit;
    *heap++ = (Inst)TOS; DROP;
  }
}


/******************************************************
 *|F| macro_class()
 *|F| Always invoke the quote.
 *|F|
 ******************************************************/
void macro_class()
{
  invoke();
}


/******************************************************
 *|F| quote_class()
 *|F| Handler for quotes; this takes two cells, one
 *|F| which is a call to this function, the other is
 *|F| the pointer to the quote to invoke. This is used
 *|F| internally by word_class().
 *|F|
 ******************************************************/
void quote_class()
{
  vm_lit();
  invoke();
}


/******************************************************
 *|F| word_class()
 *|F| Perform data_class() semantics, then, if 
 *|F| compiling, compile a call to invoke(). Otherwise,
 *|F| invoke() is called with the xt on TOS. Makes use
 *|F| of quote_class().
 *|F|
 ******************************************************/
void word_class()
{
  if (COMPILING)
  {
    *heap++ = &quote_class;
    *heap++ = (Inst)TOS; DROP;
  }
  else
  {
    invoke();
  }
}
