#ifndef GRAMMERPARSER_H
#define GRAMMERPARSER_H


class GrammerParser
{
    public:
        GrammerParser(string inputFile);
        void parseRules();
        vector<Rule> getRules();

    protected:

    private:
};

#endif // GRAMMERPARSER_H
