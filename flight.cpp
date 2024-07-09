#include "flight.h"
#include "utils.h"
#include "astronaut.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

std::vector<Flight> flights;

Flight::Flight(int flightNumber, const std::string &status, bool successful, const std::vector<Astronaut> &astronauts)
    : flightNumber(flightNumber), status(status), successful(successful), astronauts(astronauts) {}

void Flight::addAstronautToAFlight(int &flightNumber)
{
    if (flightNumber == -1)
    {
        flightNumber = Flight::selectFlightAvailable().getFlightNumber();

        if (flightNumber < 0)
        {
            return;
        }
    }

    Flight flight = Flight::findByNumber(flightNumber);

    if (flight.getFlightNumber() == 0)
    {
        cout << "Voo não encontrado, tente novamente." << endl;
    }

    if (flight.getStatus() != "planning")
    {
        cout << "Voo não está em planejamento, tente novamente." << endl;
    }

    clearScreen();
    cout << "-=-=-=- Voo: " << flightNumber << "-=-=-=-" << endl;
    cout << "Insira os passageiros:" << endl;
    cout << endl;

    std::vector<Astronaut> astronauts = Astronaut::selectAstronautsAvailable();

    for (auto &astronaut : astronauts)
    {
        Astronaut::addFlighToAAstronaut(astronaut, flight);
    }

    std::vector<Flight> newFlights;

    for (const auto &flight : flights)
    {
        if (astronauts.empty())
        {
            continue;
        }
        if (flight.getFlightNumber() == flightNumber)
        {
            const Flight newFlight(flightNumber, flight.getStatus(), flight.getSucessful(), astronauts);
            newFlights.push_back(newFlight);
        }
        else
        {
            newFlights.push_back(flight);
        }
    }

    flights = newFlights;
    newFlights = {};
}

void Flight::removeAstronautToAFlight(int &flightNumber)
{
    Flight flight = Flight::findByNumber(flightNumber);

    if (flight.getFlightNumber() == 0)
    {
        cout << "Voo não encontrado, tente novamente." << endl;
    }

    clearScreen();
    cout << "-=-=-=- Voo: " << flightNumber << "-=-=-=-" << endl;
    cout << "Qual passageiro deseja remover?:" << endl;
    cout << endl;

    std::vector<Astronaut> astronauts = Astronaut::selectAstronautsAvailable();

    for (auto &astronaut : astronauts)
    {
        Astronaut::removeFlighToAAstronaut(astronaut, flight);
    }

    std::vector<Flight> newFlights;

    for (const auto &flight : flights)
    {
        if (astronauts.empty())
        {
            continue;
        }
        if (flight.getFlightNumber() == flightNumber)
        {
            const Flight newFlight(flightNumber, flight.getStatus(), flight.getSucessful(), astronauts);
            newFlights.push_back(newFlight);
        }
        else
        {
            newFlights.push_back(flight);
        }
    }

    flights = newFlights;
    newFlights = {};
}

void Flight::createFlights()
{
    int flightNumber;

    do
    {
        cout << "-=-=-=- Criar Voo -=-=-=-" << endl;
        cout << "Digite o Número do Voo:" << endl;
        cout << ">> ";
        cin >> flightNumber;

        if (flightNumber < 0)
        {
            cout << "O número de voo precisa ser maior que 0!" << endl;
        }
    } while (flightNumber < 0);

    const Flight flight(flightNumber, "planning", false, {});

    flights.push_back(flight);

    Flight::addAstronautToAFlight(flightNumber);
}

Flight Flight::findByNumber(int flightNumber)
{
    for (const auto &flight : flights)
    {
        if (flight.getFlightNumber() == flightNumber)
        {
            return flight;
        }
    }
    return Flight(-1, "", false, {});
}

void Flight::listFlights(const std::string &status)
{
    std::vector<Flight> foundFlights;

    for (const auto &flight : flights)
    {
        if (flight.getStatus() == status)
        {
            foundFlights.push_back(flight);
        }
    }

    if (foundFlights.empty())
    {
        cout << "Nenhum voo disponível!" << endl;
        return;
    }
    if (status == "planning")
    {
        cout << "-=-=-=- Lista dos Voos em Planejamento -=-=-=-" << endl;
    }
    if (status == "inProgress")
    {
        cout << "-=-=-=- Lista dos Voos em Progresso -=-=-=-" << endl;
    }
    if (status == "ended")
    {
        cout << "-=-=-=- Lista dos Voos Finalizados -=-=-=-" << endl;
    }
    cout << "|      Número do Voo      |      Status      |   Houve Sucesso?   |" << endl;
    for (const auto &flight : foundFlights)
    {
        cout << "|   ";
        cout << flight.getFlightNumber();
        cout << "   |   ";
        cout << flight.getStatus();
        cout << "   |   ";
        cout << flight.getSucessful();
        cout << "   |" << endl;
    }
}

Flight Flight::selectFlightAvailable()
{
    Flight::listFlights("planning");
    cout << endl;

    int flightNumber;

    while (true)
    {
        cout << "Digite o Número do Voo que deseja adicionar:" << endl;
        cout << "[-1] Para retornar ao Menu Principal." << endl;
        cout << ">> ";
        cin >> flightNumber;

        if (flightNumber == -1)
        {
            return Flight(-1, "", false, {});
        }

        Flight foundFlight = Flight::findByNumber(flightNumber);

        if (foundFlight.getFlightNumber() == -1)
        {
            cout << "Voo não encontrado, tente novamente." << endl;
        }
        else if (foundFlight.getStatus() != "planning")
        {
            cout << "Voo não disponível, encerrado ou em curso. Tente novamente." << endl;
        }
        else
        {
            return foundFlight;
        }
    }
}

bool Flight::getSucessful() const
{
    return successful;
}

std::string Flight::getStatus() const
{
    return status;
}

int Flight::getFlightNumber() const
{
    return flightNumber;
}

std::vector<Astronaut> Flight::getAstronauts() const
{
    return astronauts;
}