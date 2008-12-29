void add_entry(char *name, void *xt, void *class, long primitive);
void name_quote();
void name_super();
void name_macro();
void name_data();
void find_word();
void return_quote();
void return_name();
void return_xt();
void return_class();

typedef struct {
  Inst xt;
  Inst class;
  char name[128];
} ENTRY;

