/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: toka.c
 *|F|
 *
 * Copyright (c) 2006 - 2009  Charles R. Childers
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

/******************************************************
 * For rebuild:
 *
 * USES bits class cmdline conditionals console
 * USES data debug decompile dictionary ffi files
 * USES gc initial interpret math parser quotes
 * USES stack strings vm
 *
 * LINUX_LIBS dl
 ******************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <memory.h>

#include "toka.h"

extern long isp;
extern FILE *input[];



/******************************************************
 *|F| main()
 *|F| The main entry point into Toka. Sets up the
 *|F| dictionary and calls interpret().
 *|F|
 ******************************************************/
int main(int argc, char *argv[])
{
  char *homedir = getenv("HOME");
  char *personal = "/.toka";
  char *custom;

  vm_init();
  build_dictionary();
  build_arg_list(argv, (long)argc);

  isp = 0;
  input[isp] = stdin;

  if (argc >= 2)
    include_file(argv[1]);

  if (homedir)
  {
    custom = gc_alloc(strlen(homedir) + strlen(personal) + sizeof(char), sizeof(char), GC_TEMP);
    strcpy(custom, homedir);
    strcat(custom, personal);
    include_file(custom);
  }

  if (include_file("bootstrap.toka") == FALSE)
    include_file(BOOTSTRAP);

  if (argc == 1)
  {
    printf(" _____     _              \n");
    printf("|_   _|__ | | ____ _      \n");
    printf("  | |/ _ \\| |/ / _` |    \n");
    printf("  | | (_) |   < (_| |     \n");
    printf("  |_|\\___/|_|\\_\\__,_|  \n");
    printf("Copyright (c) 2006 - 2009 by Charles Childers\n\n");
  }

  interpret();

  return 0;
}

