#include "../include/AnimaAIFSMMachine.h"

namespace AE
{
	namespace AI
	{
		//---------------------------------------------------------
		FSMMachine::FSMMachine(int type)
			: FSMState(type), mCurrentState(0), mDefaultState(0), mNextState(0), mNextStateId(FSM_STATE_NONE)
		{
		}

		//---------------------------------------------------------
		void FSMMachine::updateMachine(float dt)
		{
			//don't do anything if you have no states
			if(mStates.size() == 0 )
				return;

			//don't do anything if there's no current 
			//state, and no default state
			if(!mDefaultState)
				return;

			if(!mCurrentState)
				mCurrentState = mDefaultState;

			//check for transitions, and then update
			int currentStateId = mCurrentState->getType();
			mNextStateId = mCurrentState->checkTransitions();
			
			//switch if there was a transition
			if(mNextStateId != currentStateId)
			{
				if(transitionState(mNextStateId))
				{
					mCurrentState->onExit();
					mCurrentState = mNextState;
					mCurrentState->onEnter();
				}
			}
			mCurrentState->onUpdate(dt);	
			
		}

		//---------------------------------------------------------
		void FSMMachine::addState(AE::AI::FSMState* state)
		{
			mStates.push_back(state);
		}

		//---------------------------------------------------------
		bool FSMMachine::transitionState(int nextStateId)
		{
			//don't do anything if you have no states
			if(mStates.size() == 0 )
				return false;
			
			//determine if we have state of type 'nextStateId'
			//in the list, and switch to it, otherwise, quit out
			for(unsigned int i = 0; i < mStates.size(); i++)
			{
				if(mStates[i]->getType() == nextStateId)
				{
					mNextState = mStates[i];
					return true;
				}
			}
			return false;
		}

		//---------------------------------------------------------
		void FSMMachine::reset()
		{
			onExit();
			if(mCurrentState)
				mCurrentState->onExit();
			mCurrentState = mDefaultState;

			//init all the states
			for(unsigned int i = 0; i < mStates.size(); i++)
				mStates[i]->onInitialize();

			//and now enter the mDefaultState, if any
			if(mCurrentState)
				mCurrentState->onEnter();
		}
	}
}