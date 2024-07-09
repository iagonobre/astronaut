#ifndef ASTRONAUT_H
#define ASTRONAUT_H

#include <string>
#include <vector>

class Flight;

class Astronaut
{
public:
    Astronaut(const std::string &cpf, const std::string &name, int age, const std::string &status, const std::vector<Flight> &flights);

    static void createAstronauts();
    static void listAstronauts(const std::string &status);
    static Astronaut findByCPF(const std::string &cpf);
    static std::vector<Astronaut> selectAstronautsAvailable();
    static void addFlighToAAstronaut(Astronaut &astronaut, Flight &flight);
    static void removeFlighToAAstronaut(Astronaut &astronaut, Flight &flight);

    std::string getCpf() const;
    std::string getName() const;
    int getAge() const;
    std::string getStatus() const;
    std::vector<Flight> getFlights() const;

    void setFlight(Flight &flight);
    void removeFlight(Flight &flight);

private:
    std::string cpf;
    std::string name;
    int age;
    std::string status;
    std::vector<Flight> flights;
};

#endif
