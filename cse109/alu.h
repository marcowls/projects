#ifndef ALU_H
#define ALU_H
#include <iostream>
#include <cstdlib>
using namespace std;

/*ADT for an ALU that has two registers, an accumulator, and the
  operations add, sub, mul, div, and mod
  All operations are on ints and take the form
   acc = reg1 <op> reg2
*/
class ALU{
protected:
  int reg1,reg2, //the two arithmetic registers
    accum;      // the accumulator

  void check(bool b,const char *mess)const;
  //if b is true, do nothing. If false, print error message (mess)
  //and exit
public:
  //constants for more readable calls to op(), where the
  //operation to be performed is specified
  static const int ADD=0, SUB=1, MUL=2, DIV=3, MOD=4;

  // Postconditions: reg1=r1, reg2=r2
  ALU(int r1=0,int r2=0);
  ALU(const ALU&a);
  ~ALU();

  //Postconditions: reg2 and accum unchanged
  //                reg1=x
  // return *this
  ALU & set1(int x);

  //Postconditions: reg2 and accum unchanged
  //                reg1=x
  // return *this
  ALU & set2(int x);

  //return contents of reg1
  int get1()const;

  //return contents of reg2
  int get2()const;

  //return contents of reg2
  int acc()const;

  //Preconditions: 0<=x<=4  (specifying which <op>)
  //Postconditions: accum = reg1 <op> reg2
  // where <op> == 0(ADD), 1(SUB), 2(MUL), 3(DIV), or 4(MOD)
  // return *this
  ALU & op(int x);

  //Display "{acc: xxx, reg1: yyy, reg2: zzz}"
  friend ostream & operator<<(ostream &out,const ALU &a);
};
#endif
