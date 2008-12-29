void file_open();
void file_close();
void file_read();
void file_write();
void file_size();
void file_seek();
void file_pos();


/******************************************************
 * Modes for file_open()
 ******************************************************/
#define R     1
#define RPLUS 2
#define W     3
#define WPLUS 4
#define A     5
#define APLUS 6


/******************************************************
 * Modes for file_seek()
 ******************************************************/
#define START    1
#define CURRENT  2
#define END      3

