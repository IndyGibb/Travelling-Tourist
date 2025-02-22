#include "Journey.h"

Journey::Journey() : totalCost(0), totalTime(0) {}

void Journey::addDestination(const string& name, double cost, int travelTime) {
    route.push_back({ name, cost, travelTime });
    totalCost += cost;
    totalTime += travelTime;
}

void Journey::displayJourney() const {
    cout << "\nJourney Path:" << endl;
    for (const auto& dest : route) {
        cout << "  " << dest.name << " - Cost: $" << dest.cost << ", Travel Time: " << dest.travelTime << " hours" << endl;
    }
    cout << "Total Cost: $" << totalCost << endl;
    cout << "Total Travel Time: " << totalTime << " hours" << endl;
}
