#ifndef NOTES_H
#define NOTES_H

#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct note {
  uint32_t length;
  char *text;
} note;

typedef struct gtkNote {
  uint32_t wHandle;
  int64_t id;
  note *note;
  uint32_t width, height;
  uint32_t x, y;
  bool valid;
} gtkNote;

typedef struct gtkNoteArray {
  uint32_t length;
  gtkNote **array;
} gtkNoteArray;

void freeGTKNoteArray(gtkNoteArray *f);
void freeGTKNote(gtkNote *f);
void freeNote(note *f);

void printGTKNoteArray(gtkNoteArray *f);
void printGTKNote(gtkNote *f);
void printNote(note *f);

void addGTKNote(gtkNoteArray *notes, gtkNote *note);

#endif
