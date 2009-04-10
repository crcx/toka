/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: dictionary.c
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
extern long parser, compiler;
extern VM_STACK data, address, alternate;



/******************************************************
 *|F| Variables:
 *|F|   ENTRY dictionary[MAX_DICTIONARY_ENTRIES];
 *|F|   Holds the dictionary entries, up to
 *|F|   MAX_DICTIONARY_ENTRIES
 *|F|
 *|F|   long last
 *|F|   A pointer to the most recent dictionary entry
 *|F|
 *
 *|G| last     ( -a )      Variable holding the number
 *|G|                      of the most recent dictionary
 *|G|                      entry
 ******************************************************/
ENTRY dictionary[MAX_DICTIONARY_ENTRIES];
long  last=0;



/******************************************************
 *|F| add_entry(char *name, Inst xt, Inst class, long primitive)
 *|F| Add a word to the dictionary. If 'primitive' is set
 *|F| to TRUE, create a wrapper quote for the primitive.
 *|F|
 ******************************************************/
void add_entry(char *name, void *xt, void *class, long primitive)
{
  Inst quote;

  if (class != &data_class && primitive == TRUE)
  {
    begin_quote();
      *heap++ = &vm_primitive;
      *heap++ = (Inst)xt;
    end_quote();
    quote = (Inst)TOS; DROP;
  }
  else
  {
    quote = (Inst)xt;
  }

  last++;
  dictionary[last].xt = quote;
  dictionary[last].class = (Inst)class;
  strcpy(dictionary[last].name, name);
}


/******************************************************
 *|F| name_attach(void *class)
 *|F| Attach a name (from the input stream) to the
 *|F| specified quote address. This word is given the
 *|F| semantics of the specified class.
 *|F|
 ******************************************************/
void name_attach(void *class)
{
  char *s;
  Inst xt;

  if (PARSING)
  {
    s = gc_alloc(128, sizeof(char), GC_TEMP);
    get_token(s, 32); DROP;
  }
  else
  {
    s = (char *)TOS; DROP;
  }

  xt = (Inst)TOS; gc_keep(); DROP;
  add_entry(s, xt, class, FALSE);
}


/******************************************************
 *|G| is       ( a"- )     Attach a name to a quote
 *|G|          ( a$- )     Non-parsing form
 *
 *|F| name_quote()
 *|F| Attach a name (from the input stream) to the
 *|F| specified quote address. This word is given the
 *|F| semantics of quote_word_class().
 *|F|
 ******************************************************/
void name_quote()
{
  name_attach(&word_class);
}


/******************************************************
 *|G| is-macro ( a"- )     Attach a name to a quote
 *|G|          ( a$- )     Non-parsing form
 *
 *|F| name_macro()
 *|F| Attach a name (from the input stream) to the
 *|F| specified quote address. This word is given the
 *|F| semantics of quote_macro_class().
 *|F|
 ******************************************************/
void name_macro()
{
  name_attach(&macro_class);
}


/******************************************************
 *|G| is-data  ( a"- )     Attach a name to data memory
 *|G|          ( a$- )     Non-parsing form
 *
 *|F| name_data()
 *|F| Attach a name (from the input stream) to the data
 *|F| at the specified address. Semantics are the same
 *|F| as the data_class().
 *|F|
 ******************************************************/
void name_data()
{
  name_attach(&data_class);
}


/******************************************************
 *|F| find_word()
 *|F| Search for a word (name taken from the string
 *|F| passed on TOS) in the dictionary. Returns the
 *|F| xt, class, and a flag of TRUE if found. If not
 *|F| found, returns only a flag of FALSE.
 *|F|
 ******************************************************/
void find_word()
{
  long flag, a;
  char *s = (char *)TOS; DROP;

  flag = 0;
  for (a = last; a > 0; a--)
  {
    if ((strcmp(dictionary[a].name, s) == 0) && flag == FALSE)
    {
      vm_push((long)dictionary[a].xt);
      vm_push((long)dictionary[a].class);
      flag = TRUE;
    }
  }
  vm_push(flag);
}


/******************************************************
 *|G| `        ( "-a )     Return a quote corresponding
 *|G|                      to the specified word.
 *|G|          ( $-a )     Non-parsing form
 *
 *|F| return_quote()
 *|F| Find a name (from the input stream) and return a
 *|F| quote that corresponds to the word.
 *|F|
 ******************************************************/
void return_quote()
{
  long flag;
  Inst class, xt;

  char *s;

  if (PARSING)
  {
    s = gc_alloc(128, sizeof(char), GC_TEMP);
    get_token(s, 32);
  }

  find_word();
  flag = TOS; DROP;

  if (flag == TRUE)
  {
    class = (Inst)TOS; DROP;
    xt = (Inst)TOS; DROP;
    vm_push((long)xt);
    if (COMPILING)
    {
      *heap++ = (Inst)&vm_quote_lit;
      *heap++ = (Inst)TOS; DROP;
    }
  }
  else
  {
    vm_push(FALSE);
    if (COMPILING)
    {
      *heap++ = (Inst)&vm_quote_lit;
      *heap++ = (Inst)TOS; DROP;
    }
  }
}


/******************************************************
 *|G| :name    ( n-$ )     Return the name for a
 *|G|                      dictionary entry
 *|G| :xt      ( n-$ )     Return the address of a
 *|G|                      dictionary entry
 *|G| :class   ( n-$ )     Return the class # for a
 *|G|                      dictionary entry
 *
 *|F| return_name()
 *|F| Return a pointer to the name and the starting
 *|F| address of a specific dictionary entry.
 *|F|
 *|F| return_xt()
 *|F| Return a pointer to the execution token (address)
 *|F| of a specific dictionary entry.
 *|F|
 *|F| return_class()
 *|F| Return the class id number of a specific dictionary
 *|F| entry.
 *|F|
 ******************************************************/
void return_name()
{
  long which = TOS; DROP;
  vm_push((long)dictionary[which].name);
}
void return_xt()
{
  long which = TOS; DROP;
  vm_push((long)dictionary[which].xt);
}
void return_class()
{
  long which = TOS; DROP;
  void *class = dictionary[which].class;
  if (class == &word_class)
    which = 0;
  if (class == &macro_class)
    which = 1;
  if (class == &data_class)
    which = 2;

  vm_push(which);
}
