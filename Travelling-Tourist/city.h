#pragma once
#ifndef CITY_H
#define CITY_H
#include <iostream>
#include <vector>

using std::string;
using std::vector;

class city {
public:
	city(); // default constructor
	city(string name, double cost); // constructor which takes in the name of the city and the cost to stay in it, and adds it to the city object
	
	void addConnectedCity(city newCity); // adds a city to the connectedCities vector
	string getCityName(); // returns cityName
	double getCostToStay(); // returns costToStay
	bool isCityConnected(string cityName); // returns true if the city name is in the connectedCities vector
	bool isCityConnected(city otherCity); // returns true if the cityName of otherCity is in connectedCities
	bool isConnectedCityInCommon(city otherCity); // returns true if any of the connectedCities of this city are in the connectedCities of otherCity
	

private:
	string cityName; // holds the name of this city
	double costToStay; // holds the name of the cost to stay in this city
	vector<city> connectedCities; // holds a list of cities that are connected to this city
};

#endif CITY_H