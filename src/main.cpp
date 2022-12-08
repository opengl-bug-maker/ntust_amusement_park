#include "GameWindow.h"

int main() {
    GameWindow win = GameWindow(sf::VideoMode(800, 600), "SFML window");
    win.run();
    return EXIT_SUCCESS;
}