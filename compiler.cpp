//===================================================================
//Compiler using the FIRST method
//by: Everette & Abraham
//This is a general purpose compiler using the FIRST method.
//The compiler will take in a simple string from the user and either reject or accept it
//===================================================================

#include <iostream>
#include <stack>
#include <list>
#include <algorithm>
#include <stdlib.h>
using namespace std;

const string LINE1 = "====================================\n";
const string LINE2 = "------------------------------------\n";
const string AUTHORS = "Everette & Abraham";

struct language
{
    string name;
    string launchString;
    string table[10][10];
    string terminals[10];
    string nonTerminals[10];
    string startingNonTerminal;
};


string GoTo(language _language, string _nonTerminal, string _terminal){
    //Find index of nonTerminal
    auto itr_nonTerminal = find(_language.nonTerminals, _language.nonTerminals + 10, _nonTerminal);
    int index_nonTerminal = 0;
    if (itr_nonTerminal != end(_language.nonTerminals)) index_nonTerminal = distance(_language.nonTerminals, itr_nonTerminal);
    else index_nonTerminal = -1;

    //Find index of terminal
    auto itr_terminal = find(_language.terminals, _language.terminals + 10, _terminal);
    int index_terminal = 0;
    if (itr_terminal != end(_language.terminals)) index_terminal = distance(_language.terminals, itr_terminal);
    else index_terminal = -1;

    if (index_nonTerminal == -1 || index_terminal == -1) return "";

    return _language.table[index_nonTerminal][index_terminal];
}


bool compiler(string input, language languageToUse, bool debug = false){

    string testInput = input;
    int testInputIndex = 0;
    string currentTerminal;
    
    if(debug)std::cout << "Testing input: " << testInput << std::endl;

    bool hasFinished = false;
    bool wasRejected = false;

    stack<string> parsingStack;

    // Starts by making stack: $E
    parsingStack.push("$");
    if(debug)std::cout << "Push: " << '$';

    parsingStack.push(languageToUse.startingNonTerminal);
    if(debug)std::cout << "Push: " << languageToUse.startingNonTerminal << std::endl;

    //std::cout << "Stack Size: " << parsingStack.size() << std::endl;
    if(debug)std::cout << "Stack Top: " << parsingStack.top() << std::endl;

    while(hasFinished == false){
        bool matchFound = false;

        if(debug)std::cout << "================" << std::endl;

        // Reads the next character from the input string
        currentTerminal = testInput[testInputIndex];
        if(debug)std::cout << "Read: " << currentTerminal << std::endl;

        // Keeps moving through the parsing table until a match is found for our character from the input string
        while(matchFound == false){

            //Grabs the element from the top of our stack
            string currentStackElement = parsingStack.top();
            parsingStack.pop();
            if(debug)std::cout << "Pop: " << currentStackElement << std::endl;
            
            //Does it match our character from the input string?
            if(currentStackElement == currentTerminal){
                matchFound = true;
                if(debug)std::cout << "MATCH WITH INPUT " << currentTerminal << std::endl;

                if(currentTerminal == "$") {
                    hasFinished = true;
                }

            }else{
                //Go to [currentStackElement, currentTerminal] = newState
                //string newState = table[translateNonTerminalToIndex(currentStackElement)][translateTerminalToIndex(currentTerminal)];
                //string newState = languagesToUse.GoTo(currentStackElement, currentTerminal);
                string newState = GoTo(languageToUse, currentStackElement, currentTerminal);
                if(debug)std::cout << "GoTo [" << currentStackElement << "," << currentTerminal << "] = " << newState << std::endl;

                if(newState == ""){
                    if(debug)std::cout << "REJECT" << std::endl; // We wound up in an empty space in the parsing table
                    return false;
                }
                else if(newState != "L"){
                    stack<string> reverseStack;
                    //then push newState backwards
                    for(int i=0; i<newState.length(); ++i){
                        string tmp(1, newState[i]);
                        reverseStack.push(tmp);
                    }
                    for(int i=0; i<newState.length(); ++i){
                        parsingStack.push(reverseStack.top());
                        reverseStack.pop();
                        if(debug)std::cout << "Push: " << parsingStack.top() << std::endl;
                    }  
                }
                if(debug)std::cout << "Stack Size: " << parsingStack.size() << std::endl;
                if(debug)std::cout << "Stack Top: " << parsingStack.top() << std::endl;
            }
            if(debug)std::cout << "----------------------" << std::endl;
        }

        testInputIndex++;

    }

    if(debug)std::cout << "ACCEPT" << std::endl;

    return true;
}

