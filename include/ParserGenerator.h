#ifndef PARSERGENERATOR_H
#define PARSERGENERATOR_H


class ParserGenerator
{
    public:
        ParserGenerator(set<Rule> grammer);
        void calcNullable();
        void calcFirst();
        void calcFollow();
        Parser getParser();

    protected:

    private:
};

#endif // PARSERGENERATOR_H
