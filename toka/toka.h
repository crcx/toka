/******************************************************
 * Toka
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

#ifndef __TOKA_H
#define __TOKA_H

/******************************************************
 * These specify the paths to the library and bootstrap
 * file. Set them as desired or needed by your system.
 ******************************************************/
#define LIBRARY "/usr/share/toka/library/" 
#define BOOTSTRAP "/usr/share/toka/bootstrap.toka"



/******************************************************
 * These are the maximum size to use for various things.
 * Actually, in the current implementation, these are
 * the actual sizes allocated.
 ******************************************************/
#define MAX_QUOTE_SIZE          128
#define MAX_DATA_STACK          128
#define MAX_RETURN_STACK       2048
#define MAX_DICTIONARY_ENTRIES 4096



/******************************************************
 * Just for readability later on. Sorry if you don't
 * like my wrappers, but I find them helpful.
 ******************************************************/
#define FALSE 0
#define TRUE -1
#define ON   -1
#define OFF   0
#define COMPILING compiler == ON
#define PARSING parser == ON

typedef void (*Inst)();


/******************************************************
 * Include all of the function prototypes. Each file
 * has a corresponding header file.
 ******************************************************/
#include "headers/bits.h"
#include "headers/class.h"
#include "headers/cmdline.h"
#include "headers/conditionals.h"
#include "headers/console.h"
#include "headers/data.h"
#include "headers/debug.h"
#include "headers/decompile.h"
#include "headers/dictionary.h"
#include "headers/errors.h"
#include "headers/ffi.h"
#include "headers/files.h"
#include "headers/gc.h"
#include "headers/initial.h"
#include "headers/interpret.h"
#include "headers/math.h"
#include "headers/parser.h"
#include "headers/quotes.h"
#include "headers/stack.h"
#include "headers/strings.h"
#include "headers/toka.h"
#include "headers/vm.h"

#endif
