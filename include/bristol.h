

#ifndef BRISTOLFASHION_BRISTOL_H
#define BRISTOLFASHION_BRISTOL_H

#include <vector>
#include <string>

class Bristol
{
private:
    // meta info about circuit (first 3 lines)
    unsigned int nGates;
    unsigned int nWires;

    unsigned int nInputs;
    unsigned int  inputBitLength;

    unsigned int nOutputs;
    unsigned int outputBitLength;

    // Input strings to circuit
    std::string leftInput;
    std::string rightInput;

    //output string after evaluation
    std::vector<unsigned int> output;

public:

    Bristol(){};

    void convertMetaInfo(std::vector<std::vector<std::string>> gates);
    char* convertLeftInput(std::string input);
    char* convertRightInput(std::string right);
    int getOutputBitLength();

    std::vector<unsigned int> evaluateBinaryGate(const std::vector<std::vector<std::string>>& gates, char* leftWires, char* rightWires);
    std::vector<unsigned int> evaluateUnaryGate(const std::vector<std::vector<std::string>>& data_list, char* char_array1);

    void print(std::vector<unsigned int> output);


};
#endif //BRISTOLFASHION_BRISTOL_H
