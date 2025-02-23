#include "road.h"    // Include the Road header file
#include <iostream>

// Constructor to initialize the road with two city objects and travel time
road::road(city c1, city c2, double time)
    : city1(c1), city2(c2), travelTime(time) {}

// Getter for city1
city road::getCity1() const {
    return city1;
}

// Getter for city2
city road::getCity2() const {
    return city2;
}

// Getter for travel time
double road::getTravelTime() const {
    return travelTime;
}

// Method to display the road information
void road::displayRoadInfo() const {
    std::cout << "Road between " << city1.getCityName() << " and " << city2.getCityName()
              << " takes " << travelTime << " hours to travel." << std::endl;
}

// Check if the two cities are connected (directly)
bool road::areCitiesConnected() const {
    return city1.isCityConnected(city2);
}
