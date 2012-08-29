
#ifndef _NV_RECTANGLE_H
#define _NV_RECTANGLE_H

#include"cgenerics.h"

typedef struct {
    int x, y, width, height;
} cgRectangle;

cgRectangle *cgRectangle__new(int x, int y, int width, int height);

void cgRectangle_delete(cgRectangle * this);

int cgRectangle_calculateArea(cgRectangle * this);

cgRectangle *cgRectangle_intersect(cgRectangle * this, cgRectangle * that);

bool cgRectangle_doesOverlap(cgRectangle * this, cgRectangle * that);
#endif
