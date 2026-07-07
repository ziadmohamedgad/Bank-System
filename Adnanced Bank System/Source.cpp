#include <iostream>
#include "clsLoginScreen.h"
#include "Global.h"
#include "clsInputValidate.h"
using namespace std;
int main()
{
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen()) break;
	}
	system("pause>nul");
	return 0;
}