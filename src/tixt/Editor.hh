#pragma once
#include "Types.hh"
#define TIXT_EDITOR
#include <string>

#include "tixt.hh"
using namespace tixt::types;

namespace tixt {
class Editor {
 public:
  Editor(std::string const path) { this->path = path; }
  void mainloop();

 private:
  std::vector<std::string> buffer;
  bool has_been_read = false;
  i32 input, poll;
  u32 jy = 0;
  std::string path;
  u32 fileidx;
  u32 idx = 0;
  u32 cursy = 0;
  u32 cursx = 4;
  u32 acx = 0;
};
}  // namespace tixt
