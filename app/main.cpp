#include "cli.h"
#include "flib.h"
#include "globals.h"
#include "directory.h"

#include <iostream>
#include <string>
#include <vector>




// ProjectPilot //

/*
* 
* 
* maybe make it a class with proper iterative method? So it can auto assess level and everything without passing so much data
* Create function that finds the next statements findInstruction(pos,step) with n the number of position before or ahed (1, -1, -2 ,2 ...etc)
* 
* 1. Read line by line, identify the type. (use iterator as this is needed)
* 2. If opening structure is found, find the next line that has the starting indentation, group up those lines and re-run the iterative function on them
* 3. Position the cursor on the next line with same indentation and continue.
* - If Parameter is found, save it.
* - If FOR is found, create a real for
* - if IF, ELIF or ELSE is found, look for the following condition:
*   - ELSE found -> there must be an IF the previous statement
*   - ELIF found -> there must be an IF or ELIF in the previous statement, and ELIF or ELSE in the following one.
*   
*  Make sure that if files or folders are found, if they already exists replace/merge.
* 
* 
*/

using std::cin;
using std::cout;
using std::string;
using std::wcin;
using std::wcout;
using std::wstring;
using std::endl;



int main() {
    
    Directory root;
    root.input_template("cmake_project");
    root.validate_template();
    root.print_ivect();
   
    return 0;

}