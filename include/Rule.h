#ifndef RULE_H
#define RULE_H
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include <iostream>


using namespace std;


class Rule
{
    public:
        Rule(string name);
        bool isTerminal();
        bool isNullable();
        vector<set<string>> getFirst();
        set<string> getFollow();
        void addFollow(string f);
        void addFirst(set<string> f);
        void addFollow(set<string> f);
        string getName();
        void addProduction(vector<Rule*> r);
        void clearProductions();
        vector<vector<Rule*>> getProductions();
        void setTerminal();
        bool firstComputed();
        void markFirst();

    protected:

    private:
        bool terminal;
        vector<vector<Rule*>> productions;
        vector<set<string>>first;
        set<string> follow;
        bool nullable;
        string name;
        bool calcFirst;

};

static inline void printProductions(vector<vector<Rule*>> p){
    for(int j = 0; j < p.size(); j++){
        //cout << "production " << j << " :";
        for(int k = 0; k < p[j].size(); k++){
            cout << " " <<p[j][k]->getName();
        }
        cout << " | ";
    }
    cout << endl;
}



#endif // RULE_H
