#include <iostream>
#include <chrono> // For timing
using namespace std;

int main() {
    int n;

    cout << "Enter n: ";
    cin >> n;

    // Start measuring time for formula
    chrono::high_resolution_clock::time_point start_formula = chrono::high_resolution_clock::now();

    // Formula-based calculation
    int sum_formula = n * (n + 1) / 2;

    // Stop measuring time for formula
    chrono::high_resolution_clock::time_point stop_formula = chrono::high_resolution_clock::now();
    chrono::microseconds duration_formula = chrono::duration_cast<chrono::microseconds>(stop_formula - start_formula);

    // // Start measuring time for for-loop
    // chrono::high_resolution_clock::time_point start_loop = chrono::high_resolution_clock::now();

    // // Loop-based calculation
    // int sum_loop = 0;
    // for (int i = 1; i <= n; i++) {
    //     sum_loop += i;
    // }

    // // Stop measuring time for for-loop
    // chrono::high_resolution_clock::time_point stop_loop = chrono::high_resolution_clock::now();
    // chrono::microseconds duration_loop = chrono::duration_cast<chrono::microseconds>(stop_loop - start_loop);

    // Display results
    cout << "\nResults:\n";
    cout << "Formula result: " << sum_formula << " (calculated in " << duration_formula.count() << " microseconds)" << endl;
    //cout << "Loop result: " << sum_loop << " (calculated in " << duration_loop.count() << " microseconds)" << endl;

    return 0;
}
