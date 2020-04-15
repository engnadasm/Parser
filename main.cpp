#include <iostream>
#include "../include/GrammerParser.h"
#include "../include/GrammerOptimizer.h"

using namespace std;

int main()
{
    GrammerParser gp("rules.txt");
    gp.parseRules();
    GrammerOptimizer go(gp.getRules());
    go.RemoveLeftRecusion();
    go.leftFactorisation();
    vector<Rule*> rules = go.getRules();
    for(int i = 0; i < rules.size(); i++){
        cout << i << ": " << rules[i]->getName() << " :" << endl;
        vector<vector<Rule*>> prod = rules[i]->getProductions();
        for(int j = 0; j < prod.size(); j++){
            cout << "production " << j << " :";
            for(int k = 0; k < prod[j].size(); k++){
                cout << " " <<prod[j][k]->getName();
                //cout << " $$ terminal=" << prod[j][k]->isTerminal() << "$$  ";
            }
            cout << endl;
        }
        cout << endl;
    }
    return 0;
}
