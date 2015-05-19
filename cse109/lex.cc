#include "lex.h"

Lex::Lex(){
  loc = 0;
  tokenLoc = 0;
  loadTable();
}

void Lex::loadTable(){

  symbols["number"] = NUMBER; //
  symbols["IDENTIFIER"]= IDENTIFIER; //1
  symbols["+"] = PLUS; //2
  symbols["-"] = MINUS; //3
  symbols["*"] = TIMES; //4
  symbols["/"] = DIVIDE; //5
  symbols["IF"] = IF; //6
  symbols["WRITE"] = WRITE; //7
  symbols["READ"] = READ; //8
  symbols["["] = LBRACK; //9
  symbols["]"] = RBRACK; //10
  symbols["("] = LPAR; //11
  symbols[")"] = RPAR; //12
  symbols["BEGIN"] = BEGIN;//13
  symbols["SETEQ"] = SETEQ; //14
  symbols["GOTO"] = GOTO; //15
  symbols["<"] = LT; //16
  symbols[">"] = GT; //17
  symbols["<="] =LE; //18
  symbols[">="] = GE; //19
  symbols["="] = EQ; //20
  symbols["!="] = NE; //21
  symbols["$"] = EOLN; //22
  symbols["END"] = END; //23
  symbols[":"] = COLON; //24
  symbols["HALT"] = HALT; //25
  symbols["%"] = MODULO; //26
  }
  

void Lex::setString(const Word & w){
  line = w;
  loc = 0;
}

bool Lex::atEnd(){
  if(loc == line.length())
    return true;

  else
    return false;
}

void Lex::reset(int p){
  loc = p;
}

Word Lex::word(){
  return token;
}

int Lex::position(){
  return loc;
}

int Lex::next(){

  Word w = " ";
  token = w;
  tokenLoc = 0;
  
  if(line[loc] == '$')
    return EOLN;

  if(line[loc] == ';')
    return JUNK;

  while(!atEnd() && line[loc] == ' '){
    loc++;
  }

  if(line[loc] <= '9' && line[loc] >= '0')
    return getNumber();
    
  else if(line[loc] >= 'a' && line[loc] <= 'z')
    return getLetter();

  else
    return getSymbol();

  return JUNK;
}

int Lex::getLetter(){

  token[tokenLoc] = line[loc];
  loc++;
  tokenLoc++;

  while(line[loc] >= 'a' && line[loc] <= 'z'){
      token[tokenLoc] = line[loc];
      tokenLoc++;
      loc++;
    }

  if(symbols.inTable(line))
     return symbols[line];

  else
    return IDENTIFIER;
}
  
int Lex::getNumber(){

  tokenLoc = 0;
  token[tokenLoc] = line[loc];
  loc++;
  tokenLoc++;

  while(line[loc] >= '0' && line[loc] <= '9'){ 
    token[tokenLoc] = line[loc];
    tokenLoc++;
    loc++;
   }

  if(line[loc] == '.' && line[loc+1] >= '0' && line[loc+1] <= '9'){ 

    while(line[loc] >= '0' && line[loc] <= '9'){ 
      token[tokenLoc] = line[loc];
      tokenLoc++;
      loc++;
    }
  }

  if(symbols.inTable(line))
     return symbols[line];
  
  return NUMBER;
}
  
int Lex::getSymbol(){

  tokenLoc = 0;
  token[tokenLoc] = line[loc];
  tokenLoc++;
  loc++;

  if(line[loc] == '='  && !atEnd()){
    token[tokenLoc] = line[loc];
    tokenLoc++;
    loc++;
    }

  if(symbols.inTable(line))
    return symbols[line];

  return JUNK;
}

Word Lex::peek(){
  Word temp;
  temp = line;
  int tempLoc = loc;
  int tempToken = next();
  line = temp;
  loc = tempLoc;
  return tempToken;
}
