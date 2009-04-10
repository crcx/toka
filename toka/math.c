/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: math.c
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
extern VM_STACK data, address, alternate;



/******************************************************
 *|G| +        ( ab-c )    Add TOS and NOS
 *
 *|F| add()
 *|F| Add TOS to NOS
 *|F|
 ******************************************************/
void add()
{
  NOS += TOS; DROP;
}


/******************************************************
 *|G| -        ( ab-c )    Subtract TOS from NOS
 *
 *|F| subtract()
 *|F| Subtract TOS from NOS
 *|F|
 ******************************************************/
void subtract()
{
  NOS -= TOS; DROP;
}


/******************************************************
 *|G| *        ( ab-c )    Multiply TOS by NOS
 *
 *|F| multiply()
 *|F| Multiply TOS by NOS
 *|F|
 ******************************************************/
void multiply()
{
  NOS *= TOS; DROP;
}


/******************************************************
 *|G| /mod     ( ab-cd )   Divide and get remainder
 *
 *|F| divmod()
 *|F| Divide and return the result, including remainder
 *|F|
 ******************************************************/
void divmod()
{
  long a = TOS, b = NOS;
  NOS = b % a;
  TOS = b / a;
}
