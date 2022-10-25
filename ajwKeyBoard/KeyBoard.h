#pragma once

#include <Windows.h>

#include "Export.h"


namespace ajwCommon
{
	class AJW_KEYBOARD_DLLEXPORT KeyBoard
	{
		const static DWORD KEYMAX = 256;
	private:
		enum
		{
			NONE,
			DOWN,
			UP,
			PRESS
		};
	
		BYTE curState[KEYMAX];
		BYTE oldState[KEYMAX];
		BYTE mapState[KEYMAX];
	
	
	public:
		KeyBoard();
		~KeyBoard();
	
		void Update();
	
		bool Down(UINT key) { return mapState[key] == DOWN; }
		bool Up(UINT key) { return mapState[key] == UP; }
		bool Press(UINT key) { return mapState[key] == PRESS; }
	};
}
