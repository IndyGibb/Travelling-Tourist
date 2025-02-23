#ifndef ROAD_H
#define ROAD_H

#include <string>
#include "city.h"  // Include the city class

class road {
private:
    city city1;        // First city object
    city city2;        // Second city object
    double travelTime; // Time to travel between the cities in hours

public:
    // Constructor to initialize the road with two city objects and travel time
    Road(city c1, city c2, double time);

    // Getter for city1
    city getCity1() const;

    // Getter for city2
    city getCity2() const;

    // Getter for travel time
    double getTravelTime() const;

    // Method to display the road information
    void displayRoadInfo() const;

    // Check if the two cities are connected (directly)
    bool areCitiesConnected() const;
};

#endif // ROAD_H
