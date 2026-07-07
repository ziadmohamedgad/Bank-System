#include <iostream>
#include "clsATMLoginScreen.h"

int main()
{
    while (true)
    {
        if (!clsATMLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }
    return 0;
}
