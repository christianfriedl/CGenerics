#include<stdlib.h>
#include"cgException.h"
#include"cgAppState.h"
#include"cgRectangle.h"

cgRectangle *cgRectangle__new(int x, int y, int width, int height) {
    if (width < 0 || height < 0)
        cgAppState_THROW(cgAppState__getInstance(), Severity_fatal, cgExceptionID_CannotAllocate,
                         "either width or height are negative (%i %i %i %i), stop pulling my leg.", x, y, width, height);

    cgRectangle *this = malloc(sizeof(*this));

    if (this != NULL) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    } else
        cgAppState_THROW(cgAppState__getInstance(), Severity_fatal, cgExceptionID_CannotAllocate,
                         "cannot allocate cgRectangle (%i %i %i %i)", x, y, width, height);
    return this;
}

void cgRectangle_delete(cgRectangle * this) {
    free(this);
}

int cgRectangle_calculateArea(cgRectangle * this) {
    return this->width * this->height;
}

cgRectangle *cgRectangle_intersect(cgRectangle * this, cgRectangle * that) {
    int x = (this->x > that->x ? this->x : that->x);

    int y = (this->y > that->y ? this->y : that->y);

    int thisMaxX = this->x + this->width;

    int thatMaxX = that->x + that->width;

    int thisMaxY = this->y + this->height;

    int thatMaxY = that->y + that->height;

    int width = (thisMaxX < thatMaxX ? thisMaxX - x : thatMaxX - x);

    int height = (thisMaxY < thatMaxY ? thisMaxY - y : thatMaxY - y);

    if (width <= 0 || height <= 0)
        return NULL;
    else
        return cgRectangle__new(x, y, width, height);
}

/* determine whether this rectangle overlaps with another; true if
 * either the starting coordinates, or the end coordinates are within
 * this rectangle's area; if either rectangle has 0 area, the result is
 * false
 */
bool cgRectangle_doesOverlap(cgRectangle * this, cgRectangle * that) {
    if (cgRectangle_calculateArea(this) == 0 || cgRectangle_calculateArea(that) == 0)
        return false;

    cgRectangle* r = cgRectangle_intersect(this, that);
    bool rv = (r != NULL ? true : false);
    cgRectangle_delete(r);
    return rv;
}
