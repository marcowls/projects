#include "table.h"
#include "word.h"
using namespace std;

class Lex{

public:
  static const int JUNK = -1,NUMBER = 0, IDENTIFIER = 1,PLUS=2,MINUS=3,TIMES=4, DIVIDE=5,IF=6, WRITE=7, READ=8, LBRACK=9, RBRACK=10, LPAR=11, RPAR=12, BEGIN=13, SETEQ=14, GOTO=15, LT=16, GT=17, LE=18, GE=19, EQ=20, NE=21, EOLN=22, END=23, COLON=24, HALT=25, MODULO=26;

private:
  Table symbols;
  int loc;
  int tokenLoc;
  Word line; //stores the line to be anayzed
  Word token; //tokens
  void loadTable();
  int getSymbol();
  int getLetter();
  int getNumber();

public:
  Lex();
  int next();
  bool atEnd();
  Word word();
  void reset(int p = 0);
  int position();
  void setString(const Word & w);
  Word peek();
};
