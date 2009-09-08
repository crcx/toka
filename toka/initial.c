/******************************************************
 * Toka
 *
 *|F|
 *|F| FILE: initial.c
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

#include "toka.h"

extern long base, compiler, last, isp, parser, escapes;
extern Inst *heap;


/******************************************************
 *|F| build_dictionary()
 *|F| Attach names and classes to the various initial
 *|F| words in the Toka language.
 *|F|
 ******************************************************/
void build_dictionary()
{
  /* bits.c */
  add_entry("<<",        &lshift,        &word_class, TRUE);
  add_entry(">>",        &rshift,        &word_class, TRUE);
  add_entry("and",       &and,           &word_class, TRUE);
  add_entry("or",        &or,            &word_class, TRUE);
  add_entry("xor",       &xor,           &word_class, TRUE);

  /* cmdline.c */
  add_entry("#args",     &num_args,      &word_class, TRUE);
  add_entry("arglist",   &get_arg_list,  &word_class, TRUE);

  /* conditionals.c */
  add_entry("<",         &less_than,     &word_class, TRUE);
  add_entry(">",         &greater_than,  &word_class, TRUE);
  add_entry("=",         &equals,        &word_class, TRUE);
  add_entry("<>",        &not_equals,    &word_class, TRUE);

  /* console.c */
  add_entry(".",         &dot,           &word_class, TRUE);
  add_entry("emit",      &emit,          &word_class, TRUE);
  add_entry("type",      &type,          &word_class, TRUE);
  add_entry("bye",       &bye,           &word_class, TRUE);

  /* data.c */
  add_entry("@",         &fetch,         &word_class, TRUE);
  add_entry("!",         &store,         &word_class, TRUE);
  add_entry("c@",        &fetch_char,    &word_class, TRUE);
  add_entry("c!",        &store_char,    &word_class, TRUE);
  add_entry("#",         &make_literal,  &word_class, TRUE);
  add_entry("$#",        &make_string_literal,&word_class, TRUE);
  add_entry("copy",      &copy,          &word_class, TRUE);
  add_entry("cell-size", &cell_size,     &word_class, TRUE);
  add_entry("char-size", &char_size,     &word_class, TRUE);

  /* debug.c */
  add_entry(":stat",     &vm_info,       &word_class, TRUE);

  /* decompile.c */
  add_entry(":see",      &see,           &word_class, TRUE);

  /* dictionary.c */
  add_entry("`",         &return_quote,  &macro_class, TRUE);
  add_entry(":name",     &return_name,   &word_class, TRUE);
  add_entry(":xt",       &return_xt,     &word_class, TRUE);
  add_entry(":class",    &return_class,  &word_class, TRUE);
  add_entry("is",        &name_quote,    &word_class, TRUE);
  add_entry("is-macro",  &name_macro,    &word_class, TRUE);
  add_entry("is-data",   &name_data,     &word_class, TRUE);
  add_entry("last",      &last,          &data_class, TRUE);

  /* ffi.c */
  add_entry("from",      &ffi_from,      &word_class, TRUE);
  add_entry("import",    &ffi_import,    &word_class, TRUE);
  add_entry("as",        &ffi_rename,    &word_class, TRUE);

  /* files.c */
  add_entry("file.open", &file_open,     &word_class, TRUE);
  add_entry("file.close",&file_close,    &word_class, TRUE);
  add_entry("file.read", &file_read,     &word_class, TRUE);
  add_entry("file.write",&file_write,    &word_class, TRUE);
  add_entry("file.size", &file_size,     &word_class, TRUE);
  add_entry("file.seek", &file_seek,     &word_class, TRUE);
  add_entry("file.pos",  &file_pos,      &word_class, TRUE);

  /* gc.c */
  add_entry("malloc",    &toka_malloc,   &word_class, TRUE);
  add_entry("keep",      &gc_keep,       &word_class, TRUE);
  add_entry("gc",        &gc,            &word_class, TRUE);

  /* interpret.c */
  add_entry("compiler",  &compiler,      &data_class, TRUE);

  /* math.c */
  add_entry("+",         &add,           &word_class, TRUE);
  add_entry("-",         &subtract,      &word_class, TRUE);
  add_entry("*",         &multiply,      &word_class, TRUE);
  add_entry("/mod",      &divmod,        &word_class, TRUE);

  /* parser.c */
  add_entry("parse",     &parse,         &word_class, TRUE);
  add_entry(">number",   &to_number,     &word_class, TRUE);
  add_entry(">string",   &to_string,     &word_class, TRUE);
  add_entry("include",   &include,       &word_class, TRUE);
  add_entry("needs",     &needs,         &word_class, TRUE);
  add_entry("end.",      &force_eof,     &word_class, TRUE);
  add_entry("base",      &base,          &data_class, TRUE);
  add_entry("parser",    &parser,        &data_class, TRUE);
  add_entry("escape-sequences",&escapes, &data_class, TRUE);

  /* quotes.c */
  add_entry("[",         &begin_quote,   &macro_class, TRUE);
  add_entry("]",         &end_quote,     &macro_class, TRUE);
  add_entry("recurse",   &recurse,       &macro_class, TRUE);
  add_entry("invoke",    &invoke,        &word_class, TRUE);
  add_entry("compile",   &compile,       &word_class, TRUE);
  add_entry("countedLoop", &countedLoop, &word_class, TRUE);
  add_entry("i",         &quote_index,   &word_class, TRUE);
  add_entry("ifTrueFalse",&truefalse,    &word_class, TRUE);
  add_entry("whileTrue",  &quote_while_true,  &word_class, TRUE);
  add_entry("whileFalse", &quote_while_false, &word_class, TRUE);

  /* stack.c */
  add_entry("dup",       &stack_dup,     &word_class, TRUE);
  add_entry("drop",      &stack_drop,    &word_class, TRUE);
  add_entry("swap",      &stack_swap,    &word_class, TRUE);
  add_entry(">r",        &stack_to_r,    &word_class, TRUE);
  add_entry("r>",        &stack_from_r,  &word_class, TRUE);
  add_entry("depth",     &stack_depth,   &word_class, TRUE);

  /* strings.c */
  add_entry("string.getLength", &string_getLength,  &word_class, TRUE);
  add_entry("string.grow",      &string_grow,       &word_class, TRUE);
  add_entry("string.append",    &string_append,     &word_class, TRUE);
  add_entry("string.compare",   &string_compare,    &word_class, TRUE);

  /* vm.c */
  add_entry("heap",      &heap,          &data_class, TRUE);
  add_entry(",", &vm_comma, &word_class, TRUE);
}
