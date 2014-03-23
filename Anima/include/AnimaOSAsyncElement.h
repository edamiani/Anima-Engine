#ifndef __AE_OS_ASYNC_ELEMENT__
#define __AE_OS_ASYNC_ELEMENT__

namespace AE
{
	namespace OS
	{
		class AsyncElement
		{
		public:
			AsyncElement() {}
			virtual ~AsyncElement() {}

			virtual void onRun() = 0;
			virtual void onPostRun() = 0;
			virtual void onPreRun() = 0;

		protected:
			bool mShouldStop;
		}
	}
}

#endif