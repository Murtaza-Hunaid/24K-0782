#include <iostream>
using namespace std;

class GraphicsEngine {
public:
    void render() {
        cout << "Rendering graphics" << endl;
    }
};

class InputHandler {
public:
    void processInput() {
        cout << "Processing user input" << endl;
    }
};

class PhysicsEngine {
public:
    void updatePhysics() {
        cout << "Updating physics" << endl;
    }
};

class GameEngine {
private:
    GraphicsEngine graphics;
    InputHandler input;
    PhysicsEngine physics;

public:
    void run() {
        cout << "Game engine starting:\n" << endl;
        input.processInput();
        physics.updatePhysics();
        graphics.render();
        cout << "\nGame engine running" << endl;
    }
};

int main() {
    GameEngine game;
    game.run();
    return 0;
}
