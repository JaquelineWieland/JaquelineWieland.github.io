// TheWalkingStyx.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
using namespace std;
int main()
{
	try
	{
		Game thewalkingStyx;
		thewalkingStyx.Run();
	}
	catch (tgui::Exception& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "unhandled exception" << endl;
	}
	

	

	return 0;
}