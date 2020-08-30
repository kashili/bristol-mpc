//todo
/*
 * ZKInterface format: todo: convert one of existing 3 circuits into R1CS format
 */
#include "include/bristol.h"
#include "include/parser.h"
#include <iostream>
#include <string>
#include <vector>

void evaluateBinaryGates(std::string fn, //use const &/reference. copy is expensive
                         std::string leftInput = "0010101101100010101010101000101010101001010110110011011110001010",
                         std::string rightInput = "0000010101101100010101010101000101010101001010110110011011110000")
{
        Parser circuitFile(fn);
        Bristol* circuit = new Bristol;
        std::vector<std::vector<std::string>> gates = circuitFile.parse();

        circuit->convertMetaInfo(gates);
        char* leftWires = circuit->convertLeftInput(leftInput);
        char* rightWires = circuit->convertRightInput(rightInput); 
        std::vector<unsigned int> outputWires = circuit->evaluateBinaryGate(gates, leftWires, rightWires);//todo: use reference

        std::cout<<leftInput<<std::endl;
        std::cout<<rightInput<<std::endl;
        circuit->print(outputWires);
        std::cout<<std::endl;

        delete circuit;
}

void evaluateUnaryGates(std::string fn,  std::string leftInput = "0010101101100010101010101000101010101001010110110011011110001010")
{
    Parser circuitFile(fn);
    Bristol* circuit = new Bristol; //todo: use smart pointers to avoid explicit delete
    std::vector<std::vector<std::string>> gates = circuitFile.parse();
    circuit->convertMetaInfo(gates);
    char* leftWires = circuit->convertLeftInput(leftInput);

    std::vector<unsigned int> outputWires = circuit->evaluateUnaryGate(gates, leftWires );

    std::cout<<leftInput<<std::endl;

    circuit->print(outputWires);
    std::cout<<std::endl;

    delete circuit;
}

int main(int argc, char** argv)
{
    std::cout << "=============================   adder64  ==============================" << std::endl;
    evaluateBinaryGates("..\\..\\data\\circuit-formats\\adder64.txt"); //0011000011001110111111111101101111111110100001101001111001111010

    std::cout << "=============================   substract64  ==============================" << std::endl;
    evaluateBinaryGates("..\\..\\data\\circuit-formats\\sub64.txt" );//0010010111110110010101010011100101010100001011111101000010011010

    std::cout << "=============================   neg64  ==============================" << std::endl; //todo: fix EQW gate so following return right value
    evaluateUnaryGates("..\\..\\data\\circuit-formats\\neg64.txt" ); //1010110101001001100011111111111


     std::cout << "=============================   mul64  ==============================" << std::endl;
     evaluateBinaryGates("..\\..\\data\\circuit-formats\\mult64.txt","0000000000000000000000000000000000000000000000000000000000001010","0000000000000000000000000000000000000000000000000000000000000011");//0000000000000000000000000000000000000000000000000000000000011110

    std::cout << "=============================   mul128  ==============================" << std::endl;
    evaluateBinaryGates("..\\..\\data\\circuit-formats\\mult2_64.txt" );//111010110100100101101010001100110001010101011000010100001010101101111110010000011110011001000011110100110000110101100000


    std::cout << "=============================   div64  ==============================" << std::endl;
    evaluateBinaryGates("..\\..\\data\\circuit-formats\\divide64.txt" );//1000


    std::cout << "=============================   unsigneddiv64  ==============================" << std::endl;
    evaluateBinaryGates("..\\..\\data\\circuit-formats\\udivide64.txt" );//1000


    std::cout << "=============================   EQZ  ==============================" << std::endl;
    evaluateUnaryGates("..\\..\\data\\circuit-formats\\zero_equal.txt" ); //0


    std::cout << "=============================   end of all tests ==============================" << std::endl;
    return 0;
}

