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
    Journey();
    void addDestination(const string& name, double cost, int travelTime);
    void displayJourney() const;
};

#endif
