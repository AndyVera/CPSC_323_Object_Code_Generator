#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "SyntaxAddOn.h"
#include "SyntaxAnalyzerFunctions.h"
#include "ObjectCodeGenerator.h"

using namespace std;

int main (int argc, const char* argv[]){

  if (argc != 3){
    cout << "Didn't enter the correct number of argumens!\n";
    cout << "The proper and acceptable format is:\n <exe file> <input text file> <output text file>\n";
    return 0;
  }

  change_stream_contents(argv[1],argv[2]);
  if(checking_proper_streams() == 1){
    return 1;
  }
  checking_input_and_starting_iterator();

  //Rat21F();
  simplified_Rat21F();

  closing_streams();
  cout << "\nObject Code Generator Done!!!\n";
}
