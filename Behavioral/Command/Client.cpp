#include <iostream> 

// -----------------------------
// Command Interface
// -----------------------------
class ICommand {
public:
    virtual void execute() = 0;   // Perform the action
    virtual void undo() = 0;      // Revert the action
    virtual ~ICommand() {}
};

// -----------------------------
// Receiver (Light)
// -----------------------------
class Light {
public:
    // Actual operations performed by the Receiver
    void turnOn() {
        std::cout << "Light is ON\n";
    }

    void turnOff() {
        std::cout << "Light is OFF\n";
    }
};

// -----------------------------
// Concrete Command (LightOnCommand)
// -----------------------------
class LightOnCommand : public ICommand {
private:
    Light* light_;   // Reference to the Receiver

public:
    // Constructor binds the command to a specific Light
    LightOnCommand(Light* light) : light_(light) {}

    // Execute action → calls Receiver's method
    void execute() override {
        light_->turnOn();
    }

    // Undo action → reverses Receiver's method
    void undo() override {
        light_->turnOff();
    }
};

// -----------------------------
// Invoker (RemoteControl)
// -----------------------------
class RemoteControl {
private:
    ICommand* command_;   // Stores the current command

public:
    // Assign a command to the remote
    void setCommand(ICommand* command) {
        command_ = command;
    }

    // Trigger the command
    void pressButton() {
        command_->execute();
    }

    // Trigger undo of the command
    void pressUndo() {
        command_->undo();
    }
};

// -----------------------------
// Client (main function)
// -----------------------------
int main() {
    // Create Receiver
    Light livingRoomLight;

    // Create Concrete Command bound to Receiver
    LightOnCommand lightOn(&livingRoomLight);

    // Create Invoker and assign command
    RemoteControl remote;
    remote.setCommand(&lightOn);

    // Client triggers actions via Invoker
    remote.pressButton();  // Output: Light is ON
    remote.pressUndo();    // Output: Light is OFF

    return 0;
}