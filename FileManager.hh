#pragma once
#include <optional>
#include <string>
#include <vector>

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

class FileManager {
 public:
  FileManager(std::string const path) { this->path = path; }

  // Returns std::nullopt if the input is a file instead of a directory
  std::optional<std::vector<DirectoryContent>> get_directory_contents();
  std::string path = ".";

 private:
};

}  // namespace tixt
std::vector<std::string> readfile(std::string);
