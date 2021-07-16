#include <memory>
#include <string>
#include <regex>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>

using namespace std;

typedef vector<string>              StringVector;
typedef shared_ptr<StringVector>    StringVectorPtr;
typedef vector<int>                 IntVector;
typedef shared_ptr<IntVector>       IntVectorPtr;

// #define PARSELINE(line, result) parseLine2(line, result)
#define PARSELINE(line, result) parseLine(line, result)

void parseLine2(const string &inputline, StringVectorPtr &retArray) {
    cerr << "I'an parseLine2" << endl;    
    size_t pos = 0, index = 0;    
    try {
        while(true) {
            index = inputline.find(" ", pos);
            if (index == inputline.npos) {
                break;
            }
            retArray->push_back(inputline.substr());        
            pos = index;
        
        }
    } catch(const exception &e) {
        cerr << "catched: " << e.what() << endl;
        exit(EXIT_FAILURE);
    } catch(...) {
        cerr << "catched ..." << endl;
        exit(EXIT_FAILURE);
    }
}

void parseLine(const string &inputline, StringVectorPtr &retArray) {
    cerr << "I'an parseLine" << endl;
    std::regex rgx("\\s+");
    //std::regex rgx("(\\d+)");
    std::sregex_token_iterator iter(inputline.begin(), inputline.end(), rgx, -1);
    std::sregex_token_iterator end;    
    for ( ; iter != end; ++iter)
        retArray->push_back(*iter);    
}

void fromStringVector(const StringVectorPtr &arr, IntVectorPtr &retArr) {
    for(size_t i = 0; i < arr->size(); ++i) {
        retArr->push_back(stoi((*arr)[i]));
    }
}

void printIntInputLine(const StringVector &arr) {
    // cout << "printIntInputLine()" << endl;
    // cout << "size = " << arr.size() << endl;
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i + 1 < arr.size())
            cout << arr[i] << ", ";
        else
            cout << arr[i];
    }
    cout << endl;
    // cout << "end of printIntInputLine()" << endl;
}

template <class T> void printVector(const vector<T> &arr) {
    // cout << "printVector()";
    // cout << "size: " << arr.size() << endl;
    
    for (size_t i = 0; i < arr.size(); ++i) {
        if (i + 1 < arr.size())
            cout << arr[i] << ", ";
        else
            cout << arr[i];
    }
    cout << endl;
    
    // cout << "end of printVector()";
}

int main() {
    try {
    
        int n = 0, q = 0;        
        string              line;
        vector<IntVector>   arr;
        StringVectorPtr     stmp(new StringVector());
        IntVectorPtr        tmp(new IntVector());
        
        getline(cin, line);
        PARSELINE(line, stmp);        
        fromStringVector(stmp, tmp);
        //printIntInputLine(arr);
        //printVector(tmp);
        
        n = (*tmp)[0];
        q = (*tmp)[1];
        
        StringVectorPtr svec = StringVectorPtr(new StringVector());
        IntVectorPtr    vec = IntVectorPtr(new IntVector());
        
        for(int i = 0; i < n; ++i) {
            svec->clear();
            vec->clear();
                
            getline(cin, line);        
            PARSELINE(line, svec);
            fromStringVector(svec, vec);
            //int k = vec[0];
            IntVector t;
            t.reserve(vec->size());
            for(size_t j = 1; j < vec->size(); j++)
                t.push_back((*vec)[j]);
            arr.push_back(t);
        }
        
        //cout << "n: " << n << ", q: " << q << endl;
        svec->clear();
        vec->clear();
        
        for(int k = 0; k < q; ++k) {
            getline(cin, line);
            
            svec->clear();
            vec->clear();
            
            PARSELINE(line, svec);
            fromStringVector(svec, vec);
            cerr << "vec.size(): " << vec->size() << endl;
            int i = (*vec)[0], j = (*vec)[1];
            cout << arr[i][j] << endl;
        }
        
        // for(int i = 0; i < arr.size(); i++)
            // printVector(arr[i]);
    } catch(const runtime_error &e) {
        cerr << "catched: " << e.what() << endl;
    } catch(...) {
        cerr << "... exceptin." << endl;
    }    
    
            
    return 0;
}

#undef PARSELINE
 
