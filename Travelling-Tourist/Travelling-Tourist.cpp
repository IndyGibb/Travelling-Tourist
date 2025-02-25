#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "Journey.h"
#include "city.h"
#include "road.h"
#include "storage.h"
#include <sstream>

//WHAT I STILL NEED: A function to detect if cities are connected and a function to get the name of the city.
//I wasn't sure if that function should be in city or in storage. isCityConnected and getCityName were used as placeholders. 
//I had to use unordered map to utilize the code that I referenced.

const int INF = 999999;  // Large value representing infinity
const int MAX_TRAVEL_HOURS = 8;
const int EXTRA_NIGHT_COST = 100;

using namespace std;

// Function to find the next city with the shortest travel time
int findMinDistanceCity(const vector<int>& time, const vector<bool>& visited) {
    int minTime = INF, minIndex = -1;
    for (int i = 0; i < time.size(); ++i) {
        if (!visited[i] && time[i] < minTime) {
            minTime = time[i];
            minIndex = i;
        }
    }
    return minIndex;
}

// Dijkstra's algorithm utilizing the Journey, city, and road class
void dijkstra(city& startCity, double maxBudget, double maxDays, storage& storageObj) {
    vector<city> cities = { startCity };  // Start city
    vector<road> roads;  // Roads between cities
    Journey journey;
    unordered_map<string, int> cityIndex;  // Map city names to indices

    cityIndex[startCity.getCityName()] = 0;
    journey.addDestination(startCity.getCityName(), startCity.getCostToStay(), 0);

    // Collect all cities and their connections
    for (int i = 0; i < cities.size(); ++i) {
        for (auto& connectedCity : cities[i].getConnectedCities()) {
            if (cityIndex.find(storageObj.getCity(connectedCity).getCityName()) == cityIndex.end()) {
                cityIndex[storageObj.getCity(connectedCity).getCityName()] = cities.size();
                cities.push_back(storageObj.getCity(connectedCity));
                roads.push_back(road(cities[i], storageObj.getCity(connectedCity), storageObj.getRoad(cities[i], storageObj.getCity(connectedCity)).getTravelTime())); // Example: 8 hours of travel
            }
        }
    }

    int n = cities.size();
    vector<int> minTime(n, INF);
    vector<double> totalCost(n, INF);
    vector<bool> visited(n, false);
    vector<int> previous(n, -1); // To track path

    // Initialize the starting city's values
    minTime[0] = 0;
    totalCost[0] = startCity.getCostToStay();

    for (int count = 0; count < n - 1; ++count) {
        int city = findMinDistanceCity(minTime, visited);
        if (city == -1) break;

        visited[city] = true;

        for (int neighbor = 0; neighbor < n; ++neighbor) {
            if (cities[city].isCityConnected(cities[neighbor]) && !visited[neighbor]) {
                // Find the road between cities
                for (const road& r : roads) {
                    if ((r.getCity1().getCityName() == cities[city].getCityName() && r.getCity2().getCityName() == cities[neighbor].getCityName()) ||
                        (r.getCity1().getCityName() == cities[neighbor].getCityName() && r.getCity2().getCityName() == cities[city].getCityName())) {

                        int travelHours = r.getTravelTime();
                        int extraNights = (travelHours - 1) / MAX_TRAVEL_HOURS; // Extra nights if travel > 8 hrs
                        int newTime = minTime[city] + travelHours;
                        double newCost = totalCost[city] + cities[neighbor].getCostToStay() + (extraNights * EXTRA_NIGHT_COST);

                        if (newTime < minTime[neighbor] && !journey.exceedsBudget(newCost, maxBudget) && !journey.exceedsTime(newTime, maxDays * 24)) {
                            minTime[neighbor] = newTime;
                            totalCost[neighbor] = newCost;
                            previous[neighbor] = city;

                            journey.addDestination(cities[neighbor].getCityName(), cities[neighbor].getCostToStay(), travelHours);
                        }
                    }
                }
            }
        }
    }

    // Display the results
    journey.displayJourney();
}

string getStartCity(string filename) {
    ifstream fin(filename);
    string line;
	getline(fin, line);
	stringstream ss(line);
	string startCity;
    ss.ignore(999, ',');
	ss.ignore(999, ',');
	ss >> startCity;
	return startCity;
}

double getBudget(string filename) {
    ifstream fin(filename);
    string line;
    getline(fin, line);
    stringstream ss(line);
    string budget;
    ss.ignore(999, ',');
    getline(ss, budget, ',');
    double budgetD = stod(budget);
    return budgetD;
}

double getMaxDays(string filename) {
    ifstream fin(filename);
    string line;
    getline(fin, line);
    stringstream ss(line);
    string maxDays;
    getline(ss, maxDays, ',');
	double maxDaysD = stod(maxDays);
	return maxDaysD;
}

int main() {
    storage storageObj;
    string filename;
    cout << "Insert file name: ";
    cin >> filename;
    storageObj.inputFile(filename); // INPUTFILE NEEDS TO BE MADE

    // Example input: New York city will be used as the starting point
    city startCity = storageObj.getCity(getStartCity(filename));

    double maxBudget = getBudget(filename);
    double maxDays = getMaxDays(filename);

    // Start the journey optimization
    dijkstra(startCity, maxBudget, maxDays, storageObj);

    return 0;
}
