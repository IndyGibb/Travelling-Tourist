#pragma once
#ifndef CITY_H
#define CITY_H
#include <iostream>
#include <vector>

using std::string;
using std::vector;

class city {
public:
	city();
	city(string name, double cost);
	
	void addConnectedCity(city newCity);
	string getCityName();
	double getCostToStay();
	bool isCityConnected(string cityName);
	bool isCityConnected(city cityName);
	bool isConnectedCityInCommon(city cityName);
	

private:
	string cityName;
	double costToStay;
	vector<city> connectedCities;
};

#endif CITY_H