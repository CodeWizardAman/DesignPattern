#include <memory.h>
#include <iostream>

// ===============================
// Abstract Expression (Base Class)
// ===============================
// Defines the common interface for all expressions.
// Every concrete expression must implement interpret().
class Expression {
public:
    virtual int interpret() = 0;
    virtual ~Expression() {}
};

// ===============================
// Terminal Expression: Number
// ===============================
// Represents leaf nodes in the syntax tree.
// Holds a constant integer value and simply returns it.
class Number : public Expression {
private:
    int value_;   // data part: the actual number

public:
    Number(int value) : value_(value) {}

    int interpret() override {
        return value_;  // terminal returns its stored value
    }
};

// ===============================
// Non-Terminal Expression: Add
// ===============================
// Represents grammar rule: Expression ::= Expression + Expression
// Holds references to left and right child expressions.
// Recursively calls interpret() on children and adds results.
class Add : public Expression {
private:
    std::shared_ptr<Expression> left_, right_; // object references

public:
    Add(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left_(left), right_(right) {
    }

    int interpret() override {
        return left_->interpret() + right_->interpret();
    }
};

// ===============================
// Non-Terminal Expression: Subtract
// ===============================
// Represents grammar rule: Expression ::= Expression - Expression
// Holds references to left and right child expressions.
// Recursively calls interpret() on children and subtracts results.
class Subtract : public Expression {
private:
    std::shared_ptr<Expression> left_, right_;

public:
    Subtract(std::shared_ptr<Expression> left, std::shared_ptr<Expression> right)
        : left_(left), right_(right) {
    }

    int interpret() override {
        return left_->interpret() - right_->interpret();
    }
};

// ===============================
// Client Code
// ===============================
int main() {
    // Expression: (5 + 3) - 2
    // Build the Abstract Syntax Tree (AST) object-wise.

    // Terminals (leaf nodes)
    auto five = std::make_shared<Number>(5);
    auto three = std::make_shared<Number>(3);
    auto two = std::make_shared<Number>(2);

    // Non-terminal: Add(Number(5), Number(3))
    auto addExpr = std::make_shared<Add>(five, three);

    // Non-terminal: Subtract(Add(...), Number(2))
    auto expr = std::make_shared<Subtract>(addExpr, two);

    // Recursively interpret the tree:
    // Subtract → calls Add → calls Number(5) & Number(3)
    // Result = (5 + 3) - 2 = 6
    std::cout << "Result: " << expr->interpret() << std::endl;
}
