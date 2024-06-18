#include <iostream>
#include <vector>

using namespace std;

class UINode {
public:
	virtual void display() const = 0;
	virtual ~UINode(){}
};

class DimensionNode : public UINode {

private:
	string dimensionName_;
	double value_;

public:

DimensionNode(const string& name, double value)
	: dimensionName_(name), value_(value){}

void display() const override {
	cout << "Dimension Name " << dimensionName_ << endl;
	cout << "Dimension Value " << value_ << endl;
}
};


class NotesNode : public UINode {
private:
	std::string title_;

public:
	NotesNode(const string& title): title_(title){}

	void display() const override {
		cout << "Note: " << title_ << endl;
	}
};

class CompositeNode : public UINode {

private:
	string name_;
	std::vector<UINode*> nodes;

public:
	CompositeNode(const string& name): name_(name){}

	~CompositeNode() {
		for (const auto& node : nodes) {
			delete node;
		}
		nodes.clear();
	}
	
	void addNode(UINode* node) {
		nodes.emplace_back(node);
	}

	void display() const override {
		cout << name_ <<"--->"<<endl;
		
		for (const auto& node : nodes) {
			node->display();
		}
	}
};

int main() {


	CompositeNode rootNode("TDC");
	CompositeNode* measurementsNode = new CompositeNode("Measurements");
	CompositeNode* annotationNode = new CompositeNode("Annotation");

	measurementsNode->addNode(new DimensionNode("Length", 12));
	measurementsNode->addNode(new DimensionNode("Width", 9));

	annotationNode->addNode(new NotesNode("All is well"));
	annotationNode->addNode(new NotesNode("Status"));

	rootNode.addNode(measurementsNode);
	rootNode.addNode(annotationNode);

	rootNode.display();

	return 0;
}