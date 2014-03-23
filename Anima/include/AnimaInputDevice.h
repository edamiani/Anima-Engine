#ifndef __AE_INPUT_DEVICE__
#define __AE_INPUT_DEVICE__

namespace AE
{
	namespace Input
	{
		class Device
		{
		public:
							Device() { mBuffered = false; }
			virtual			~Device() {  }

			bool			isBuffered() { return mBuffered; }
			void			setBuffered(bool buffered) { mBuffered = buffered; }
			virtual bool	poll() = 0;

		protected:
			bool			mBuffered;
		};
	}
}

#endif