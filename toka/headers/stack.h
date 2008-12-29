#define TOS data.stack[data.sp]
#define NOS data.stack[data.sp-1]
#define TOAS alternate.stack[alternate.sp]
#define NOAS alternate.stack[alternate.sp-1]
#define TORS address.stack[address.sp]
#define NORS address.stack[address.sp-1]
#define DROP data.sp--

void stack_dup();
void stack_drop();
void stack_swap();

void stack_to_r();
void stack_from_r();

void stack_depth();
