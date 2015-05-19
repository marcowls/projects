/*Marc Greenspan
  cse109
  kalafut
  p9
*/

#include "fullprog.h"

FullProg::FullProg():ProgChip(){}

FullProg::~FullProg() {}

void FullProg::doExpression(){
  doTerm();
  while(tok == lex.PLUS || tok == lex.MINUS){
  int savTok = tok;
    tok = lex.next();
    doTerm();
    pop(-2);
    pop(-1);
    if(savTok == lex.PLUS)
      op(ALU::ADD);

    else
      op(ALU::SUB);
    push();
  }
}

void FullProg::doTerm(){
  doFactor();
  while(tok == lex.TIMES || tok == lex.DIVIDE || tok == lex.MODULO){
    int savTok = tok;
    tok = lex.next();
    doTerm();
    pop(-2);
    pop(-1);
    if(savTok == lex.TIMES)
      op(ALU::MUL);

    if(savTok == lex.DIVIDE){
      check(get2() != 0, "Error: FullProg::doTerm() -> cannot divide by zero");
      op(ALU::DIV);
    }

    if(savTok == lex.MODULO)
      op(ALU::MOD);

    push();
  }
}

void FullProg::doFactor(){
  if(tok == lex.LPAR){
    tok = lex.next();
    doExpression();
    check(tok ==lex.RPAR, "Error: fullprog::doFactor()-> invalid synatx");
  }

  else{
    ProgChip::doExpression();
    push();
  }
  
}

  
void FullProg::check(bool b, string mess){
    if(!b){
      cout << mess << endl;
      exit(1);
    }
  }
  
