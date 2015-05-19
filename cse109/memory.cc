/*
Marc Greenspan
mag216
cse109
p4

This class represents the implementation of the memory class  
 */
#include "memory.h"

//no-arg constuctor, sets value = 0
Memory :: Memory() {

  value = 0;
  
}

//one-arg constuctor, sets value = the num passed in
Memory :: Memory(int num){

  value = num;

}

//copy constructor, copys the value in memory
Memory :: Memory(const Memory & mem){

  value = mem.value;
 
}

//sets the memory location to a vaule of num
Memory &  Memory :: set(int num){

  value = num;
  return *this;
  
}

//gets the content of the memory
int Memory :: get() const {

  // check(value == 0, "Error: nothing stored in memory");

  if(value == 0){
    cout << "Error: nothing stored in memory " << endl;
    exit(1);

  }
  
  return value;

}

void Memory :: check(bool good, string message){

  if(good){
    cout << message;
    exit(1);

  }
  
}
