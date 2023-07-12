/*****************************************************************************/
/*                                                                           */
/* Date: November                                                            */
/* Description: This file contains the driver for the class Circuit.         */
/*          The program utilizes the classw circuit to create a vector of    */
/*          gate objects in order to create a circuit based upon the input.  */
/*          The program loops for each case of input(or each circuit) and    */
/*          and provides an analysis for each cicuit along with its case     */
/*          number. The program loops for input until terminated with 0 0 0  */
/*****************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "circuit.h"

// set DEBUG to true for debugging
#define DEBUG false
#define debug if (DEBUG) cout

using namespace std;

/*****************************************************************************/
/*                                                                           */
/* Function name: main                                                       */
/* Input parameters: cin                                                    */
/* Returned result:  n/a                                                     */
/* Description: This program is centered around creating circut objects that */
/*          act as gates to mimic a the circuit given by input by the user   */
/*          The input is in the form of:                                     */
/*          3 numbers seperated by spaces: inputs, gates, and outputs        */      
/*          A gate of form 'o', 'a', 'n', 'x' along with its input in the    */
/*          form of i1 i2 ect.. or another gate g1 g2 ect..                  */
/*          After all gates entered the next line of input is the gate/s that*/
/*          act as the source of output/s. Next the number of observations   */
/*          is given. Finally each observation of the circuits behavior is   */
/*          given in the form of inputs and outputs.                         */
/*          The gates are initialized with the inputs for each loop and      */
/*          the expected outputs are stored in an 2d array along with the    */
/*          given outputs to compare the values. After being compared if any */
/*          discrepencies are found the failure gate is found (if possible)  */
/*          and is outputed along with the case number for each circuit.     */
/*          The program terminates when 0 0 0 is entered to start input.     */
/*****************************************************************************/

