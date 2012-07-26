#ifndef _CGENERICS_H
#define _CGENERICS_H

#ifndef min
    #define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#ifndef max
    #define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif


#define bool int
#define true (-1)
#define false (0)
#define toBool(i) ((i) ? true : false)

#endif
