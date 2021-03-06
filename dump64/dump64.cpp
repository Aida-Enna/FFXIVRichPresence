// dump.cpp: Definiert die exportierten Funktionen für die DLL-Anwendung.
//

#include "stdafx.h"
#include <string>

VOID StartProcess( LPCTSTR lpApplicationName )
{
   // additional information
   STARTUPINFO si;
   PROCESS_INFORMATION pi;

   // set the size of the structures
   ZeroMemory( &si, sizeof( si ) );
   si.cb = sizeof( si );
   ZeroMemory( &pi, sizeof( pi ) );

   // start the program up
   CreateProcess( lpApplicationName,   // the path
                  NULL,        // Command line
                  NULL,           // Process handle not inheritable
                  NULL,           // Thread handle not inheritable
                  FALSE,          // Set handle inheritance to FALSE
                  0,              // No creation flags
                  NULL,           // Use parent's environment block
                  NULL,           // Use parent's starting directory 
                  &si,            // Pointer to STARTUPINFO structure
                  &pi             // Pointer to PROCESS_INFORMATION structure (removed extra parentheses)
   );
   // Close process and thread handles. 
   CloseHandle( pi.hProcess );
   CloseHandle( pi.hThread );
}

BOOL GetModulePath( TCHAR* pBuf, DWORD dwBufSize ) {

   if( GetModuleFileName( NULL, pBuf, dwBufSize ) ) {

      PathRemoveFileSpec( pBuf ); // remove executable name

      return TRUE;
   }

   return FALSE;
}

extern "C" __declspec( dllexport ) const char * func( const char * in )
{
   TCHAR acPath[MAX_PATH];

   GetModulePath( acPath, MAX_PATH );

   wchar_t path[MAX_PATH];

   wcscpy_s( path, acPath );
   wcscat_s( path, L"/RichPresence/FFXIVRichPresenceRunner.exe" );

   StartProcess( path );

   return "";
}

