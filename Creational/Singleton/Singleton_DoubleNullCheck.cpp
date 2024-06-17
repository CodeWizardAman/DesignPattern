#include <iostream>
#include <mutex>

using namespace std; 

class TDC {
	
private:
	static TDC* instance_;
	static mutex mutex_;

	TDC(){}
	~TDC(){}

	TDC(const TDC& other) = delete;

	TDC* operator=(const TDC& other) = delete;

public:

	static TDC* getInstance() {
		if (instance_ == nullptr) {

			// T1 and T2 both entered, T2 few millseconds after T1, T1 acquired lock, instantiates TDC
			// releases lock, now T2 acquires and if no null condition provided below, new instance will be created
			// to restrict this 2nd null check added.

			lock_guard<mutex> lock(mutex_);

			if (instance_ == nullptr) {

				instance_ = new TDC();
			}
		}
		return instance_;
	}

	void createSnapshot() {
		cout << "Create Snapshot" << endl;
	}

	void executeCompareReport() {
		cout << "Execute Compare Report" << endl;
	}

};

TDC* TDC::instance_ = nullptr;
mutex TDC::mutex_;

int main() {

	TDC* tdc = TDC::getInstance();
	tdc->createSnapshot();
	tdc->executeCompareReport();
}