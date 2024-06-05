#include <iostream> 
using namespace std; 
int accept = 0; 
string input; 

enum States { 
  OPEN, 
  CLOSED, 
  LOCKED
}; 
States state = States::OPEN; 

int Proc(string input){ 
  if (state == States::OPEN){ 
    if (input == "PUSH"){ 
      state = States::CLOSED; 
    } 
    else if (input == "PULL"){ 
      state = States::OPEN; 
    } 
    else if (input == "TURN"){ 
      state = States::OPEN; 
    } 
  } 
  else if (state == States::CLOSED){ 
    if (input == "PUSH"){ 
      state = States::CLOSED; 
    } 
    else if (input == "PULL"){ 
      state = States::OPEN; 
    } 
    else if (input == "TURN"){ 
      state = States::LOCKED; 
    } 
  } 
  else if (state == States::LOCKED){ 
    if (input == "PUSH"){ 
      state = States::LOCKED; 
    } 
    else if (input == "PULL"){ 
      state = States::LOCKED; 
    } 
    else if (input == "TURN"){ 
      state = States::CLOSED; 
    } 
  } 
 return state == States::LOCKED; 
} 

int main(){ 
  while(1){ 
    cout << " state = " << state << " enter signal" << endl; 
    cin >> input;
    accept = Proc(input);
    cout <<" new state = " << state << endl; 
    cout <<" accept = "<< (accept == 1 ? "Yes" : "No") << endl; 
  } 
} 
