#pragma once

#include <ncurses.h>
#define BACKGROUND COLOR_BLACK
#define FOREGROUND COLOR_WHITE

#ifndef TIXT_TYPES
#include "Types.hh"
#endif

#ifndef TIXT_FILEMGR
#include "FileManager.hh"
#endif

#ifndef TIXT_EDITOR
#include "Editor.hh"
#endif

#ifndef TIXT_NCURSES_UTILS
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

#define INIT_COLORS()                      \
  start_color();                           \
  init_pair(1, COLOR_YELLOW, COLOR_BLACK); \
  init_pair(2, COLOR_CYAN, BACKGROUND);    \
  init_pair(3, COLOR_BLUE, BACKGROUND);    \
  init_pair(4, FOREGROUND, BACKGROUND);    \
  init_pair(5, BACKGROUND, FOREGROUND)

#define TIXT_NCURSES_UTILS
#endif
