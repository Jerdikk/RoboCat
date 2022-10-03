class Client : public Engine
{
public:

	static bool StaticInit( );

protected:

	Client();

	virtual bool	DoFrame() override;
	virtual void	HandleEvent( SDL_Event* inEvent ) override;

private:



};