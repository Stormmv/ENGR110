/*Exercise 2 of FSM asignment 1*/
/*recognize "cat" at the end of the string*/
#include <iostream>
#include <string>

using namespace std;
enum States {s0,s1,s2,s3};
States states;
int ProcessChar(char in_char){
    int accept = 0;  
	switch (states) {
    case s0:
        switch(in_char){
            case 'c':
                states = s1;
                break;
        }
        break;
    case s1:
        switch (in_char){
            case 'c':
                states = s1;
                break;
            case 'a':
                states = s2;
                break;
            default:
                states = s0;
        }
        break;
    case s2:
        switch (in_char){
            case 'c':
                states = s1;
                break;
            case 't':
                states = s3;
                accept = 1;
                break;
            default:
                states = s0;
        }
        break;
    case s3:
        accept = 0;
        switch(in_char){
            case 'c':
                states = s1;
                break;
            default:
                states = s0;
        }
        break;
    }
	return accept;
}

int main(){
   string input;
   cout<<"enter input string:";
   getline(std::cin,input);
   states = s0;
   cout<<"Input is "<<input<<" state is "<<states<<endl;
   bool string_accepted = 0;
   for (char s:input){
	   string_accepted = ProcessChar(s);
   } 
   cout<<" accepted = "<<string_accepted<<endl;
}

