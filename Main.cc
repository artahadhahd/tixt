#include <curses.h>
#include <ncurses.h>

#include <iostream>

#include "FileManager.hh"
#include "Types.hh"
#include "Utils.hh"

#define KEY_ESC   27
#define ENTERKEY  13
#define ctrl(key) ((key)&31)

#define BACKGROUND COLOR_BLACK
#define FOREGROUND COLOR_WHITE

using namespace tixt::types;

i32 main(i32 argc, char *argv[]) {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  nonl();
  set_escdelay(10);

  start_color();
  init_pair(1, COLOR_YELLOW, COLOR_BLACK);  // Warnings
  init_pair(2, COLOR_CYAN, BACKGROUND);     // Symlinks
  init_pair(3, COLOR_BLUE, BACKGROUND);     // Directories
  init_pair(4, FOREGROUND, BACKGROUND);     // main color
  init_pair(5, BACKGROUND, FOREGROUND);     // main color inversed

  // FILE MANAGER
  // I recommend checking out FileManager.hh
  u32 cursy = 0;
  u32 cursx = 0;
  tixt::FileManager filemanager(argc == 1 ? "." : argv[1]);
  auto dirc = filemanager.get_directory_contents();
  if (!dirc.has_value()) {
    endwin();
    std::cerr << "NotImplemented!\n";
    return 1;
  }
  u32 jy = 0;
  move(cursy, cursx);
  i32 input, poll;
  u32 idx = 0;
  // this is how many files are in the directory
  u32 const sizec = dirc.value().size() - 1;
  // pidx stores the previous value of idx. once pidx is updated, the screen
  // will be "re-rendered"
  u32 pidx = 2;
  bool running = true;
  u32 maxY = getmaxy(stdscr);
  u32 fileidx = 0;
  while (running) {
    if (pidx != idx) {
      for (u64 i = idx; i < dirc->size() && i < (u64)maxY - 1 + idx; i++) {
        auto file = dirc.value().at(i);
        attron(COLOR_PAIR(file.filetype));
        mvprintw(jy, 1, "%s\n", file.name.c_str());
        attroff(COLOR_PAIR(file.filetype));
        jy++;
      }
      pidx = idx;
    }
    jy = 0;
    move(cursy, cursx);
    switch ((input = getch())) {
      case ctrl('w'):
        if ((poll = getch()) == ctrl('w')) {
          cursy = 0;
        } else {
          W_INVALID_CTRL_SEQ('w', poll);
        }
        break;
      case ctrl('s'):
        if ((poll = getch()) == ctrl('s')) {
          if (sizec < maxY - 2)
            cursy = sizec;
          else
            cursy = maxY - 2;
        } else if (poll == ENTERKEY) {
          W_MESSAGE("Operation not possible");
        } else {
          W_INVALID_CTRL_SEQ('s', poll);
        }
        break;
      case ctrl('q'):
        if ((poll = getch()) == ENTERKEY)
          running = false;
        else
          W_INVALID_CTRL_SEQ('q', poll);
        break;
      case KEY_ESC:
        W_CLEARWARNINGS();
        break;
      [[likely]] case ctrl('j') :
        [[fallthrough]];
      case KEY_DOWN:
        fileidx++;
        if (cursy < dirc->size() - 1) cursy++;
        if (cursy > maxY - 2) {
          if (fileidx <= sizec) idx++;
          cursy = getmaxy(stdscr) - 2;
        }
        break;
      [[likely]] case ctrl('k') :
        [[fallthrough]];
      case KEY_UP:
        fileidx--;
        if (cursy != 0) cursy--;
        if (cursy == 0 && idx != 0) idx--;
        break;
      case '0' ... '9':
        [[fallthrough]];
      case 'a' ... 'z':
        [[fallthrough]];
      case 'A' ... 'Z':
        [[fallthrough]];
      case '\'':
        [[fallthrough]];
      [[unlikely]] case '"':
        W_MESSAGE("Cannot modify text here");
        break;
      default:
        W_MESSAGE("Invalid Sequence");
        break;
    }
  }
  endwin();
}
