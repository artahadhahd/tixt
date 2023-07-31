#include "FileManager.hh"

#include <dirent.h>

#include <cstring>
#include <iostream>

// An abstraction for seeing and managing files and directories
std::optional<std::vector<tixt::DirectoryContent>>
tixt::FileManager::get_directory_contents() {
  std::vector<tixt::DirectoryContent> directories;
  DIR *d = opendir(this->path.c_str());
  if (!d) return std::nullopt;
  struct dirent *dir;
  while ((dir = readdir(d)) != NULL) {
    if (strcmp(dir->d_name, ".") == 0) continue;
    if (dir->d_type == 4) {  // if it's a directory
      directories.push_back((tixt::DirectoryContent){
          dir->d_name,
          tixt::Directory,
      });
    } else if (dir->d_type == 10) {  // If it's a symlink
      directories.push_back((tixt::DirectoryContent){
          dir->d_name,
          tixt::Symlink,
      });
    } else {
      directories.push_back((tixt::DirectoryContent){
          dir->d_name,
          tixt::File,
      });
    }
  }
  closedir(d);
  return directories;
}
