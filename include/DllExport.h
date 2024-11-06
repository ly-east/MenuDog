#ifndef DLLEXPORT_H
#define DLLEXPORT_H

#if MENUDOG_DLL
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif // MENUDOG_DLL
#else
#define DllExport

#endif // DLLEXPORT_H
