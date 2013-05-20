/* 
 * File:   cgEvent.h
 * Author: xian
 *
 * An event is something that binds a source, an identifier, and a target together
 * Created on 15. Mai 2013, 19:21
 */

#ifndef CGEVENT_H
#define	CGEVENT_H

#ifdef	__cplusplus
extern "C" {
#endif

#include"cgenerics.h"
#include"cgInteger.h"

typedef struct {
    void *source;
    cgInteger *ident;
    void *target;
    bool (*func)(void *this, void *source, void *context);
} cgEvent;


#ifdef	__cplusplus
}
#endif

#endif	/* CGEVENT_H */

