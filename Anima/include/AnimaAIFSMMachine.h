#ifndef __AE_AI_FSM_STATE_MACHINE__
#define __AE_AI_FSM_STATE_MACHINE__

#include "AnimaAIFSMState.h"
#include <vector>

namespace AE
{
	namespace AI
	{
		class FSMMachine: public AE::AI::FSMState
		{
		public:
			FSMMachine(int type = FSM_STATE_NONE);
			virtual ~FSMMachine() {  }

			virtual void	addState(FSMState* state);
			FSMState*		getCurrentState() { return mCurrentState; }
			virtual void	reset();
			virtual void	setDefaultState(FSMState* state) { mDefaultState = state; }
			virtual bool	transitionState(int goal);
			virtual void	updateMachine(float dt);
		    
		protected:
			FSMState* mCurrentState;
			FSMState* mDefaultState;
			FSMState* mNextState;
			int mNextStateId;
			std::vector<AE::AI::FSMState *> mStates;
		};
	}
}

#endif