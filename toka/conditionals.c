/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: conditionals.c
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
 *|G| <        ( ab-f )    Compare 'a' and 'b', return
 *|G|                      a flag
 *
 *|F| less_than()
 *|F| Compare TOS and NOS, return a flag.
 *|F|
 ******************************************************/
void less_than()
{
  NOS = (TOS <= NOS) ?  FALSE : TRUE; DROP;
}


/******************************************************
 *|G| >        ( ab-f )    Compare 'a' and 'b', return
 *|G|                      a flag
 *
 *|F| greater_than()
 *|F| Compare TOS and NOS, return a flag.
 *|F|
 ******************************************************/
void greater_than()
{
  NOS = (TOS >= NOS) ?  FALSE : TRUE; DROP;
}


/******************************************************
 *|G| =        ( ab-f )    Compare 'a' and 'b', return
 *|G|                      a flag
 *
 *|F| equals()
 *|F| Compare TOS and NOS, return a flag.
 *|F|
 ******************************************************/
void equals()
{
  NOS = (TOS != NOS) ? FALSE : TRUE; DROP;
}


/******************************************************
 *|G| <>       ( ab-f )    Compare 'a' and 'b', return
 *|G|                      a flag
 *
 *|F| not_equals()
 *|F| Compare TOS and NOS, return a flag.
 *|F|
 ******************************************************/
void not_equals()
{
  NOS = (TOS == NOS) ? FALSE : TRUE; DROP;
}
