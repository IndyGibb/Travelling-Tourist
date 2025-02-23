#ifndef JOURNEY_H
#define JOURNEY_H

#include <iostream>
#include <vector>
using namespace std;

class Journey {
private:
    struct Destination {
        string name;
        double cost;
        int travelTime;
    };

    vector<Destination> route;
    double totalCost;
    int totalTime;

public:
    // Checks if a city is already in the journey
    bool isCityInPath(const string& name) const;

    // Replaces a city in the journey with a new destination
    bool replaceCity(const string& oldName, const string& newName, double newCost, int newTravelTime);

    // Checks if adding a city exceeds max budget
    bool exceedsBudget(double newCost, double maxBudget) const;

    // Checks if adding travel time exceeds max time
    bool exceedsTime(int newTravelTime, int maxTime) const;
    Journey();
    void addDestination(const string& name, double cost, int travelTime);
    void displayJourney() const;
};

#endif
