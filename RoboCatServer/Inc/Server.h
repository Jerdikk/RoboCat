class Server : public Engine
{
public:

	static bool StaticInit();

	virtual bool DoFrame() override;
	virtual void HandleEvent(SDL_Event* inEvent) override;

	virtual int Run();

	void HandleNewClient( ClientProxyPtr inClientProxy );
	void HandleLostClient( ClientProxyPtr inClientProxy );

	RoboCatPtr	GetCatForPlayer( int inPlayerId );
	void	SpawnCatForPlayer( int inPlayerId );
	//void	RemoveCatForPlayer(int inPlayerId);
	~Server();

private:
	Server();

	

	bool	InitNetworkManager();
	void	SetupWorld();

	SDL_Window* mMainWindow;

};