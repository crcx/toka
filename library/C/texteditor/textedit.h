char *draw_modes();
void *get_buffer();
void spaces(long n);
void cursor();
void status();
char *drawline(char *p, long draw);
void draw(long flag);
char *curpos();
char *eol(char *p);
void scrollup(long n);
void msg(char *s);
void clearmsg();
void promptmsg(char *s);
long ync(char *s);
void prompt(char *msg, char *buf); 
void dirty();
void load(char *file);
void save(char *filename);
void Lnup();
void Lndn();
void Pgup();
void Pgdn();
void Top();
void Bottom();
void Home();
void End();
void Up();
void Down();
void Right();
void Left();
void Wordright();
void Wordleft();
void Del();
void Back();
void Insert(long c);
void edit();
void getscreensize();
void quit();
