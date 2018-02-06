#include "database.h"
#include "notes.h"
#include "stdio.h"

int main(int argc, char **argv) {
  notesDB db = {.errFunc = "", .errMsg = ""};

  if (!initDB(&db)) {
    printLastDBError(&db);
  } else {
    gtkNoteArray array = loadNotes(&db);
    printGTKNoteArray(&array);
    freeGTKNoteArray(&array);
    closeDB(&db);
  }

  return 0;
}
