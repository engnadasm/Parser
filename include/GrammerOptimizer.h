#ifndef GRAMMEROPTIMIZER_H
#define GRAMMEROPTIMIZER_H
#include <vector>
#include <string>
#include <iostream>
#include "Rule.h"

using namespace std;


class GrammerOptimizer
{
    public:
        GrammerOptimizer(vector<Rule*> grammer);
        void RemoveLeftRecusion();
        void leftFactorisation();
        vector<Rule*> getRules();

    protected:

    private:
        vector<Rule*> grammer;
        void eliminateLeftImmidiateRecursion(Rule* r);
        bool hasImmidiateLeftRecursion(Rule* r);
};

#endif // GRAMMEROPTIMIZER_H
