#include "GameWindow.h"
#include "thread"

string str = "";

void EatInput(){
    str = "123";
    while(str != "end"){
        cin >> str;
        cout << str << endl;
        GameWindow::magic->ConsoleEvent(str);
    }
    cout << "thread end!";
}

int main() {
    srand(time(NULL));
    //GameWindow win(sf::VideoMode(1200, 900), "SFML window");
    sf::RenderWindow final_window(sf::VideoMode(240, 180), "final");
    GameWindow win(sf::VideoMode(1200, 900), "SFML window", &final_window);
//    listen.detach();
    win.run();
//    str = "end";
    return 0;
}