#ifndef PARSERGENERATOR_H
#define PARSERGENERATOR_H
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include "../include/Rule.h"
using namespace std;

class ParserGenerator
{
    public:
        ParserGenerator(vector<Rule*> grammer);
        void generateParsingTable();
        void printParsingTable();
        void printParsingTable(string outputFile);
        unordered_map<string,unordered_map<string, Rule*>>getParsingTable();
        // parse(next token)

    protected:

    private:
        vector<Rule*> grammer;
        //string:nonTerminal , map:terminal, table entry = rule
        unordered_map<string,unordered_map<string, Rule*>> parsingTable;

        void calcFirst(Rule* lhs);
        void calcFollow();
        void calcNullable();
        void addToTable();
};

#endif // PARSERGENERATOR_H
