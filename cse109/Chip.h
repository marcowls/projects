/*
Marc Greenspan
mag216
cse109
p4

This class is the header file for the class Chip. It represents and
instance of 200 bytes of memory that is used for intermidiate storage
and for a stack. Chip is a subclass of ALU
 */  
#include <iostream>
#include <cstdlib>
#include "alu.h"
#include "memory.h"

using namespace std;

class Chip: public ALU{

 public:
  const static int NUM_SIZE = 200; // constant to for the size of the memeory array
  
 protected:
  Memory memArray[NUM_SIZE]; //array of size 200 to represent 200 loctions			 //in a memory 
  int sp;// pointer that allows for an array to be used as a stack
  
 public: 
  Chip(); // no arg constructor for chip
  Chip(int reg1); //one arg constructor for chi[
  Chip(int reg1, int reg2); //two argument constructor for chip
  ~Chip(); //destructor for chip

  //this method pushes the conents of the accumulator to the stack
  Chip & push();

  //pops the top of the stack and discards 
  Chip & pop();

  //pops the top of the stack to a memory location of in one of the registers
  Chip & pop(int num);

  //puts the top of the stack in a memory location or one of the
  //registers. It does not remove anythring from the stack
  Chip & top(int num);

  //stores the contents of the accumulator in some memory location
  Chip & store(int num);

  //loads contents of some memory location into register 1
  Chip & load1(int num);

  //loads contents of some memory location into register 2
  Chip & load2(int num);
  
};