int main ()
{  
    vector <Circuit> test;  //Used to hold gate objects
    bool start = true;      //To terminate program
    bool badInput = false;  //Validate input from user
    int testCase = 0; //To record test case number for each circuit
    do
    {
        testCase++; //Increment test case
        int inputs = 0;     //Number of inputs
        int gates = 0;      //Number of gates
        int outputs = 0;    //Number of outputs

        do{
            //Recieve input for number of inputs, gates and ouputs
            cin >> inputs >> gates >> outputs;

            //Validate input
            if((inputs >= 9 || gates >= 20 || outputs >= 20) ||
                (inputs < 0 || gates < 0 || outputs < 0)) {
                    badInput = true;
                    cout << "Input too large " << endl;
                }
            else 
                badInput = false;

        }while(badInput);
        
        //Stop if user enters 0 0 0
        if(inputs == 0 && gates == 0 && outputs == 0){
            start = false;
        }

        if(start)
        {
            test.clear(); //Clear vector array
            char gate;    //Temp to hold gate type
            int numOfObsv = 0;  //Number of observations
            string inp1;  //Temp to hold input 1
            string inp2;  //Temp to hold input 2
            string word;  //Used to parse input

            cin.ignore();  //Used for getline()

            int count = 0;  //Number of inputs for each gate
            for(int i = 0; i < gates; i++) {  //For as many gates their are    
                getline (cin, word);     //Get line of input 
                stringstream ss(word);

                while(ss >> word){   //Get gate-type and input for each gate
                    if(count == 0) 
                    gate = word.at(0);
                    
                    else if(count == 1)
                    inp1 = word;

                    else if(count == 2)
                    inp2 = word;

                    count++;
                } 

                Circuit c1;  //Temp object to push back each value
                if(gate == 'n') {  //Determine if gate-type is Not
                    c1.setNotGate(inp1); 
                    test.push_back(c1);
                }
                else {
                    c1.setGate(gate, inp1, inp2);
                    test.push_back(c1);
                }
                count = 0;  //Reinitialize # of inputs for each gate
            }

            //Set number of output gates
            int outGate = 0;  //Temp to hold output gate entered
            for(int i = 0; i < outputs; i++) {  //For as many outputs their are
                cin >> outGate;
                //Set object number as output gate with index i
                //Index of out-gate is used to print in same order inputted
                test[outGate - 1].setOutGate(i);  
            }

            cin >> numOfObsv;  //Get number of Observations
            
            int max = inputs + outputs;  //Find length of each observation

            bool value;  //For each value in observation

            //Create 2D array of boolean values to hold sets of observations
            bool obsv[numOfObsv][max]; 

            //Create 2D array to hold expected results of observations
            bool expObsv[numOfObsv][outputs]; 

            //Test Cases (Iterate for # of observations)
            for(int obsvIndex = 0; obsvIndex < numOfObsv; obsvIndex++){

                //Store observed boolean values in vector
                for(int i = 0; i < max; i++){   
                    cin >> value;
                    obsv[obsvIndex][i] = value;
                }

                //Temp string to find value to use setGateValue/setGateInput
                //Needed to inc from i1 to i2 to i3 as well as g1 to g2...ect
                string inp = "i0";

                //Find at set all Input values of form i#
                for(int i = 0; i < inputs; i++){  //Search for each input
                    inp[1] = (49 + i);  //Change from Ascii for what input is being sent  
                    for(int j = 0; j < gates; j++){  //Search for each input for each gate 
                        if(test[j].getInp1() == inp){  //If input1 is equal to inp string

                            test[j].setGateValue(inp, obsv[obsvIndex][i]);
                        }
                        else if(test[j].getInp2() == inp){  //If input2 is equal to inp string
                            test[j].setGateValue(inp, obsv[obsvIndex][i]);
                        }
                    }
                }

                //Find at set all Input values of form g#
                inp = "g0";
                for(int i = 0; i < outputs; i++){  //Search for each input
                    inp[1] = (49 + i);  //Change from Ascii for what input is being sent  
                    for(int j = 0; j < gates; j++){  //Search for each input for each gate 
                        if(test[j].getInp1() == inp){  //If input1 is equal to inp string
                            test[j].setValue1(test[j].setGateInput(inp));  
                        }
                        else if(test[j].getInp2() == inp){  //If input2 is equal to inp string
                            test[j].setValue2(test[j].setGateInput(inp));  
                        }
                    }
                }

                int outIndex = 0;   //Used to find output corresponding gate 
                int index = 0;      //Used to store outputs in order given
                int i = 0;          //Used to find output gates

                //Find output gates (using true outputObj variable) and store result in array
                do{ //Determine its an output gate and correct index for which it was inputted 
                    for(i = 0; i < gates; i++){
                        if(test[i].getOuput() == true && test[i].getOutIndex() == outIndex){
                            expObsv[obsvIndex][index] = test[i].findOutput();
                            index++;
                            outIndex++;
                        } 
                    }
                    i++;
                }while(index < outputs);
            }   
            
            //Find length of each col for observed array size
            int maxLength = (inputs + outputs); 
            //Define new array to store observed output values
            bool obsvOutput[numOfObsv][outputs];

            //Index's for obsvOutput array
            int row = 0;
            int col = 0;

            //Store observed ouput values into seperate array to analyze
            for(int i = 0; i < numOfObsv; i++){
                for(int j = inputs; j < maxLength; j++){
                    obsvOutput[row][col] = obsv[i][j];
                    col++;
                }
                row++;
                col = 0;
            }
        
            bool outputInverted = false;  //To determine if ouput inverted
            int failgate = 0;  //To store faulted gate 
            int failCount = 0; //To determine number of faults by gate 
            bool result = 0;     //To record if output is stuck or inverted
            bool lastResult = 0; //To record if output is stuck or inverted/what is stuck on
            
            //Compare arrays and determine failing gate if any
            //Start index of observed ouput array at numOfInputs to start at entered output 
            for(int i = 0; i < numOfObsv; i++){
                for(int j = 0; j < outputs; j++){
                    if(obsvOutput[i][j] != expObsv[i][j]){
                        failCount++;
                        result = obsvOutput[i][j];  //Make result equal to first observed output!= expected

                        //Determine if gate has inverted ouput
                        if(failCount > 1 && lastResult != result){ 
                            outputInverted = true;
                        } 

                        //Store last result to know if output is inverted or stuck 
                        lastResult = obsvOutput[i][j]; 
                        failgate =  test[i].getOutIndex(); //Store gate that has failed
                    }
                }
            }

            //Used to determine result of circuit analysis (no faults as default)
            int faultCode = 1;

            //If unable to detect reason for failure
            if(failCount == 1 && numOfObsv == 1){
                faultCode = 2;
            }

            //Determine if gate has inverted ouput
            else if(outputInverted){
                faultCode = 3;
            }
            //Determine if stuck at 0
            else if(lastResult == 0 && failCount > 0){
                faultCode = 4;
            }
            
            //Determine if stuck at 1
            else if(lastResult == 1 && failCount > 0){
                faultCode = 5;
            }
        
            //Print Circuit analysis
            cout << "Case " << testCase << ": ";

            //Used to print prompt of reason for incorrect circuit performance if any
            switch(faultCode) {
                case 1 :
                    cout << "No faults detected" << endl;
                    break;
                case 2 :
                    cout << "Unable to totally classify the failure" << endl;
                    break;
                case 3 : 
                    cout << "Gate " << failgate + 1 << " is failing; output inverted" << endl;
                    break;
                case 4 :
                    cout << "Gate " << failgate + 1 << " is failing; output stuck at 0" << endl;
                    break;
                case 5 :
                    cout << "Gate " << failgate + 1 << " is failing; output stuck at 1" << endl;
                    break;
            }
        } 
    }while(start);

    return 0;
}