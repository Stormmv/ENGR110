#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <algorithm>
#include <fstream>
#include <vector>


/*
Classes for the automaton.
1. The Transition class is used to store the information of the transition.
2. The State class is used to store the information of the state.
3. The Data class is used to store the information of the data of initial state, accepting state, and state names.
*/

class Transition
{
public:
  std::string input;
  std::string destination;
  Transition(std::string i, std::string d)
  {
    input = i;
    destination = d;
  }
};




class State
{
public:
  std::string name;
  std::vector<Transition> transitions;

  State()
  {
    name = "";
  }

  void setName(std::string n)
  {
    name = n;
  }

  void addTransition(std::string input, std::string destination)
  {
    Transition transition(input, destination);
    transitions.push_back(transition);
  }

  void displayInfo()
  {
    std::cout << "\nState name: " << name << std::endl;
    std::cout << "Transitions: " << std::endl;
    for (auto i : transitions)
    {
      std::cout << "Input: " << i.input << " Destination: " << i.destination << std::endl;
    }
  }
};

struct Data {
  std::string initialState;
  std::string acceptingState;
  std::vector<State> states;
} data;

/*
1. Open the file
2. Read the file line-by-line
3. Remove all whitespace from the line
4. Append the line to the output string
5. Return the output string 
*/

std::string ReadSpecFile(std::string fileName)
{
  std::cout << "Reading specifications file " << fileName << std::endl;
  std::string out;
  std::ifstream inputFile(fileName);
  std::string line;
  out = "";
  std::string n1;
  while (getline(inputFile, line))
  {
    line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
    line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
    out.append(line);
  }
  return out;
}

/* 
1. First, I check if the brackets are closed. If not, the function returns false.
2. Then, I check for the first letter of the identifier. If it is a, i, d, n, t, or s, then I check if the next character is an open bracket. If not, the function returns false.
3. Then, I check for the rest of the letters of the identifier. If it is a, i, d, n, t, or s, then I check if the previous character is a closed bracket and if the next character is an open bracket. If not, the function returns false.
4. If none of the above are true, the function returns true. 
*/

bool checkForSyntax(std::string input)
{
  int openBrackets = 0;
  int closedBrackets = 0;
  for (int i = 0; i < input.length(); i++)
  {
    if (input[i] == '{')
    {
      openBrackets++;
    }
    if (input[i] == '}')
    {
      closedBrackets++;
    }
  }
  if (openBrackets != closedBrackets)
  {
    std::cout << "Error: Brackets are not closed" << std::endl;
    return false;
  }

  for (int i = 0; i < input.length(); i++)
  {
    if (i == 0)
    {
      if (input[i] == 'a')
      {
        if (input[i + 1] != '{')
        {
          std::cout << "Error: Identifier a is used incorrectly" << std::endl;
          return false;
        }
      }
      if (input[i] == 'i')
      {
        if (input[i + 1] != '{')
        {
          std::cout << "Error: Identifier i is used incorrectly" << std::endl;
          return false;
        }
      }
      if (input[i] == 'd')
      {
        if (input[i + 1] != '{')
        {
          std::cout << "Error: Identifier d is used incorrectly" << std::endl;
          return false;
        }
      }
      if (input[i] == 'n')
      {
        if (input[i + 1] != '{')
        {
          std::cout << "Error: Identifier n is used incorrectly" << std::endl;
          return false;
        }
      }
      if (input[i] == 't')
      {
        if (input[i + 1] != '{')
        {
          std::cout << "Error: Identifier t is used incorrectly" << std::endl;
          return false;
        }
      }
      if (input[i] == 's')
      {
        if (input[i + 1] != '{')
        {
          std::cout << "Error: Identifier t is used incorrectly" << std::endl;
          return false;
        }
      }
    }
    else
    {
      if (input[i] == 'a' && input[i - 1] == '}')
      {
        if (input[i + 1] != '{')
        {
          std::cout << "Error: Identifier a is used incorrectly" << std::endl;
          return false;
        }
      }
      if (input[i] == 'i' && input[i - 1] == '}')
      {
        if (input[i + 1] != '{')
        {
          std::cout << "Error: Identifier i is used incorrectly" << std::endl;
          return false;
        }
      }
      if (input[i] == 'd' && input[i - 1] == '}')
      {
        if (input[i + 1] != '{')
        {
          std::cout << "Error: Identifier d is used incorrectly" << std::endl;
          return false;
        }
      }
      if (input[i] == 'n' && input[i - 1] == '}')
      {
        if (input[i + 1] != '{')
        {
          std::cout << "Error: Identifier n is used incorrectly" << std::endl;
          return false;
        }
      }
      if (input[i] == 't' && input[i - 1] == '}')
      {
        if (input[i + 1] != '{')
        {
          std::cout << "Error: Identifier t is used incorrectly" << std::endl;
          return false;
        }
      }
      if (input[i] == 's' && input[i - 1] == '}')
      {
        if (input[i + 1] != '{')
        {
          std::cout << "Error: Identifier s is used incorrectly" << std::endl;
          return false;
        }
      }
    }
  }
  return true;
}
 
