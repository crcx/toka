/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: cmdline.c
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


/******************************************************
 *|F| Variables:
 *|F|   long arg_count
 *|F|   Holds the number of command line arguments
 *|F|
 *|F|   char *arg_list[128]
 *|F|   Holds the list of command line arguments. 
 *|F|
 ******************************************************/
long arg_count;
char *arg_list[128];


/******************************************************
 *|G| #args    (  -n )     Return the number of arguments
 *
 *|F| num_args()
 *|F| Return the number of arguments passed to Toka.
 *|F|
 ******************************************************/
void num_args()
{
  vm_push(arg_count);
}


/******************************************************
 *|G| arglist  (  -a )     Return a pointer to the 
 *|G|                      array of command line arguments.
 *
 *|F| get_arg_list()
 *|F| Return the number of arguments, not including the
 *|F| file names used to launch this program.
 *|F|
 ******************************************************/
void get_arg_list()
{
  vm_push((long)&arg_list);
}


/******************************************************
 *|F| build_arg_list(char *args[], long count)
 *|F| Copy pointers to the command line arguments to
 *|F| arg_list[]. Also sets arg_count.
 *|F|
 ******************************************************/
void build_arg_list(char *args[], long count)
{
  long a;
  if (count >= 2)
  {
    for (a = 0; a < count; a++)
       arg_list[a] = args[a+1];
    arg_count = count - 1;
  }
  else
  {
    arg_count = 0;
  }
}
