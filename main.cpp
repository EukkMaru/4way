#include <iostream>
#include <string>
#include "lv0cipher.h"
#include "lv1cipher.h"
#include "lv2cipher.h"

using namespace std;

const bool DEBUG = false;

void debug(const string& msg, const string& state = "") {
    if (!DEBUG) return;
    cout << (state.empty() ? "[DEBUG]" : ("[DEBUG : " + state + "]")) << " " << msg << endl;
}

int main() {
    
    return 0;
}