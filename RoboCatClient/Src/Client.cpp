
#include <RoboCatClientPCH.h>

bool Client::StaticInit( )
{
	// Create the Client pointer first because it initializes SDL
	Client* client = new Client();

	if( WindowManager::StaticInit() == false )
	{
		return false;
	}
	
	if( GraphicsDriver::StaticInit( WindowManager::sInstance->GetMainWindow() ) == false )
	{
		return false;
	}

	TextureManager::StaticInit();
	RenderManager::StaticInit();
	InputManager::StaticInit();

	HUD::StaticInit();

	sInstance.reset( client );

	return true;
}

Client::Client()
{
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'RCAT', RoboCatClient::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'MOUS', MouseClient::StaticCreate );
	GameObjectRegistry::sInstance->RegisterCreationFunction( 'YARN', YarnClient::StaticCreate );

	string destination = StringUtils::GetCommandLineArg( 1 );
	string name = StringUtils::GetCommandLineArg( 2 );

	SocketAddressPtr serverAddress = SocketAddressFactory::CreateIPv4FromString( destination );

	NetworkManagerClient::StaticInit( *serverAddress, name );

	//NetworkManagerClient::sInstance->SetDropPacketChance( 0.6f );
	//NetworkManagerClient::sInstance->SetSimulatedLatency( 0.25f );
	//NetworkManagerClient::sInstance->SetSimulatedLatency( 0.5f );
	//NetworkManagerClient::sInstance->SetSimulatedLatency( 0.1f );
}



bool Client::DoFrame()
{
	InputManager::sInstance->Update();

	Engine::DoFrame();

	NetworkManagerClient::sInstance->ProcessIncomingPackets();

	if (NetworkManagerClient::sInstance->bExit)
		return false;

	RenderManager::sInstance->Render();

	NetworkManagerClient::sInstance->SendOutgoingPackets();
	return true;
}

void Client::HandleEvent( SDL_Event* inEvent )
{
	bool isUp = false;
	bool isDown = false;
	switch( inEvent->type )
	{
	case SDL_MOUSEWHEEL:             /**< Mouse wheel motion */
		InputManager::sInstance->HandleMouse(inEvent, isUp, isDown);
		break;

	case SDL_MOUSEBUTTONDOWN:        /**< Mouse button pressed */
		isDown = true;
		InputManager::sInstance->HandleMouse(inEvent, isUp, isDown);
		break;

	case SDL_MOUSEBUTTONUP:          /**< Mouse button released */
		isUp = true;
		InputManager::sInstance->HandleMouse(inEvent, isUp, isDown);
		break;

	case SDL_MOUSEMOTION:
		//SDL_MouseMotionEvent motion;    /**< Mouse motion event data */

		InputManager::sInstance->HandleMouse(inEvent,isUp,isDown);
		break;
	case SDL_KEYDOWN:
		InputManager::sInstance->HandleInput( EIA_Pressed, inEvent->key.keysym.sym );
		break;
	case SDL_KEYUP:
		InputManager::sInstance->HandleInput( EIA_Released, inEvent->key.keysym.sym );
		break;
	default:
		break;
	}
}

