#include <iostream>

#include "utils.h"
#include "flight.h"
#include "astronaut.h"

using std::cin;
using std::cout;
using std::endl;

void showMenu()
{
    cout << "-=-=- SIGAVE - Sistema de Gestão de Astronautas e Voos Espaciais -=-=-" << endl;
    cout << "Escolha uma opção abaixo:" << endl
         << endl;
    cout << "(1) Cadastrar Astronauta" << endl;
    cout << "(2) Cadastrar Voo" << endl;
    cout << "(3) Adicionar Astronauta em Voo" << endl;
    cout << "(4) Remover Astronauta de um Voo" << endl;
    cout << "(5) Lançar um Voo" << endl;
    cout << "(6) Explodir Voo" << endl;
    cout << "(7) Finalizar Voo" << endl;
    cout << "(8) Listar todos os voos" << endl;
    cout << "(9) Listar todos os astronautas" << endl;
    cout << "(10) Finalizar programa" << endl;
    cout << ">> ";
}

int main()
{
    int option;

    do
    {
        clearScreen();
        showMenu();
        cin >> option;

        switch (option)
        {
        case 1:
        {
            clearScreen();
            Astronaut::createAstronauts();

            goBackToMenu();
            break;
        }
        case 2:
        {
            clearScreen();
            Flight::createFlights();

            goBackToMenu();
            break;
        }
        case 3:
        {
            clearScreen();
            int flightNumber = -1;
            Flight::addAstronautToAFlight(flightNumber);

            goBackToMenu();
            break;
        }
        case 4:
        {
            clearScreen();
            Flight::removeAstronautToAFlight();

            goBackToMenu();
            break;
        }
        case 5:
        {
            clearScreen();
            Flight::launchFlight();
            goBackToMenu();
            break;
        }
        case 6:
        {
            clearScreen();
            Flight::explodeFlight();

            goBackToMenu();
            break;
        }
        case 7:
        {
            clearScreen();
            Flight::endFlight();

            goBackToMenu();
            break;
        }
        case 8:
        {
            clearScreen();
            int choice = 0;

            do
            {
                cout << "Escolha uma opção abaixo:" << endl
                     << endl;
                cout << "(1) Voos Planejados " << endl;
                cout << "(2) Voos Em Curso" << endl;
                cout << "(3) Voos Finalizados " << endl;
                cout << ">> ";
                cin >> choice;
            } while (choice < 0 || choice > 3);

            switch (choice)
            {
            case 1:
                clearScreen();
                Flight::listFlights("planning");
                break;
            case 2:
                clearScreen();
                Flight::listFlights("inProgress");
                break;
            case 3:
                clearScreen();
                Flight::listFlights("ended");
                break;
            default:
                break;
            }

            goBackToMenu();
            break;
        }
        case 9:
        {
            clearScreen();
            int choice = 0;

            do
            {
                cout << "Escolha uma opção abaixo:" << endl
                     << endl;
                cout << "(1) Astronautas Disponíveis" << endl;
                cout << "(2) Astronautas Mortos" << endl;
                cout << ">> ";
                cin >> choice;
            } while (choice < 0 || choice > 2);

            switch (choice)
            {
            case 1:
                clearScreen();

                Astronaut::listAstronauts("available");

                break;
            case 2:
                clearScreen();
                Astronaut::listAstronauts("dead");
                break;
            default:
                break;
            }

            goBackToMenu();
            break;
        }
        case 10:
        {
            cout << "Finalizando programa..." << endl;
            break;
        }
        default:
        {
            cout << "Opção inválida, tente novamente." << endl;
            break;
        }
        }

    } while (option != 10);

    return 0;
}