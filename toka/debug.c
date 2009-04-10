/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: debug.c
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
#include <errno.h>
#include <ctype.h>
#include <memory.h>

#include "toka.h"

extern Inst *heap;
extern long gc_used, gc_objects, gc_depth, gc_tdepth, last;
extern VM_STACK data, address, alternate;
extern ENTRY dictionary[];
extern GCITEM gc_list[];
extern GCITEM gc_trash[];


/******************************************************
 *|G| :stat    (  -  )     Display information about
 *|G|                      the virtual machine status
 *
 *|F| vm_info()
 *|F| Display information about Toka's memory use,
 *|F| dictionary, etc.
 *|F|
 ******************************************************/
void vm_info()
{
  long a, b, c, total;
  long permanent_objects, permanent_size;
  long size, tsize;

  size = 0; tsize = 0;

  for (a = 0; a != gc_depth; a++)
    size += gc_list[a].size;
  for (a = 0; a != gc_tdepth; a++)
    tsize += gc_trash[a].size;

  permanent_objects = gc_objects - gc_depth - gc_tdepth;
  permanent_size = gc_used - size - tsize;

  a = (sizeof(GCITEM) * 128)*2;
  b = (sizeof(ENTRY) * MAX_DICTIONARY_ENTRIES);
  c = sizeof(VM_STACK) * 3 + ((MAX_DATA_STACK * sizeof(long))*2) + (MAX_RETURN_STACK * sizeof(long));

  total = a + b + c + permanent_size + size + tsize;

  printf("-- Memory Use -------------------------------\n");
  printf("  %lu KiB (%lu) used for dictionary\n", b/1024, b);
  printf("  %lu KiB (%lu) used for gc bookkeeping\n", a/1024, a);
  printf("  %lu KiB (%lu) used for stacks\n", c/1024, c);
  printf("\n");
  printf("  Permanent Allocations:\n");
  printf("    %lu objects totaling %lu KiB (%lu)\n", permanent_objects, permanent_size/1024, permanent_size);
  printf("  Temporary Allocations:\n");
  printf("    User:   %lu objects totaling %lu KiB (%lu)\n", gc_depth, size/1024, size);
  printf("    System: %lu objects totaling %lu KiB (%lu)\n", gc_tdepth, tsize/1024, tsize);
  printf("\n");
  printf("  Total: %lu KiB (%lu)\n", total/1024, total);
  printf("-- Dictionary -------------------------------\n");
  printf("  %lu named items (Max: %lu)\n", last, (long)MAX_DICTIONARY_ENTRIES);
  printf("-- Stacks -----------------------------------\n");
  printf("  Data: %lu items (Max: %lu)\n", data.sp, (long)MAX_DATA_STACK);
  printf("  Alternate: %lu items (Max: %lu)\n", alternate.sp, (long)MAX_DATA_STACK);
  printf("  Address: %lu items (Max: %lu)\n", address.sp, (long)MAX_RETURN_STACK);
  printf("---------------------------------------------\n");
}
