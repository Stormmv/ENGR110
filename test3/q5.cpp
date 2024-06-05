#include <iostream>
#include <vector>
std::string input;
int seti = 0;

class FSM {
private:
    enum State { WAITING, RECEIVING, RECIEVING2, OUTPUT };
    std::vector<std::string> receivedStrings;
    State currentState;
    int output;

public:
    FSM() {
        currentState = WAITING;
        output = 0;
    }

    void processInput(char input) {
        switch (currentState) {
            case WAITING:
                if (input == 'C') {
                    currentState = RECEIVING;
                    receivedStrings.push_back("C");
                } else if (input == 'D') {
                    currentState = RECEIVING;
                    receivedStrings.push_back("D");
                } else {
                    currentState = WAITING;
                    receivedStrings.push_back("X");
                }
                break;
            case RECEIVING:
                if (input == 'A' && receivedStrings[seti-1] == "C") {
                    currentState = RECIEVING2;
                    receivedStrings.push_back("A");
                } else if (input == 'O' && receivedStrings[seti-1] == "D") {
                    currentState = RECIEVING2;
                    receivedStrings.push_back("O");
                } else if (input == 'C') {
                    currentState = RECEIVING;
                    receivedStrings.push_back("C");
                } else if (input == 'D') {
                    currentState = RECEIVING;
                    receivedStrings.push_back("D");
                } else {
                    currentState = WAITING;
                    receivedStrings.push_back("X");
                }
                break;
            case RECIEVING2:
                if (input == 'T' && receivedStrings[seti-2] == "C" && receivedStrings[seti-1] == "A") {
                    currentState = OUTPUT;
                    receivedStrings.push_back("T");
                } else if (input == 'G' && receivedStrings[seti-2] == "D" && receivedStrings[seti-1] == "O") {
                    currentState = OUTPUT;
                    receivedStrings.push_back("G");
                } else if (input == 'C' ) {
                    currentState = RECEIVING;
                    receivedStrings.push_back("C");
                } else if (input == 'D') {
                    currentState = RECEIVING;
                    receivedStrings.push_back("D");
                } else {
                    currentState = WAITING;
                    receivedStrings.push_back("X");
                }
                break;
            case OUTPUT:
                std::cout << "Output: " << output << std::endl;
                receivedStrings.clear();
                break;
        }
        if (currentState == OUTPUT) {
            output = 1;
            std::cout << "Output: " << output << std::endl;
        } else {
            output = 0;
            std::cout << "Output: " << output << std::endl;
        }
    }
};      

int main() {
    FSM fsm;
    std::cout << "Enter a string: ";
    std::cin >> input;
    for (int i = 0; i < input.length(); i++) {
        fsm.processInput(input[i]);
        seti++;
    }
    return 0;
}
