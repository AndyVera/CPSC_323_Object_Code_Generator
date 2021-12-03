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
void Opt_Decleration_List_v2();
void Declaration_list_v2();
void Declaration_v2();
void IDs_v2();
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
  }
  else{
    cout << "What was expected was a '#'\n";
  }

}

#endif /*ObjectCodeGenerator_h*/
