#pragma once
#ifndef STORAGE_H
#define STORAGE_H
#include <iostream>
#include <vector>
#include <iomanip>
#include "city.h"
#include "road.h"
#include <fstream>
#include <sstream>

using std::string;
using std::vector;

class storage {
public:
	storage(); //default constructor
	~storage();

	void inputCity(city newCity); // Function to input a city into a vector
	void inputRoad(road newRoad); // Function to input a road into a vector
	city getCity(int); // Function to return cities.
	city getCity(string cityName);
	road getRoad(int); // Function to return roads.
	road getRoad(city city1, city city2);
	int lineCounter(const string); // Function to count the # of lines in the file.
	void inputFile(string); // Function to input data from a file

private:
	vector<city> cityV; // vector of all the cities
	vector<road> roadV; // Vector of all the roads
	int lines; // Number of lines in the file.
	int getCityLocation(string cityName); // Function to get the location of a city in the vector.
	int getRoadLocation(city city1, city city2); // Function to get the location of a road in the vector.
};

#endif // STORAGE_H