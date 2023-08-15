#include "tixt/Editor.hh"

#include "tixt/FileManager.hh"
#include "tixt/tixt.hh"
void tixt::Editor::mainloop() {
  mvprintw(0, 30, "%s", path.c_str());
  if (!has_been_read) {
    buffer = readfile(this->path);
    has_been_read = true;
  }
  move(cursy, cursx);
  u32 bufsize = buffer.size() - 1;
  for (u32 j = idx; j < buffer.size() && j < (u32)getmaxy(stdscr) - 2; j++) {
    mvprintw(j, 4, "%s", buffer.at(j).c_str());
    mvprintw(j, 2, "%d", j + 1);
  }
  move(cursy, cursx);
  while ((input = getch())) {
    acx = cursx - 4;
    switch (input) {
      case ctrl('q'):
        if ((poll = getch()) == ENTERKEY) {
          // FIXME: free resources
          endwin();
          exit(0);
        }
        W_INVALID_CTRL_SEQ(input, poll);
        break;
      case KEY_DOWN:
        [[fallthrough]];
      case ctrl('j'):
        if (cursy < bufsize) {
          cursy++;
          fileidx++;
        }
        break;
      case KEY_UP:
        [[fallthrough]];
      case ctrl('k'):
        if (cursy != 0) cursy--;
        break;
      case ctrl('l'):
        cursx++;
        break;
      [[likely]] case ' ' ... '~':
        mvprintw(cursy, cursx, "%c", input);
        cursx++;
        break;
      case KEY_BACKSPACE:
        if (cursx > 4) {
          cursx--;
          mvprintw(cursy, cursx, " ");
        }
        break;
      default:
        W_MESSAGE("Invalid Sequence");
        break;
    }
    // FIXME
    try {
      mvprintw(0, 30, "%c", buffer.at(fileidx).at(acx));
    } catch (...) {
      mvprintw(0, 30, "Fucked up index");
    }
    move(cursy, cursx);
  }
}
