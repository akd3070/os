#include <dirent.h>
#include <stdio.h>

int main() {
  DIR *dir;
  struct dirent *entry;

  // Specifing the directory path (".") to list the current directory
  const char *path = ".";

  dir = opendir(path);
  if (dir == NULL) {
    perror("Unable to open directory");
    return 1;
  }

  printf("Contents of directory: %s\n", path);

  while ((entry = readdir(dir)) != NULL) {
    printf("%s\n", entry->d_name);
  }

  closedir(dir);

  return 0;
}
