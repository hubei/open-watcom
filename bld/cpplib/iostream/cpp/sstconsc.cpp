/****************************************************************************
*
*                            Open Watcom Project
*
*    Portions Copyright (c) 1983-2002 Sybase, Inc. All Rights Reserved.
*
*  ========================================================================
*
*    This file contains Original Code and/or Modifications of Original
*    Code as defined in and that are subject to the Sybase Open Watcom
*    Public License version 1.0 (the 'License'). You may not use this file
*    except in compliance with the License. BY USING THIS FILE YOU AGREE TO
*    ALL TERMS AND CONDITIONS OF THE LICENSE. A copy of the License is
*    provided with the Original Code and Modifications, and is also
*    available at www.sybase.com/developer/opensource.
*
*    The Original Code and all software distributed under the License are
*    distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
*    EXPRESS OR IMPLIED, AND SYBASE AND ALL CONTRIBUTORS HEREBY DISCLAIM
*    ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
*    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR
*    NON-INFRINGEMENT. Please see the License for the specific language
*    governing rights and limitations under the License.
*
*  ========================================================================
*
* Description:
*
****************************************************************************/

#ifdef __SW_FH
#include "iost.h"
#else
#include "variety.h"
#include <string.h>
#include <strstrea>
#endif

namespace std {

  // Construct a strstream that will put characters into the buffer
  // starting at str for length size. If ios::append or ios::atend are
  // specified, the putting will commence at the end of the buffer. Gets
  // are also allowed. Gets start at the beginning. The array will not
  // grow dynamically.

  strstream::strstream( signed char *str, int size, ios::openmode mode )
    : strstreambase( (char *)str,
                     size,
                     ((str==0) ? 0 : (char *)str +
                            ((mode & (ios::atend|ios::append)) ?
                                       ::strlen( (char *)str ) : 0) ) ) {
  }

}


