#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "SyntaxAddOn.h"

#ifndef SyntaxAnalyzerFunctions_h
#define SyntaxAnalyzerFunctions_h

//Lexem structs used during SA
Lexeme a;
Lexeme temp;
Lexeme temp2;
Lexeme temp3;
Lexeme temp4;
Lexeme temp5;

// Flags that aid if there are any saved values and other functions
int second_time = 0;
int holding_something = 0;
int holding_something2 = 0;
int holding_something3 = 0;
int holding_something4 = 0;
int scanned_used = 0;
int return_semi_used = 0;


//Function Definitions
void Rat21F ();
void Opt_Function_Definitions ();
void Function_Definitions ();
void Function ();
void Opt_Parameter_List ();
void Parameter_List ();
void Parameter ();
void Qualifier ();
void Body ();
void Opt_Decleration_List ();
void Decleration_list ();
void Decleration ();
void IDs ();
void Statement_List();
void Statement ();
void Compound ();
void Assign ();
void If ();
void If_prime ();
void Return ();
void Print ();
void Scan ();
void While ();
void Condition ();
void Relop ();
void Expression ();
void Expression_prime ();
void Term ();
void Term_prime ();
void Factor ();
void Primary ();


//The Syntax Functions implemented

// Rule 1: Starts the Syntax Analyzer
void Rat21F (){
  Opt_Function_Definitions();

  a = Lexer();
  ////cout << "\nTesting what lexer is: " << a.lexeme_word << "\n";
  if ( a.lexeme_word == "#"){
    //cout << a.lexeme_word << " ";
    Opt_Decleration_List();
    Statement_List();

    a = Lexer();
    if ( a.lexeme_word == "#"){
      //cout << a.lexeme_word << " ";
    }
    else {
      //Error Messages
      outputfile << "Error in Line: " << line_number << '\n';
      outputfile << "What was expected was a #\n";
    }
  }
  else {
    //cout << "What is expected is a '#'\n";
  }


}

//Rule 2
void Opt_Function_Definitions(){
  Function_Definitions();
}
//Rule 3
void Function_Definitions(){
  Function();
}

//Rule 4
void Function() {
 a = Lexer();

  if (a.lexeme_word == "function"){
    // Prints Syntax Rules
    outputfile << "<Opt Function Definitions> ::= <Function Definitions>  |  <Empty>\n";
    outputfile << "<Function Definitions> ::= <Function> | <Function> <Function Definitions>\n";
    outputfile << "function  <Identifier> ( <Opt Parameter List> )  <Opt Declaration List>  <Body>\n";
    //cout << a.lexeme_word << " ";
    a = Lexer();

    //Inner Loop 2
    if (a.lexeme_token == "Identifier"){
      // Prints Syntax Rules
      outputfile << "function  <Identifier>   ( <Opt Parameter List> )  <Opt Declaration List>  <Body>\n";
      //cout << a.lexeme_word << " ";
      a = Lexer();

      //Inner Loop 1
      if (a.lexeme_word == "("){
        // Prints Syntax Rules
        outputfile << "function  <Identifier>   ( <Opt Parameter List> )  <Opt Declaration List>  <Body>\n";
        //cout << a.lexeme_word << " ";
        Opt_Parameter_List();


        a = temp;
        ////cout << "\nlexeme after coming from Opt_Parameter_List is: " << a.lexeme_word << "--\n";

        if ( a.lexeme_word == ")"){
          // Prints Syntax Rules
          outputfile << "function  <Identifier>   ( <Opt Parameter List> )  <Opt Declaration List>  <Body>\n";
          //cout << a.lexeme_word << " ";
          Opt_Decleration_List();

          Body();
        }
        else {
          // Error Messages
          outputfile << "Error in Line: " << line_number << '\n';
          outputfile << "What was expected was a ')'\n";
        }
      }
      else {
        // Error Messages
        outputfile << "Error in Line: " << line_number << '\n';
        outputfile << "What was expected is a '('\n";
      }
      //End of Inner Loop 1


    }
    else {
      // Error Messages
      outputfile << "Error in Line: " << line_number << '\n';
      outputfile << "What was expected is an 'Identifier'\n";
    }
    //End of Inner Loop 2
  }

  else {
    // Error Messages
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected was the keyword 'function'\n";
  }
}
//Rule 5
void Opt_Parameter_List(){
  Parameter_List();
}
//Rule 6
void Parameter_List(){
  Parameter();

    a = Lexer();
    if (a.lexeme_word == ")");
    temp = a;
  if( a.lexeme_word == ","){
    //cout << a.lexeme_word << " ";
    Parameter_List();
  }
}
//Rule 7
void Parameter(){
  IDs();
  Qualifier();
  //Prints out Syntax Rules
  outputfile << "<Opt Parameter List> ::=  <Parameter List>    |     <Empty>\n";
  outputfile << "<Parameter List>  ::=  <Parameter>    |     <Parameter> , <Parameter List>\n";
  outputfile << "<Parameter> ::=  <IDs >  <Qualifier\n";
}

