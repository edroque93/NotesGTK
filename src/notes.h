#include "stdint.h"

typedef struct note {
  uint32_t length;
  char *text;
} note;

typedef struct gtkNote {
  uint32_t wHandle;
  note *note;
  uint32_t width, height;
  uint32_t x, y;
} gtkNote;
