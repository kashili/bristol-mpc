
#include "../include/bristol.h"

#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>

int Bristol::getOutputBitLength(){
    return outputBitLength;
}

void Bristol::convertMetaInfo(std::vector<std::vector<std::string>> gates)
{
    nGates = std::stoi(gates[0][0]);
    nWires = std::stoi(gates[0][1]);

    nInputs = std::stoi(gates[1][0]);
    inputBitLength = std::stoi(gates[1][1]);

    nOutputs = std::stoi(gates[2][0]);
    outputBitLength = std::stoi(gates[2][1]);
}

char* Bristol::convertLeftInput(std::string input)
{
    static char convertedLeftInput[64];
    leftInput = input;
    strcpy(convertedLeftInput, leftInput.c_str());
    return convertedLeftInput;
}

char* Bristol::convertRightInput(std::string input)
{
    static char convertedRightInput[64];
    rightInput = input;
    strcpy(convertedRightInput, rightInput.c_str());
    return convertedRightInput;
}

std::vector<unsigned int> Bristol::evaluateBinaryGate(const std::vector<std::vector<std::string>>& gates, char* leftWires, char* rightWires)
{
    unsigned int wires[nWires];
    int index;
    for (index = 63; index >= 0; --index) //todo: take out hard coded values
    {
        wires[index] = *leftWires - 48;
        leftWires++;
    }
    for (index = 127; index >= 64; --index)
    {
        wires[index] = *rightWires - 48;
        rightWires++;
    }
    for (index = 4; index < gates.size(); ++index) //ignore first 4 lines of circuit file and start from 4th index
    {
        if (gates[index].size() == 6) //binary gate
        {
            if (gates[index][5] == "XOR") //todo enums as type identifiers
            {
                wires[std::stoi(gates[index][4])] = wires[std::stoi(gates[index][2])] ^ wires[std::stoi(gates[index][3])];

            }

            else if (gates[index][5] == "AND")
            {
                wires[std::stoi(gates[index][4])] = wires[std::stoi(gates[index][2])] & wires[std::stoi(gates[index][3])];

            }
        }

        else if (gates[index].size() == 5) //unary gate
        {
            if (gates[index][4] == "INV")
            {
                wires[std::stoi(gates[index][3])] = !wires[std::stoi(gates[index][2])];
            }
        }
    }

    std::cout << std::endl;

    output.resize(nWires);
    std::copy(wires, wires + nWires, output.begin());

    return output;
}


std::vector<unsigned int> Bristol::evaluateUnaryGate(const std::vector<std::vector<std::string>>& gates, char* leftWires ) //todo
{
    unsigned int wires[nWires];
    int index;
    for (index = 63; index >= 0; --index)
    {
        wires[index] = *leftWires - 48;
        leftWires++;
    }

    for (index = 4; index < gates.size(); ++index) //ignore first 4 lines of circuit file and start from 4th index
    {
        if (gates[index].size() == 6) //binary gate
        {
            if (gates[index][5] == "XOR")
            {
                wires[std::stoi(gates[index][4])] = wires[std::stoi(gates[index][2])] ^ wires[std::stoi(gates[index][3])];

            }

            else if (gates[index][5] == "AND")
            {
                wires[std::stoi(gates[index][4])] = wires[std::stoi(gates[index][2])] & wires[std::stoi(gates[index][3])];

            }
        }

        else if (gates[index].size() == 5) //unary gate
        {
            if (gates[index][4] == "INV")
            {
                wires[std::stoi(gates[index][3])] = !wires[std::stoi(gates[index][2])];
            }
            else if (gates[index][4] == "EQW")
            {
                wires[std::stoi(gates[index][3])] = wires[std::stoi(gates[index][2])];
            }
        }
    }

    std::cout << std::endl;

    output.resize(nWires);
    std::copy(wires, wires + nWires, output.begin());

    return output;
}

void Bristol::print(std::vector<unsigned int> wires_temp)
{
    int count = 0;
    int size = outputBitLength * nOutputs;
    int index;

    if (size == 128)  //todo: how about more than 2 blocks of 64
    {
        std::vector<unsigned int> lsbOutputWireIndex;
        int lsbCounter = 0;

        for (index = nWires - 1; index > 0; --index)
        {
            lsbOutputWireIndex.push_back(index);
            lsbCounter += 1;
            if (lsbCounter >= 64)
                break;
        }

        std::vector<unsigned int> msbOutputWireIndex;
        int msbCounter = 0;

        for (index = nWires - 65; index > 0; --index)
        {
            msbOutputWireIndex.push_back(index);
            msbCounter += 1;
            if (msbCounter >= 64)
                break;
        }

        for (std::vector<unsigned int>::iterator it = msbOutputWireIndex.begin(); it != msbOutputWireIndex.end(); ++it)
        {
            std::cout << wires_temp[*it];
        }

        for (std::vector<unsigned int>::iterator it = lsbOutputWireIndex.begin(); it != lsbOutputWireIndex.end(); ++it)
        {
            std::cout << wires_temp[*it];
        }
    }
    else {
        std::vector<unsigned int> outputWireIndex;
        for (int i = nWires - 1; i > 0; --i) {
            outputWireIndex.push_back(i);
            count += 1;
            if (count >= size)
                break;
        }
        for (std::vector<unsigned int>::iterator it = outputWireIndex.begin(); it != outputWireIndex.end(); ++it) {
            std::cout << wires_temp[*it];
        }
    }
    std::cout << std::endl;
}