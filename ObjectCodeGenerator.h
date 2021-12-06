#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "SyntaxAddOn.h"

#ifndef ObjectCodeGenerator_h
#define ObjectCodeGenerator_h

// All the variables needed
Lexeme token1;
Lexeme save;
int addr;
Lexeme relop;

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
void Statement_List_v2();//
void Statement_v2();//
void Compound_v2();//
void Assign_v2();//
void If_v2();
void Return_v2();
void Print_v2();
void Scan_v2();
void While_v2();//
void Condition_v2();//
void Relop_v2();//
void Expression_v2();//
void Expression_prime_v2();//
void Term_v2();//
void Term_prime_v2();//
void Factor_v2();//


void simplified_Rat21F(){

  token1 = Lexer();
  assembly_code main_table[1000];

  if(token1.lexeme_word == "#"){
      cout << "The token that was read was: " << token1.lexeme_word << "\n";
      token1 = Lexer();

      cout << "\n--THIS IS OPT_DECLERATION_LIST_V2--\n";
      Opt_Decleration_List_v2();

      cout << "\n--THS IS THE STATEMENT_LIST_V2--\n";
      Statement_List_v2();

      //cout << "\nCurrent token1 value is: " << token1.lexeme_word << "\n";
      if(token1.lexeme_word == "#"){
        cout << "The token that was read was: " << token1.lexeme_word << "\n";
      }
      else {
        cout << "What was expected was a '#'\n";
      }
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
    //token1 = Lexer();
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

void Statement_List_v2(){
  Statement_v2();
}
void Statement_v2(){
  token1 = Lexer();
  Compound_v2();
  Assign_v2();
  While_v2();
}

void Compound_v2(){
  if (token1.lexeme_word == "{"){
    Statement_List_v2();
    if (token1.lexeme_word == "}"){
      ;
    }
    else {
      cout << "What was expected was an '}'\n";
    }
  }
}

void Assign_v2(){
    if (token1.lexeme_token == "Identifier"){
      cout << "What was read in the Assign function first is: " << token1.lexeme_word << "\n";
      save = token1;
      token1 = Lexer();

      if(token1.lexeme_word == "="){
        cout << "What was read in the Assign function second is: " << token1.lexeme_word << "\n";
        token1 = Lexer();

        Expression_v2();
        //instruction
        //cout << "Current token1 value is: " << token1.lexeme_word << "\n";
        if(token1.lexeme_word == ";"){
          cout << "What was read was a semicolon (;)\n";
          token1 = Lexer();
        }
        else {
          cout << "What was expected was a semicolon (;)\n";
        }
      }
      else {
        cout << "What was expected was an '='\n";
      }
    }
    // else {
    //   cout << "What was expected was an Identifier\n";
    // }
}

void Expression_v2(){
  Term_v2();
  Expression_prime_v2();
}

void Term_v2(){
  Factor_v2();
  Term_prime_v2();
}

void Factor_v2(){
  if (token1.lexeme_token == "Identifier"){
    cout << "The Identifier that was read in was: " << token1.lexeme_word << "\n";
    //instruction
    token1 = Lexer();
  }
  else {
    cout << "What was expected was an Identifier\n";
  }
}

void Term_prime_v2(){
  if (token1.lexeme_word == "*"){
    cout << "What was read in was: " << token1.lexeme_word << "\n";
    token1 = Lexer();
    Factor_v2();
    //instruction
    Term_prime_v2();
  }
}

void Expression_prime_v2(){
  if(token1.lexeme_word == "+"){
    cout << "What was read in was: " << token1.lexeme_word << "\n";
    token1 = Lexer();
    Term_v2();
    //instruction
    Expression_prime_v2();

  }
}

void While_v2(){
  if(token1.lexeme_word == "while"){
    //addr = adressnum
    //instruction
    cout << "What was read in the While function first was: " << token1.lexeme_word << "\n";
    token1 = Lexer();

    if(token1.lexeme_word == "(") {
      cout << "What was read was a: " << token1.lexeme_word << "\n";
      token1 = Lexer();

      Condition_v2();
      if(token1.lexeme_word == ")"){
        cout << "What was read in was a: " << token1.lexeme_word << "\n";
        //token1 = Lexer();

        Statement_v2();
        //instructions
        //token1 = Lexer();
      }
      else {
        cout << "What was expected was a: ')'\n";
      }
    }
    else {
      cout << "What was expected was a '('\n";
    }
  }
}

void Condition_v2(){
  Expression_v2();

  if(token1.lexeme_token == "Operator"){
    cout << "The Relational Operator that was read in was: " << token1.lexeme_word << "\n";
    relop = token1;

    token1 = Lexer();
    Expression_v2();

    //instructions
  }
  else {
    cout << "What was expected was a Relational Operator\n";
  }
}

#endif /*ObjectCodeGenerator_h*/
