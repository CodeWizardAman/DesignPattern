#include <iostream>

using namespace std;

class ILoggerStrategy {

public:
	
	virtual void log(const string& message) const = 0;

	virtual ~ILoggerStrategy() = default;
};

class XMLLoggerStrategy : public ILoggerStrategy {

public:
	void log(const string& msg) const override{
		cout << "Lets log following message in xml: " << msg << endl;
		cout << "Logged in xml" << endl;
	}
};

class TextLoggerStrategy : public ILoggerStrategy {

public:
	void log(const string &msg) const override {
		cout << "Lets log following message in text: " << msg << endl;
		cout << "Loggd in txt" << endl;
	}
};

class LoggerContext {
private:
	ILoggerStrategy* logger_strategy_;

public:
	LoggerContext(ILoggerStrategy* loggerStrategy = nullptr): logger_strategy_(loggerStrategy){}

	void log(const string& msg) {

		if (logger_strategy_) {
			logger_strategy_->log(msg);
		}
		else {
			throw std::runtime_error("logger strategy is not set");
		}
	}
};

static string readLoggerTypeFromJson(const std::string config) {

	//....logic to readLoggerType from Json
	string type = "TXT";

	return type;
}

class LoggerFactory {
public:
	static ILoggerStrategy* createLoggerStrategy(string type) {

		if (type == "XML") {
			return new XMLLoggerStrategy();
		}
		else if (type == "TXT") {
			return new TextLoggerStrategy();
		}
		else {
			throw std::invalid_argument("Unsupported logger type");
		}
	}
};

int main() {

	string configFile = "config.json";
	string loggerType = readLoggerTypeFromJson(configFile);

	ILoggerStrategy* logger_strategy = LoggerFactory::createLoggerStrategy(loggerType);

	LoggerContext loggerContext(logger_strategy);
	loggerContext.log("This is the log message");

	delete logger_strategy;

}