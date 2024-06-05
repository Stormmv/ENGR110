/*Exercise 3 of FSM asignment 1*/
/*recognize numbers without leading 0 excluding the singular number 0*/
#include <iostream>
#include <string>

using namespace std;
enum States {s0,s1,s2};
States states;
int num0 = 0;
int accept = 0; 
int ProcessChar(char in_char){  
	switch (states) {
    case s0:
        switch(in_char){
            case '0':
                states = s0;
                accept = 0;
                break;
            default:
                states = s2;
                accept = 1;
                break;
        }
        if (num0 == 0){
            accept = 1;
            num0++;
            states = s1;
        }
        break;
    case s1:
        switch(in_char){
            case '0':
                states = s2;
                accept = 0;
                break;
            default:
                states = s2;
                accept = 0;
                break;
        }
        break;
    }
    
    cout<<"state after "<<in_char<<" is "<<states<<endl;
    cout<<"accept after "<<in_char<<" is "<<accept<<endl;
	return accept;
}

int main(){
   string input;
   cout<<"enter input numbers:";
   getline(std::cin,input);
   states = s0;
   cout<<"Input is "<<input<<" state is "<<states<<endl;
   bool string_accepted = 0;
   for (char s:input){
	   string_accepted = ProcessChar(s);
   } 
   cout<<" accepted = "<<string_accepted<<endl;
}

