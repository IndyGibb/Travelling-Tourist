#include "Journey.h"

Journey::Journey() : totalCost(0), totalTime(0) {}

void Journey::addDestination(const string& name, double cost, int travelTime) {
    route.push_back({ name, cost, travelTime });
    totalCost += cost;
    totalTime += travelTime;
}

bool Journey::isCityInPath(const string& name) const {
    for (const auto& dest : route) {
        if (dest.name == name) {
            return true;
        }
    }
    return false;
}

bool Journey::replaceCity(const string& oldName, const string& newName, double newCost, int newTravelTime) {
    for (auto& dest : route) {
        if (dest.name == oldName) {
            totalCost = totalCost - dest.cost + newCost;
            totalTime = totalTime - dest.travelTime + newTravelTime;
            dest.name = newName;
            dest.cost = newCost;
            dest.travelTime = newTravelTime;
            return true;
        }
    }
    return false;
}

bool Journey::exceedsBudget(double newCost, double maxBudget) const {
    return (totalCost + newCost) > maxBudget;
}

bool Journey::exceedsTime(int newTravelTime, int maxTime) const {
    return (totalTime + newTravelTime) > maxTime;
}

void Journey::displayJourney() const {
    cout << "\nJourney Path:" << endl;
    for (const auto& dest : route) {
        cout << "  " << dest.name << " - Cost: $" << dest.cost << ", Travel Time: " << dest.travelTime << " hours" << endl;
    }
    cout << "Total Cost: $" << totalCost << endl;
    cout << "Total Travel Time: " << totalTime << " hours" << endl;
}
