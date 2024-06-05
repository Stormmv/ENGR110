#include <iostream>
#include <vector>

class FSMTransducer {
private:
    enum State { WAITING, RECEIVING, OUTPUT };
    State currentState;
    std::vector<int> receivedBits;
    int output;

public:
    FSMTransducer() {
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
                    currentState = WAITING;
                    receivedBits.clear();
                } else if (input == 1) {
                    currentState = RECEIVING;
                    receivedBits.push_back(input);
                }
                break;
            case OUTPUT:
                if (input == 0) {
                    currentState = WAITING;
                    receivedBits.clear();
                } else if (input == 1) {
                    currentState = RECEIVING;
                    receivedBits.push_back(input);
                }
                break;
        }
        if (currentState == RECEIVING && receivedBits.size() == 2) {
            if (receivedBits[0] == 1 && receivedBits[1] == 1) {
                currentState = OUTPUT;
                output = 1;
                std::cout << "Output: " << output << std::endl;
                currentState = RECEIVING;
                receivedBits.clear();
            } else {
                currentState = WAITING;
                receivedBits.clear();
            }
        }
    }
};

int main() {
    FSMTransducer transducer;
    int input;
    std::cout << "Enter 0 or 1: ";
    std::cin >> input;
    while (input == 0 || input == 1) {
        transducer.processInput(input);
        std::cout << "Enter 0 or 1: ";
        std::cin >> input;
    }
    return 0;
}