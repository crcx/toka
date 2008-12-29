/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: bits.c
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
 *|G| <<       ( ab-c )    Shift 'a' left by 'b' bits
 *
 *|F| lshift()
 *|F| Shift NOS left by TOS bits
 *|F|
 ******************************************************/
void lshift()
{
  NOS = NOS << TOS; DROP;
}


/******************************************************
 *|G| >>       ( ab-c )    Shift 'a' right by 'b' bits
 *
 *|F| rshift()
 *|F| Shift NOS right by TOS bits
 *|F|
 ******************************************************/
void rshift()
{
  NOS = NOS >> TOS; DROP;
}


/******************************************************
 *|G| and      ( ab-c )    Perform a bitwise AND
 *
 *|F| and()
 *|F| Perform a bitwise AND
 *|F|
 ******************************************************/
void and()
{
  NOS = TOS & NOS; DROP;
}


/******************************************************
 *|G| or       ( ab-c )    Perform a bitwise OR
 *
 *|F| or()
 *|F| Perform a bitwise OR
 *|F|
 ******************************************************/
void or()
{
  NOS = TOS | NOS; DROP;
}


/******************************************************
 *|G| xor      ( ab-c )    Perform a bitwise XOR
 *
 *|F| xor()
 *|F| Perform a bitwise XOR
 *|F|
 ******************************************************/
void xor()
{
  NOS = TOS ^ NOS; DROP;
}
