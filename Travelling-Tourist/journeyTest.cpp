#include "journey.h"
#include <iostream>

using namespace std;

int main() {
	Journey journey;
	journey.addDestination("Paris", 100, 2);
	journey.addDestination("London", 200, 3);
	journey.addDestination("New York", 300, 4);
	journey.displayJourney();
}