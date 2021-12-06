#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "SyntaxAddOn.h"

#ifndef ObjectCodeGenerator_h
#define ObjectCodeGenerator_h

// All the variables needed
Lexeme token1;

struct assembly_code {
  int step_num;
  string opertion;
  int address;
};

// Declared all the functions needed corresponding to the Partial Solution given
void simplified_Rat21F();
void Opt_Decleration_List_v2(); //
void Declaration_list_v2(); //
void Declaration_v2(); //
void Qualifier_v2(); //
void IDs_v2(); //
void Statement_List_v2();
void Statement_v2();
void Compound_v2();
void Assign_v2();
void If_v2();
void Return_v2();
void Print_v2();
void Scan_v2();
void While_v2();
void Condition_v2();
void Relop_v2();
void Expression_v2();
void Expression_prime_v2();
void Term_v2();
void Term_prime_v2();
void Factor_v2();


void simplified_Rat21F(){

  token1 = Lexer();
  assembly_code main_table[1000];

  if(token1.lexeme_word == "#"){
      cout << "The token that was read was: " << token1.lexeme_word << "\n";
      token1 = Lexer();

      cout << "\n--THIS IS OPT_DECLERATION_LIST_V2--";
      Opt_Decleration_List_v2();

      cout << "\n--THS IS THE STATEMENT_LIST_V2--\n";


  }
  else{
    cout << "What was expected was a '#'\n";
  }
}

void Opt_Decleration_List_v2(){
  Declaration_list_v2();
}
void Declaration_list_v2(){
  Declaration_v2();

  if(token1.lexeme_word == ";"){
    cout << "What was read was a semicolon\n";
    token1 = Lexer();
  }
  else{
    cout << "What was expected was a ';'\n";
  }
}
void Declaration_v2(){
  Qualifier_v2();
  IDs_v2();
}

void Qualifier_v2(){
  if(token1.lexeme_word == "integer" || token1.lexeme_word == "boolean"){
    cout << "What was read in Qualifier function was: " << token1.lexeme_word << "\n";
    token1 = Lexer();
  }
  else {
    cout << "What was expected was 'integer' or boolean\n";
  }
}

void IDs_v2(){
  if (token1.lexeme_token == "Identifier"){
    cout << "The Identifier that was read was: " << token1.lexeme_word << "\n";
    token1 = Lexer();
    if(token1.lexeme_word == ","){
      cout << "A comman was read\n";
      token1 = Lexer();
      IDs_v2();
    }
  }
  else {
    cout << "What was expected was an Identifier\n";
  }
}

#endif /*ObjectCodeGenerator_h*/
