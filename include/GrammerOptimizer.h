#ifndef GRAMMEROPTIMIZER_H
#define GRAMMEROPTIMIZER_H


class GrammerOptimizer
{
    public:
        GrammerOptimizer(set<Rule> grammer);
        void RemoveLeftRecusion();
        void leftFactorisation();
        set<Rule> getRules();

    protected:

    private:
};

#endif // GRAMMEROPTIMIZER_H
