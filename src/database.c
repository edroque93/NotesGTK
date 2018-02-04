#include "database.h"

static bool createStructure(notesDB *db);
static void replaceErrMsg(notesDB *db, char *newMsg, bool toBeFreed);
static int loadNotesCallback(void *param, int argc, char **data, char **col);

bool initDB(notesDB *db) {
  if (!db)
    return false;

  char *home = getenv("HOME");
  if (!home) {
    db->errFunc = __func__;
    replaceErrMsg(db, ERROR_ENV_HOME, false);
    return false;
  }
  db->path = (char *)malloc((strlen(home) + 1 + strlen(DB_FILENAME) + 1) *
                            sizeof(char));
  strcpy(db->path, home);
  strcat(db->path, "/");
  strcat(db->path, DB_FILENAME);

  if ((db->lastRC = sqlite3_open(db->path, &db->handle))) {
    db->errFunc = __func__;
    replaceErrMsg(db, (char *)sqlite3_errmsg(db->handle), false);
    return closeDB(db);
  }

  return createStructure(db);
}

bool closeDB(notesDB *db) {
  if (!db)
    return false;

  if (db->errMsg)
    replaceErrMsg(db, "", false);
  if (db->path)
    free(db->path);
  sqlite3_close(db->handle);

  return true;
}

void printLastDBError(notesDB *db) {
  fprintf(stderr, "Error found, debug information:\n"
                  "\t__func__: %s\n"
                  "\terrMsg: %s\n"
                  "\tlastRC: %d\n",
          db->errFunc, db->errMsg, db->lastRC);
}

gtkNoteArray loadNotes(notesDB *db) {
  gtkNoteArray notes = {.length = 0, .array = NULL};

  if (!db)
    return notes;

  char *err = NULL;

  sqlite3_exec(db->handle, DB_NOTES_TABLE_SELECT, loadNotesCallback, &notes,
               &err);
  return notes;
}

static int loadNotesCallback(void *param, int argc, char **data, char **col) {
  gtkNoteArray *notes = (gtkNoteArray *)param;

  note *nNote = (note *)malloc(sizeof(note));
  gtkNote *gNote = (gtkNote *)malloc(sizeof(gtkNote));

  notes->array[notes->length++] = gNote;
  notes->array[notes->length] = NULL;

  size_t length = strlen(data[1]);
  nNote->text = (char *)malloc((length + 1) * sizeof(char));
  nNote->length = length;
  strcpy(nNote->text, data[1]);

  gNote->note = nNote;
  gNote->x = atoi(data[2]);
  gNote->y = atoi(data[3]);
  gNote->width = atoi(data[4]);
  gNote->height = atoi(data[5]);

  return 0;
}

static bool createStructure(notesDB *db) {
  char *err = NULL;
  if ((db->lastRC =
           sqlite3_exec(db->handle, DB_NOTES_TABLE_CREATE, NULL, NULL, &err))) {
    db->errFunc = __func__;
    replaceErrMsg(db, err, true);
    return false;
  }
  return true;
}

static void replaceErrMsg(notesDB *db, char *newMsg, bool toBeFreed) {
  static bool replace = false;
  if (replace) {
    if (db->errMsg)
      sqlite3_free((char *)db->errMsg);
    replace = false;
  }
  db->errMsg = newMsg;
  replace = toBeFreed;
}
