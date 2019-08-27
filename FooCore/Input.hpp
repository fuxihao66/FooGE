#pragma once

#include <queue>
#include <windows.h>
#include "../FooMath/utility.hpp"
namespace FooGE{
    class Input{
    
    class GC // 单例资源析构
	{
	public:
		GC(){}
		~GC()
		{
			if (m_Input != NULL)
			{
				delete(m_Input);
				m_Input = NULL;
			}
		}
	};
	static GC gc;  //垃圾回收类的静态成员

    
    private:
        Input(){}
        ~Input(){}

        vec2<UINT> m_MousePos; 

        static Input* m_Input;

        bool keyDown[0xFF];   // from 0x01 to 0xFE
        bool mouseDown[3];   // LEFT MIDDLE RIGHT
    public:

        vec2<UINT> GetMousePos();
        void SetMousePos(UINT x, UINT y);
        bool GetMouseDown(UINT m);
        bool GetKeyDown(UINT k);
        void SetMouseDown(UINT m);
        void SetMouseUp(UINT m);
        void SetKeyDown(UINT k);
        void SetKeyUp(UINT K);
        static Input& Instance();
    };
}