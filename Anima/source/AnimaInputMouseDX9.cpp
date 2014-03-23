#include "../include/AnimaInputMouseDX9.h"

namespace AE
{
	namespace Input
	{
		MouseDX9::MouseDX9(AE::Input::ContextDX9 *inputContext) :
			mInputContext(inputContext)
		{ 
			HRESULT result = inputContext->_getDInput8()->CreateDevice(GUID_SysMouse, &mMouseDI8, NULL);
			assert(!FAILED(result));

			result = mMouseDI8->SetDataFormat(&c_dfDIMouse);
			assert(!FAILED(result));

			result = mMouseDI8->SetCooperativeLevel(inputContext->_getWindowHandle(), DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
			assert(!FAILED(result));

			DIPROPDWORD dipdw;
			// Header
			dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
			dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			dipdw.diph.dwObj        = 0;
			dipdw.diph.dwHow        = DIPH_DEVICE;
			// Data
			dipdw.dwData            = 16; // Buffer size

			result = mMouseDI8->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
			assert(!FAILED(result));

			mIsAcquired = false;
		}

		MouseDX9::~MouseDX9() 
		{
			mMouseDI8->Unacquire();
			mMouseDI8->Release();
		}

		AE::int32 MouseDX9::getAbsoluteX()
		{ 
			return 0;
		}
		
		AE::int32 MouseDX9::getAbsoluteY() 
		{ 
			return 0;
		}

		AE::Math::Point2 MouseDX9::getCoordinates()
		{
			POINT ptCursor;
			::GetCursorPos( &ptCursor );
			::ScreenToClient( mInputContext->_getWindowHandle(), &ptCursor );
			return AE::Math::Point2(ptCursor.x, ptCursor.y);
		}
		
		AE::int32 MouseDX9::getRelativeX() 
		{ 
			return 0;
		}
		
		AE::int32 MouseDX9::getRelativeY() 
		{ 
			return 0;
		}

		bool MouseDX9::isButtonDown(AE::Input::MouseButtonType button) 
		{
			bool isButtonDown = false;

			switch(button)
			{
			case AE::Input::MBT_LEFT:
				if(mMouseState.rgbButtons[0] & 0x80) 
					isButtonDown = true;
				break;
			}

			return isButtonDown;
		}
		
		bool MouseDX9::poll() 
		{
			HRESULT result;
			while(1) 
			{
				// Poll device
				mMouseDI8->Poll();

				// Read in state
				if(SUCCEEDED(result = mMouseDI8->GetDeviceState(sizeof(DIMOUSESTATE), &mMouseState)))
					break;

				// Return on an unknown error
				if(result != DIERR_INPUTLOST && result != DIERR_NOTACQUIRED)
					return false;

				// Reacquire and try again
				if(FAILED(mMouseDI8->Acquire()))
					return false;
			}

			// Return a success
			return true;
		}
	}
}