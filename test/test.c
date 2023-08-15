#include <ncurses.h>

int main(void) {
  initscr();
  noecho();
  mvprintw(0, 20, "%d", getch());
  getch();
  endwin();
  return 0;
}