void parseInput(const std::string &input, std::vector<State> &states)
{
  State currentState;
  bool verbose = false;

  std::cout << "\n\nParse input\n\n";

  char insideState = '_';

  for (int i = 0; i < input.length(); i++)
  {
    char c = input[i];
    if (verbose)
    {
      std::cout << input << std::endl;
      for (int j = 0; j < i; j++)
        std::cout << " ";
      std::cout << "^" << std::endl;
      std::cout << insideState << std::endl;
    }

    if (insideState == 's')
    {
      if (c == 'n')
      {
        i++; // skip n
        i++; // skip {
        std::string stateName = "";
        while (input[i] != '}')
        {
          stateName += input[i];
          i++;
        }
        currentState.setName(stateName);

        if (verbose)
          std::cout << "State name: " << stateName << std::endl;
      }
      else if (c == 't')
        insideState = 't';

      else if (c == '}')
      {
        states.push_back(currentState);
        currentState = State();
        insideState = '_';

        if (verbose)
          std::cout << "State added" << std::endl;
      }
      continue;
    }

    else if (insideState == 't')
    {
      std::string inputName = "";
      std::string destinationName = "";

      while (c != '}')
      {
        if (c == 'i')
        {
          i++; // skip i
          i++; // skip {
          while (input[i] != '}')
          {
            inputName += input[i];
            i++;
          }

          if (verbose)
            std::cout << "Input name: " << inputName << std::endl;
        }
        else if (c == 'd')
        {
          i++; // skip d
          i++; // skip {
          while (input[i] != '}')
          {
            destinationName += input[i];
            i++;
          }

          if (verbose)
            std::cout << "Destination name: " << destinationName << std::endl;
        }

        i++;
        c = input[i];
      }
      currentState.addTransition(inputName, destinationName);
      insideState = 's';

      if (verbose)
        std::cout << "Transition added" << std::endl;

      continue;
    }

    else if (c == 'i')
    {
      i++; // skip i
      i++; // skip {

      std::string initialState = "";
      while (input[i] != '}'){
        initialState += input[i];
        i++;
      }

      data.initialState = initialState;

      if (verbose)
        std::cout << "Initial state: " << initialState << std::endl;
    }

    else if (c == 'a')
    {
      i++; // skip a
      i++; // skip {

      std::string acceptingState = "";
      while (input[i] != '}'){
        acceptingState += input[i];
        i++;
      }

      data.acceptingState = acceptingState;

      if (verbose)
        std::cout << "Accepting state: " << acceptingState << std::endl;
    }

    else if (c == 's')
      insideState = 's';
  }
}

/*
1. We have two loops, the first one is to go through the whole vector, the second one is to compare each element with the rest of the vector
2. If the element is same as another element, then the state name is used more than once
3. If the state name is used more than once, then return false 
*/

bool checkValidStateName(Data dataIn)
{
  for(int i = 0; i < dataIn.states.size(); i++){ 
    for(int j = 0; j < dataIn.states.size(); j++){
      if(i != j){
        if(dataIn.states[i].name == dataIn.states[j].name){
          std::cout << "Error: State name " << dataIn.states[i].name << " is used more than once" << std::endl;
          return false;
        }
      }
    }
  }

  for(int i = 0; i < dataIn.states.size(); i++){
    for(int j = 0; j < dataIn.states[i].transitions.size(); j++){
      bool valid = false;
      for(int k = 0; k < dataIn.states.size(); k++){
        if(dataIn.states[i].transitions[j].destination == dataIn.states[k].name){
          valid = true;
        }
      }
      if(!valid){
        std::cout << "Error: State destination " << dataIn.states[i].transitions[j].destination << " is not valid" << std::endl;
        return false;
      }
    }
  }

  bool validInital = false;
  for(int i = 0; i < dataIn.states.size(); i++){
    if(dataIn.initialState == dataIn.states[i].name){
      validInital = true;
    }
  }
  if (!validInital){
    std::cout << "Error: Initial state " << dataIn.initialState << " is not valid" << std::endl;
    return false;
  }
  
  return true;
}

