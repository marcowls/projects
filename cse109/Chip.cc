/*
Marc Greenspan
mag216
cse109
p4
This class represents a memory with 200 locations and a stack pointer
to have a stack
*/

#include "Chip.h"

//No arg constuctor, sets the stack pointer to the top of the stack
Chip :: Chip(): ALU(){

  sp = 199;
  
}

//One-arg constructor, sets the register1 in ALU to num and sets the
//stack pointer to the top of the stack  
Chip :: Chip(int num): ALU(num){

  sp = 199;
  
}

//two-arg constuctor that sets each register to num one and num two
//sets stack pointer to the top of stack
Chip :: Chip(int num1,int num2): ALU(num1,num2){

  sp = 199;
  
}

//destructor 
Chip :: ~Chip(){
  
}

//pushes contents of the accumulator onto the stack by calling the set
//method and decrementing the stack pointer
//pre: sp points to top of stack
//post: sp points to the new top of stack
Chip & Chip :: push(){

  memArray[sp].set(accum);
  sp--;
  return *this;

}

//takes the top of the stack off and discards itby incrementing the
//stack pointer and set the value of that me location
//pre: sp points to the top of stack
//post: sp spoints to the top of the new stack
Chip & Chip :: pop(){

  sp++;
  memArray[sp].set(0);
  return *this;
}


//takes the top of the stack and puts to memory location num or one of
//the two register
//checks for the value of num to see if it needs to put to the top  the
//register
//pre:sp points to the top of the stack
//post: sp points to the new top of the stack
Chip & Chip :: pop(int num){

  sp++;
  
  if(num == -1)
    reg1 = memArray[sp].get();  

  if(num == -2)
    reg2 = memArray[sp].get();

  else{
    accum = memArray[sp].get();
    store(num);
  }
 
  return *this;
  
}

//put the top of the stack in some memory location of in one of the
//two regsiters
//increment the stack pointer, check for where to put the top of the
//stack and decrement it
// sp is the same before and after the method
Chip & Chip :: top(int num){

  sp++;
  
  if(num == -1)
     reg1 = memArray[sp].get();
    
  if(num == -2)
    reg2 = memArray[sp].get();

  else{
    accum = memArray[sp].get();  
   store(num);
  }


  sp--;
  return *this;
}

//stors the contents of the accumulator in some memory location
//uses the set method to store the accum
//nothing chnages besides the location of the memory
Chip & Chip :: store(int num){

  memArray[num].set(accum);
  return *this;
  
}

//load the conetnts of some memory location into register one
//uses the get method to extract the value of the memory location
Chip & Chip :: load1(int num){

 reg1 = memArray[num].get();
 return *this;
 
}

//loads the contents of some memory location into register two
//uses the get method to extract the value of the memory location
Chip & Chip :: load2(int num){

  reg2 = memArray[num].get();
  return *this;
  
}
