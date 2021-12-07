#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "LexicalAnalyzer.h"

#ifndef ObjectCodeGenerator_h
#define ObjectCodeGenerator_h

// All the variables needed
Lexeme token1;
Lexeme save;
int addr;
Lexeme relop;
int index_num = 0;
int address_num = 7000;

struct assembly_code {
  int step_num;
  string operation;
  int address;
};

int jumz_addr;

assembly_code main_table[1000];
assembly_code list_element;

// Declared all the functions needed corresponding to the Partial Solution given
void simplified_Rat21F();//
void Opt_Decleration_List_v2(); //
void Declaration_list_v2(); //
void Declaration_v2(); //
void Qualifier_v2(); //
void IDs_v2(); //
void Statement_List_v2();//
void Statement_v2();//
void Compound_v2();//
void Assign_v2();//
void If_v2();//
void Return_v2(); //
void Print_v2();//
void Scan_v2();//
void While_v2();//
void Condition_v2();//
void Relop_v2();//
void Expression_v2();//
void Expression_prime_v2();//
void Term_v2();//
void Term_prime_v2();//
void Factor_v2();//
void print_assembly_table(assembly_code table[]);//

//The Syntax Analyzer for the Simplified Rat21F language
//with Object Code Generator
void simplified_Rat21F(){

  token1 = Lexer();

  if(token1.lexeme_word == "#"){
      token1 = Lexer();

      Opt_Decleration_List_v2();

      Statement_List_v2();

      if(token1.lexeme_word == "#"){
        ;
      }
      else {
        cout << "What was expected was a '#'\n";
      }
  }
  else{
    cout << "What was expected was a '#'\n";
  }

  print_assembly_table(main_table);
}

void Opt_Decleration_List_v2(){
  Declaration_list_v2();
}

void Declaration_list_v2(){
  Declaration_v2();

  if(token1.lexeme_word == ";"){
    ;
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
    token1 = Lexer();
  }
  else {
    cout << "What was expected was 'integer' or boolean\n";
  }
}

