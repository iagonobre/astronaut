#include <iostream>
#include "utils.h"

using std::cin;
using std::cout;
using std::endl;

#ifdef _WIN32
#include <windows.h>
#else
#include <cstdlib>
#endif

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void goBackToMenu()
{
    int option = 0;
    cout << "Operação finalizada com sucesso" << endl;
    cout << "[1] Retornar ao Menu Inicial" << endl;
    cout << ">> ";
    cin >> option;
}