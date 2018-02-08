#include "database.h"
#include "notes.h"
#include "stdio.h"

int main(int argc, char **argv) {
  notesDB db = {.errFunc = "", .errMsg = ""};

  if (!initDB(&db)) {
    printLastDBError(&db);
  } else {
    gtkNote g;
    note n;
    n.text = "asd asd";
    n.length = 7;
    g.note = &n;
    g.x = 0;
    g.y = 0;
    g.width = 0;
    g.height = 0;
    gtkNoteArray array = loadNotes(&db);
    addGTKNote(&array, &g);
    printGTKNoteArray(&array);
    freeGTKNoteArray(&array);
    closeDB(&db);
  }

  return 0;
}
