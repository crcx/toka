void vm_init();
void vm_run(Inst prog[]);
void vm_stack_check();
void vm_lit();
void vm_quote_lit();
void vm_string_lit();
void vm_push(long a);
void vm_primitive();
void vm_comma();

typedef struct {
  long sp;
  long *stack;
} VM_STACK;