void IDs(){
    a = Lexer();

    // cout << "\nTesting IDs output: " << ""

  if (a.lexeme_token == "Identifier"){
      //Prints out Syntax Rules
      outputfile << "<IDs> ::=     <Identifier>    | <Identifier>, <IDs> \n";
      //cout << a.lexeme_word << " ";
  }

  else {
    //Prints out Error Messages
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected is an 'Identifier'\n";
  }
}
//Rule 8
void Qualifier(){

  if ( second_time == 0){
  a = Lexer();
  }

  else if ( second_time == 1){
    a = temp2;
  }

  if (a.lexeme_word == "integer" || a.lexeme_word == "boolean" || a.lexeme_word == "real"){
    //Prints out Syntax Rules
    outputfile << "<Qualifier> ::= integer    |    boolean    |  real\n";
    //cout << a.lexeme_word << " ";
  }
  else {
    //Print out Error Message
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected was either an 'integer', 'boolean', or 'real'\n";
  }
}

//Rule 10
void Opt_Decleration_List(){
  //cout << "\nWorking #8\n";
  Decleration_list();
}

//Rule 11
void Decleration_list(){
  //cout << "Working #9\n";
  Decleration();
}

//Rule 12
void Decleration(){
  //cout << "Working #10\n";
    //cout << "\n";

  Qualifier();
  IDs();
  //Prints out Syntax Rules
  outputfile << "<Opt Declaration List> ::= <Declaration List>   |    <Empty>\n";
  outputfile << "<Declaration List>  := <Declaration> ;     |     <Declaration> ; <Declaration List>\n";
  outputfile << "<Declaration> ::=   <Qualifier > <IDs>\n";

  second_time = 0;
  a = Lexer();
  if( a.lexeme_word == ";"){
    //cout << a.lexeme_word << " ";
    a = Lexer();

    if (a.lexeme_token == "Keyword" ){
      second_time = 1;
      temp2 = a;
      Decleration();
    }
    else {
      temp = a;
      holding_something4 = 1;
      ////cout << "\nTesting what temp is: " << temp.lexeme_word << "\n";
    }
  }
  else {
    //Prints out Error Message
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected was a ';'\n";
  }
}

//Rule 9
void Body(){
  a = temp;
  ////cout << "\nTesting: " << a.lexeme_word << "\n";
  if ( a.lexeme_word == "{"){
    //Prints out Syntax Rule
    outputfile << "<Body>  ::=  {  < Statement List>  }\n";
    //cout << a.lexeme_word << " ";
    Statement_List();

    a = Lexer();
      if (a.lexeme_word == "}"){
        //cout << a.lexeme_word << " ";
      }
      else {
        //Error Message
        outputfile << "Error in Line: " << line_number << '\n';
        outputfile << "What was expected was a '}'\n";
      }
  }
  else {
    //Error Message
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected was a '{'\n";
  }
}
//Rule 14
void Statement_List(){
  Statement();
}

