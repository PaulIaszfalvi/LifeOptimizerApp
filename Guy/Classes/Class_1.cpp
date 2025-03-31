#include <iostream>
using namespace std;

// Base Class
class Vehicle {
public:
    int wheels;

    // Constructor
    Vehicle(int w) : wheels(w) {}

    // Virtual function for honking
    virtual void honk() {
        cout << "Vehicle beep!" << endl;
    }
};

// Derived Class (Single Inheritance)
class Car : public Vehicle {
public:
    string brand;

    // Constructor
    Car(string b, int w) : Vehicle(w), brand(b) {}

    // Method to display Car info
    void showInfo() {
        cout << "Brand: " << brand << ", Wheels: " << wheels << endl;
    }

    // Override honk function
    void honk() override {
        cout << "Car honk!" << endl;
    }
};

// Multiple Inheritance Example
class Engine {
public:
    void engineInfo() {
        cout << "This is a V8 engine." << endl;
    }
};

class Transmission {
public:
    void transmissionInfo() {
        cout << "This is an automatic transmission." << endl;
    }
};

// Car inherits from both Engine and Transmission
class CarWithFeatures : public Engine, public Transmission {
public:
    string brand;

    CarWithFeatures(string b) : brand(b) {}

    void showInfo() {
        cout << "Car brand: " << brand << endl;
    }
};

// Multilevel Inheritance Example
class SportsCar : public Car {
public:
    SportsCar(string b, int w) : Car(b, w) {}

    void showSportsCarInfo() {
        cout << "This is a sports car!" << endl;
    }
};

int main() {
    // Single Inheritance Example
    Car myCar("Toyota", 4);
    myCar.showInfo();  // Calls Car's function
    myCar.honk();      // Calls overridden honk function in Car

    cout << endl;

    // Multiple Inheritance Example
    CarWithFeatures myFeatureCar("Ford");
    myFeatureCar.engineInfo();      // Access Engine's function
    myFeatureCar.transmissionInfo(); // Access Transmission's function

    cout << endl;

    // Multilevel Inheritance Example
    SportsCar mySportsCar("Ferrari", 4);
    mySportsCar.showInfo();        // Calls Car's function
    mySportsCar.showSportsCarInfo(); // SportsCar's own method
    mySportsCar.honk();            // Calls overridden honk function in Car

    return 0;
}
