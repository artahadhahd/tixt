#include <dirent.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>

#include "tixt/tixt.hh"

using namespace tixt::types;

// TODO: sort directories
// An abstraction for seeing and managing files and directories
auto tixt::FileManager::get_directory_contents() -> DirManager {
  std::vector<tixt::DirectoryContent> directories;
  DIR *d = opendir(this->path.c_str());
  if (!d) return std::nullopt;
  struct dirent *dir;
  directories.push_back(DirectoryContent{
      "..",
      tixt::Directory,
  });
  while ((dir = readdir(d)) != NULL) {
    if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0)
      continue;
    if (dir->d_type == 4) {  // if it's a directory
      directories.push_back(tixt::DirectoryContent{
          dir->d_name,
          tixt::Directory,
      });
    } else if (dir->d_type == 10) {  // If it's a symlink
      directories.push_back(tixt::DirectoryContent{
          dir->d_name,
          tixt::Symlink,
      });
    } else {
      directories.push_back(tixt::DirectoryContent{
          dir->d_name,
          tixt::File,
      });
    }
  }
  closedir(d);
  return directories;
}

auto readfile(std::string path) -> std::vector<std::string> {
  std::vector<std::string> lines;
  std::string tmp;
  std::fstream fs(path);
  if (fs.is_open()) {
    while (fs.peek() != EOF) {
      getline(fs, tmp);
      lines.push_back(tmp);
    }
  }
  fs.close();
  return lines;
}

void tixt::FileManager::print(DirManager dirc) {
  if (this->pidx != this->idx) {
    for (u64 i = this->idx;
         i < dirc->size() && i < (u64)this->maxY - 1 + this->idx; i++) {
      auto file = dirc.value().at(i);
      attron(COLOR_PAIR(file.filetype));
      mvprintw(this->jy, 1, "%s\n", file.name.c_str());
      attroff(COLOR_PAIR(file.filetype));
      this->jy++;
    }
    this->pidx = this->idx;
  }
  this->jy = 0;
}

auto tixt::FileManager::mainloop(DirManager dirc) -> MaybeDirectory {
  const u32 sizec = dirc.value().size() - 1;
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
  if (fileidx > sizec) fileidx = sizec;
  switch ((input = getch())) {
    case ctrl('w'):
      if ((poll = getch()) == ctrl('w')) {
        fileidx -= cursy;
        cursy = 0;
      } else {
        W_INVALID_CTRL_SEQ('w', poll);
      }
      break;
    case ctrl('s'):
      if ((poll = getch()) == ctrl('s')) {
        fileidx += maxY - 2 < sizec ? maxY - 3 - cursy : sizec;
        cursy = std::min(sizec, maxY - 3);
      } else if (poll == ENTERKEY) {  // if user tries to save it
        W_MESSAGE("Operation not possible");
      } else {
        W_INVALID_CTRL_SEQ(input, poll);
      }
      break;
    case ctrl('q'):
      if ((poll = getch()) == ENTERKEY) {
        endwin();
        exit(0);
      } else {
        W_INVALID_CTRL_SEQ('q', poll);
      }
      break;
    case KEY_ESC:
      W_CLEARWARNINGS();
      break;
    [[likely]] case ctrl('j') :
      [[fallthrough]];
    case KEY_DOWN:
      if (fileidx < sizec) cursy++;
      if (fileidx < sizec) fileidx++;
      if (cursy >= maxY - 2 && fileidx < sizec) {
        idx++;
        cursy = maxY - 3;
      }
      break;
    [[likely]] case ctrl('k') :
      [[fallthrough]];
    case KEY_UP:
      if (cursy != 0) {
        fileidx--;
        cursy--;
      }
      if (cursy == 0 && idx > 0) {
        idx--;
        fileidx--;
      }
      break;
    case ' ' ... '~':
      W_MESSAGE("Cannot modify text here");
      break;
    case ENTERKEY:
      if (dirc.value().at(fileidx).filetype == tixt::File) {
        Editor ed(dirc.value().at(fileidx).name);
        erase();
        ed.mainloop();
      }
      return DirectoryContent{dirc.value().at(fileidx).name,
                              dirc.value().at(fileidx).filetype};
    default:
      W_MESSAGE("Invalid Sequence");
      break;
  }
  return std::nullopt;
}
