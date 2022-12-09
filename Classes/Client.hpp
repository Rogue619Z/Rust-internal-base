class Client 
{
public:
	CLASS("", "Client");

	auto connection() -> Connection*
	{
		METHOD(Connection * (**)(Client*), get_Connection);
		return get_Connection(this);
	}

};