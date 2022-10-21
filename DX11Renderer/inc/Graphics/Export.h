#pragma once


//#define AJW_GRAPHICS_LIBNAME 
//
//
//#ifdef WIN32//x86
//#ifdef _DEBUG
//#define AJW_GRAPHICS_LIBNAME "ajwUtility_Win32Debug.lib"//Debug
//#else
//#define AJW_GRAPHICS_LIBNAME "ajwUtility_Win32Release.lib"//Release
//#endif
//#else//x64
//#ifdef _DEBUG
//#define AJW_GRAPHICS_LIBNAME "ajwUtility_x64Debug.lib"//Debug
//#else
//#define AJW_GRAPHICS_LIBNAME "ajwUtility_x64Release.lib"//Release
//#endif
//#endif


#ifdef AJW_GRAPHICS

#define AJW_GRAPHICS_DLLEXPORT __declspec(dllexport)

#else

//#pragma comment (lib, AJW_GRAPHICS_LIBNAME)
#define AJW_GRAPHICS_DLLEXPORT __declspec(dllimport)

#endif
