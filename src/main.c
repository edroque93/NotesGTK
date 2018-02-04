#include "database.h"
#include "stdio.h"

int main(int argc, char **argv) {
  notesDB db;

  if (!initDB(&db)) {
    printLastDBError(&db);
  } else {
    closeDB(&db);
  }

  return 0;
}
