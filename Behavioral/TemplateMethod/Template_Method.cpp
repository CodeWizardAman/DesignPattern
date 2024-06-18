#include <string>
#include <iostream>

using namespace std;

class QueryBuilder {

public:
	virtual ~QueryBuilder() = default;

	virtual string createInsertQuery(const string& tableName, const string& colName, const string& value) = 0;
};

class PostgresQueryBuilder : public QueryBuilder {

public:
	string createInsertQuery(const string& tableName, const string& colName, const string& value) override {
		cout << "created query" << endl;
		string query = "";
		return query ;
	}

};

class PersistentManager {

private:
	QueryBuilder* queryBuilder_;

protected:
	// Abstract steps of alogirthm

	virtual std::string prepareData(const string& data) = 0;
	virtual bool validateQuery(const string& query) = 0;
	virtual void executeQuery(const string& query) = 0;

public:
	PersistentManager(QueryBuilder *builder): queryBuilder_(builder){}

	virtual ~PersistentManager() = default;

	void persistInsert(const string& table, const string& col, const string& value) {
		string preparedValue = prepareData(value);
		string query = queryBuilder_->createInsertQuery(table, col, preparedValue);

		if (validateQuery(query)) {
			executeQuery(query);
		}
		else {
			throw std::runtime_error("Invalid query: " + query);
		}
	}

};

class PostgresPersistenceManager : public PersistentManager {

public:
	PostgresPersistenceManager(QueryBuilder* queryBuilder): PersistentManager(queryBuilder){}

protected:
	string prepareData(const string& data) override {
		cout << "Data Preparation Step" << endl;
		return data;
	}

	bool validateQuery(const string& query) override {
		cout << "Query Validation step" << endl;
		return true;
	}

	void executeQuery(const string& query) override {
		cout << "Executing Query" << endl;
	}
};

enum class DbType {
	PostGres,
	SQLite
};

class PersistenceManagerFactory {
public:
	static PersistentManager* createPersistenceManager(DbType type) {

		switch (type) {
		case DbType::PostGres:
			cout << "factory method creates PostGresPersistnece Manager" << endl;
			return new PostgresPersistenceManager(new PostgresQueryBuilder());

		case DbType::SQLite:
			return new PostgresPersistenceManager(new PostgresQueryBuilder()); // Just for demo, we need to create SQLite

		default:
			throw std::invalid_argument("Unsupported Database type");
		}

	}

};

int main() {
	try{
		PersistentManager* persistenceManager = PersistenceManagerFactory::createPersistenceManager(DbType::PostGres);
		persistenceManager->persistInsert("Vehicle Info", "Vehicle Type", " Vehical Data");

		delete persistenceManager;
	}

	catch (const exception& ex) {
		cout << ex.what()<< endl;
	}
}