#include "Rule.h"

Rule::Rule(string name)
{
    this->name = name;
}

bool Rule::isTerminal(){
    return this->terminal;
}
bool Rule::isNullable(){
    return this->nullable;
}
set<string> Rule::getFirst(){
    return this->first;
}
set<string> Rule::getFollow(){
    return this->follow;
}
string Rule::getName(){
    return this->name;
}
void Rule::addProduction(Rule r){
    this->productions.push_back(r);
}

void Rule::addFirst(string f){
    this->first.insert(f);
}
void Rule::addFollow(string f){
    this->follow.insert(f);
}
void Rule::addFirst(set<string> f){
    first.insert(f.begin(), f.end());
}
void Rule::addFollow(set<string> f){
    follow.insert(f.begin(), f.end());
}
