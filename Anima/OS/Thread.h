#ifndef __AE_OS_THREAD__
#define __AE_OS_THREAD__

namespace AE
{
	namespace OS
	{
		class AsyncElement;

		class Thread
		{
		public:
			Thread(AE::OS::AsyncElement *asyncElement) : mAsyncElement(asyncElement) {}
			virtual ~Thread() {}

			bool getShouldStop() { return mShouldStop; }
			virtual void join(const AE::OS::Thread &otherThread, void **returnValue) = 0;
			void setShouldStop(bool shouldStop) { mShouldStop = shouldStop; }
			virtual void start() = 0;

		protected:
			AE::OS::AsyncElement *mAsyncElement;
			bool mShouldStop;
		}
	}
}

#endif