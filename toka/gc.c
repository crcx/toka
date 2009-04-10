/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: gc.c
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
 *|F| Variables:
 *|F|   GCITEM gc_list[128]
 *|F|   Holds the list of items marked as garbage
 *|F|
 *|F|   long gc_depth
 *|F|   A pointer to the top of the garbage collection
 *|F|   list
 *|F|
 *|F|   GCITEM gc_trash[128]
 *|F|   Holds the short list of items marked as garbage
 *|F|
 *|F|   long gc_tdepth
 *|F|   A pointer to the top of the short garbage
 *|F|   collection list
 *|F|
 *|F|   long gc_used
 *|F|   Contains the total size of all currently used
 *|F|   memory, including permanent quotes.
 *|F|
 *|F|   long gc_objects
 *|F|   Contains the total number of objects that are
 *|F|   currently existing, including permanent ones.
 *|F|
 ******************************************************/
long gc_used = 0, gc_objects = 0;
GCITEM gc_list[128];  long gc_depth = 0;
GCITEM gc_trash[128]; long gc_tdepth = 0;



/******************************************************
 *|F| gc_alloc(long items, long size, long type)
 *|F| Allocate the requested memory and add it to the
 *|F| garbage collection list.
 *|F| If type is set to GC_MEM, add to the normal garbage
 *|F| collection list. If set to GC_TRASH, add to the short
 *|F| list of known garbage items which can be safely
 *|F| freed at the next gc().
 *|F| If the allocation fails, gc() is called, and the
 *|F| allocation is retried. If it still fails, an
 *|F| error is reported and Toka is terminated.
 *|F|
 ******************************************************/
void *gc_alloc(long items, long size, long type)
{
  void *memory;

  if (gc_depth == 127 || gc_tdepth == 127)
    gc();

  memory  = calloc((int)items, (int)size);

  if (memory == NULL)
  {
    gc();
    memory = calloc((int)items, (int)size);
    if (memory == NULL)
      error(ERROR_NO_MEM);
  }

  memset(memory, 0, size * items);

  if (type == GC_MEM)
  {
    gc_list[gc_depth].xt = (Inst)memory;
    gc_list[gc_depth].size = size * items;
    gc_depth++;
  }
  if (type == GC_TEMP)
  {
    gc_trash[gc_tdepth].xt = (Inst)memory;
    gc_trash[gc_tdepth].size = size * items;
    gc_tdepth++;
  }

  gc_used += size * items;
  gc_objects++;

  return memory;
}



/******************************************************
 *|G| keep     ( a-a )     Mark quotes/allocated memory
 *|G|                      as permanent.
 *
 *|F| gc_keep()
 *|F| Remove the specified address (and any childern it
 *|F| has registered) from the garbage collection list.
 *|F| If the TOS is not an allocated address, this will
 *|F| silently ignore it.
 *|F|
 ******************************************************/
void gc_keep()
{
  long a, which;

  Inst item = (Inst)TOS;
  which = -1;

  for (a = 0; a != gc_depth; a++)
  {
    if (gc_list[a].xt == item)
      which = a;
  }

  if (which != -1)
  {
    for (a = gc_depth; a > which; a--)
      gc_depth--;
  }
}



/******************************************************
 *|G| gc       ( - )       Clean the garbage
 *
 *|F| gc()
 *|F| Free the oldest allocations on the garbage list.
 *|F| Will free up to 64 trash entries and 32 normal
 *|F| entries per call.
 *|F|
 ******************************************************/
void gc()
{
  long a, b;

  /* Allocations known to be temporary */
  if (gc_tdepth < 64)
    b = 0;
  else
    b = 64;

  for (a = 0; a != b; a++)
  {
    free(gc_trash[a].xt);
    gc_used -= gc_trash[a].size;
    gc_list[a].xt = 0;
    gc_objects--;
  }

  if (b != gc_tdepth)
  {
    for (a = 0; a != gc_tdepth; a++)
    {
      gc_trash[a].xt = gc_trash[a+b].xt;
      gc_trash[a].size = gc_trash[a+b].size;
    }
  }

  gc_tdepth -= b;


  /* General Allocations  */
  if (gc_depth < 32)
    b = 0;
  else
    b = 32;

  for (a = 0; a != b; a++)
  {
    free(gc_list[a].xt);
    gc_used -= gc_list[a].size;
    gc_list[a].xt = 0;
    gc_objects--;
  }

  if (b != gc_depth)
  {
    for (a = 0; a != gc_depth; a++)
    {
      gc_list[a].xt = gc_list[a+b].xt;
      gc_list[a].size = gc_list[a+b].size;
    }
  }

  gc_depth -= b;
}



/******************************************************
 *|G| malloc   ( n-a )     Allocate 'n' bytes of memory
 *
 *|F| toka_malloc()
 *|F| Allocate TOS bytes of memory. Returns a pointer to
 *|F| the allocated memory.
 *|F|
 ******************************************************/
void toka_malloc()
{
  TOS = (long)gc_alloc(TOS, sizeof(char), GC_MEM);
}
