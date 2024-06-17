#include <iostream>
#include <mutex>

using namespace std;

class TDC {

private:

	static TDC* instance_;
	static mutex muxtex_;

    TDC(){}

	TDC(const TDC& other) = delete;
	TDC& operator=(const TDC& other) = delete;

public:

	static TDC* getInstance() {
		lock_guard<mutex> lock(muxtex_);
		if (instance_ == nullptr) {
			
				instance_ = new TDC();
		}
		return instance_;

	}

	void createSnapshot() {
		cout << "Snasphot Created" << endl;
	}

	void executeReport() {
		cout << "Report Created" << endl;
	}
};

TDC* TDC::instance_ = nullptr;
mutex TDC::muxtex_;

int main() {

	TDC* tdc = TDC::getInstance();
	
	tdc->createSnapshot();
	tdc->executeReport();
}