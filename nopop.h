#pragma once
#include <windows.h>        // Provides Win32 API
#include <windowsx.h>       // Provides GDI helper macros
#include "winbgim.h"         // API routines
#include "winbgitypes.h"    // Internal structure data

//THIS FILE HOLDS THE GETMOUSECLICKNOPOP FUNCTION THAT IS NECESSARY FOR THE ISBUTTONCLICKED FUNCTION IN DISPLAY.H

static bool MouseKindInRange( int kind )
{
    return ( (kind >= WM_MOUSEFIRST) && (kind <= WM_MOUSELAST) );
}

void getmouseclicknopop( int kind, int& x, int& y )
{
    WindowData *pWndData = BGI__GetWindowDataPtr( );
    POINTS where; // POINT (short) to tell where mouse event happened.

    // Check if mouse event is in range
    if ( !MouseKindInRange( kind ) )
        return;

    // Set position variables to mouse location, or to NO_CLICK if no event occured
    if ( MouseKindInRange( kind ) && pWndData->clicks[kind - WM_MOUSEFIRST].size( ) )
    {
	where = pWndData->clicks[kind - WM_MOUSEFIRST].front( );
        //pWndData->clicks[kind - WM_MOUSEFIRST].pop( );
        x = where.x;
        y = where.y;
    }
    else
    {
        x = y = NO_CLICK;
    }
}
