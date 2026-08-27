#include <iostream>
#include <memory>
#include <string>
using namespace std;

// Mediator Interface
class Mediator {
public:
    virtual bool requestLanding(const string& flight) = 0;
    virtual void notifyLanded(const string& flight) = 0;
    virtual ~Mediator() {}
};

// Concrete Mediator
class ATCTower : public Mediator {
private:
    bool runwayFree = true;

public:
    bool requestLanding(const string& flight) override {
        if (runwayFree) {
            cout << "ATC: " << flight << " cleared to land.\n";
            runwayFree = false; // runway now occupied
            return true;
        }
        else {
            cout << "ATC: " << flight << " hold, runway busy.\n";
            return false;
        }
    }

    void notifyLanded(const string& flight) override {
        cout << "ATC: " << flight << " has landed. Runway free now.\n";
        runwayFree = true;
    }
};

// Colleague class: Aircraft
class Aircraft {
private:
    string flightNo_;
    shared_ptr<Mediator> atc_;
    bool canLand = false; // track clearance

public:
    Aircraft(string id, shared_ptr<Mediator> tower) : flightNo_(id), atc_(tower) {}

    void requestLanding() {
        canLand = atc_->requestLanding(flightNo_);
        if (canLand) {
            cout << flightNo_ << " waiting to land...\n";
        }
        else {
            cout << flightNo_ << " landing request denied. Runway busy\n";
        }
    }

    void land() {
        if (canLand) {
            cout << flightNo_ << " is landing...\n";
            atc_->notifyLanded(flightNo_);
            canLand = false; // reset after landing
        }
        else {
            cout << flightNo_ << " cannot land without clearance!\n";
        }
    }
};

// Client Code
int main() {
    auto tower = make_shared<ATCTower>();

    Aircraft flight1("Flight-101", tower);
    Aircraft flight2("Flight-202", tower);

    flight1.requestLanding();   // cleared, runway busy
    flight2.requestLanding();   // denied, runway busy
    flight1.land();             // Flight-101 lands, runway free
    flight2.requestLanding();   // now cleared
    flight2.land();             // Flight-202 lands

    return 0;
}
