#include "storage.h"
#include <iostream>
#include <iomanip>

using std::string;
using std::vector;

int lineCounter(const string fileName) {
    int number_of_lines = 0;
    string line;
    std::ifstream infile(fileName);

    while (std::getline(infile, line))
        ++number_of_lines;
    std::cout << "Number of lines in text file: " << number_of_lines;
    lines = number_of_lines;

    return number_of_lines;
}
void getRoad(int a) {
	return roadV<a>;
}
void getCity(int b) {
	return cityV<b>;
}

void inputCities() {
    string cityname;
    double cost, 
    for (int i = 0; i < lines; i++) {
        std::cin >> cityname >> cost;
        cityV<i> = city(cityname, cost);
    }
    //how to tell apart city lines and road lines??????
    //it doesn't look like much but this is the grand result of 5+ hours of trying to figure out how to do this while visual studio keeps crashing and taking progress away

}

void inputRoads() {

}