#include <iostream>
#include "../src/Rise.hpp"
/*
class Sandbox : public RiseEngine::Application
{
public:
	Sandbox(int32, int32, const char*) {}
};

*/
int main()
{
	RiseEngine::Application app(720, 600, "The Rise Engine lifts for the first time");
	app.Run();

	return 0;
}