bool userWantsToExit(string exitMessage){
    while( 1 > 0){
        string input = "";
        std::cout << exitMessage << "(y/n): ";
        std::cin >> input;

        if (input == "N"||input == "n") return false;
        else if(input == "Y"||input == "y") return true;

        std::cout << "I'm sorry I did not recognize that input\nPlease try again" << std::endl;
    }
}

void welcomeMessage(){
    std::cout << LINE1 << "This is a compiler using the FIRST method\n" << "Designed by: " << AUTHORS << "\n" << LINE1;
}

void goodByeMessage(){
    std::cout << "Good Bye :)" << std::endl << flush;
    system("PAUSE");
    system("CLS");
}


// Driver Code
int main()
{
    welcomeMessage();

    bool isDone = false;
    bool usingCurrentCompiler = false;
    bool isInDebugMode = false;

    language AllLanguages[3];
    AllLanguages[0].name = "Problem1";
    AllLanguages[0].launchString = "1";

    AllLanguages[0].startingNonTerminal = "E";

    AllLanguages[0].table[0][0] = "TQ";
    AllLanguages[0].table[0][5] = "TQ";
    AllLanguages[0].table[1][1] = "+TQ";
    AllLanguages[0].table[1][2] = "-TQ";
    AllLanguages[0].table[1][6] = "L";
    AllLanguages[0].table[1][7] = "L";
    AllLanguages[0].table[2][0] = "FR";
    AllLanguages[0].table[2][5] = "FR";
    AllLanguages[0].table[3][1] = "L";
    AllLanguages[0].table[3][2] = "L";
    AllLanguages[0].table[3][3] = "*FR";
    AllLanguages[0].table[3][4] = "/FR";
    AllLanguages[0].table[3][6] = "L";
    AllLanguages[0].table[3][7] = "L";
    AllLanguages[0].table[4][0] = "i";
    AllLanguages[0].table[4][5] = "(E)";

    AllLanguages[0].nonTerminals[0] = "E";
    AllLanguages[0].nonTerminals[1] = "Q";
    AllLanguages[0].nonTerminals[2] = "T";
    AllLanguages[0].nonTerminals[3] = "R";
    AllLanguages[0].nonTerminals[4] = "F";

    AllLanguages[0].terminals[0] = "i";
    AllLanguages[0].terminals[1] = "+";
    AllLanguages[0].terminals[2] = "-";
    AllLanguages[0].terminals[3] = "*";
    AllLanguages[0].terminals[4] = "/";
    AllLanguages[0].terminals[5] = "(";
    AllLanguages[0].terminals[6] = ")";
    AllLanguages[0].terminals[7] = "$";

    AllLanguages[1].name = "Problem2";
    AllLanguages[1].launchString = "2";

    AllLanguages[1].startingNonTerminal = "S";

    AllLanguages[1].table[0][0] = "aW";
    AllLanguages[1].table[1][7] = "=E";
    AllLanguages[1].table[2][0] = "TQ";
    AllLanguages[1].table[2][5] = "TQ";
    AllLanguages[1].table[3][1] = "+TQ";
    AllLanguages[1].table[3][2] = "-TQ";
    AllLanguages[1].table[3][6] = "L";
    AllLanguages[1].table[3][8] = "L";
    AllLanguages[1].table[4][0] = "FR";
    AllLanguages[1].table[4][5] = "FR";
    AllLanguages[1].table[5][1] = "L";
    AllLanguages[1].table[5][2] = "L";
    AllLanguages[1].table[5][3] = "*FR";
    AllLanguages[1].table[5][4] = "/FR";
    AllLanguages[1].table[5][6] = "L";
    AllLanguages[1].table[5][8] = "L";
    AllLanguages[1].table[6][0] = "a";
    AllLanguages[1].table[6][5] = "(E)";

    AllLanguages[1].nonTerminals[0] = "S";
    AllLanguages[1].nonTerminals[1] = "W";
    AllLanguages[1].nonTerminals[2] = "E";
    AllLanguages[1].nonTerminals[3] = "Q";
    AllLanguages[1].nonTerminals[4] = "T";
    AllLanguages[1].nonTerminals[5] = "R";
    AllLanguages[1].nonTerminals[6] = "F";

    AllLanguages[1].terminals[0] = "a";
    AllLanguages[1].terminals[1] = "+";
    AllLanguages[1].terminals[2] = "-";
    AllLanguages[1].terminals[3] = "*";
    AllLanguages[1].terminals[4] = "/";
    AllLanguages[1].terminals[5] = "(";
    AllLanguages[1].terminals[6] = ")";
    AllLanguages[1].terminals[7] = "=";
    AllLanguages[1].terminals[8] = "$";

    AllLanguages[2].name = "Blank";
    AllLanguages[2].launchString = "3";

    int currentLanguageIndex = 0;
    int numberOfAvailableLanguages = sizeof(AllLanguages)/sizeof(language);

    while(!isDone){

        while(usingCurrentCompiler){
            system("CLS");
            if(isInDebugMode) std::cout << "DEBUG MODE: ON" << std::endl;
            std::cout << "You are using the " << AllLanguages[currentLanguageIndex].name << " language" << std::endl;
            std::cout << "Please enter the string you want to compile followed by a '$'" << std::endl;
            string input = "";

            std::cin >> input;

            system("CLS");

            std::cout << "Attempting to compile: '" << input << "' using '" << AllLanguages[currentLanguageIndex].name << "' language" << std::endl;

            if(compiler(input, AllLanguages[currentLanguageIndex], isInDebugMode)) std::cout << "Your string compiled!" << std::endl;
            else std::cout << "I'm sorry your string was rejected" << std::endl;

            std::cout << LINE2;

            if(userWantsToExit("Do you want to exit or try a different language?")) usingCurrentCompiler = false;
        }

        system("CLS");

        std::cout << "What language would you like to use?" << std::endl;

        //Display all avaliable languages
        for(int i=0; i < numberOfAvailableLanguages; ++i){
            std::cout << AllLanguages[i].launchString << ":  " << AllLanguages[i].name << std::endl;
        }

        //Display Exit option
        std::cout << "9:  EXIT" << std::endl; 

        //Display DebugMode on/off
        if(isInDebugMode)
        std::cout << "Debug Mode: ON  (input 'D' to toggle off)" << std:: endl;

        //Get user input 
        string input = "";
        std::cin >> input;

        //act on user input
        if(input == "9"){
            system("CLS");
            if(userWantsToExit("Are you sure you want to exit?")) isDone = true;
        }
        else if(input == "D"){
            isInDebugMode = !isInDebugMode;
            system("CLS");
        }
        else{
            for(int i=0; i < numberOfAvailableLanguages; ++i){
                if(input == AllLanguages[i].launchString){
                    currentLanguageIndex = i;
                    usingCurrentCompiler = true;
                    i = numberOfAvailableLanguages;
                    system("CLS");
                }
            }
            if(!usingCurrentCompiler){
                std::cout << "I'm sorry I don't recognize that input" << std::endl << flush;
                system("PAUSE");
            }
        }
    }

    goodByeMessage();

    return 0;
}