#include <curses.h>
#include <ncurses.h>

#include <iostream>
#include <optional>

#include "tixt/Editor.hh"
#include "tixt/FileManager.hh"
#include "tixt/tixt.hh"

#define FOREGROUND COLOR_WHITE
#define BACKGROUND COLOR_BLACK

using namespace tixt::types;

void tixt_mainloop(std::string &);

i32 main(i32 argc, char *argv[]) {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  nonl();
  set_escdelay(10);

  INIT_COLORS();

  // FILE MANAGER
  tixt::FileManager filemanager(argc == 1 ? "." : argv[1]);
  tixt::DirManager dirc = filemanager.get_directory_contents();
  // This occurs when the user wants to open a file.
  if (!dirc.has_value()) {
    tixt::Editor editor(argv[1]);
  }
  std::string inp = argc == 1 ? "." : argv[1];
  tixt_mainloop(inp);
  endwin();
}

void tixt_mainloop(std::string &a) {
  using namespace tixt;
  FileManager filemgr(a);
  auto dirc = filemgr.get_directory_contents();
  if (!dirc.has_value()) {
    tixt::Editor ed(a);
    ed.mainloop();
    return;
  }
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
      a += "/" + userinput.value().name;
      tixt_mainloop(a);
    } else if (filetype == tixt::Symlink) {
      endwin();
      std::cerr << "Symlinks cannot be opened in current version\n";
    }
  }
}
