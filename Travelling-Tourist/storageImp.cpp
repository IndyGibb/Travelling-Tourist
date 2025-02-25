#include "storage.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <ctype.h>

using std::string;
using std::vector;
using namespace std;

storage::storage() {
    lines = 0;
	cout << "Storage created" << endl;
    return;
}

storage::~storage() {
	cout << "Storage was destroyed" << endl;
	return;
}

int storage::lineCounter(const string fileName) {
    int number_of_lines = 0;
    string line;
    std::ifstream infile(fileName);

    while (std::getline(infile, line))
        ++number_of_lines;
    std::cout << "Number of lines in text file: " << number_of_lines;
    lines = number_of_lines;

    return number_of_lines;
}
road& storage::getRoad(int a) {
	return roadV[a];
}

road& storage::getRoad(city cityA, city cityB) {
	int location = getRoadLocation(cityA, cityB);
    return getRoad(location);
}

city& storage::getCity(int b) {
	return cityV[b];
}

city& storage::getCity(string cityName) {
	int location = getCityLocation(cityName);
	return getCity(location);
}

void storage::inputCity(city newCity) {
	cityV.push_back(newCity);
    return;

}

void storage::inputRoad(road newRoad) {
    roadV.push_back(newRoad);
    return;
}

int storage::getCityLocation(string cityName) {
	for (int i = 0; i < cityV.size(); i++) {
		if (cityV[i].getCityName() == cityName) {
			return i;
		}
	}
	return -1;
}

int storage::getRoadLocation(city city1, city city2) {
    for (int i = 0; i < roadV.size(); i++) {
        if (roadV[i].getCity1().getCityName() == city1.getCityName() && roadV[i].getCity2().getCityName() == city2.getCityName()) {
            return i;
        }
    }
    return -1;
}
void storage::inputFile(string fileName) {
    ifstream fin(fileName);
    stringstream ss;
    string line, cityName, cityBName;
    char c;
    double cityCost, distance;
    getline(fin, line);
    ss << line;
    ss.ignore(9999, ',');
    ss.ignore(9999, ',');
    getline(ss, cityName);
    city newCity(cityName, 0);
    inputCity(newCity);
    do {
		
        getline(fin, line);
        ss.str("");
        ss.clear();
        ss << line;
        getline(ss, cityName, ',');
        c = ss.peek();
        if (isdigit(c)) {
            string strCityCost;
            getline(ss, strCityCost);
			cityCost = stod(strCityCost);
            city newCity(cityName, cityCost);
            inputCity(newCity);
        }

    
    
    } while (!fin.eof());
    fin.close();
    fin.open(fileName);
    getline(fin, line);
    do {
        getline(fin, line);
        ss.str("");
        ss.clear();
        ss << line;
        getline(ss, cityName, ',');
        c = ss.peek();
        if (isalpha(c)) {
            getline(ss, cityBName, ',');
			string strDistance;
            getline(ss, strDistance);
            distance = stod(strDistance);
            connectRoads(getCity(cityName), getCity(cityBName));
            road newRoad(getCity(cityName), getCity(cityBName), distance);
			inputRoad(newRoad);
        }
	} while (!fin.eof());
    fin.close();
    return;
}

void storage::connectRoads(city& city1, city& city2) {
    if (!city1.isCityConnected(city2)) {
        city1.addConnectedCity(city2);
    }
	if (!city2.isCityConnected(city1)) {
		city2.addConnectedCity(city1);
	}
	return;
}