//Rule 15
void Statement(){
  if (holding_something4 == 1){
    a = temp;
    holding_something4 = 0 ;
  }
  else{
  a = Lexer();
}

  ////cout << "\ntesting: " << a.lexeme_word << "\n";
    if (a.lexeme_word == "{"){
      outputfile << "<Statement> ::=   <Compound>  |  <Assign>  |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While> \n";
      //cout << a.lexeme_word << " ";
      Compound();
    }
    //when analyzing the lexeme it will go to the appropriate function/syntax rule
    else if (a.lexeme_token == "Identifier"){
      outputfile << "<Statement> ::=   <Compound>  |  <Assign>  |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While> \n";
      //cout << a.lexeme_word << " ";
      Assign();
    }
    else if (a.lexeme_word == "if"){
      outputfile << "<Statement> ::=   <Compound>  |  <Assign>  |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While> \n";
      //cout << a.lexeme_word << " ";
      If();
    }
    else if (a.lexeme_word == "return"){
      outputfile << "<Statement> ::=   <Compound>  |  <Assign>  |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While> \n";
      //cout << a.lexeme_word << " ";
      Return();
    }
    else if (a.lexeme_word == "put"){
      outputfile << "<Statement> ::=   <Compound>  |  <Assign>  |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While> \n";
      //cout << a.lexeme_word << " ";
      Print();
    }
    else if (a.lexeme_word == "get"){
      outputfile << "<Statement> ::=   <Compound>  |  <Assign>  |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While> \n";
      //cout << a.lexeme_word << " ";
      Scan();
    }
    else if (a.lexeme_word == "while"){
      outputfile << "<Statement> ::=   <Compound>  |  <Assign>  |   <If>  |  <Return>   | <Print>   |   <Scan>   |  <While> \n";
      //cout << a.lexeme_word << " ";
      While();
    }
    else if (a.lexeme_word != "{" && a.lexeme_token != "Identifier" && a.lexeme_word != "if" && a.lexeme_word != "return" && a.lexeme_word != "put" && a.lexeme_word != "get" && a.lexeme_word != "while" ){
      //Error Message
      outputfile << "Error in Line: " << line_number << '\n';
      outputfile << "What was expected were either '{', an 'Identifier', 'if', 'return', 'put', 'get', or 'while'\n";

    }
}
//Rule 16
void Compound(){
  outputfile << "<Compound> ::=   {  <Statement List>  }\n";
  Statement_List();
}
//Rule 17
void Assign() {
  a = Lexer();

  if (a.lexeme_word == "="){
    outputfile << "<Assign> ::=     <Identifier> = <Expression>\n";
    //cout << a.lexeme_word << " ";
    Expression();

    if (holding_something == 1){
      a = temp;
      holding_something = 0;
    }
    else {
      a = Lexer();
    }
    if ( a.lexeme_word == ";"){
      //cout << a.lexeme_word << " ";
    }
    else {
      outputfile << "Error in Line: " << line_number << '\n';
      outputfile << "what was expected was an ';'\n";
    }
  }
  else {
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected was a '='\n";
  }
}

