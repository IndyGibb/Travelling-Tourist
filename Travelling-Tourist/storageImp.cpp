#include "storage.h"
#include <iostream>
#include <iomanip>

using std::string;
using std::vector;

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
void storage::getRoad(int a) {
	return roadV<a>;
}
void storage::getCity(int b) {
	return cityV<b>;
}

void storage::inputCity(city newCity) {
	cityV.push_back(newCity);
    return;

}

void storage::inputRoad(road newRoad) {
    roadV.push_back(newRoad);
    return;
}