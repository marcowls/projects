/*Marc Greenspan
  mag216
  cse109
  p8
*/

#include "chip.h"
#include "word.h"
#include "lex.h"
#include <fstream>


/*This class represents a parser for a Tiny program */
class ProgChip: public Chip{
public:
  //declaration of the static size of the program

  static const int MAXSIZE = 100;
  //Pre-condition: inherits all methods and variables from memory and
  //stack class
  ////Post: Inittiliazes the the tok and steps variables
  //no-arg constructor for ProgChip
  ProgChip();
  // Precondition: the closed program file is passed through from the main.
		  // Postcondtion: the file is opened, included the
		  // data and symbols files which are hardcoded into
		  // load.
		  // Also looks for any numbers at the end to take in
		  // as input. When the program is successfully
		  // loaded, it prints
		  // to tell the user that the program has loaded
  void load(ifstream &in);
  // Precondition: Sk  Program is not yet running and pc is set to 0.
  // Post: After checking the programn counter, it begins runnning the
  // program by calling the doLine() method
  void run(bool v);
  
  static void check(bool b, string mess);

protected:
  //array of words to store the whole program
  Word program[MAXSIZE];
  //numerous variables to keep track of where we are in the program
  int steps,inputTok,progSize,pc,tok,varCount;
  //two tables for variables and labels
  Table labelTable, varTable;
  //a lex for the input variables and the lex for each line
  Lex lex,input;
  //Pre:the program is intialized and stored in the program array
  //Post: 
  virtual void doDeclaration(ifstream &in);
  void doIdent();
  //Precondition:takes the current token and checks to see which
  //method to perform associated with that token
  //Post: The method associated with the token has been performed and
  //it checks the switch again after having the token changed in
  //another helper method
  void doLine();
  void doIf();
  bool doBoolExpression();
  void doExpression();
  void doGoTo();
  void readLine(ifstream &in);
  void doHalt();
  // Precondition: reads an identifier, number or input at the end of
  // the file
  // Post: If its an identifier, it will set the register to whatever
  // the identifier is. If it is a number, it sets the register to
  // that value, but as a double
  //If its input, it hold the token in a tempory variable because were
  // using the input Lex object. It then set the register to the input
  // as a double and prints the input
  void doRead();
  //Precondition:the tok is pointing to a write
  //Post: 
  void doWrite();
  void doEquals();
  void getInput();
  void setInput(ifstream &in);
  void loadProgram(ifstream&in);
  void addVar();
  void checkLabel();
  void skipLabel();
};
