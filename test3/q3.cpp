#include <iostream>
#include <vector>

class FSMmoore{
private:
    enum State { WAITING, RECEIVING, WAITINGZERO, OUTPUT };
    State currentState;
    std::vector<int> receivedBits;
    int output;

public:
    FSMmoore() {
        currentState = WAITING;
        output = 0;
    }

    void processInput(int input) {
        switch (currentState) {
            case WAITING:
                if (input == 0) {
                    currentState = WAITING;
                } else if (input == 1) {
                    currentState = RECEIVING;
                    receivedBits.push_back(input);
                }
                break;
            case RECEIVING:
                if (input == 0) {
                    currentState = WAITINGZERO;
                    receivedBits.clear();
                } else if (input == 1) {
                    output = 1;
                    currentState = OUTPUT;
                    receivedBits.push_back(input);
                }
                break;
            case WAITINGZERO:
                if (input == 0) {
                    currentState = WAITING;
                } else if (input == 1) {
                    output = 1;
                    currentState = OUTPUT;
                    receivedBits.push_back(input);
                }
                break;
            case OUTPUT:
                std::cout << "Output: " << output << std::endl;
                currentState = RECEIVING;
                receivedBits.push_back(input);
                output = 0;
                break;
        }
    }
};


int main() {
    FSMmoore moore;
    int input;
    std::cout << "Enter 0 or 1: ";
    std::cin >> input;
    while (input == 0 || input == 1) {
        moore.processInput(input);
        std::cout << "Enter 0 or 1: ";
        std::cin >> input;
    }
    return 0;
}

