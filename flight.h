#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
#include <vector>

class Astronaut;

class Flight
{
public:
    Flight(int flightNumber, const std::string &status, bool successful, const std::vector<Astronaut> &astronauts);

    static void createFlights();
    static void listFlights(const std::string &status);
    static void addAstronautToAFlight(int &flightNumber);
    static void removeAstronautToAFlight(int &flightNumber);
    static Flight selectFlightAvailable();
    static Flight findByNumber(int flightNumber);

    int getFlightNumber() const;
    std::string getStatus() const;
    bool getSucessful() const;
    std::vector<Astronaut> getAstronauts() const;

private:
    int flightNumber;
    std::string status;
    bool successful;
    std::vector<Astronaut> astronauts;
};

#endif
