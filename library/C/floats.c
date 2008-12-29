/************************************************************
 * This provides a floating point stack and basic operations
 * for Toka.
 *
 *|F|
 *|F| File: floats.c
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
 ************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE -1
#define FALSE 0

#define TOS fstack[fsp]
#define NOS fstack[fsp-1]
#define DROP fsp--

double fstack[100];
long  fsp;


/******************************************
 *|F| toka_float_init()
 *|F| Setup support for floating point
 *|F|
 ******************************************/
void toka_float_init()
{
  fsp = 0;
}


/******************************************
 *|F| toka_float_make(char *buf)
 *|F| Convert the value in the buffer to a
 *|F| floating point number.
 *|F|
 ******************************************/
void toka_float_make(char *buf)
{
  fsp++;
  TOS = strtod(buf, 0);
}


/******************************************
 *|F| toka_float_add()
 *|F| Add TOS and NOS together, leaving the 
 *|F| result on the stack.
 *|F|
 ******************************************/
void toka_float_add()
{
  NOS += TOS; DROP;
}


/******************************************
 *|F| toka_float_subtract()
 *|F| Subtract TOS from NOS, leaving the 
 *|F| result on the stack.
 *|F|
 ******************************************/
void toka_float_subtract()
{
  NOS -= TOS; DROP;
}


/******************************************
 *|F| toka_float_divide()
 *|F| Divide TOS by NOS leaving the result
 *|F| on the stack.
 *|F|
 ******************************************/
void toka_float_divide()
{
  double a = TOS, b = NOS;
  NOS = b / a;
  DROP;
}


/******************************************
 *|F| toka_float_multiply()
 *|F| Multiply TOS and NOS, leaving the 
 *|F| result on the stack.
 *|F|
 ******************************************/
void toka_float_multiply()
{
  NOS *= TOS; DROP;
}


/******************************************
 *|F| long toka_float_size()
 *|F| Return the size of a float
 *|F|
 ******************************************/
long toka_float_size()
{
  return (long)sizeof(double);
}


/******************************************
 *|F| toka_float_display()
 *|F| Display a float. Consumes TOS.
 *|F|
 ******************************************/
void toka_float_display()
{
  printf("%f ", TOS); DROP;
}


/******************************************
 *|F| toka_float_fetch(long address)
 *|F| Fetch from a double variable
 *|F|
 ******************************************/
void toka_float_fetch(long address)
{
  double a;
  a = *(double *)address;
  fsp++; TOS = a;
}


/******************************************************
 *|F| toka_float_store()
 *|F| Store NOS into the memory location specified by
 *|F| TOS.
 *|F|
 ******************************************************/
void toka_float_store(long address)
{
  *(double *)address = TOS;
  DROP;
}


/******************************************************
 *|F| toka_float_dup()
 *|F| Duplicate the TOS
 *|F|
 ******************************************************/
void toka_float_dup()
{
  fstack[fsp+1] = TOS;
  fsp++;
}


/******************************************************
 *|F| toka_float_drop()
 *|F| Drop the TOS
 *|F|
 ******************************************************/
void toka_float_drop()
{
  fsp--;
}


/******************************************************
 *|F| toka_float_swap()
 *|F| Exchange TOS and NOS
 *|F|
 ******************************************************/
void toka_float_swap()
{
  double a, b;
  a = TOS;    b = NOS;
  TOS = b;    NOS = a;
}


/******************************************************
 *|F| long toka_float_depth()
 *|F| Return the number of items on the stack
 *|F|
 ******************************************************/
long toka_float_depth()
{
  long items = fsp;
  return items;
}


/******************************************************
 *|F| toka_float_display_stack()
 *|F| Display all items on the stack.
 *|F|
 ******************************************************/
void toka_float_display_stack()
{
  long a;
  printf("<%li> ", fsp);
  for (a = 1; a <= fsp; a++)
  {
    printf("%f ", fstack[a]);
  }
  printf("\n");
}


/******************************************************
 *|F| toka_float_compare_equals()
 *|F| Compare two floats
 *|F|
 ******************************************************/
long toka_float_compare_equals()
{
  long flag = FALSE;
  flag = (TOS != NOS) ? 0 : -1; DROP; DROP;
  return flag;
}


/******************************************************
 *|F| toka_float_compare_not_equals()
 *|F| Compare two floats
 *|F|
 ******************************************************/
long toka_float_compare_not_equals()
{
  long flag = FALSE;
  flag = (TOS == NOS) ? 0 : -1; DROP; DROP;
  return flag;
}


/******************************************************
 *|F| toka_float_compare_greater_than()
 *|F| Compare two floats
 *|F|
 ******************************************************/
long toka_float_compare_greater_than()
{
  long flag = FALSE;
  flag = (TOS >= NOS) ? 0 : -1; DROP; DROP;
  return flag;
}


/******************************************************
 *|F| toka_float_compare_less_than()
 *|F| Compare two floats
 *|F|
 ******************************************************/
long toka_float_compare_less_than()
{
  long flag = FALSE;
  flag = (TOS <= NOS) ? 0 : -1; DROP; DROP;
  return flag;
}


/******************************************************
 *|F| toka_float_push(long x)
 *|F| Push 'x' to the float stack
 *|F|
 ******************************************************/
void toka_float_push(long x)
{
  fsp++;
  TOS = (double)x;
}


/******************************************************
 *|F| long toka_float_pop()
 *|F| Pop a value from the float stack
 *|F|
 ******************************************************/
long toka_float_pop()
{
  long x = (long)TOS;
  DROP;
  return x;
}

