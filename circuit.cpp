/*****************************************************************************/
/* Date: November 2022                                                       */
/* Modified by:                                                              */
/* Description: This file contains the implementation of a class called      */
/*      Circuit. This class is designed to hold gate objects to create a     */
/*      circuit based upon input by the user. The class implements a circuit */
/*      that is limited to the use of four gate: And, Not, Or, Xor            */
/*****************************************************************************/

#include "circuit.h"
#include <string>

// set DEBUG to true for debugging
#define DEBUG false
#define debug if (DEBUG) cout

using namespace std;

/*****************************************************************************/
/* Function name: Circuit                                                    */
/* Input parameters: N/A                                                     */
/* Returned result: N/A                                                      */
/* Description: As a the default constructor it initializes the private      */
/*        variables to 0, empty char/string and all boolean values to false  */
/*****************************************************************************/

Circuit::Circuit ()
{       
    gate = ' ';       //Initialize gate to escaped zero
    outputObj = false;   //Set false as an output gate
    value1 = false;   //Set observed values as false
    value2 = false;   
    outIndex = 0;
    input1.clear();   //Empty both strings
    input2.clear();   
}

/*****************************************************************************/
/* Function name: ~Circuit                                                   */
/* Input parameters: N/A                                                     */
/* Returned result: N/A                                                      */
/* Description: The Destructor, deallocates memory allocated                 */
/*        for any class objects. N/A because no memory was                   */
/*        dynamically allocated.                                             */
/*****************************************************************************/

Circuit::~Circuit ()
{
}

/*****************************************************************************/
/* Function name: And                                                        */
/* Input parameters: n/a                                                     */
/* Returned result: A boolean value indicating true or false                 */
/* Description: Functions as an And operation by returning the result of     */
/*          input1 and input2                                                */
/*****************************************************************************/

bool Circuit::And()
{
    if(value1 == true && value2 == true) {
        return true;
    }
    else 
        return false;
}


/*****************************************************************************/
/* Function name: Or                                                         */
/* Input parameters: n/a                                                     */
/* Description: Functions as an Or operation by returning the result of      */
/*          input1 and input2                                                */
/*****************************************************************************/

bool Circuit::Or()
{
    if(value1 == true || value2 == true){
        return true;
    }
    else 
        return false;
}

/*****************************************************************************/
/* Function name: Xor                                                        */
/* Input parameters: n/a                                                     */
/* Returned result: A boolean value indicating true or false                 */
/* Description: Functions as an Xor operation by returning the result of     */
/*          input1 and input2                                                */
/*****************************************************************************/

bool Circuit::Xor()
{
    if(value1 == true && value2 == true){
        return false;
    }
    else if(value1 == false && value2 == false){
        return false;
    }
    else
        return true;
    
}


/*****************************************************************************/
/* Function name: Not                                                        */
/* Input parameters: n/a                                                     */
/* Returned result: A boolean value indicating true or false                 */
/* Description: Functions as an Not operation by returning the result of     */
/*          input1 and input2                                                */
/*****************************************************************************/

bool Circuit::Not()
{
    if(value1) {
        return false;
    }
    else 
        return true;
}

/*****************************************************************************/
/* Function name: setGate                                                    */
/* Input parameters: A char and two input values as strings                  */
/* Returned result: N/A                                                      */
/* Description: Sets the inputs associated with the gate specified.          */
/*          i:e if g1 is an Or gate and is given input from i1 and i2 then   */
/*          'O' is set as the gate and i1 and i2 is set as the input. If the */
/*          input is given by a gate1 and gate2 then g1 and g2 will be set   */
/*          as the input values.                                             */
/*****************************************************************************/

void Circuit::setGate(char g, string i1, string i2)
{
    gate = g;     //set gate
    input1 = i1;  //set input1
    input2 = i2;  //set input2
}


/*****************************************************************************/
/* Function name: setNotGate                                                 */
/* Input parameters: A string indicating the input given to the gate         */
/* Returned result: N/A                                                      */
/* Description: Sets the input associated with the not gate specified.       */
/*          i:e if g1 is is the input then it will be set to the not gate.   */
/*****************************************************************************/

void Circuit::setNotGate(string i1)
{
    gate = 'n';   //set not gate
    input1 = i1;  //set input1
}

/*****************************************************************************/
/* Function name: setGateValues                                              */
/* Input parameters: A vector of circuit objects, a string indicating the    */
/*          input(i#), the boolean value of the input, and the index of the  */
/*          object in the vector needing to be changed.                      */
/* Returned result: N/A                                                      */
/* Description: Sets the boolean value for the gate containing the specified */
/*          input value. i:e if gate 1 containes the input o i1 i2 and the   */
/*          the first boolean value is 0 then i1 on this OR gate would be set*/
/*          to 0. The input variable is comapared to ensure the correct value*/
/*          is set                                                            */
/*****************************************************************************/