//Rule 18
void Expression(){
  Term();
  Expression_prime();
}
//Rule 28
void Term(){
  Factor();
  Term_prime();
}
//Rule 30
void Factor(){
  Primary();
}
//Rule 31
void Primary(){
  if (holding_something2 == 1){
    a = temp5;
    holding_something2 = 0;
  }
  else{
  a = Lexer();
  }
  //cout << "\nTesting: " << a.lexeme_word << "\n";
  if (a.lexeme_token == "Integer"){
    outputfile << "<Expression>  ::=    <Term> <Expression’>   |    <Term>\n";
    outputfile << "<Term>    ::=     <Factor> <Term’>    |   <Factor>\n";
    outputfile << "<Factor> ::= <Primary>\n";
    outputfile << "<Primary> ::=     <Identifier>  |  <Integer>  |   <Identifier>  ( <IDs> )   |   ( <Expression> )   |  <Real>  |   true   |  false \n";
    //cout << a.lexeme_word << " ";
  }
  else if (a.lexeme_word == "("){
    outputfile << "<Expression>  ::=    <Term> <Expression’>   |    <Term>\n";
    outputfile << "<Term>    ::=     <Factor> <Term’>    |   <Factor>\n";
    outputfile << "<Factor> ::= <Primary>\n";
    outputfile << "<Primary> ::=     <Identifier>  |  <Integer>  |   <Identifier>  ( <IDs> )   |   ( <Expression> )   |  <Real>  |   true   |  false \n";
    //cout << a.lexeme_word << " ";
    Expression();
  }
  else if (a.lexeme_token == "Real"){
    outputfile << "<Expression>  ::=    <Term> <Expression’>   |    <Term>\n";
    outputfile << "<Term>    ::=     <Factor> <Term’>    |   <Factor>\n";
    outputfile << "<Factor> ::= <Primary>\n";
    outputfile << "<Primary> ::=     <Identifier>  |  <Integer>  |   <Identifier>  ( <IDs> )   |   ( <Expression> )   |  <Real>  |   true   |  false \n";
    //cout << a.lexeme_word << " ";
  }
  else if ( a.lexeme_word == "true"){
    outputfile << "<Expression>  ::=    <Term> <Expression’>   |    <Term>\n";
    outputfile << "<Term>    ::=     <Factor> <Term’>    |   <Factor>\n";
    outputfile << "<Factor> ::= <Primary>\n";
    outputfile << "<Primary> ::=     <Identifier>  |  <Integer>  |   <Identifier>  ( <IDs> )   |   ( <Expression> )   |  <Real>  |   true   |  false \n";
    //cout << a.lexeme_word << " ";
  }
  else if ( a.lexeme_word == "false"){
    outputfile << "<Expression>  ::=    <Term> <Expression’>   |    <Term>\n";
    outputfile << "<Term>    ::=     <Factor> <Term’>    |   <Factor>\n";
    outputfile << "<Factor> ::= <Primary>\n";
    outputfile << "<Primary> ::=     <Identifier>  |  <Integer>  |   <Identifier>  ( <IDs> )   |   ( <Expression> )   |  <Real>  |   true   |  false \n";
    //cout << a.lexeme_word << " ";
  }
  else if (a.lexeme_token == "Identifier"){
    outputfile << "<Expression>  ::=    <Term> <Expression’>   |    <Term>\n";
    outputfile << "<Term>    ::=     <Factor> <Term’>    |   <Factor>\n";
    outputfile << "<Factor> ::= <Primary>\n";
    outputfile << "<Primary> ::=     <Identifier>  |  <Integer>  |   <Identifier>  ( <IDs> )   |   ( <Expression> )   |  <Real>  |   true   |  false \n";
    //cout << a.lexeme_word << " ";
    a = Lexer();
    holding_something = 1;
    temp4 = a;
    //cout << "\nTesting: " << a.lexeme_word << "\n";
    if (a.lexeme_word == "("){
      //cout << a.lexeme_word << " ";
      IDs();
      a = Lexer();
      if (a.lexeme_word == ")"){
        //cout << a.lexeme_word << " ";
      }
    }
  }
  else {
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected are either 'Integer', '(', 'Real', 'true', 'false', or an 'Identifier'\n";
  }

}

void Term_prime(){
  if (holding_something == 1){
    a = temp3;
    holding_something = 0;
  }
  else {
    a = Lexer();
  }
//cout << "\nTesting #12: " << a.lexeme_word << "\n";
  if(a.lexeme_word == "*" || a.lexeme_word == "/"){
    outputfile << "<Expression>  ::=    <Term> <Expression’>   |    <Term>\n";
    outputfile << "<Term>    ::=     <Factor> <Term’>    |   <Factor>\n";
    outputfile << "<Term’> ::= * <Factor> <Term’> | / <Factor> <Term’> | ε\n";
    //cout << a.lexeme_word << " ";
    holding_something = 0;
    Factor();
    Term_prime();
  }
  else {
    temp = a;
    holding_something = 1;
  }
}

//Rule 27
void Expression_prime (){
  if (holding_something == 1){
    a = temp;
  }
  else {
    a = Lexer();
  }

  if(a.lexeme_word == "+" || a.lexeme_word == "-"){
    outputfile << "Expression>  ::=    <Term> <Expression’>   |    <Term>\n";
    outputfile << "<Expression’> ::= + <Term> <Expression’> | -  <Term> <Expression’> | ε\n";
    //cout << a.lexeme_word << " " ;
    holding_something = 0;
    Term();
    Expression_prime();
  }
  else {
    temp = a;
    holding_something = 1;
    holding_something3 = 1;
  }
}
//18
void If(){
  a = Lexer();

//cout << "\nTesting: " << a.lexeme_word << "\n";
  if (a.lexeme_word == "("){
    //cout << a.lexeme_word << " ";
    Condition();

    if (a.lexeme_word == ")"){
      //cout << a.lexeme_word << " ";
      Statement();
      If_prime();

    }
    else {
      outputfile << "Error in Line: " << line_number << '\n';
      outputfile << "What was expected was ')'\n";
    }
  }
  else {
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected was '('\n";
  }
}
//Rule 24
void Condition(){
  outputfile << "<Condition> ::=     <Expression>  <Relop>   <Expression>\n";
  Expression();
  Relop();
  Expression();
}

