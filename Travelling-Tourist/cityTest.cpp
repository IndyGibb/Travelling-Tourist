#include "city.h"
#include <iostream>

using namespace std;

int main() {
    city city1("New York", 200);
    city city2("Los Angeles", 180);
    city city3("Chicago", 150);

    city1.addConnectedCity(city2);
    city1.addConnectedCity(city3);
    city2.addConnectedCity(city3);

    cout << "City Name: " << city1.getCityName() << ", Cost: " << city1.getCostToStay() << endl;
    cout << "City Name: " << city2.getCityName() << ", Cost: " << city2.getCostToStay() << endl;
    cout << "City Name: " << city3.getCityName() << ", Cost: " << city3.getCostToStay() << endl;

    cout << "Is Los Angeles connected to New York? " << (city1.isCityConnected(city2) ? "Yes" : "No") << endl;
    cout << "Is Chicago connected to New York? " << (city1.isCityConnected(city3) ? "Yes" : "No") << endl;
    cout << "Is there a common connection between New York and Los Angeles? "
         << (city1.isConnectedCityInCommon(city2) ? "Yes" : "No") << endl;

    return 0;
}
