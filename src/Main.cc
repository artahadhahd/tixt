#include <curses.h>
#include <ncurses.h>

#include <iostream>
#include <optional>

#include "tixt/tixt.hh"

#define FOREGROUND COLOR_WHITE
#define BACKGROUND COLOR_BLACK

using namespace tixt::types;

void tixt_mainloop(std::string a) {
  using namespace tixt;
  FileManager filemgr(a);
  auto dirc = filemgr.get_directory_contents();
  while (filemgr.running) {
    u32 const sizec = dirc.value().size();
    mvprintw(_WARNY, 2, "%d files found in directory '%s'", sizec,
             filemgr.path.c_str());
    filemgr.print(dirc);
    move(filemgr.cursy, filemgr.cursx);
    auto userinput = filemgr.mainloop(dirc);
    if (!userinput.has_value()) continue;
    auto filetype = userinput.value().filetype;
    if (filetype == Directory) {
      erase();
      tixt_mainloop(a + "/" + userinput.value().name);
    } else if (filetype == File) {
    } else {
      endwin();
      std::cerr << "Symlinks cannot be opened in current version\n";
    }
  }
}

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
  tixt::FileManager filemanager(argc == 1 ? "." : argv[1]);
  tixt::DirManager dirc = filemanager.get_directory_contents();
  // This occurs when the user wants to open a file. the file editor isnt yet
  // programmed
  if (!dirc.has_value()) {
    endwin();
    std::cerr << "NotImplemented!\n";
    return 1;
  }
  // this is how many files are in the directory
  // u32 const sizec = dirc.value().size();
  // mvprintw(_WARNY, 2, "%d files found in directory '%s'", sizec,
  // filemanager.path.c_str());
  try {
    tixt_mainloop(argc == 1 ? "." : argv[1]);
  } catch (std::bad_optional_access e) {
    erase();
    attron(COLOR_PAIR(5));
    printw("Please run tixt as root");
    attroff(COLOR_PAIR(5));
    getch();
  }
  endwin();
}
