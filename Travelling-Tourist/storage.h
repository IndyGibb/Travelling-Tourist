#pragma once
#ifndef STORAGE_H
#define STORAGE_H
#include <iostream>
#include <vector>
#include <iomanip>
#include "city.h"
#include "road.h"

using std::string;
using std::vector;

class storage {
public:
	storage(); //default constructor

	void inputCity(city newCity);// Function to imput a city into a vector
	void inputRoad(road newRoad);// Function to input a road into a vector
	void getCity(int); //Function to return cities.
	void getRoad(int); //Function to return roads.
	int lineCounter(const string); //Function to count the # of lines in the file.

	
private:
	vector<city> cityV; //vector of all the cities
	vector<road> roadV; //Vector of all the roads
	int lines; //Number of lines in the file.


};