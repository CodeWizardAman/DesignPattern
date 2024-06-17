#include <iostream>

using namespace std;

class TDC {

private:
	static TDC* instance_;

	TDC(){}
	TDC(const TDC& other) = delete;
	TDC& operator=(const TDC& other) = delete;

public:
	static TDC* getInstance() {
		if (instance_ == nullptr) {
			instance_ = new TDC();
		}
		return instance_;
	}

	void createSnapshot() {
		cout << "Snapshot Created" << endl;
	}

	void executeReport() {
		cout << "Report Executed" << endl;
	}
};

TDC* TDC::instance_ = nullptr;

int main() {
	TDC* tdc = TDC::getInstance();
	tdc->createSnapshot();
	tdc->executeReport();
}