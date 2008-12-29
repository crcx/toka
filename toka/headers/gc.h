typedef struct {
  Inst xt;
  long size;
} GCITEM;

void gc();
void gc_keep();
void *gc_alloc(long items, long size, long type);
void toka_malloc();

#define GC_KEEP 2
#define GC_TEMP 1
#define GC_MEM  0

