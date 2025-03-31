#include <iostream>
#include <cmath> // For exp()
using namespace std;

int main() {
    double initial_pop, growth_rate;
    int days;

    // Input: Initial population, growth rate, and number of days
    cout << "Enter the initial population, daily growth rate (in %), and number of days: ";
    cin >> initial_pop >> growth_rate >> days;

    // Output population for each day
    for (int i = 0; i <= days; i++) {
        // Calculate population for day i using continuous growth formula
        double pop = initial_pop * exp((growth_rate / 100.0) * i);
        cout << "Day " << i << ": " << pop << endl;
    }

    return 0;
}