void Circuit::setGateValue(string inp, bool obsValue)
{
    if(this->input1 == inp) {  //If input1 string is same as the value passed
        this->value1 = obsValue; //Set to observed value
    }  
    else if(this->input2 == inp) {  //If input2 string is same as the value passed
        this->value2 = obsValue; //Set to observed value
    } 
}

/*****************************************************************************/
/* Function name: setGateInput                                               */
/* Input parameters: A vector of circuit objects, a string indicating the    */
/*          the gate number that is providing the input.                     */
/* Returned result: A boolean value                                          */
/* Description: Finds the ouput value of the gate that is the input for the  */
/*          gate in question. The boolean value in found for the output      */
/*          of the other gate after using the logic gate in that is paired   */
/*          with the object and is used to initialize the input variable     */
/*          for the gate in question.                                        */
/*****************************************************************************/
bool Circuit::setGateInput(string inputGate)
{   
    int gateIndex = 0;  //To find what gate
    char c = inputGate[1]; //Get Gate number
    gateIndex = (int(c) - 49);  //Change from ascii to get gate index

    //Used to determine what type of gate needs to be used
    switch(this[gateIndex].gate) {
        case 'a' :
            return this -> And();
        case 'o' :
            return this -> Or();
        case 'x' :
            return  this -> Xor();
        case 'n' :
            return this -> Not();
    }
    //unexpected fault
    return 0;
}

/*****************************************************************************/
/* Function name: findOutput                                                 */
/* Input parameters: A vector of circuit objects, an integer indicating the  */
/*          the index of the object.                                         */
/* Returned result: A boolean value                                          */
/* Description: Finds the ouput value of the gate in question after using the*/
/*          logic gate in that is paired with the object.                    */
/*****************************************************************************/
bool Circuit::findOutput()
{   
    //Used to determine what type of gate needs to be used
    switch(this -> gate) {
        case 'a' :
            return this -> And();
        case 'o' :
            return this -> Or();
        case 'x' :
            return this -> Xor();
        case 'n' :
            return this -> Not();
    }

    //unexpected fault
    return 0;
}

/*****************************************************************************/
/* Function name: setOutGate                                                 */
/* Input parameters: An integer                                              */
/* Returned result: N/A                                                      */
/* Description: Sets the object as an output gate by initializing the        */
/*          variable outputObj and sets its outIndex to the integer passed to*/
/*          record its output postion in the observation.                    */
/*****************************************************************************/

void Circuit::setOutGate(int index)
{
    outputObj = true;  //set as an output gate 
    outIndex = index;  //Set outIndex to know what order the gates were entered
}

/*****************************************************************************/
/* Function name: setValue1                                                  */
/* Input parameters: A boolean value to set value 1                          */
/* Returned result: N/A                                                      */
/* Description: Sets value1.                                                 */
/*****************************************************************************/

void Circuit::setValue1(bool val)
{
    value1 = val;
}

/*****************************************************************************/
/* Function name: setValue2                                                  */
/* Input parameters: A boolean value to set value 1                          */
/* Returned result: N/A                                                      */
/* Description: Sets value2.                                                 */
/*****************************************************************************/

void Circuit::setValue2(bool val)
{
    value2 = val;
}

/*****************************************************************************/
/* Function name: getGate                                                    */
/* Input parameters: N/A                                                     */
/* Returned result: N/A                                                      */
/* Description: Returns the gate.                                            */
/*****************************************************************************/

char Circuit::getGate()
{
    return gate;
}

/*****************************************************************************/
/* Function name: getInp1                                                    */
/* Input parameters: N/A                                                     */
/* Returned result: N/A                                                      */
/* Description: Returns input1.                                              */
/*****************************************************************************/

string Circuit::getInp1()
{
    return input1;
}

/*****************************************************************************/
/* Function name: getInp2                                                    */
/* Input parameters: N/A                                                     */
/* Returned result: N/A                                                      */
/* Description: Returns input2.                                              */
/*****************************************************************************/

string Circuit::getInp2()
{
    return input2;
}


/*****************************************************************************/
/* Function name: getOuput                                                   */
/* Input parameters: N/A                                                     */
/* Returned result: N/A                                                      */
/* Description: Returns boolean variable that determines if the object is an */
/*          output object.                                                   */
/*****************************************************************************/

bool Circuit::getOuput()
{
    return outputObj;
}

/*****************************************************************************/
/* Function name: getOutIndex                                                */
/* Input parameters: N/A                                                     */
/* Returned result: N/A                                                      */
/* Description: Returns index of the object that is an output object.        */
/*          Used to determine index of out-gate results.                     */
/*****************************************************************************/

int Circuit::getOutIndex()
{
    return outIndex;
}

 
 
 
 