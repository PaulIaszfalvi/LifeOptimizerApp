#include <iostream>
#include <vector>
using namespace std;

class TellersSickDays {
private:
    vector<vector<int> > sickDays;

public:
    TellersSickDays(int tellerCount) {
        sickDays.resize(tellerCount, vector<int>(3, 0));
        for (int i = 0; i < tellerCount; ++i) {
            cout << "Enter sick days for teller " << i + 1 << " for the last 3 years:\n";
            for (int j = 0; j < 3; ++j) {
                cout << "Year " << j + 1 << ": ";
                cin >> sickDays[i][j];
            }
        }
    }

    void displaySickDays() const {
        for (size_t i = 0; i < sickDays.size(); ++i) {
            cout << "Teller " << i + 1 << " sick days:\n";
            for (int j = 0; j < 3; ++j) {
                cout << "Year " << j + 1 << ": " << sickDays[i][j] << "\n";
            }
        }
    }
};

int main() {
    int tellerCount;
    cout << "Enter the number of tellers: ";
    cin >> tellerCount;

    TellersSickDays tellers(tellerCount);
    tellers.displaySickDays();

    return 0;
}