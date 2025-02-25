// FinalProject.cpp : This program reads in a list of destinations, their costs, and travel times
// between them, and outputs the route that visits the most destinations within a given cost and
// time budget.

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
using namespace std;

int num_destinations = 0;
const int max_destinations = 15, max_connections = max_destinations - 1;
string destination[max_destinations], connection[max_destinations][max_connections];  // list of connections for each of the destinations
double destination_cost[max_destinations], travel_time[max_destinations][max_connections];
int num_connections[max_destinations];  // for each destination, how many other places can you get to
string best_route[max_destinations];
double best_cost[max_destinations];
int best_time[max_destinations];
int best_route_length = 0;

int read_one_line(ifstream& file, string& dest1, string& dest2, double& num) {
    string s;
    int first_comma, second_comma, num_items = 2;
    num = sqrt(-1);
    getline(file, s);
    first_comma = s.find(',');
    dest1 = s.substr(0, first_comma);
    second_comma = s.find(',', first_comma + 1);
    if (second_comma > first_comma) {
        dest2 = s.substr(first_comma + 1, second_comma - first_comma - 1);
        num = stod(s.substr(second_comma + 1, s.length() - second_comma - 1));
        num_items++;
    }
    else {
        num = stod(s.substr(first_comma + 1, s.length() - first_comma - 1));
    }
    return num_items;
}

int found(const string item, const string list[], const int length) {
    for (int i = 0; i < length; i++) {
        if (list[i] == item) { return i; }
    }
    return -1;
}

void display_route(const string list[], const double cost[], const int time[], const int length,
                   const bool final = false) {
    double total_cost = 0, total_time = 0;
    cout << "\nHere's " << (final ? "the best" : "a") << " route:\n";
    for (int i = 1; i < length; i++) {
        int from_index = found(list[i - 1], destination, num_destinations);
        cout << "  $" << cost[i] << "  from " << list[i - 1] << " to " << list[i] << " (";
        // Find out which column in the 2D array is for the given destination.
        for (int j = 0; j < num_connections[from_index]; j++) {
            if (connection[from_index][j] == list[i]) {
                cout << travel_time[from_index][j];
                break;
            }
        }
        cout << " hours)\n";
        total_cost += cost[i];
        total_time += time[i];
    }

    if (final) {
        cout << "Total cost: $" << total_cost << endl;
        cout << "Total time: " << total_time << " days\n";
    }
}

bool better_route(const int length) {
    return length > best_route_length;
}

void copy_route(const string list[], const double cost[], const int time[], const int length) {
    for (int i = 0; i < length; i++) {
        best_route[i] = list[i];
        best_cost[i] = cost[i];
        best_time[i] = time[i];
    }
    best_route_length = length;
}

void find_route(string dest_list[], double cost_list[], int time_list[], const int original_length,
                const double remaining_budget, const int remaining_days) {
    bool added_to_route = false;
    int from_index = found(dest_list[original_length - 1], destination, num_destinations);
    for (int i = 0; i < num_connections[from_index]; i++) {
        int length = original_length;
        string to = connection[from_index][i];
        int to_index = found(to, destination, num_destinations);
        int extra_days = travel_time[from_index][i] / 8;
        int days = remaining_days - extra_days;
        double budget = remaining_budget - destination_cost[to_index] - extra_days * 100;
        if (travel_time[from_index][i] > extra_days * 8) {
            days--;
        }
        else { budget += 100; }
        if (budget >= 0 && days >= 0 && found(to, dest_list, length) < 0) {
            dest_list[length] = to;
            cost_list[length] = remaining_budget - budget;
            time_list[length++] = remaining_days - days;
            find_route(dest_list, cost_list, time_list, length, budget, days);
            added_to_route = true;
        }
    }

    if (!added_to_route && original_length > 1) {
        // Since no destination could be added to the route that was passed in
        // when this function was called, we have a candidate for the best route.
        display_route(dest_list, cost_list, time_list, original_length);
        if (better_route(original_length)) {
            if (best_route_length > 0) {
                cout << "This is a better route!\n";
            }
            else {
                cout << "This is the first route I've found.\n";
            }
            copy_route(dest_list, cost_list, time_list, original_length);
        }
    }
}

int mainx()
{
    string input_file_name, starting_location, from, to;
    string route[max_destinations];
    double cost[max_destinations];
    int time[max_destinations];
    int days, start_index, route_length = 0;
    double budget, num;
    char comma;
    for (int i = 0; i < max_destinations; i++) {
        num_connections[i] = 0;
    }

    cout << "Hello!  What input file would you like to use? ";
    getline(cin, input_file_name);
    ifstream input_file;
    input_file.open(input_file_name);
    if (!input_file) {
        cout << "Unable to open file \"" << input_file_name << "\"\n";
        return -1;
    }

    input_file >> days >> comma >> budget >> comma >> starting_location;
    cout << "Starting on a trip of " << days << " days from " << starting_location << " with a budget of $" << budget << endl;
    destination[num_destinations] = starting_location;
    destination_cost[num_destinations++] = 0;
    input_file.ignore(9999, '\n');

    while (!input_file.eof()) {
        int items_read = read_one_line(input_file, from, to, num);
        int index = found(from, destination, num_destinations);
        if (index < 0) {
            if (num_destinations >= max_destinations) {
                cout << "There are too many destinations!\n";
                return -1;
            }
            index = num_destinations++;
            destination[index] = from;
        }
        if (2 == items_read) {
            cout << "The cost of accommodations at " << from << " is $" << num << endl;
            destination_cost[index] = num;
        }
        else {
            cout << "It takes " << num << " hours to travel from " << from << " to " << to << endl;
            if (found(to, destination, num_destinations) < 0) {
                if (num_destinations >= max_destinations) {
                    cout << "There are too many destinations!\n";
                    return -1;
                }
                destination[num_destinations++] = to;
            }
            travel_time[index][num_connections[index]] = num;
            connection[index][num_connections[index]++] = to;
        }
    }

    cout << "Here are the destinations and their costs:\n";
    for (int i = 0; i < num_destinations; i++) {
        cout << "   $" << destination_cost[i] << "  " << destination[i] << endl;
    }
    cout << "Here are the connections between destinations and their corresponding travel times:\n";
    for (int i = 0; i < num_destinations; i++) {
        cout << "   From " << destination[i] << ":\n";
        for (int j = 0; j < num_connections[i]; j++) {
            cout << "      " << connection[i][j] << "  " << travel_time[i][j] << " hours\n";
        }
    }

    start_index = found(starting_location, destination, num_destinations);  // start_index should be zero
    route_length = 0;
    route[route_length] = destination[start_index];  // destination[start_index] == starting_location
    cost[route_length] = 0;
    time[route_length++] = 0;
    find_route(route, cost, time, route_length, budget, days);
    display_route(best_route, best_cost, best_time, best_route_length, true);
    return 0;
}