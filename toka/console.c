/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: console.c
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

extern long base;
extern VM_STACK data, address, alternate;



/******************************************************
 *|G| .        ( n- )      Display the numeric value
 *|G|                      TOS represents
 *
 *|F| dot()
 *|F| Display the number on TOS using the current base
 *|F| if possible. If not possible, uses decimal output.
 *|F|
 ******************************************************/
void dot()
{
  switch(base)
  {
    case  8: printf("%lo ", TOS); break;
    case 16: printf("%lx ", TOS); break;
    default: printf("%li ", TOS); break;
  }
  DROP;
}


/******************************************************
 *|G| emit     ( c- )      Display the ASCII character
 *|G|                      TOS represents.
 *
 *|F| emit()
 *|F| Display the character TOS corresponds to. Consumes
 *|F| TOS.
 *|F|
 ******************************************************/
void emit()
{
  putchar((char)TOS);
  DROP;
}


/******************************************************
 *|G| type     ( a- )      Display a string
 *
 *|F| type()
 *|F| Display the string TOS points to. Consumes TOS.
 *|F|
 ******************************************************/
void type()
{
  printf((char *)TOS);
  DROP;
}


/******************************************************
 *|G| bye      ( - )       Quit Toka
 *
 *|F| bye()
 *|F| Quit Toka
 *|F|
 ******************************************************/
void bye()
{
  exit(0);
}
