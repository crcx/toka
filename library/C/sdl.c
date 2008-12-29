/***************************************************************
 * Simple Directmedia Layer (SDL) Abstraction Layer
 *
 * This is part of a hybrid library module for Toka. It helps
 * abstract the underlying SDL implementation making basic SDL
 * programming easier.
 ***************************************************************
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
 ***************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>


SDL_Surface *screen;
long width, height;


void sdl_setup(long req_width, long req_height)
{
   if (req_width == 0 || req_height == 0)
   {
      SDL_Init(0);
      return;
   }

   height = req_height;
   width  = req_width;
   SDL_Init(SDL_INIT_VIDEO);
   screen = SDL_SetVideoMode((int)width, (int)height, 32, SDL_SWSURFACE);
}


void sdl_render()
{
  SDL_UpdateRect(screen, 0, 0, width, height);
}


long sdl_event_type(SDL_Event *event)
{
  return (long)event->type;
}


long sdl_surface_size()
{
  return (long)sizeof(SDL_Surface);
}


long sdl_event_size()
{
  return (long)sizeof(SDL_Event);
}


void sdl_putpixel(long x, long y, long color)
{
  unsigned int *ptr = (unsigned int*)screen->pixels;
  int lineoffset = (int)y * (screen->pitch / 4);
  ptr[lineoffset + x] = (int)color;
}


void sdl_circle(long x, long y, long radius, long color)
{
  long x_position, y_position, d, delta_e, delta_se;

  x_position = -1;
  y_position = radius;
  d = 1 - radius;
  delta_e = -1;
  delta_se = (-radius << 1) + 3;

  while (y_position > x_position)
  {
    delta_e += 2;
    x_position++;

    if (d < 0)
    {
      d += delta_e;
      delta_se += 2;
    }
    else
    {
      d += delta_se;
      delta_se += 4;
      y_position--;
    }

    sdl_putpixel(x + x_position, y + y_position, color);
    sdl_putpixel(x + y_position, y + x_position, color);
    sdl_putpixel(x + y_position, y - x_position, color);
    sdl_putpixel(x + x_position, y - y_position, color);

    sdl_putpixel(x - x_position, y - y_position, color);
    sdl_putpixel(x - y_position, y - x_position, color);
    sdl_putpixel(x - y_position, y + x_position, color);
    sdl_putpixel(x - x_position, y + y_position, color);
  }
  sdl_render();
}


void sdl_hline(long x1, long y, long x2, long color)
{
  long x;
  for (x = x1; x <= x2; x++)
    sdl_putpixel(x, y, color);
  sdl_render();
}


void sdl_vline(long x, long y1, long y2, long color)
{
  long y;
  for (y = y1; y <= y2; y++)
    sdl_putpixel(x, y, color);
  sdl_render();
}


void sdl_line(long x1, long y1, long x2, long y2, long color)
{
  long dx, dy, inx, iny, e;

  dx = x2 - x1;
  dy = y2 - y1;
  inx = dx > 0 ? 1 : -1;
  iny = dy > 0 ? 1 : -1;

  dx = abs(dx);
  dy = abs(dy);
       
  if (dx >= dy)
  {
    dy <<= 1;
    e = dy - dx;
    dx <<= 1;
    while (x1 != x2)
    {
      sdl_putpixel(x1, y1, color);
      if (e >= 0)
      {
        y1 += iny;
        e-= dx;
      }
      e += dy; x1 += inx;
    }
  } 
  else
  {
    dx <<= 1;
    e = dx - dy;
    dy <<= 1;
    while (y1 != y2)
    {
      sdl_putpixel(x1, y1, color);
      if (e >= 0)
      {
        x1 += inx;
        e -= dy;
      }
      e += dx; y1 += iny;
    }
  }
  sdl_putpixel(x1, y1, color);
}


void sdl_box(long x1, long y1, long x2, long y2, long color)
{
  sdl_hline(x1, y1, x2, color);
  sdl_hline(x1, y2, x2, color);
  sdl_vline(x1, y1, y2, color);
  sdl_vline(x2, y1, y2, color);
}


long sdl_event_mousecoord_x(SDL_Event *event)
{
  return (long)event->motion.x;
}


long sdl_event_mousecoord_y(SDL_Event *event)
{
  return (long)event->motion.y;
}


long sdl_event_keysym(SDL_Event *event)
{
  return (long)event->key.keysym.sym;
}


void sdl_angle_line(long x, long y, long angle, long dist, long color)
{
  double x2, y2;
  long xa, ya, signa, signb;

  x2 = dist * cos(angle);
  y2 = dist * sin(angle);

  signa = 1;
  signb = 1;

  if (x2 < 0)
    signa = -1;
  if (y2 < 0)
    signb = -1;

  x2 = abs(x2);
  y2 = abs(y2);

  xa = (long)x2;
  ya = (long)y2;

  xa = xa * signa;
  ya = ya * signb;

  sdl_line(x, y, xa + x, ya + y, color);
  sdl_render();
}
