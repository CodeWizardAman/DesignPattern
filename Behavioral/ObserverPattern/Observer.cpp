#include <iostream>
#include <vector>

using namespace std;
// Observer interface defines the update() method 
// which will be called when the subject changes.
class Observer {
public:
	virtual ~Observer() = default;
	virtual void update() = 0;
};

// Subject interface correctly defines methods 
// to register, remove, and notify observers
class Subject {

public:
	
	virtual ~Subject() = default;
	virtual void registerObserver(Observer* observer)=0;
	virtual void removeObserver(Observer* observer) = 0;
	virtual void notifyObservers() = 0;

};

class VitalSignsMonitor : public Subject {

private:
	std::vector<Observer*> observers_;
	float heartRate_;
	float bloodPressure_;

public:
	void setVitals(float hRate, float bp) {
		heartRate_ = hRate;
		bloodPressure_ = bp;
		notifyObservers();
	}

	float getHeartRate() const { return heartRate_; }
	float getBloodPressuere() const { return bloodPressure_; }

	void registerObserver(Observer* observer) override {
		observers_.emplace_back(observer);
	}

	void removeObserver(Observer* observer) override {
		observers_.erase(std::remove(observers_.begin(), observers_.end(), observer));
	}

	void notifyObservers() override {
		for (Observer* observer : observers_) {
			observer->update();
		}
	}
};

class HealthCareProvider : public Observer {
private:
	string name_;
	VitalSignsMonitor& monitor_;

public:
	HealthCareProvider(VitalSignsMonitor& monitor, string name) : monitor_(monitor), name_(name)
	{
		monitor.registerObserver(this);
	}

	~HealthCareProvider() {
		monitor_.removeObserver(this);
	}

	void update() override {
		float heartRate_ = monitor_.getHeartRate();
		float bloodPressure_ = monitor_.getBloodPressuere();
		
		std::cout << "Update Vitals to " << name_ << "----------" << endl;
		std::cout << "Heart rate " << heartRate_ << endl;
		std::cout << "Blood Pressure: " << bloodPressure_ << endl;
	}
};

int main() {
	VitalSignsMonitor monitor;

	HealthCareProvider doctor(monitor, "Doctor");
	HealthCareProvider nurse(monitor, "Nurse");

	monitor.setVitals(75, 120);
	monitor.setVitals(89, 130);


}