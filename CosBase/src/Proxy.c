/*
 o---------------------------------------------------------------------o
 |
 | COS Proxy (root class)
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C Object System framework.
 |
 | The C Object System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C Object System is distributed in the hope that it will be
 | useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: Proxy.c,v 1.2 2008/06/27 16:53:06 ldeniau Exp $
 |
*/

#include <cos/Object.h>
#include <cos/Proxy.h>
#include <cos/gen/object.h>
#include <cos/gen/message.h>

#include <stdlib.h>

// -----

makclass(Proxy,Any);

// ----- new

defmethod(OBJ, gnewWith, mProxy, Any)
  retmethod( ginitWith(galloc(_1),_2) );
endmethod

// ----- constructor, destructor

defmethod(OBJ, ginitWith, Proxy, Any)
  self->obj = gretain(_2);
  retmethod(_1);
endmethod

defmethod(OBJ, gdeinit, Proxy)
  grelease(self->obj);
  retmethod(_1);
endmethod

// ----- allocator, deallocator

defmethod(OBJ, galloc, mProxy)
  useclass(ExBadAlloc);

  struct Class *cls = STATIC_CAST(struct Class*, _1);
  struct Proxy *pxy = malloc(cls->isz);

  if (!pxy) THROW(ExBadAlloc);

  pxy->Any.id = cls->Behavior.id;
  pxy->Any.rc = COS_RC_UNIT;

  retmethod( (OBJ)pxy );
endmethod

defmethod(void, gdealloc, Proxy)
  PRE  TestAssert( self->Any.rc == COS_RC_UNIT );
  BODY free(_1);
endmethod

// ----- understanding

// rank 1
defmethod(OBJ, gunderstandMessage1, Proxy, (SEL)msg)
  next_method(self1,msg);
  if (retval == False) forward_message(self1->obj);
endmethod

// rank 2
defmethod(OBJ, gunderstandMessage2, Proxy, Any, (SEL)msg)
  next_method(self1,self2,msg);
  if (retval == False) forward_message(self1->obj,_2);
endmethod

defmethod(OBJ, gunderstandMessage2, Any, Proxy, (SEL)msg)
  next_method(self1,self2,msg);
  if (retval == False) forward_message(_1,self2->obj);
endmethod

defmethod(OBJ, gunderstandMessage2, Proxy, Proxy, (SEL)msg)
  next_method(self1,self2,msg);
  if (retval == False) forward_message(self2->obj,self2->obj);
endmethod

// rank 3
defmethod(OBJ, gunderstandMessage3, Proxy, Any, Any, (SEL)msg)
  next_method(self1,self2,self3,msg);
  if (retval == False) forward_message(self1->obj,_2,_3);
endmethod

defmethod(OBJ, gunderstandMessage3, Any, Proxy, Any, (SEL)msg)
  next_method(self1,self2,self3,msg);
  if (retval == False) forward_message(_1,self2->obj,_3);
endmethod

defmethod(OBJ, gunderstandMessage3, Any, Any, Proxy, (SEL)msg)
  next_method(self1,self2,self3,msg);
  if (retval == False) forward_message(_1,_2,self3->obj);
endmethod

defmethod(OBJ, gunderstandMessage3, Proxy, Proxy, Any, (SEL)msg)
  next_method(self1,self2,self3,msg);
  if (retval == False) forward_message(self1->obj,self2->obj,_3);
endmethod

defmethod(OBJ, gunderstandMessage3, Proxy, Any, Proxy, (SEL)msg)
  next_method(self1,self2,self3,msg);
  if (retval == False) forward_message(self1->obj,_2,self3->obj);
endmethod

defmethod(OBJ, gunderstandMessage3, Any, Proxy, Proxy, (SEL)msg)
  next_method(self1,self2,self3,msg);
  if (retval == False) forward_message(_1,self2->obj,self3->obj);
endmethod

defmethod(OBJ, gunderstandMessage3, Proxy, Proxy, Proxy, (SEL)msg)
  next_method(self1,self2,self3,msg);
  if (retval == False) forward_message(self1->obj,self2->obj,self3->obj);
endmethod

// rank 4
defmethod(OBJ, gunderstandMessage4, Proxy, Any, Any, Any, (SEL)msg)
  next_method(self1,self2,self3,self4,msg);
  if (retval == False) forward_message(self1->obj,_2,_3,_4);
endmethod

defmethod(OBJ, gunderstandMessage4, Any, Proxy, Any, Any, (SEL)msg)
  next_method(self1,self2,self3,self4,msg);
  if (retval == False) forward_message(_1,self2->obj,_3,_4);
endmethod

defmethod(OBJ, gunderstandMessage4, Any, Any, Proxy, Any, (SEL)msg)
  next_method(self1,self2,self3,self4,msg);
  if (retval == False) forward_message(_1,_2,self3->obj,_4);
endmethod

defmethod(OBJ, gunderstandMessage4, Any, Any, Any, Proxy, (SEL)msg)
  next_method(self1,self2,self3,self4,msg);
  if (retval == False) forward_message(_1,_2,_3,self4->obj);
endmethod

// rank 5
defmethod(OBJ, gunderstandMessage5, Proxy, Any, Any, Any, Any, (SEL)msg)
  next_method(self1,self2,self3,self4,self5,msg);
  if (retval == False) forward_message(self1->obj,_2,_3,_4,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Any, Proxy, Any, Any, Any, (SEL)msg)
  next_method(self1,self2,self3,self4,self5,msg);
  if (retval == False) forward_message(_1,self2->obj,_3,_4,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Any, Any, Proxy, Any, Any, (SEL)msg)
  next_method(self1,self2,self3,self4,self5,msg);
  if (retval == False) forward_message(_1,_2,self3->obj,_4,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Any, Any, Any, Proxy, Any, (SEL)msg)
  next_method(self1,self2,self3,self4,self5,msg);
  if (retval == False) forward_message(_1,_2,_3,self4->obj,_5);
