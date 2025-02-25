// City Class Implimentation File created by: Andrew Gibbons, 2025

#include "city.h"
#include <iostream>

using namespace std;

city::city() {
	cityName = "";
	costToStay = 0;
	cout << "Default city created" << endl;
}

city::~city() {
	cout << "City " << cityName << " was bombed" << endl;
}

city::city(string name, double cost) {
	cityName = name;
	costToStay = cost;
	cout << "City " << cityName << " created with cost " << costToStay << endl;
}

void city::addConnectedCity(city newCity) {
	if (!isCityConnected(newCity.getCityName())) {
		connectedCities.push_back(newCity.getCityName());
	}
}

string city::getCityName() const {
	return cityName;
}

double city::getCostToStay() const {
	return costToStay;
}

bool city::isCityConnected(string cityName) const {
	for (int i = 0; i < connectedCities.size(); i++) {
		if (connectedCities[i] == cityName) {
			return true;
		}
	}
	return false;
}

bool city::isCityConnected(city otherCity) const {
	return isCityConnected(otherCity.getCityName());
}

bool city::isConnectedCityInCommon(city otherCity) const {
	for (int i = 0; i < connectedCities.size(); i++) {
		if (otherCity.isCityConnected(connectedCities[i])) {
			return true;
		}
	}
	return false;
}