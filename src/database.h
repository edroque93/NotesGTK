#ifndef DATABASE_H
#define DATABASE_H

#include "notes.h"
#include "sqlite3.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DB_FILENAME ".notesgtk.sqlite3"

#define DB_NOTES_TABLE_CREATE                                                  \
  "CREATE TABLE IF NOT EXISTS notes ("                                         \
  "id integer PRIMARY KEY,"                                                    \
  "note text NOT NULL,"                                                        \
  "x integer,"                                                                 \
  "y integer,"                                                                 \
  "w integer,"                                                                 \
  "h integer"                                                                  \
  ");"
#define DB_NOTES_TABLE_DROP "DROP TABLE IF EXISTS notes;"
#define DB_NOTES_TABLE_SELECT "SELECT * FROM notes;"
#define DB_NOTES_TABLE_INSERT                                                  \
  "INSERT INTO notes "                                                         \
  "VALUES (%d, %s, %d, %d, %d, %d);"

#define ERROR_ENV_HOME "Cannot find home path"

typedef struct notesDB {
  char *path;
  sqlite3 *handle;
  int32_t lastRC;
  const char *errFunc;
  const char *errMsg;
} notesDB;

bool initDB(notesDB *db);
bool closeDB(notesDB *db);
gtkNote *loadNotes(notesDB *db);
void printLastDBError(notesDB *db);

#endif
