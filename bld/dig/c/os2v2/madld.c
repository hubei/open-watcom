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
* Description:  MAD module loader for 32-bit OS/2.
*
****************************************************************************/


#include <string.h>
#include <stdlib.h>

#define INCL_DOSMODULEMGR
#define INCL_DOSMISC
#include <os2.h>

#include "mad.h"
#include "madimp.h"

mad_status MADSysLoad( char *path, mad_client_routines *cli,
                       mad_imp_routines **imp, unsigned long *sys_hdl )
{
    HMODULE             dll;
    mad_imp_routines    *(*init_func)( mad_status *, mad_client_routines * );
    mad_status          status;
    char                madname[CCHMAXPATH] = "";
    char                madpath[CCHMAXPATH] = "";

    /* To prevent conflicts with the 16-bit MAD DLLs, the 32-bit versions have the "D32"
     * extension. We will search for them along the PATH (not in LIBPATH);
     */
    strcpy( madname, path );
    strcat( madname, ".D32" );
    _searchenv( madname, "PATH", madpath );
    if( madpath[0] == '\0' ) {
        return( MS_ERR | MS_FOPEN_FAILED );
    }
    if( DosLoadModule( NULL, 0, madpath, &dll ) != 0 ) {
        return( MS_ERR | MS_FOPEN_FAILED );
    }
    if( DosQueryProcAddr( dll, 0, "MADLOAD", (PFN FAR *)&init_func ) != 0 ) {
        DosFreeModule( dll );
        return( MS_ERR | MS_INVALID_MAD );
    }
    *imp = init_func( &status, cli );
    if( *imp == NULL ) {
        DosFreeModule( dll );
        return( status );
    }
    *sys_hdl = dll;
    return( MS_OK );
}

void MADSysUnload( unsigned long sys_hdl )
{
    DosFreeModule( sys_hdl );
}