endmethod

defmethod(OBJ, gunderstandMessage5, Any, Any, Any, Any, Proxy, (SEL)msg)
  next_method(self1,self2,self3,self4,self5,msg);
  if (retval == False) forward_message(_1,_2,_3,_4,self5->obj);
endmethod

// ----- unrecognized

static inline void
chkret(SEL sel, OBJ* ret, struct Proxy* pxy)
{
  if (COS_GEN_ORET(sel) && *ret == pxy->obj)
    *ret = (OBJ)pxy;
}

static inline void
chkret2(SEL sel, OBJ* ret, struct Proxy* pxy1, struct Proxy* pxy2)
{
  if (COS_GEN_ORET(sel)) {
    if (*ret == pxy1->obj)
      *ret = (OBJ)pxy1;
    else if (*ret == pxy2->obj)
      *ret = (OBJ)pxy2;
  }
}

static inline void
chkret3(SEL sel, OBJ* ret, struct Proxy* pxy1, struct Proxy* pxy2, struct Proxy* pxy3)
{
  if (COS_GEN_ORET(sel)) {
    if (*ret == pxy1->obj)
      *ret = (OBJ)pxy1;
    else if (*ret == pxy2->obj)
      *ret = (OBJ)pxy2;
    else if (*ret == pxy3->obj)
      *ret = (OBJ)pxy3;
  }
}

// rank 1
defmethod(void, gunrecognizedMessage1, Proxy)
  forward_message(self1->obj);
  chkret(_sel,_ret,self1);
endmethod

// rank 2
defmethod(void, gunrecognizedMessage2, Proxy, Any)
  forward_message(self1->obj,_2);
  chkret(_sel,_ret,self1);
endmethod

defmethod(void, gunrecognizedMessage2, Any, Proxy)
  forward_message(_1,self2->obj);
  chkret(_sel,_ret,self2);
endmethod

defmethod(void, gunrecognizedMessage2, Proxy, Proxy)
  forward_message(self1->obj,self2->obj);
  chkret2(_sel,_ret,self1,self2);
endmethod

// rank 3
defmethod(void, gunrecognizedMessage3, Proxy, Any, Any)
  forward_message(self1->obj,_2,_3);
  chkret(_sel,_ret,self1);
endmethod

defmethod(void, gunrecognizedMessage3, Any, Proxy, Any)
  forward_message(_1,self2->obj,_3);
  chkret(_sel,_ret,self2);
endmethod

defmethod(void, gunrecognizedMessage3, Any, Any, Proxy)
  forward_message(_1,_2,self3->obj);
  chkret(_sel,_ret,self3);
endmethod

defmethod(void, gunrecognizedMessage3, Proxy, Proxy, Any)
  forward_message(self1->obj,self2->obj,_3);
  chkret2(_sel,_ret,self1,self2);
endmethod

defmethod(void, gunrecognizedMessage3, Proxy, Any, Proxy)
  forward_message(self1->obj,_2,self3->obj);
  chkret2(_sel,_ret,self1,self3);
endmethod

defmethod(void, gunrecognizedMessage3, Any, Proxy, Proxy)
  forward_message(_1,self2->obj,self3->obj);
  chkret2(_sel,_ret,self2,self3);
endmethod

defmethod(void, gunrecognizedMessage3, Proxy, Proxy, Proxy)
  forward_message(self1->obj,self2->obj,self3->obj);
  chkret3(_sel,_ret,self1,self2,self3);
endmethod

// rank 4
defmethod(void, gunrecognizedMessage4, Proxy, Any, Any, Any)
  forward_message(self1->obj,_2,_3,_4);
  chkret(_sel,_ret,self1);
endmethod

defmethod(void, gunrecognizedMessage4, Any, Proxy, Any, Any)
  forward_message(_1,self2->obj,_3,_4);
  chkret(_sel,_ret,self2);
endmethod

defmethod(void, gunrecognizedMessage4, Any, Any, Proxy, Any)
  forward_message(_1,_2,self3->obj,_4);
  chkret(_sel,_ret,self3);
endmethod

defmethod(void, gunrecognizedMessage4, Any, Any, Any, Proxy)
  forward_message(_1,_2,_3,self4->obj);
  chkret(_sel,_ret,self4);
endmethod

// rank 5
defmethod(void, gunrecognizedMessage5, Proxy, Any, Any, Any, Any)
  forward_message(self1->obj,_2,_3,_4,_5);
  chkret(_sel,_ret,self1);
endmethod

defmethod(void, gunrecognizedMessage5, Any, Proxy, Any, Any, Any)
  forward_message(_1,self2->obj,_3,_4,_5);
  chkret(_sel,_ret,self2);
endmethod

defmethod(void, gunrecognizedMessage5, Any, Any, Proxy, Any, Any)
  forward_message(_1,_2,self3->obj,_4,_5);
  chkret(_sel,_ret,self3);
endmethod

defmethod(void, gunrecognizedMessage5, Any, Any, Any, Proxy, Any)
  forward_message(_1,_2,_3,self4->obj,_5);
  chkret(_sel,_ret,self4);
endmethod

defmethod(void, gunrecognizedMessage5, Any, Any, Any, Any, Proxy)
  forward_message(_1,_2,_3,_4,self5->obj);
  chkret(_sel,_ret,self5);
endmethod