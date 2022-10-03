class Server : public Engine
{
public:

	static bool StaticInit();

	virtual bool DoFrame() override;

	virtual int Run();

	void HandleNewClient( ClientProxyPtr inClientProxy );
	void HandleLostClient( ClientProxyPtr inClientProxy );

	RoboCatPtr	GetCatForPlayer( int inPlayerId );
	void	SpawnCatForPlayer( int inPlayerId );


private:
	Server();

	bool	InitNetworkManager();
	void	SetupWorld();

};