//25
void Relop(){
  if (holding_something == 1 ) {
    a = temp4;
    holding_something = 0;
  }
  else{
    a = Lexer();
  }

  //NOTE: WITHINT THE CONDITION STATEMENT, EVERYTHING NEEDS TO BE ONE SPACE APART

  if (a.lexeme_word == "==" || a.lexeme_word == "!=" || a.lexeme_word == ">" || a.lexeme_word == "<" || a.lexeme_word == "<=" || a.lexeme_word == "=>") {
    outputfile << "<Relop> ::=        ==   |   !=    |   >     |   <    |  <=   |    => \n";
    //cout << a.lexeme_word << " ";

  }
  else {
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected were '==', '!=', '>', '<', '<=', or '=>'\n";
  }
}

//Rule 19
void If_prime(){

  a = Lexer();

  if(a.lexeme_word == "endif"){
    //cout << a.lexeme_word << " ";
  }

  else if (a.lexeme_word == "else"){
    //cout << a.lexeme_word << " ";
    Statement();

    if (scanned_used == 1){
    a = Lexer();
    }
    if (a.lexeme_word == "endif"){
      //cout << a.lexeme_word << " ";
    }
    else {
      outputfile << "Error in Line: " << line_number << '\n';
      outputfile << "What was expected was an 'endif'\n";

    }
  }
  else {
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected was an 'else'\n";
  }
}

//Rule 20
void Return(){
  a = Lexer();

  if( a.lexeme_word == ";"){
    //cout << a.lexeme_word << " ";
  }
  else if ( a.lexeme_word != ";"){
    holding_something2 = 1;
    temp5 = a;
    Expression();
  //  a = Lexer();
    if ( a.lexeme_word == ";"){
      outputfile << "Error in Line: " << line_number << '\n';
      outputfile << "What was expected was an ';'\n";
      //cout << a.lexeme_word << " ";

    }
  }
}

//Rule 21
void Print(){
  a = Lexer();

  if (a.lexeme_word == "("){
    //cout << a.lexeme_word << " ";
    Expression();


    if (a.lexeme_word == ")"){
      //cout << a.lexeme_word << " ";
      a = Lexer();
      if ( a.lexeme_word == ";"){
        //cout << a.lexeme_word << " ";
      }
      else {
        outputfile << "Error in Line: " << line_number << '\n';
        outputfile << "What was expected was an ';'\n";
      }
    }
    else {
      outputfile << "Error in Line: " << line_number << '\n';
      outputfile << "What was expected was an ')'\n";
    }
  }
  else {
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected was an '('\n";
  }
}

//Rule 22
void Scan(){
  a = Lexer();

  if (a.lexeme_word == "("){
    //cout << a.lexeme_word << " ";
    IDs();

    a = Lexer();
    if (a.lexeme_word == ")"){
      //cout << a.lexeme_word << " ";
      a = Lexer();
      if ( a.lexeme_word == ";"){
        //cout << a.lexeme_word << " ";
        scanned_used = 1;
      }
      else {
        outputfile << "Error in Line: " << line_number << '\n';
        outputfile << "What was expected was an ';'\n";
      }
    }
    else {
      outputfile << "Error in Line: " << line_number << '\n';
      outputfile << "What was expected was an ')'\n";
    }
  }
  else {
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected was an '('\n";
  }
}

//Rule 23
void While(){
  a = Lexer();

  if(a.lexeme_word == "("){
    //cout << a.lexeme_word << " ";
    Condition();

  //May or May Not Need It
  //  a = Lexer();

    if(a.lexeme_word == ")"){
      //cout << a.lexeme_word << " ";
      Statement();

      if ( a.lexeme_word == ";"){
        //cout << a.lexeme_word << " ";
      }
      else {
        outputfile << "Error in Line: " << line_number << '\n';
        outputfile << "What was expected was an ';'\n";
      }
    }
    else {
      outputfile << "Error in Line: " << line_number << '\n';
      outputfile << "What was expected was an ')'\n";
    }
  }
  else {
    outputfile << "Error in Line: " << line_number << '\n';
    outputfile << "What was expected was an '('\n";
  }
}
#endif /*SyntaxAnalyzerFunctions_h*/
