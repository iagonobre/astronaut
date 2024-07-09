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
        flightNumber = Flight::selectFlight("available").getFlightNumber();

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

    Flight::changeAstronautsInAFlight(flightNumber, astronauts);
}

void Flight::removeAstronautToAFlight()
{
    int flightNumber = Flight::selectFlight("available").getFlightNumber();
    Flight flight = Flight::findByNumber(flightNumber);

    if (flight.getFlightNumber() == 0)
    {
        cout << "Voo não encontrado, tente novamente." << endl;
    }

    clearScreen();
    cout << "-=-=-=- Voo: " << flightNumber << "-=-=-=-" << endl;
    cout << "Qual passageiro deseja remover?:" << endl;
    cout << endl;

    std::vector<Astronaut> astronauts = Astronaut::selectAstronautsByFlight(flightNumber);

    for (auto &astronaut : astronauts)
    {
        Astronaut::removeFlighToAAstronaut(astronaut, flight);
    }

    std::vector<Astronaut> finalAstronauts;
    std::vector<Astronaut> currentAstronauts = flight.getAstronauts();

    for (auto &astronaut : currentAstronauts)
    {
        bool shouldRemove = false;
        for (const auto &astronautToRemove : astronauts)
        {
            if (astronaut.getCpf() == astronautToRemove.getCpf())
            {
                shouldRemove = true;
                break;
            }
        }
        if (!shouldRemove)
        {
            finalAstronauts.push_back(astronaut);
        }
    }

    Flight::changeAstronautsInAFlight(flightNumber, finalAstronauts);
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
    for (auto &flight : flights)
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
    cout << "| Número do Voo |      Status      |   Houve Sucesso?   |" << endl
         << endl;
    for (const auto &flight : foundFlights)
    {
        cout << "|   ";
        cout << flight.getFlightNumber();
        cout << "   |   ";
        cout << flight.getStatus();
        cout << "   |   ";
        if (flight.getStatus() != "ended")
        {
            cout << "Não finalizado";
        }
        else if (flight.getSucessful() && flight.getStatus() == "ended")
        {
            cout << "Sim";
        }
        else
        {
            cout << "Não";
        }
        cout << "   |" << endl;

        if (!flight.astronauts.empty())
        {
            cout << "Astronautas: ";
            for (const auto astronaut : flight.astronauts)
            {
                std::string name = astronaut.getName();
                cout << name;
                if (flight.astronauts.size() > 1)
                {
                    cout << ", ";
                }
            }
            cout << endl
                 << endl;
        }
    }
}

Flight Flight::selectFlight(const std::string &status)
{
    Flight::listFlights(status);
    cout << endl;

    int flightNumber;

    while (true)
    {
        cout << "Digite o Número do Voo que deseja selecionar:" << endl;
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
        else if (foundFlight.getStatus() != status)
        {
            cout << "Voo não disponível para seleção. Tente novamente." << endl;
        }
        else
        {
            return foundFlight;
        }
    }
}

void Flight::changeAstronautsInAFlight(int &flightNumber, std::vector<Astronaut> &astronauts)
{
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

void Flight::explodeFlight()
{
    Flight flight = Flight::selectFlight("inProgress");

    for (auto &realFlight : flights)
    {
        if (flight.getFlightNumber() == realFlight.getFlightNumber())
        {
            bool successful = false;
            std::string status = "ended";
            realFlight.setSuccessful(successful);
            realFlight.setStatus(status);

            for (auto &flightAstronaut : realFlight.getAstronauts())
            {
                std::string status = "dead";
                flightAstronaut.setStatus(status);

                Astronaut::setDeadAstronaut(flightAstronaut.getCpf());
            }
        }
    }
}

void Flight::endFlight()
{
    Flight flight = Flight::selectFlight("inProgress");

    for (auto &realFlight : flights)
    {
        if (flight.getFlightNumber() == realFlight.getFlightNumber())
        {
            bool successful = true;
            std::string status = "ended";
            realFlight.setSuccessful(successful);
            realFlight.setStatus(status);

            for (auto &flightAstronaut : realFlight.getAstronauts())
            {
                std::string status = "available";
                flightAstronaut.setStatus(status);

                Astronaut::setAvailableAstronaut(flightAstronaut.getCpf());
            }
        }
    }
}

void Flight::launchFlight()
{
    Flight flight = Flight::selectFlight("planning");

    if (flight.getAstronauts().empty())
    {
        cout << "Deve haver ao menos 1 astronauta para o lançamento";
        return;
    }

    for (auto &astronaut : flight.getAstronauts())
    {
        if (astronaut.getStatus() == "unavailable")
        {
            cout << "Existem astronautas indisponíveis neste voo";
            return;
        }
    }

    for (auto &realFlight : flights)
    {
        if (flight.getFlightNumber() == realFlight.getFlightNumber())
        {
            std::string status = "inProgress";
            realFlight.setStatus(status);

            for (auto &flightAstronaut : realFlight.getAstronauts())
            {
                std::string status = "inProgress";
                flightAstronaut.setStatus(status);

                Astronaut::setUnavailableAstronaut(flightAstronaut.getCpf());
            }
        }
    }
}

void Flight::setStatus(std::string &status)
{
    this->status = status;
}

void Flight::setSuccessful(bool &successful)
{
    this->successful = successful;
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