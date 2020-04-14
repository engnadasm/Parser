#include "../include/ParserGenerator.h"

ParserGenerator::ParserGenerator(vector<Rule*> grammer)
{
    //ctor
    this->grammer = grammer;
}

void ParserGenerator::generateParsingTable()
{//1-compute first of all Rules
    vector< Rule* >::iterator lhs = this->grammer.begin();
    //for each nonTerminal
    for (auto lhs : grammer)
    {  //compute lhs if not computed
       if(!lhs->firstComputed())
            calcFirst(lhs);
    }
//2-compute follow of all nonTerminals
    calcFollow();
//3-construct parsing table
    addToTable();

}
void ParserGenerator::calcFirst(Rule* lhs){
        //mark lhs as computed
        lhs->markFirst();
        vector<set<string>> first;//-------------------

        //loop over its productions
        vector<vector<Rule*>>productions = lhs->getProductions();
         for(auto p: productions){
             if(p[0]->isTerminal()){
                    set<string> s;
                    s.insert(p[0]->getName());
                    lhs->addFirst(s);
                    first.push_back(s);//--------------------
             }else{// p[0] is nonTerminal
                bool nullable = true;
                unsigned int i = 0;
                set<string> f1;
                while(nullable && i < p.size()){
                    if(!p[i]->firstComputed())
                        calcFirst(p[i]);

                    vector<set<string>>f2 = p[i]->getFirst();
                    //convert f2 to set<string> and check if it is nullable
                    bool eps;
                    if(!eps){
                      nullable = false;
                    }else{
                    //remove eps
                    }
                    //add to f1
                    i++;
                }
                lhs->addFirst(f1);
                first.push_back(f1);//-----------------------------
            }
         }

}
void ParserGenerator::calcFollow(){
}
void ParserGenerator::printParsingTable()
{

}
void ParserGenerator::printParsingTable(string outputFile)
{

}
unordered_map<string,unordered_map<string, Rule*>>ParserGenerator::getParsingTable()
{
   return this->parsingTable;

}
void::ParserGenerator::addToTable(){
}
