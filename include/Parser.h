#ifndef PARSER_H
#define PARSER_H


class Parser
{
    public:
        Parser(set<Rule> grammer);
        void generateParsingTable();
        void printParsingTable();
        void printParsingTable(string outputFile);
        // parse(next token)

    protected:

    private:
};

#endif // PARSER_H
