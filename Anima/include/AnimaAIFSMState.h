#ifndef __AE_AI_FSM_STATE__
#define __AE_AI_FSM_STATE__

#include "AnimaOSEvent.h"

enum
{
	FSM_STATE_NONE = -1
};

namespace AE
{
	namespace AI
	{
		class FSMState
		{
		public:
			FSMState(int type = FSM_STATE_NONE) : mType(type) {  }
			virtual ~FSMState() {  }

			virtual int		checkTransitions() { return FSM_STATE_NONE; }
			virtual void	onEnter() {  }
			virtual void	onExit() {  }
			int				getType() { return mType; }
			virtual void	onInitialize() {  }
			virtual void	onUpdate(float dt) {  }

		protected:
			int mType;
		};
	}
}

#endif