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
    GameWindow win(sf::VideoMode(1200, 900), "SFML window");
//    std::thread listen(EatInput);
//    listen.detach();
    win.run();
//    str = "end";
    return 0;
}