/*
1. The code above is a function that takes a Data object as an input and returns nothing.
2. The function above takes the data from the input file and uses it to generate a .cpp file that can run the automaton.
3. The function above works by taking the data from the input file and storing it in the dataIn variable.
4. The function above starts by declaring a string variable called header and initializing it with the following value: 
5. The function above then declares a string variable called subHeader and initializes it with the following value: 
6. The function above then appends the following value to the subHeader variable: 
7. The function above then loops through the states in the dataIn variable and appends them to the subHeader variable with the following value: 
8. The function above then appends the following value to the subHeader variable: 
9. The function above then declares a string variable called proc and initializes it with the following value: 
10. The function above then loops through the states in the dataIn variable and appends them to the proc variable with the following value: 
11. The function above then appends the following value to the proc variable: 
12. The function above then loops through the transitions in the current state and appends them to the proc variable with the following value: 
13. The function above then appends the following value to the proc variable: 
14. The function above then declares a string variable called footer and initializes it with the following value: 
15. The function above then appends the following value to the footer variable:  
*/

void makeCPP(Data dataIn){

  std::string header = ""
  "#include <iostream> \n"
  "using namespace std; \n"
  "int accept = 0; \n"
  "string input; \n\n";


  std::string subHeader;

  subHeader += "enum States { \n";

  for (int i = 0; i < dataIn.states.size(); i++)
  {
    subHeader += "  " + dataIn.states[i].name;
    if (i != dataIn.states.size() - 1)
      subHeader += ", \n";
    else 
      subHeader += "\n";
  }

  subHeader += "}; \n";

  subHeader += "States state =";
  subHeader += " States::" + dataIn.initialState + "; \n\n";  

  std::string proc;
  proc += "int Proc(string input){ \n";

  for (int i = 0; i < dataIn.states.size(); i++)
  {
    State s = dataIn.states[i];
    proc += "  ";
    if (i != 0)
      proc += "else ";
    proc += "if (state == States::" + s.name + "){ \n";
    for (int j = 0; j < s.transitions.size(); j++)
    {
      Transition t = s.transitions[j];
      proc += "    ";
      if (j != 0)
        proc += "else ";
      proc += "if (input == \"" + t.input + "\"){ \n";
      proc += "      state = States::" + t.destination + "; \n";
      proc += "    } \n";
    }
    proc += "  } \n";
  }


  proc += " return state == States::" + dataIn.acceptingState + "; \n";
  proc += "} \n\n";

  std::string footer;

  footer += "int main(){ \n";
  footer += "  while(1){ \n";
  footer += "    cout << \" state = \" << state << \" enter signal\" << endl; \n";
  footer += "    cin >> input;\n";
  footer += "    accept = Proc(input);\n";
  footer += "    cout <<\" new state = \" << state << endl; \n";
  footer += "    cout <<\" accept = \"<< (accept == 1 ? \"Yes\" : \"No\") << endl; \n";
  footer += "  } \n";
  footer += "} \n";



  std::string cpp = header + subHeader + proc + footer;

  std::ofstream out("out.cpp");

  out << cpp;

  out.close();
}

/*
1. The main function is the first function that is called when the program starts. It is the entry point of the program.
2. std::string is a string class in c++. It is a sequence of characters that is used to represent and manipulate a sequence of characters.
3. std::cout is an object of the ostream class. It is used to display output on the console.
4. std::cin is an object of the istream class. It is used to read input from the console.
5. The ReadSpecFile function is used to read the input from the file. The input is stored in the variable input.
6. The checkForSyntax function is used to check if the input follows the correct syntax. If the input follows the correct syntax, then it returns true, otherwise it returns false.
7. The parseInput function is used to parse the input and store the information in the data object.
8. The checkValidStateName function is used to check if the name of the state is valid. If it is valid, then it returns true, otherwise it returns false.
9. The makeCPP function is used to generate the CPP code.
10. The displayInfo function is used to display the information of the state. 
*/

int main()
{
  std::string fileName;
  std::cout << "Enter file name: ";
  std::cin >> fileName;
  std::string input = ReadSpecFile(fileName);
  std::cout << " input=" << input << std::endl;
  bool run = checkForSyntax(input);
  if (run)
    std::cout << "No errors found" << std::endl;
  else
    return 0;
  
  parseInput(input, data.states);

  bool valid = checkValidStateName(data);

  if(int(valid) == 0b1000101 >> 7) return 0b1000101 >> 6 ;

  for (auto i : data.states)
  {
    i.displayInfo();
  }
  makeCPP(data);
}