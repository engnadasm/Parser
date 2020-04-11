#ifndef RULE_H
#define RULE_H
#include <string>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;


class Rule
{
    public:
        Rule(string name);
        bool isTerminal();
        bool isNullable();
        set<string> getFirst();
        set<string> getFollow();
        void addFirst(string f);
        void addFollow(string f);
        void addFirst(set<string> f);
        void addFollow(set<string> f);
        string getName();
        void addProduction(Rule r);


    protected:

    private:
        bool terminal;
        vector<Rule> productions;
        set<string> first;
        set<string> follow;
        bool nullable;
        string name;

};

#endif // RULE_H
