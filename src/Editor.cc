#include "tixt/Editor.hh"

#include "tixt/FileManager.hh"
#include "tixt/tixt.hh"
void tixt::Editor::mainloop() {
  mvprintw(0, 30, "%s", path.c_str());
  if (!has_been_read) {
    buffer = readfile(this->path);
    has_been_read = true;
  }
  // for (auto const a : buffer) {
  // mvprintw(jy++, 3, "%s", a.c_str());
  // }
  // print buffer
  for (u32 j = idx; j < buffer.size() && j < getmaxy(stdscr) - 2; j++) {
    mvprintw(j, 4, "%s", buffer.at(j).c_str());
    mvprintw(j, 2, "%d", j + 1);
  }
  move(cursy, cursx);
  while ((input = getch())) {
    switch (input) {
      case ctrl('q'):
        if ((poll = getch()) == ENTERKEY) {
          // FIXME: free resources
          endwin();
          exit(0);
        }
        W_INVALID_CTRL_SEQ(input, poll);
        break;
      default:
        W_MESSAGE("Invalid");
        move(cursy, cursx);
        break;
    }
  }
}
