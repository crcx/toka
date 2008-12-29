/* term.h - ncurses replacement :)
   VT100 version for Linux, Xterm, etc.

  REV   DATE    REVISION NOTES
   -  10/16/02  Moved terminal code from te.c
   A   7/24/03  Turned off ^M -> ^J translation (ICRNL+INLCR) so you can
                tell the difference. Now ^J=10, ^M=13, and Return=13;
                Added getkey() w/ translation.

---------------------------------------------------------------------------
                              VT100/ANSI CODES

\e[nA   Cursor movement ("n" is optional) .....   A
                                                D B C
\e[E    Move to start of next line ... same as ^M^J or ^J ...?
\e[r;cH Move to (row, column)
\e7     Save position
\e8     Restore position
\e[nK   Erase line... 0: to right, 1: to left, 2: entire line
\e[nJ   Erase screen... 0: bottom, 1: top, 2: entire screen
\e[nL   Insert line(s) (n is optional)
\e[nM   Delete line(s)
\e[n@   Insert character(s)
\e[nP   Delete character(s)

\e[nm   Attributes.. (can do multiple settings, ie, \e[0;34;41m)
    0=reset  1=bold  4=underline  7=inverse
    Colors: 3x=foreground (bold=bright)  4x=background
              where x = 0 black             gray (when bold)
                        1 red               crimson
                        2 green             lime green
                        3 brown             yellow
                        4 blue              light blue
                        5 purple            pink
                        6 turquoise         cyan
                        7 white             bright white
\eH     Set tab stop (at current column)
\e[g    Clear tab stop (at current column)
\e[3g   Clear all tab stops (including default ones at 8 chars)
------------------------------------------------------------------------ */

#include <termios.h>

struct termios new_termios, old_termios;

void term_init()
{
  tcgetattr(0, &old_termios);
  new_termios = old_termios;
  new_termios.c_iflag &= ~(BRKINT+ISTRIP+IXON+IXOFF +ICRNL+INLCR);
  new_termios.c_iflag |= (IGNBRK+IGNPAR);
  new_termios.c_lflag &= ~(ICANON+ISIG+IEXTEN+ECHO);
  new_termios.c_cc[VMIN] = 1;
  new_termios.c_cc[VTIME] = 0;
  tcsetattr(0, TCSANOW, &new_termios);
}

void term_cleanup()
{
  tcsetattr(0, TCSANOW, &old_termios);
}

void xy(long x, long y) { printf("\e[%lu;%luH", y, x); }
void home() { xy(1,1); }
void cls() { printf("\e[2J"); home(); }
void mode(long n) { printf("\e[%lum", n); }
void color(long n) { printf("\e[0%s;3%lu;4%lum", (n<128) ? "" : ";1", (n>>4)%8, n%8); }


#define ALT(c)  (256+c)   // ex: ALT('a') = 353
#define CTL(c)  (c&31)    // ex: CTL('a') = 1

#define K_BS    127
#define K_F(c)  (127+c)   // F1 thru F12
#define K_UP    140
#define K_DOWN  141
#define K_RIGHT 142
#define K_LEFT  143
#define K_HOME  144
#define K_INS   145
#define K_DEL   146
#define K_END   147
#define K_PGUP  148
#define K_PGDN  149

long getkey()
{
//
// Get a keystroke & translate to 1-byte keycodes:
//  0-31     Control keys (no translation) .................. CTL('a') macro
//  32-127   Regular keys (no translation) .................. 'a' etc.
//  128-159  Function/Keypad keys (arbitrary translation) ... F(x) and K_ macros
//  160-255  Alt-keys (translate Alt-A -> 128+'a') .......... ALT('a') macro
//
  char s[3];
  long i=0;
  long c = (long)getchar();
  if (c!=27)               // Regular key
    return c;
  c = getchar();
  if (c!='[')              // Alt+key
    return ALT(c);
  else {                   // Function keys & Keypad
    c = getchar();
    if (c>='A' && c<='D')                // Arrows
      return K_UP + c - 'A';
    if (c=='[')                          // F1-F5
      return K_F(1) + (long)getchar() - 'A';
    while (c!='~' && i<3) {
      s[i++]= c;
      c = (long)getchar();
    }
    s[i]=0;
    i = atol(s);
    if (i>=1 && i<=6)                    // Home/Ins/Del/End/Pgup/Pgdn
      return K_HOME + i - 1;
    if (i>=17 && i<=21)                  // F6-F10
      return K_F(6) + i - 17;
    if (i>=23 && i<=24)                  // F11-F12
      return K_F(11) + i - 23;
  }
  return 0;
}