void IDs_v2(){
  if (token1.lexeme_token == "Identifier"){
    token1 = Lexer();
    if(token1.lexeme_word == ","){
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
  if (token1.lexeme_word != "#"){
  Statement_List_v2();
}
}

void Statement_v2(){
  token1 = Lexer();
  Compound_v2();
  Assign_v2();
  While_v2();
  If_v2();
  Print_v2();
  Scan_v2();
  Return_v2();
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

      save = token1;
      token1 = Lexer();

      if(token1.lexeme_word == "="){
        token1 = Lexer();

        Expression_v2();

        //instruction
        list_element.step_num = index_num + 1 ;
        list_element.operation = "POPM";
        list_element.address = address_num;
        main_table[index_num] = list_element;
        index_num++;
        address_num++;

        if(token1.lexeme_word == ";"){
          ;
        }
        else {
          cout << "What was expected was a semicolon (;)\n";
        }
      }
      else {
        cout << "What was expected was an '='\n";
      }
    }
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
  if (token1.lexeme_token == "Identifier" || token1.lexeme_token == "Integer"){

    //instruction
    list_element.step_num = index_num + 1;
    if(token1.lexeme_token == "Identifier"){
      list_element.operation = "PUSHM";
    }
    else if (token1.lexeme_token == "Integer"){
      list_element.operation = "PUSHI";
    }
    list_element.address = address_num;
    main_table[index_num] = list_element;
    index_num++;
    address_num++;

    token1 = Lexer();
  }
  else {
    cout << "What was expected was an Identifier or an Integer\n";
  }
}

void Term_prime_v2(){
  Lexeme saved_temp;
  if (token1.lexeme_word == "*" || token1.lexeme_word == "/"){
    saved_temp = token1;
    token1 = Lexer();
    Factor_v2();

    //instruction
    list_element.step_num = index_num + 1 ;
    if(saved_temp.lexeme_word == "*"){
      list_element.operation = "MUL";
    }
    else if(saved_temp.lexeme_word == "/"){
      list_element.operation = "DIV";
    }
    list_element.address = 0;
    main_table[index_num] = list_element;
    index_num++;

    Term_prime_v2();
  }
}

void Expression_prime_v2(){
  Lexeme saved_temp;
  if(token1.lexeme_word == "+" || token1.lexeme_word == "-"){
    saved_temp = token1;
    token1 = Lexer();
    Term_v2();

    //instruction
    list_element.step_num = index_num + 1;
    if(saved_temp.lexeme_word == "+"){
      list_element.operation = "ADD";
    }
    else if(saved_temp.lexeme_word == "-"){
      list_element.operation = "SUB";
    }
    list_element.address = 0;
    main_table[index_num] = list_element;
    index_num++;

    Expression_prime_v2();

  }
}

void While_v2(){
  int saved_address;
  if(token1.lexeme_word == "while"){
    saved_address = index_num;
    //instruction
    list_element.step_num = index_num + 1;
    jumz_addr = list_element.step_num;
    list_element.operation = "LABEL";
    list_element.address = 0;
    main_table[index_num] = list_element;
    index_num++;

    token1 = Lexer();

    if(token1.lexeme_word == "(") {
      token1 = Lexer();

      Condition_v2();
      if(token1.lexeme_word == ")"){

        Statement_v2();

        list_element.step_num = index_num + 1;
        list_element.operation = "JUMP";
        list_element.address = saved_address;
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
    relop = token1;

    token1 = Lexer();
    Expression_v2();

    //instructions{
    if(relop.lexeme_word == "<"){
      list_element.step_num = index_num + 1 ;
      list_element.operation = "LES";
      list_element.address = 0;
      main_table[index_num] = list_element;
      index_num++;

      list_element.step_num = index_num + 1 ;
      list_element.operation = "JUMPZ";
      list_element.address = jumz_addr;
      main_table[index_num] = list_element;
      index_num++;
    }
    else if(relop.lexeme_word == ">"){
      list_element.step_num = index_num + 1 ;
      list_element.operation = "GRT";
      list_element.address = 0;
      main_table[index_num] = list_element;
      index_num++;

      list_element.step_num = index_num + 1 ;
      list_element.operation = "JUMPZ";
      list_element.address = jumz_addr;
      main_table[index_num] = list_element;
      index_num++;
    }
    else if(relop.lexeme_word == "=="){
      list_element.step_num = index_num + 1 ;
      list_element.operation = "EQU";
      list_element.address = 0;
      main_table[index_num] = list_element;
      index_num++;

      list_element.step_num = index_num + 1 ;
      list_element.operation = "JUMPZ";
      list_element.address = jumz_addr;
      main_table[index_num] = list_element;
      index_num++;
    }
    else if(relop.lexeme_word == "!="){
      list_element.step_num = index_num + 1 ;
      list_element.operation = "NEQ";
      list_element.address = 0;
      main_table[index_num] = list_element;
      index_num++;

      list_element.step_num = index_num + 1 ;
      list_element.operation = "JUMPZ";
      list_element.address = jumz_addr;
      main_table[index_num] = list_element;
      index_num++;
    }
    else if(relop.lexeme_word == "=>"){
      list_element.step_num = index_num + 1 ;
      list_element.operation = "GRT EQU";
      list_element.address = 0;
      main_table[index_num] = list_element;
      index_num++;

      list_element.step_num = index_num + 1 ;
      list_element.operation = "JUMPZ";
      list_element.address = jumz_addr;
      main_table[index_num] = list_element;
      index_num++;
    }
    else if(relop.lexeme_word == "<="){
      list_element.step_num = index_num + 1 ;
      list_element.operation = "LES EQU";
      list_element.address = 0;
      main_table[index_num] = list_element;
      index_num++;

      list_element.step_num = index_num + 1 ;
      list_element.operation = "JUMPZ";
      list_element.address = jumz_addr;
      main_table[index_num] = list_element;
      index_num++;
    }
  }
  else {
    cout << "What was expected was a Relational Operator\n";
  }
}

void If_v2(){
  if(token1.lexeme_word == "if"){
    token1 = Lexer();

      if(token1.lexeme_word == "("){
        token1 = Lexer();
        Condition_v2();

        if (token1.lexeme_word == ")"){

          Statement_v2();
          //instruction
          list_element.step_num = index_num + 1;
          list_element.operation = "LABEL";
          list_element.address = 0;
          main_table[index_num] = list_element;
          index_num++;


          //cout << "The value of the lexeme is: " << token1.lexeme_word << "\n";
          token1 = Lexer();
          if (token1.lexeme_word == "endif"){
            token1 = Lexer();
          }
          else {
            cout << "What was expected was 'endif'\n";
          }
        }
        else {
          cout << "What was expected was a ')'\n";
        }
      }
      else {
        cout << "What was expected was a '('\n";
      }
  }
}

void Print_v2(){
  if (token1.lexeme_word == "put"){
    token1 = Lexer();

    if(token1.lexeme_word == "("){
      token1 = Lexer();

      Expression_v2();

      if(token1.lexeme_word == ")"){
        token1 = Lexer();

        if(token1.lexeme_word == ";"){
          ;
        }
        else {
          cout << "What was expected was ';'\n";
        }
        list_element.step_num = index_num + 1;
        list_element.operation = "STDOUT";
        list_element.address = 0;
        main_table[index_num] = list_element;
        index_num++;
      }
      else {
        cout << "What was expected was ')'\n";
      }
    }
    else {
      cout << "What was expected was '('\n";
    }
  }
}

void Scan_v2(){
  if (token1.lexeme_word == "get"){
    token1 = Lexer();

    if (token1.lexeme_word == "("){
      token1 = Lexer();

      IDs_v2();

      if(token1.lexeme_word == ")"){
        token1 = Lexer();

        if(token1.lexeme_word == ";"){
          ;
        }
        else {
          cout << "What was expected was ';'\n";
        }
        list_element.step_num = index_num + 1;
        list_element.operation = "STDIN";
        list_element.address = 0;
        main_table[index_num] = list_element;
        index_num++;
      }
      else {
        cout << "What was expected was ')'\n";
      }
    }
    else {
      cout << "What was expected was '('\n";
    }
  }
}

void Return_v2(){
  Lexeme saved_temp;
  if(token1.lexeme_word == "return"){
    saved_temp = token1;
    token1 = Lexer();

    Expression_v2();
    if(token1.lexeme_word == ";"){
      ;
    }
    list_element.step_num = index_num + 1;
    list_element.operation = "STDOUT";
    list_element.address = 0;
    main_table[index_num] = list_element;
    index_num++;

  }
}

void print_assembly_table(assembly_code table[]) {

  assembly_code temp;
  int i = 0;
  outputfile << "-----OBJECT GENERATED CODE-----\n";
  while(table[i].step_num != 0){
    temp = table[i];
    outputfile << temp.step_num << " " << temp.operation << " " << temp.address << "\n";
    i++;
  }
}

#endif /*ObjectCodeGenerator_h*/
