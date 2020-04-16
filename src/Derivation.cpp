#include "../include/Derivation.h"
#include <fstream>
Derivation* Derivation::derivationInstance = NULL;

Derivation::Derivation()
{
    // do init stuff
}

Derivation* Derivation::GetInstance()
{
    if (derivationInstance== NULL)
    {
        derivationInstance = new Derivation();
    }
    return derivationInstance;
}

void Derivation::generateDerivations()
{
    string input = tokens.front();
    Rule* currentTopStack = ourStack.top();
    string nameTopStack = (*currentTopStack).getName();
    bool flag = true;
    bool error = false;
    if(!(*currentTopStack).isTerminal())
    {
        unordered_map<string, vector<Rule*>> currentRow = ourParsingTable[nameTopStack];
        vector<Rule*> nextTran = currentRow[input];
        cout << "Output of begin and end: ";
        if(nextTran.empty() == false)
        {
            ourStack.pop();
            string out = "";
            for (auto i = nextTran.rbegin(); i != nextTran.rend(); ++i)
            {
                //for (auto i = nextTran.begin(); i != nextTran.end(); ++i) {
                cout << *i << " ";
                ourStack.push(*i);
                out = out + (*i)->getName() + " ";
            }
            outToPrint.push_back(out);
            currentTopStack = ourStack.top();
        }
        else
        {
            error = true;
            //accept = false;
        }
    }

    while(flag)
    {
        if((*currentTopStack).isTerminal())
        {
            if(input.compare((*currentTopStack).getName()) == 0)
            {
                tokens.pop();
                ourStack.pop();
                flag = false;
            }
            else
            {
                flag = false;
                cout << "there is error in matching " + input +"\n";
                outToPrint.push_back("there is error in matching " + input );
                tokens.pop();
                // accept = false;
            }
        }
        else if(error)
        {
            flag = false;
            cout << "there is error where can't reach to " + input + " under non terminal "
                 + (*currentTopStack).getName() + "\n";
            outToPrint.push_back("there is error where can't reach to " + input
                                 + " under non terminal " + (*currentTopStack).getName());
            tokens.pop();
            error = false;
        }
        else if ((*currentTopStack).getName().compare("sync") == 0)
        {
            cout << "we reach to sync under terminal " +input + " in non terminal"
                 + (*currentTopStack).getName() + "\n";
            outToPrint.push_back("we reach to sync under terminal " +input + " in non terminal"
                                 + (*currentTopStack).getName());
            ourStack.pop();
        }
        else if((*currentTopStack).getName().compare("\\L") == 0)
        {
            //for epsilon
            ourStack.pop();
        }
        else if(ourStack.empty())   //case if ourstack finish but still we have tokens
        {
            flag = false;
            cout << "error,we can't complete parser and not accept this program\n";
            outToPrint.push_back("error,we can't complete parser\n");
            tokens.pop();
            accept = false;
        }
    }
}

void Derivation::PrintDerivations()
{
    ofstream myfile ("Syntax_file.txt");
    if (myfile.is_open())
    {
        for(int i = 0; i < outToPrint.size(); i++)
        {
            myfile << outToPrint[i];
            myfile << "\n";
            cout << outToPrint[i] << "\n";
        }
        myfile.close();
    }
    else
        cout << "Unable to open file";
}

void Derivation::enterToken(string token)
{
    this->tokens.push(token);
    generateDerivations();
}

void Derivation::setStart(Rule* start)
{
    this->ourStack.push(start);
    outToPrint.push_back((*start).getName());
    cout<< (*start).getName();
}

void Derivation::setParsingTable(unordered_map<string,unordered_map<string, vector<Rule*>>> parsingTable)
{
    this->ourParsingTable = parsingTable;
}

bool Derivation::getAccept()
{
    return this->accept;
}

void Derivation::endDerivation()
{
    if (!ourStack.empty())
    {
        cout << "we reach to case that token finish but still we have non terminals in ourstack which they are :\n";
        outToPrint.push_back("we reach to case that token finish but still we have non terminals in ourstack which they are :\n");
        while(!ourStack.empty())   //case if token finish but still we have things in ourstack
        {
            cout << ourStack.top()->getName()<< "\n";
            outToPrint.push_back(ourStack.top()->getName());
            ourStack.pop();
        }
    }
}
