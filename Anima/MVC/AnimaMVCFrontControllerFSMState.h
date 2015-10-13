#ifndef __AE_MVC_FRONT_CONTROLLER_FSM_STATE__
#define __AE_MVC_FRONT_CONTROLLER_FSM_STATE__

#include "AnimaAIFSMState.h"
#include "AnimaMVCModel.h"
#include "AnimaMVCView.h"

namespace AE
{
	namespace MVC
	{
		class FrontControllerFSMState : public AE::AI::FSMState
		{
		public:
			FrontControllerFSMState(int type, AE::MVC::Model *model, AE::MVC::View *view) : 
			  FSMState(type), mModel(model), mView(view) {  }
			virtual ~FrontControllerFSMState() {  }

			virtual int		checkTransitions() { return FSM_STATE_NONE; }
			AE::MVC::Model*	getModel() { return mModel; }
			AE::MVC::View*	getView() { return mView; }
			virtual void	onEnter() {  }
			virtual void	onExit() {  }
			virtual void	onInitialize() {  }
			virtual void	onUpdate(float dt) {  }
			void			setModel(AE::MVC::Model *model) { mModel = model; }
			void			setView(AE::MVC::View *view) { mView = view; }

		protected:
			AE::MVC::Model	*mModel;
			AE::MVC::View	*mView;
		};
	}
}

#endif