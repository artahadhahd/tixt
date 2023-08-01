#include <ncurses.h>

#include <iostream>

#include "tixt/FileManager.hh"
#include "tixt/Types.hh"
#include "tixt/Utils.hh"

#define FOREGROUND COLOR_WHITE
#define BACKGROUND COLOR_BLACK

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
  u32 const sizec = dirc.value().size();
  mvprintw(_WARNY, 2, "%d files found in directory '%s'", sizec,
           filemanager.path.c_str());
  while (filemanager.running) {
    filemanager.print(dirc);
    move(filemanager.cursy, filemanager.cursx);
    filemanager.mainloop(dirc);
  }
  endwin();
}
