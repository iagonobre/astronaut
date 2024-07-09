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
    static void removeAstronautToAFlight();
    static void explodeFlight();
    static void endFlight();
    static void launchFlight();
    static Flight selectFlight(const std::string &status);
    static Flight findByNumber(int flightNumber);
    static void changeAstronautsInAFlight(int &flightNumber, std::vector<Astronaut> &astronauts);

    int getFlightNumber() const;
    std::string getStatus() const;
    bool getSucessful() const;
    std::vector<Astronaut> getAstronauts() const;

    void setStatus(std::string &status);
    void setSuccessful(bool &successful);

private:
    int flightNumber;
    std::string status;
    bool successful;
    std::vector<Astronaut> astronauts;
};

#endif
