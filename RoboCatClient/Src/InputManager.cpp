#include <RoboCatClientPCH.h>

unique_ptr< InputManager >	InputManager::sInstance;

namespace
{
	float kTimeBetweenInputSamples = 0.03f;
}

void InputManager::StaticInit()
{
	sInstance.reset( new InputManager() );
}


namespace
{
	inline void UpdateDesireVariableFromKey( EInputAction inInputAction, bool& ioVariable )
	{
		if( inInputAction == EIA_Pressed )
		{
			ioVariable = true;
		}
		else if( inInputAction == EIA_Released )
		{
			ioVariable = false;
		}
	}

	inline void UpdateDesireFloatFromKey( EInputAction inInputAction, float& ioVariable )
	{
		if( inInputAction == EIA_Pressed )
		{
			ioVariable = 1.f;
		}
		else if( inInputAction == EIA_Released )
		{
			ioVariable = 0.f;
		}
	}
}

void InputManager::HandleInput( EInputAction inInputAction, int inKeyCode )
{
	switch( inKeyCode )
	{
	case 27:
		NetworkManagerClient::sInstance->WantToExit();
		break;
	case 'a':
		UpdateDesireFloatFromKey( inInputAction, mCurrentState.mDesiredLeftAmount );
		break;
	case 'd':
		UpdateDesireFloatFromKey( inInputAction, mCurrentState.mDesiredRightAmount );
		break;
	case 'w':
		UpdateDesireFloatFromKey( inInputAction, mCurrentState.mDesiredForwardAmount );
		break;
	case 's':
		UpdateDesireFloatFromKey( inInputAction, mCurrentState.mDesiredBackAmount );
		break;
	case 'k':
		UpdateDesireVariableFromKey( inInputAction, mCurrentState.mIsShooting );
		break;
	}

}

void InputManager::HandleMouse(SDL_Event *event,bool isUp, bool isDown)
{
	if (isUp)
	{
		int yy = 1;
	}
	else
		if (isDown)
		{
			int yyyy = 2;
		}
		else
		{/// only mouse move

		}
}


InputManager::InputManager() :
	mNextTimeToSampleInput( 0.f ),
	mPendingMove( nullptr )
{

}

const Move& InputManager::SampleInputAsMove()
{
	return mMoveList.AddMove( GetState(), Timing::sInstance.GetFrameStartTime() );
}

bool InputManager::IsTimeToSampleInput()
{
	float time = Timing::sInstance.GetFrameStartTime();
	if( time > mNextTimeToSampleInput )
	{
		mNextTimeToSampleInput = mNextTimeToSampleInput + kTimeBetweenInputSamples;
		return true;
	}

	return false;
}

void InputManager::Update()
{
	if( IsTimeToSampleInput() )
	{
		mPendingMove = &SampleInputAsMove();
	}
}