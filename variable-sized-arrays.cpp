#include <string>
#include <regex>
#include <sstream>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

typedef vector<string>  StringVector;
typedef vector<int>     IntVector;

StringVector parseLine(const string &inputline) {
    std::regex rgx("\\s+");
    //std::regex rgx("(\\d+)");
    std::sregex_token_iterator iter(inputline.begin(), inputline.end(),
        rgx, -1);
    std::sregex_token_iterator end;
    vector<string> retArray;
    
    for ( ; iter != end; ++iter)
        retArray.push_back(*iter);
    
    return retArray;
}

IntVector fromStringVector(const StringVector &arr) {
    IntVector retArr;
    for(size_t i = 0; i < arr.size(); ++i) {
        retArr.push_back(stoi(arr[i]));
    }
    return retArr;
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
    int n = 0, q = 0;
        
    string line;
    vector<IntVector> arr;
    IntVector tmp;
    
    getline(cin, line);        
    tmp = fromStringVector(parseLine(line));
    //printIntInputLine(arr);
    //printVector(tmp);
    
    n = tmp[0];
    q = tmp[1];
    
    for(int i = 0; i < n; ++i) {
        getline(cin, line);
        IntVector vec = fromStringVector(parseLine(line));
        //int k = vec[0];
        IntVector t;
        for(size_t j = 1; j < vec.size(); j++)
            t.push_back(vec[j]);
        arr.push_back(t);
    }
    
    //cout << "n: " << n << ", q: " << q << endl;
    
    for(int k = 0; k < q; ++k) {
        getline(cin, line);
        auto vec = fromStringVector(parseLine(line));
        int i = vec[0], j = vec[1];
        cout << arr[i][j] << endl;
    }
    
    // for(int i = 0; i < arr.size(); i++)
        // printVector(arr[i]);
            
    return 0;
}

