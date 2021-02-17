#pragma once
#include <Windows.h>

namespace JEngine
{
	class POINT
	{
	public:
		int x;
		int y;

		POINT();
		POINT(int x_, int y_);
		~POINT();
	};

	class POINTF
	{
	public:
		float x;
		float y;

		POINTF();
		POINTF(float x_, float y_);
		~POINTF();
	};

	class RECT
	{
	public:
		int left;
		int top;
		int right;
		int bottom;

		inline void Set(int left_, int top_, int right_, int bottom_)
		{
			left = left_;
			top = top_;
			right = right_;
			bottom = bottom_;
		}

		inline ::RECT ToWinRECT()
		{
			::RECT rc = { left , top , right , bottom };
			return rc;
		}

		bool isCollision(RECT rcOther);
		bool isPtin(POINT ptOther);
		RECT();
		RECT(int left_, int top_, int right_, int bottom_);
		~RECT();
	};
}

