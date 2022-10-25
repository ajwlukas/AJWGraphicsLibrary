#pragma once
//
//#define AJW_KEYBOARD_LIBNAME 
//
//#ifdef WIN32//x86
//	#ifdef _DEBUG
//		#define AJW_KEYBOARD_LIBNAME "ajwKeyBoard_Win32Debug.lib"//Debug
//	#else
//		#define AJW_KEYBOARD_LIBNAME "ajwKeyBoard_Win32Release.lib"//Release
//	#endif
//#else//x64
//	#ifdef _DEBUG
//		#define AJW_KEYBOARD_LIBNAME "ajwKeyBoard_x64Debug.lib"//Debug
//	#else
//		#define AJW_KEYBOARD_LIBNAME "ajwKeyBoard_x64Release.lib"//Release
//	#endif
//#endif

#ifdef AJW_KEYBOARDDLL

	#define AJW_KEYBOARD_DLLEXPORT __declspec(dllexport)

#else

	//#pragma comment (lib, AJW_KEYBOARD_LIBNAME)
	#define AJW_KEYBOARD_DLLEXPORT __declspec(dllimport)

#endif