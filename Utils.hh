#pragma once
#include <ncurses.h>

#define _WARNY getmaxy(stdscr) - 1

#define W_CLEARWARNINGS()                   \
  for (int i = 0; i < getmaxx(stdscr); i++) \
  mvprintw(getmaxy(stdscr) - 1, i, " ")

#define W_INVALID_CTRL_SEQ(prefix, bad_char)                        \
  W_CLEARWARNINGS();                                                \
  attron(COLOR_PAIR(1));                                            \
  mvprintw(_WARNY, 2, "Invalid command '$%c%c'", prefix, bad_char); \
  attroff(COLOR_PAIR(1))

#define W_MESSAGE(message)      \
  W_CLEARWARNINGS();            \
  attron(COLOR_PAIR(1));        \
  mvprintw(_WARNY, 2, message); \
  attroff(COLOR_PAIR(1))
