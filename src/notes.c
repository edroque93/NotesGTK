#include "notes.h"

void freeGTKNoteArray(gtkNoteArray *f) {
  uint32_t index = 0;
  for (; index < f->length; ++index) {
    freeGTKNote(f->array[index]);
    free(f->array[index]);
  }
  free(f->array);
}

void freeGTKNote(gtkNote *f) {
  freeNote(f->note);
  free(f->note);
}

void freeNote(note *f) {
  free(f->text);
}

void printGTKNoteArray(gtkNoteArray *f) {
  uint32_t index = 0;
  for (; index < f->length; ++index) {
    printf("[Note %d]\n", index);
    printGTKNote(f->array[index]);
  }
}

void printGTKNote(gtkNote *f) {
  printf("\tNote: ");
  printNote(f->note);
  printf("\tP(x,y): P(%d, %d)\n", f->x, f->y);
  printf("\tS(w,h): S(%d, %d)\n", f->width, f->height);
}

void printNote(note *f) { printf("%s\n", f->text); }
