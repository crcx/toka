/************************************************************
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

#include <sys/types.h>
#include <dirent.h>
#include <regex.h>
#include <stdio.h>


/************************************************************
 *|F| shell_directory_list_by_pattern(char *dir, char *pattern)
 ************************************************************/
void shell_directory_list_by_pattern(char *dir, char *pattern)
{
  struct dirent *entry;
  regex_t reg;
  DIR *d; 

  if (regcomp(&reg, pattern, REG_EXTENDED | REG_NOSUB))
    return;

  if (!(d = opendir(dir)))
    return;

  while ((entry = readdir(d)))
  {
    if (!regexec(&reg, entry->d_name, 0, NULL, 0))
      puts(entry->d_name);
  }
  closedir(d);
}
