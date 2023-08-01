#pragma once
#include <ncurses.h>

#include <optional>
#include <string>
#include <vector>

#include "Types.hh"
#include "Utils.hh"

#define KEY_ESC   27
#define ENTERKEY  13
#define ctrl(key) ((key)&31)

using namespace tixt::types;

namespace tixt {
enum FileType {
  Symlink = 2,
  Directory = 3,
  File = 4,
};

struct DirectoryContent {
  std::string name;
  FileType filetype;
};

typedef std::optional<std::vector<DirectoryContent>> DirManager;
typedef std::optional<DirectoryContent> MaybeDirectory;

class FileManager {
 public:
  FileManager(std::string const path) { this->path = path; }

  // Returns std::nullopt if the input is a file instead of a directory
  std::optional<std::vector<DirectoryContent>> get_directory_contents();
  std::string path = ".";
  void print(DirManager);
  // Returns std::nullopt if the user has chosen nothing.
  MaybeDirectory mainloop(DirManager);
  bool running = true;
  u32 cursy = 0;
  u32 cursx = 0;
  i32 input;

 private:
  // the cursor's y and x position, respectively.
  u32 jy = 0;   // a counter.
  u32 idx = 0;  // "render" index
  // pidx stores the previous value of idx. once pidx is updated, the screen
  // will be "re-rendered". It stands for "previous index"
  u32 pidx = 2;
  // the main cause of all bugs: file index.
  // it has to be updated with each movement key
  // it can cause segfaults if you do something wacky
  // it refers to DirManager.value().at(fileidx)
  u32 fileidx = 0;
  // Terminal's height
  u32 maxY = getmaxy(stdscr);
  u32 poll;
};

}  // namespace tixt
std::vector<std::string> readfile(std::string);
