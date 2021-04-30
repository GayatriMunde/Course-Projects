#include <iostream>
#include "ChatRoom.h"

using namespace std;

int main(){
    int type = 1, exit = 1;

    cout << "---------------------------\n  CHAT ROOM  \n---------------------------" << endl;

    while (exit) {
        try {
            cout << "Choose? \n  [1] -> Client \n  [2] -> Server  \n  [3] -> Help  \n  [4] -> Exit" << endl;

            cin >> type;

            switch (type) {
            case 1:
                ChatClient();
                break;
            case 2:
                ChatServer();
                break;
            case 3:
                cout << "Commands:\n /exit -> Exit current chat room\n /file [filepath] Send file to" << endl;
                break;
            case 4:
                exit = 0;
                break;
            default:
                cout << "Uknown command!" << endl;
                cin.clear();
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}

