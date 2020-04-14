#include "../include/GrammerOptimizer.h"

GrammerOptimizer::GrammerOptimizer(vector<Rule*> grammer){
    this->grammer = grammer;
}

void GrammerOptimizer::RemoveLeftRecusion(){
    int len = grammer.size();
    for(int i = 0; i < len; i++){
        for(int j = 0; j < i; j++){
            vector<vector<Rule*>> p = grammer[i]->getProductions();
            grammer[i]->clearProductions();
            for(auto v: p){
                if(v[0] == grammer[j]){
                    vector<vector<Rule*>> alphas = grammer[j]->getProductions();
                    vector<Rule*> n = v;
                    n.erase(n.begin());
                    for(auto alpha: alphas){
                        vector<Rule*> x = alpha;
                        x.insert(x.end(), n.begin(), n.end());
                        grammer[i]->addProduction(x);
                    }
                } else {
                    grammer[i]->addProduction(v);
                }
            }
        }
        eliminateLeftImmidiateRecursion(grammer[i]);
    }
}
void GrammerOptimizer::leftFactorisation(){
}
vector<Rule*> GrammerOptimizer::getRules(){
    return this->grammer;
}

void GrammerOptimizer::eliminateLeftImmidiateRecursion(Rule* r){
    if(!hasImmidiateLeftRecursion(r)){
        return;
    }
    Rule* B = new Rule(r->getName() + "_dash");
    vector<vector<Rule*>> p = r->getProductions();
    r->clearProductions();
    for(auto v: p){
        if(v[0] == r){
            vector<Rule*> n = v;
            n.erase(n.begin());
            n.push_back(B);
            B->addProduction(n);
        } else {
            vector<Rule*> n = v;
            n.push_back(B);
            r->addProduction(n);
        }
    }
    Rule* eps = new Rule("\\L");
    eps->setTerminal();
    vector<Rule*> e;
    e.push_back(eps);
    B->addProduction(e);
    grammer.push_back(B);
}

bool GrammerOptimizer::hasImmidiateLeftRecursion(Rule* r){
    for(auto v: r->getProductions()){
        if(v[0] == r) return true;
    }
    return false;
}
