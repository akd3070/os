#include <stdio.h>
#include <string.h>

#define MAX 100
//@read_write_details: read and write details to a file
//@cmp_print : compare the files and print the matches

void read_write_details(const char *filename) {
  FILE *file = fopen(filename, "w");
  if (file == NULL) {
    perror("Error opening file");
    return;
  }

  char name[MAX], email[MAX];
  int age;

  printf("Enter name: ");
  fgets(name, MAX, stdin);
  name[strcspn(name, "\n")] = 0;

  printf("Enter email: ");
  fgets(email, MAX, stdin);
  email[strcspn(email, "\n")] = 0;

  printf("Enter age: ");
  scanf("%d", &age);
  getchar();

  fprintf(file, "Name: %s\nEmail: %s\nAge: %d\n", name, email, age);
  fclose(file);
}

void cmp_print(const char *file1, const char *file2) {
  FILE *f1 = fopen(file1, "r");
  FILE *f2 = fopen(file2, "r");

  if (f1 == NULL || f2 == NULL) {
    perror("Error opening one of the files");
    return;
  }

  char line1[MAX], line2[MAX];

  printf("\nMatching lines in both files:\n");
  while (fgets(line1, MAX, f1) != NULL && fgets(line2, MAX, f2) != NULL) {
    if (strcmp(line1, line2) == 0) {
      printf("%s", line1);
    }
  }

  fclose(f1);
  fclose(f2);
}

int main() {
  const char *myDetailsFile = "my_details.txt";
  const char *friendDetailsFile = "friend_details.txt";

  printf("Enter your details:\n");
  read_write_details(myDetailsFile);

  printf("\nEnter your friend's details:\n");
  read_write_details(friendDetailsFile);

  cmp_print(myDetailsFile, friendDetailsFile);

  return 0;
}
