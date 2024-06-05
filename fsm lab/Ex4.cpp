/*Exercise 4 of FSM asignment 1*/
/*print string*/
#include <iostream>
#include <string>

using namespace std;
enum States {s0,s1,s2,s3};
States states;
string output;
int ProcessChar(char in_char){
    switch (states) {
        case s0:
            switch (in_char){
                case ',':
                    break;
            default:
                output = output + in_char;
                states = s1;
                break;
            }
        break;
        case s1:
            switch (in_char){
                case ',':
                    output = output + in_char;
                    states = s0;
                    break;
                default:
                    output = output + in_char;
                    states = s1;
                    break;
            }
        break;
    }
    cout<<output<<endl;
    return 1;
}

int main(){
   string input;
   cout<<"enter input string:";
   getline(std::cin,input);
   states = s0;
   cout<<"Input is "<<input<<" state is "<<states<<endl;
   int run = 0;
   for (char s:input){
	   run = ProcessChar(s);
   } 
   cout<<"Output is: "<<output<<endl;
}

