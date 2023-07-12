/*****************************************************************************/
/* Date: November 2022                                                       */
/* Modified by:                                                              */
/* Description: This file contains the description of a class called         */
/*      Circuit.                                                             */
/*****************************************************************************/

#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*****************************************************************************/
/* Class name: Circuit                                                       */
/* Description: This class is designed to create circuit objects to test the */
/*          input given by a user to see if the logic gates in a hypothetical*/
/*          circuit are functioning properly.                                */
/*****************************************************************************/

class Circuit
{
public:
    Circuit ();
    ~Circuit ();

    //Gate Setter/Getter Functions
    void setGateValue(string , bool);
    bool setGateInput(string);
    bool findOutput();  

    //Logic Gates
    bool And();
    bool Or();
    bool Xor();
    bool Not();
    
    //Getter Functions
    char getGate();
    string getInp1();
    string getInp2();
    bool getOuput();
    int getOutIndex();  

    //Setter Functions
    void setGate(char, string, string);
    void setOutGate(int);
    void setNotGate(string);
    void setValue1(bool);
    void setValue2(bool);
    

private:
    char gate;      //Used to recognize gate-type
    string input1;  //Used to store where input is coming from to gate
    string input2;  
    bool value1;    //Used as the testing observed boolean value
    bool value2;
    bool outputObj; //Used to recognize if gate is an output gate
    int outIndex;   //Used to determine index of output gate
};

#endif