#include "wdist.h"
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    const int d = word_distance("HONDA", "HYUNDAI");
    cout << " this is a test" << d << endl;
    return 0;
}

