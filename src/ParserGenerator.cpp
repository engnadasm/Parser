#include "../include/ParserGenerator.h"
#include <fstream>
ParserGenerator::ParserGenerator(vector<Rule*> grammer)
{
    //ctor
    this->grammer = grammer;
}

void ParserGenerator::generateParsingTable()
{//1-compute first of all Rules
    //for each nonTerminal
    for (auto lhs : grammer)
    {  //compute lhs if not computed
       if(!lhs->firstComputed()){
        //cout <<"compute :" <<lhs->getName()<<"----------------------------" << endl;
            calcFirst(lhs);
       }
    }
//2-compute follow of all nonTerminals
    //calcFollow();
//3-construct parsing table
    addToTable();

}
void ParserGenerator::calcFirst(Rule* lhs){
        //mark lhs as computed
        //cout << "********************before mark " <<lhs->getName()<<" = "<< lhs->firstComputed()<<endl;
        lhs->markFirst();
        //cout << "********************mark " <<lhs->getName()<<" = "<< lhs->firstComputed()<<endl;
        //loop over its productions
        vector<vector<Rule*>>productions = lhs->getProductions();
        if(lhs->isTerminal()){
            //cout << lhs->getName() << "is terminal" <<endl;
                    set<string> s;
                    s.insert(lhs->getName());
                    lhs->addFirst(s);
                    if(lhs->getName()=="\\L"){
                        //cout << "is nullable" <<endl;
                       lhs->addNullable(true);
                    }else{
                       lhs->addNullable(false);
            }
        }
        else{for(auto p: productions){
             if(p[0]->isTerminal()){
                 //cout << p[0]->getName() << "is terminal" <<endl;
                    set<string> s;
                    s.insert(p[0]->getName());
                    lhs->addFirst(s);
                    if(p[0]->getName()=="\\L"){
                        //cout << "is nullable" <<endl;
                       lhs->addNullable(true);
                    }else{
                       lhs->addNullable(false);
                    }
             }else{// p[0] is nonTerminal
                eps = true;
                unsigned int i = 0;
                set<string> f1;
                //cout << p[i]->getName() << "is non terminal" <<endl;
                while(eps && i < p.size()){
                    if(!p[i]->firstComputed()){
                      //cout << "*compute "<<p[i]->getName()<< "----------------------------"<<endl;
                        calcFirst(p[i]);
                    }
                    //convert first from vector to set<string> and check if it is nullable
                    //cout << "finish" <<p[i]->getName()<< endl;
                    set<string> f2 = checkEps(p[i]->getFirst(), (i+1 == p.size()));

                    //add to f1
                    f1.insert(f2.begin(),f2.end());

                    i++;
                    //cout << "i = " <<i<< endl;
                }
                lhs->addNullable(eps);
                lhs->addFirst(f1);
            }
         }
        }
}
set<string> ParserGenerator::checkEps(vector<set<string>> f , bool lastSymbol){
    //cout << "check eps, last symbol = " << lastSymbol << endl;
    eps = false;
    set<string> first;
    for (auto s : f){
        //1- remove epsilon unless it comes from the last production
        set<string>::iterator it = s.find("\\L");
        if (it != s.end()) {
            //cout << "eps found"<<endl;
            eps = true;
            if(!lastSymbol){
             s.erase(*it);
            }
        }
        //2- add s to first
        first.insert(s.begin(), s.end());
    }

    return first;
}
void ParserGenerator::calcFollow(){
}
void ParserGenerator::printParsingTable()
{

}
void ParserGenerator::printParsingTable(string outputFile)
{
    ofstream myfile (outputFile);
  if (myfile.is_open())
  {         int i = 1;
            for (auto& nonterminal : parsingTable)
            {
                myfile << i << "- " <<nonterminal.first;
                myfile << " :\n";
                i++;
                for(auto& terminal : nonterminal.second){
                    myfile << terminal.first << " :";
                    for(auto r : terminal.second){
                        myfile << " " << r->getName();
                    }
                    myfile << "  ";
                }
                myfile << "\n";
            }
    myfile.close();
  }
  else cout << "Unable to open file";

}
unordered_map<string,unordered_map<string, vector<Rule*>>>ParserGenerator::getParsingTable()
{
   return this->parsingTable;

}
void::ParserGenerator::addToTable(){
    for(auto g : grammer){
        vector<vector<Rule*>>productions = g->getProductions();
        vector<vector<Rule*>>::iterator pitr = productions.begin();
        vector<bool>nullable = g->getNullable();
        vector<bool>::iterator nitr = nullable.begin();
        //f = set<string>
        for(auto f : g->getFirst()){
            // t = string -> terminal name
            for(auto t : f){
                if(t != "\\L"){
                parsingTable[g->getName()][t]=*pitr;
                }
            }
            if(*nitr == true){
                //insert pitr under the follow set into the parsing table
            }
            pitr++;
            nitr++;
        }
        //add sync to table
    }
}
