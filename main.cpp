#include <iostream>
#include "GrammerParser.h"

using namespace std;

int main()
{
    GrammerParser gp("rules.txt");
    gp.parseRules();
    return 0;
}
