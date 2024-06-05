#include <iostream>
#include <vector>

class FSM {
private:
    enum State { WAITING, RECEIVING, OUTPUT };
    State currentState;
    std::vector<int> receivedBits;
    int output;

public:
    FSM() {
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
                } else if (input == 1) {
                    currentState = RECEIVING;
                    receivedBits.push_back(input);
                }
                break;
            case OUTPUT:
                if (input == 0) {
                    currentState = WAITING;
                } else if (input == 1) {
                    currentState = RECEIVING;
                    receivedBits.push_back(input);
                }
                break;
        }
        if (currentState == RECEIVING && receivedBits.size() >= 3) {
            int sum = 0;   
            for (int i = 0; i < receivedBits.size(); i++) {
                sum += receivedBits[i];
            }
            if (sum % 3 == 0) {
                currentState = OUTPUT;
                output = 1;
                std::cout << "Output: " << output << std::endl;
                currentState = RECEIVING;
            } else {
                currentState = WAITING;
            }
        }
    }
};

int main() {
    FSM fsm;
    int input;
    std::cout << "Enter 0 or 1: ";
    std::cin >> input;
    while (input == 0 || input == 1) {
        fsm.processInput(input);
        std::cout << "Enter 0 or 1: ";
        std::cin >> input;
    }
    return 0;
}