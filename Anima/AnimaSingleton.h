#ifndef __AE_SINGLETON__
#define __AE_SINGLETON__

#include <cassert>

namespace AE 
{
	// Template class for creating single-instance global classes.
	template <typename T> 
	class Singleton
	{
	public:
		static T* getInstance() 
		{ 
			assert(mInstance);
			return mInstance;
		}

		virtual ~Singleton() 
		{ 
			//assert(mSingleton);  mSingleton = 0;
			if(mInstance)
			{
				delete mInstance;
				mInstance = 0;
			}
		}

	protected:
		Singleton()
		{
			//mSingleton = static_cast<T*>(this);
		}

		virtual bool initialize() = 0;
		virtual bool shutdown() = 0;

		static T* mInstance;
	};
}

#endif