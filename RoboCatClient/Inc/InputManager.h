
class InputManager
{
public:


	static void StaticInit();
	static unique_ptr< InputManager >	sInstance;

	void HandleInput( EInputAction inInputAction, int inKeyCode );
	void HandleMouse(SDL_Event *event,bool isUp, bool isDown);
	//void HandleMouseMove(SDL_Event *event);

	const InputState& GetState()	const	{ return mCurrentState; }

	MoveList&			GetMoveList()		{ return mMoveList; }

	const Move*			GetAndClearPendingMove()	{ auto toRet = mPendingMove; mPendingMove = nullptr; return toRet; }

	void				Update();

	bool mButton[4];

	Vector3 mClickedDown[4];
	Vector3 mClickedUp[4];

private:

	InputState							mCurrentState;

	InputManager();

	bool				IsTimeToSampleInput();
	const Move&			SampleInputAsMove();
	
	MoveList		mMoveList;
	float			mNextTimeToSampleInput;
	const Move*		mPendingMove;
};