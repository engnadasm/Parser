#include "GrammerParser.h"

GrammerParser::GrammerParser(string inputFile)
{
    this->path = inputFile;
}

void GrammerParser::parseRules(){
    string line;
    string r;
    ifstream file(path);
    while(getline(file, line)){
        trim(line);
        //cout<<"line: " << line <<endl;
        if(line[0] == '#'){
            if(!r.empty()){
                addRule(r);
            }
            r = line;
        } else {
            r += " " + line;
        }
    }
    file.close();
}

vector<string> GrammerParser::segmentation(string line){
    line.erase(0,1);
    vector<string> segs;
    int i = 0;
    string seg;
    while(i < line.size()){
        if (line[i] == '=' || line[i] == '|') {
            if(seg.size() > 0){
                segs.push_back(seg);
            }
            seg = string(1, line[i]);
            segs.push_back(seg);
            seg.clear();
        } else if(line[i] == ' '){
            if(seg.size() > 0){
                segs.push_back(seg);
                seg.clear();
            }
        } else {
            seg.append(string(1,line[i]));
            if(line[i] == '\\'){
                seg += string(1,line[i+1]);
                i++;
            }
        }
        i++;
    }
    if(seg.size() > 0){
        segs.push_back(seg);
    }
    return segs;
}

void GrammerParser::addRule(string r){
    vector<string> segs = segmentation(r);
    vector<string> rhs(segs.begin()+2, segs.end());
    pair<string, vector<string>> t(segs[0], rhs);
    passOne.push_back(t);
    Rule rule(segs[0]);
    rules.push_back(rule);
}

