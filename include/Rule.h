#ifndef RULE_H
#define RULE_H


class Rule
{
    public:
        Rule(string name);
        bool isTerminal();
        bool isNullable();
        set<string> getFirst();
        set<string> getFollow();


    protected:

    private:
        bool terminal;
        set<string> first;
        set<string> follow;
        bool nullable;
        string name;

};

#endif // RULE_H
