#include "astronaut.h"
#include "flight.h"
#include "utils.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

std::vector<Astronaut> astronauts;

Astronaut::Astronaut(const std::string &cpf, const std::string &name, int age, const std::string &status, const std::vector<Flight> &flights)
    : cpf(cpf), name(name), age(age), status(status), flights(flights) {}

void Astronaut::createAstronauts()
{
    std::string cpf, name;
    int age;

    cout << "-=-=-=- Criar Astronauta -=-=-=-" << endl;
    cout << "Digite o CPF:" << endl;
    cout << ">> ";
    cin >> cpf;
    cout << "Digite o Nome:" << endl;
    std::cin.ignore();
    cout << ">> ";
    std::getline(std::cin, name);
    cout << "Digite a Idade:" << endl;
    cout << ">> ";
    cin >> age;

    Astronaut isAvailable = findByCPF(cpf);

    if (cpf == "0" || cpf == "")
    {
        cout << "Você deve fornecer um CPF válido. Tente novamente!" << endl;
    }

    if (isAvailable.getCpf() == cpf)
    {
        cout << "Já existe um usuário com este CPF. Tente novamente!" << endl;
        return;
    }

    const Astronaut astronaut(cpf, name, age, "available", {});

    astronauts.push_back(astronaut);
}

void Astronaut::listAstronauts(const std::string &status)
{
    std::vector<Astronaut> foundAstronauts;

    for (const auto &astronaut : astronauts)
    {
        if (astronaut.getStatus() == status)
        {
            foundAstronauts.push_back(astronaut);
        }
    }

    if (foundAstronauts.empty())
    {
        cout << "Nenhum astronauta disponível!" << endl;
        return;
    }
    if (status == "available")
    {
        cout << "-=-=-=- Lista dos Astronautas Disponíveis -=-=-=-" << endl;
    }
    if (status == "unavailable")
    {
        cout << "-=-=-=- Lista dos Astronautas Indisponíveis -=-=-=-" << endl;
    }
    if (status == "dead")
    {
        cout << "-=-=-=- Lista dos Astronautas Mortos -=-=-=-" << endl;
    }

    cout << "|      Nome      |      CPF      | Idade |    Status    |" << endl;
    for (const auto &astronaut : foundAstronauts)
    {
        cout << "|   ";
        cout << astronaut.getName();
        cout << "   |   ";
        cout << astronaut.getCpf();
        cout << "   |   ";
        cout << astronaut.getAge();
        cout << "   |   ";
        cout << astronaut.getStatus();
        cout << "   |" << endl;

        if (!astronaut.flights.empty())
        {
            cout << "Voos realizados: ";
            for (const auto flight : astronaut.flights)
            {
                int flightNumber = flight.getFlightNumber();
                cout << flightNumber;
                if (astronaut.flights.size() > 1)
                {
                    cout << ", ";
                }
            }
            cout << endl
                 << endl;
        }
    }
}

Astronaut Astronaut::findByCPF(const std::string &cpf)
{
    for (auto &astronaut : astronauts)
    {
        if (astronaut.getCpf() == cpf)
        {
            return astronaut;
        }
    }
    return Astronaut("", "", 0, "", {});
}

std::vector<Astronaut> Astronaut::selectAstronautsAvailable()
{
    Astronaut::listAstronauts("available");
    cout << endl;

    std::string cpf;
    std::vector<Astronaut> astronauts;

    while (true)
    {
        cout << "Digite o CPF do astronauta que deseja selecionar:" << endl;
        cout << "[0] Encerrar operação com passageiros" << endl;
        cout << ">> ";

        std::cin.ignore();
        std::getline(std::cin, cpf);

        if (cpf == "0" || cpf == "")
        {
            break;
        }

        Astronaut foundAstronaut = Astronaut::findByCPF(cpf);

        if (foundAstronaut.getCpf() == "")
        {
            cout << "Astronauta não encontrado, tente novamente." << endl;
        }
        else if (foundAstronaut.getStatus() != "available")
        {
            cout << "Astronauta não disponível, tente novamente." << endl;
        }
        else
        {
            astronauts.push_back(foundAstronaut);
            cout << "Astronauta adicionado: " << foundAstronaut.getName() << endl;
        }
    }

    return astronauts;
}

void Astronaut::addFlighToAAstronaut(Astronaut &astronaut, Flight &flight)
{
    for (auto &currentAstronaut : astronauts)
    {
        if (currentAstronaut.getCpf() == astronaut.getCpf())
        {
            currentAstronaut.setFlight(flight);
            break;
        }
    }
}

void Astronaut::removeFlighToAAstronaut(Astronaut &astronaut, Flight &flight)
{
    for (auto &currentAstronaut : astronauts)
    {
        if (currentAstronaut.getCpf() == astronaut.getCpf())
        {
            currentAstronaut.removeFlight(flight);
            break;
        }
    }
}

void Astronaut::removeFlight(Flight &flight)
{
    std::vector<Flight> newFlights;

    for (auto &currentFlight : flights)
    {
        if (currentFlight.getFlightNumber() == flight.getFlightNumber())
        {
            continue;
        }
        else
        {
            newFlights.push_back(currentFlight);
        }
    }

    flights = newFlights;
    newFlights = {};
}

void Astronaut::setFlight(Flight &flight)
{
    flights.push_back(flight);
}

std::string Astronaut::getCpf() const
{
    return cpf;
}

std::string Astronaut::getName() const
{
    return name;
}

int Astronaut::getAge() const
{
    return age;
}

std::string Astronaut::getStatus() const
{
    return status;
}

std::vector<Flight> Astronaut::getFlights() const
{
    return flights;
}