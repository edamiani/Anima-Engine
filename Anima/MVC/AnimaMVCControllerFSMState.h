#ifndef __AE_MVC_CONTROLLER_FSM_STATE__
#define __AE_MVC_CONTROLLER_FSM_STATE__

#include "AnimaAIFSMState.h"
#include "AnimaMVCController.h"
#include "AnimaMVCModel.h"
#include "AnimaMVCView.h"

namespace AE
{
	namespace MVC
	{
		class ControllerFSMState : public AE::AI::FSMState
		{
		public:
			ControllerFSMState(int type, AE::MVC::Controller *parentController, AE::MVC::Model *model, AE::MVC::View *view) 
				: FSMState(type), mParentController(parentController), mModel(model), mView(view) {  }
			virtual ~ControllerFSMState() {  }

			virtual int			checkTransitions() { return FSM_STATE_NONE; }
			AE::MVC::Model*		getModel() { return mModel; }
			AE::MVC::View*		getView() { return mView; }
			virtual void		onEnter() {  }
			virtual void		onExit() {  }
			virtual void		onInitialize() {  }
			virtual void		onUpdate(float dt) {  }
			void				setModel(AE::MVC::Model *model) { mModel = model; }
			void				setView(AE::MVC::View *view) { mView = view; }

		protected:
			AE::MVC::Model		*mModel;
			AE::MVC::Controller	*mParentController;
			AE::MVC::View		*mView;
		};
	}
}

#endif