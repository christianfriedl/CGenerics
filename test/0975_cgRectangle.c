#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>
#include"cgAppState.h"
#include"cgRectangle.h"

void testNewDelete() {
    printf("%s... ", __func__);
    cgRectangle* r = cgRectangle__new(0, 0, 10, 10);
    cgRectangle_delete(r);
    printf("ok -- ");
}

void testIntersect() {
    printf("%s... ", __func__);
    cgRectangle* r1 = cgRectangle__new(10, 10, 10, 10);
    cgRectangle* r2 = cgRectangle__new(10, 10, 1, 1);
    cgRectangle* rI = cgRectangle_intersect(r1, r2);
    assert(rI->x == 10);
    assert(rI->y == 10);
    assert(rI->width == 1);
    assert(rI->height == 1);
    cgRectangle_delete(rI);
    cgRectangle_delete(r2);

    r2 = cgRectangle__new(11, 11, 10, 10);
    rI = cgRectangle_intersect(r1, r2);
    assert(rI->x == 11);
    assert(rI->y == 11);
    assert(rI->width == 9);
    assert(rI->height == 9);
    cgRectangle_delete(rI);
    cgRectangle_delete(r2);

    r2 = cgRectangle__new(19, 19, 10, 10);
    rI = cgRectangle_intersect(r1, r2);
    assert(rI->x == 19);
    assert(rI->y == 19);
    assert(rI->width == 1);
    assert(rI->height == 1);
    cgRectangle_delete(rI);
    cgRectangle_delete(r2);

    r2 = cgRectangle__new(8, 12, 10, 10);
    rI = cgRectangle_intersect(r1, r2);
    assert(rI->x == 10);
    assert(rI->y == 12);
    assert(rI->width == 8);
    assert(rI->height == 8);
    cgRectangle_delete(rI);
    cgRectangle_delete(r2);
    
    /* NULL outcomes */
    r2 = cgRectangle__new(10, 10, 0, 0);
    rI = cgRectangle_intersect(r1, r2);
    assert(rI == NULL);
    cgRectangle_delete(r2);

    r2 = cgRectangle__new(20, 20, 10, 10);
    rI = cgRectangle_intersect(r1, r2);
    assert(rI == NULL);
    cgRectangle_delete(r2);

    r2 = cgRectangle__new(20, 10, 10, 10);
    rI = cgRectangle_intersect(r1, r2);
    assert(rI == NULL);
    cgRectangle_delete(r2);

    r2 = cgRectangle__new(0, 10, 10, 10);
    rI = cgRectangle_intersect(r1, r2);
    assert(rI == NULL);
    cgRectangle_delete(r2);

    cgRectangle_delete(r1);

    printf("ok -- ");
}

void testDoesOverlap() {
    printf("%s... ", __func__);
    cgRectangle* r1 = cgRectangle__new(10, 10, 10, 10);
    cgRectangle* r2 = cgRectangle__new(10, 10, 1, 1);
    /* true, is inside */
    assert(cgRectangle_doesOverlap(r1, r2) == true);
    assert(cgRectangle_doesOverlap(r2, r1) == true);
    cgRectangle_delete(r2);
    /* true, from left */
    r2 = cgRectangle__new(9, 10, 2, 1);
    assert(cgRectangle_doesOverlap(r1, r2) == true);
    assert(cgRectangle_doesOverlap(r2, r1) == true);
    cgRectangle_delete(r2);
    /* true, from above */
    r2 = cgRectangle__new(10, 9, 1, 2);
    assert(cgRectangle_doesOverlap(r1, r2) == true);
    assert(cgRectangle_doesOverlap(r2, r1) == true);
    cgRectangle_delete(r2);
    /* true, rightmost bottom point */
    r2 = cgRectangle__new(19, 19, 1, 1);
    assert(cgRectangle_doesOverlap(r1, r2) == true);
    assert(cgRectangle_doesOverlap(r2, r1) == true);
    cgRectangle_delete(r2);
    /* true, from left above */
    r2 = cgRectangle__new(9, 9, 2, 2);
    assert(cgRectangle_doesOverlap(r1, r2) == true);
    assert(cgRectangle_doesOverlap(r2, r1) == true);
    cgRectangle_delete(r2);

    /* false, area is 0 */
    r2 = cgRectangle__new(10, 10, 0, 0);
    assert(cgRectangle_doesOverlap(r1, r2) == false);
    assert(cgRectangle_doesOverlap(r2, r1) == false);
    cgRectangle_delete(r2);
    /* false, left-above */
    r2 = cgRectangle__new(9, 9, 1, 1);
    assert(cgRectangle_doesOverlap(r1, r2) == false);
    assert(cgRectangle_doesOverlap(r2, r1) == false);
    cgRectangle_delete(r2);
    /* false, right-below */
    r2 = cgRectangle__new(20, 20, 1, 1);
    assert(cgRectangle_doesOverlap(r1, r2) == false);
    assert(cgRectangle_doesOverlap(r2, r1) == false);
    cgRectangle_delete(r2);


    cgRectangle_delete(r1);

    printf("ok -- ");
}

int main() {
    printf("=== %s ===\n", __FILE__);
    cgAppState__init(__FILE__);

    testNewDelete();
    testIntersect();
    testDoesOverlap();

    printf("=== %s ok ===\n", __FILE__);
    return 0;
}
