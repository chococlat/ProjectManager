#include "cli.h"
#include "flib.h"
#include "globals.h"

// ProjectPilot //

using std::cin;
using std::cout;
using std::string;
using std::wcin;
using std::wcout;
using std::wstring;
using std::endl;


int main() {

    cout << "Templates path is : " << TEMPLATE_PATH << "\n";
    if (validate_template("cmake_project")) cout << "cmake_project is valid\n";

    return 0;
}