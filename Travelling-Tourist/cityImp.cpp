#include "city.h"

city::city() {
	cityName = "";
	costToStay = 0;
}

city::city(string name, double cost) {
	cityName = name;
	costToStay = cost;
}

void city::addConnectedCity(city newCity) {
	connectedCities.push_back(newCity);
}

string city::getCityName() {
	return cityName;
}

double city::getCostToStay() {
	return costToStay;
}

bool city::isCityConnected(string cityName) {
	for (int i = 0; i < connectedCities.size(); i++) {
		if (connectedCities[i].getCityName() == cityName) {
			return true;
		}
	}
	return false;
}

bool city::isCityConnected(city cityName) {
	return isCityConnected(cityName.getCityName());
}

bool city::isConnectedCityInCommon(city cityName) {
	for (int i = 0; i < connectedCities.size(); i++) {
		if (cityName.isCityConnected(connectedCities[i])) {
			return true;
		}
	}
	return false;
}