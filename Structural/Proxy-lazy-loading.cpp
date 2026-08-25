#include <iostream>
#include <string>

// -----------------------------
// Subject Interface
// -----------------------------
class IImage {
public:
    virtual void display() = 0;
    virtual ~IImage() {}
};

// -----------------------------
// RealSubject (Heavy Object)
// -----------------------------
class RealImage : public IImage {
private:
    std::string filename;

    void loadFromDisk() {
        std::cout << "Loading image from disk: " << filename << "\n";
    }

public:
    RealImage(const std::string& file) : filename(file) {
        loadFromDisk(); // Expensive operation
    }

    void display() override {
        std::cout << "Displaying image: " << filename << "\n";
    }
};

// -----------------------------
// Proxy (Controls Access)
// -----------------------------
class ProxyImage : public IImage {
private:
    std::string filename;
    RealImage* realImage; // Lazy-loaded

public:
    ProxyImage(const std::string& file) : filename(file), realImage(nullptr) {}

    void display() override {
        // Lazy initialization: load only when needed
        if (realImage == nullptr) {
            realImage = new RealImage(filename);
        }
        std::cout << "[Proxy] Logging access to image...\n";
        realImage->display();
    }

    ~ProxyImage() {
        delete realImage;
    }
};

// -----------------------------
// Client
// -----------------------------
int main() {
    IImage* img = new ProxyImage("design_pattern.png");

    // First call → loads from disk
    img->display();

    // Second call → uses cached RealImage
    img->display();

    delete img;
    return 0;
}
