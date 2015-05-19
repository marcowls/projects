/*Marc Greenspan
  mag216
  cse109
  p8
*/

#include "ProgChip.h"
#include <cstdlib>
#include <fstream>

ProgChip::ProgChip():Chip(){
  pc = 0;
  tok = 0;
  steps = 0;
}

void ProgChip::load(ifstream &in){
  varCount = 0;
  cout << "Declaring variables"<<endl;
  doDeclaration(in);
  cout << "loading program" << endl;
  loadProgram(in);
  setInput(in);
  cout<<"Program successfully loaded..."<<endl; 
}

void ProgChip::loadProgram(ifstream & in){
  bool end = false;
  progSize = 0;
  readLine(in);
  while(in.good() && progSize < MAXSIZE && tok != lex.END){
    cout << progSize << ":" << program[progSize] << endl;
    lex.setString(program[progSize]);
    tok = lex.next();
    checkLabel();
    progSize++;
    readLine(in);
  }
  if(tok == lex.END)
    end = true;
  
    check(end, "Error 'end' expected");
}

void ProgChip::checkLabel(){

  if(!lex.atEnd()){
    if(tok == lex.IDENTIFIER &&  lex.peek() == lex.COLON){
      labelTable[lex.word()] = progSize;
    }
  }
}

void ProgChip::doDeclaration(ifstream & in){
  readLine(in);
  while(in.good() && tok != lex.BEGIN){
    cout<<"tok = " <<tok<<endl;
    if(tok == lex.IDENTIFIER && !varTable.inTable(lex.word())){
      addVar();
    }
    readLine(in);
  }
  check(tok == lex.BEGIN, "Error: ProgChip::doDelaration-> must begin program with 'BEGIN'");
}

void ProgChip::readLine(ifstream &in){
  in>>program[progSize];
  lex.setString(program[progSize]);
  tok = lex.next();
}

void ProgChip::run(bool v){
   cout << "-----------------------"<<endl;
  cout << "Running....."<< endl;
  lex.setString(program[pc]);
  tok=lex.next();
  skipLabel();

  while(pc < progSize && tok != lex.END && tok != lex.HALT){
     doLine();
    if(v){
      cout<<"[Step: "<<steps<<", line = "<<pc<<"]: "<<program[pc]<<endl;   
    }
    lex.setString(program[++pc]);
    tok=lex.next();
    skipLabel();
  }check(tok == Lex::HALT, "Error: program runs past end");
}

void ProgChip::doIdent(){
  if(tok == lex.IDENTIFIER){
    cout << program[progSize] << endl;
    check(varTable.inTable(lex.word()),"ProgChip::doIdent-> undefined variable");
    check(lex.peek() == Lex::EQ, "ProgChip::doIdent -> invalid syntax");
    doEquals();
  }
}

void ProgChip::skipLabel(){
  if (tok == lex.IDENTIFIER && lex.peek() == lex.COLON) {
    tok = lex.next();
    tok = lex.next();
  }
}

void ProgChip::doLine(){
  steps++;
  switch(tok){
  case Lex::IDENTIFIER: //1
    doEquals();
    break;
  case Lex::IF: // 6
   doIf();
   break;
  case Lex::READ: // 8
   doRead();
   break;
  case Lex::WRITE: //7
   doWrite();
   break;
  case Lex::GOTO: //15
   doGoTo();
   break;
  case Lex::EOLN: //22
   break;
  case Lex::HALT: //25
    doHalt();
    break;
 default:
   cout<<"Error: ProgChip::doLine->Invalid syntax";
   exit(1);
  }
}

void ProgChip::doGoTo(){
  check(lex.peek() == Lex::IDENTIFIER, "ProgChip::doGoto() invalid syntax");
    tok = lex.next();
    pc = labelTable[lex.word()] - 1;
}

void ProgChip::doIf(){
  tok = lex.next();
  if(doBoolExpression()){
    doGoTo();
  }

  else{
    lex.setString(program[pc]);
    tok = lex.next();
  }
}

bool ProgChip::doBoolExpression(){
  doExpression();
  push();
  int tempTok = tok;
  tok = lex.next();
  doExpression();
  push();
  top(-2);
  pop();
  top(-1);
  pop();
  switch(tempTok){
  case Lex::LT:
    if(reg1 < reg2){
      return true;
    }

    else{
      return false;
    }
      break;
      
    case Lex::LE:
      if(reg1 <= reg2)
      return true;

    else
      return false;
   
      break;
        
    case Lex::GT:
      if(reg1 > reg2){	
      return true;
    }

    else{
      return false;
    }
      break;
        
    case Lex::GE:
      if(reg1 >= reg2){
      return true;
    }

    else{
      return false;
    }
      break;
        
    case Lex::EQ:
      if(reg1  == reg2){
      return true;
    }

    else
      return false;
 
      break;
        
    case Lex::NE:
      if(reg1 != reg2)
      return true;

    else
      return false;
      
      break;

  default:
    check(false, "ProgChip::doBoolExpression() : Junk");
    
  }
  return false;
}

void ProgChip::doEquals(){
  int memLoc = varTable[lex.word()];
  tok = lex.next();
  if(tok == lex.SETEQ){
  tok = lex.next();
  doExpression();
  store(memLoc);
  }
}  

void ProgChip::doWrite(){
  tok = lex.next();
  doExpression();
  cout << "         OUTPUT ----> " << accum << endl;
}

void ProgChip::doExpression(){
  if(tok == lex.IDENTIFIER){
    check(varTable.inTable(lex.word()), "ProgChip::doExpression -> error: invalid identifier");
    accum = mem[varTable[lex.word()]].get();
    tok = lex.next();    
  }

  if(tok == lex.NUMBER){
    accum = lex.word().toInt();
    tok = lex.next();
  }
}

void ProgChip::doRead(){
  tok = lex.next();
  check(varTable.inTable(lex.word()),"Error: ProgChip::doRead->Invalid Syntax"); 
  getInput();
  int temp = varTable[lex.word()];
  store(temp);
  cout<< "INPUT  <-----" << accum  <<endl;
  
}

void ProgChip::addVar(){
  check(varCount < 20, "Error: Variable Memory full");
  varTable[lex.word()] = varCount;
  mem[varCount].set(0);
  varCount++;
}

void ProgChip::setInput(ifstream &in){
  Word w;
  in>>w;
  input.setString(w);
  inputTok = input.next();
}

void ProgChip::doHalt(){
  pc = progSize;
}

void ProgChip::getInput(){
  int flag = 1;
  check(inputTok == input.NUMBER || inputTok == input.MINUS, "Error: ProgChip::getInput-> invalid input");
  if(inputTok == input.MINUS){
    flag = -1;
    inputTok = input.next();
    check(inputTok == input.NUMBER, "Error: ProgChip::getInput->invalid synatx");
    inputTok = input.word().toInt() * flag;
  }
  
  else
    inputTok = input.word().toInt();
  
  
  accum = inputTok;
  inputTok = input.next();
}

void ProgChip::check(bool b, string mess){
  if(!b){
    cout << mess << endl;
    exit(1);
  }
}
