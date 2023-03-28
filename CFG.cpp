#include<bits/stdc++.h>
using namespace std;

map<string, vector<string> > mp;
string language;

stack<string> st;


void grammarize(){
    mp["S"].push_back("A1B");

    mp["A"].push_back("0A");
    mp["A"].push_back("");

    mp["B"].push_back("0B");
    mp["B"].push_back("1B");
    mp["B"].push_back("");
}

void check(string s){
    int cnt=0;
    for(char x: s){
        if(x=='0' or x=='1') cnt++;
    }
    if(cnt > language.size()) return;

    st.push(s);

    if(s == language){
        cout << "The string is accepted.\nTransion is given below:\n";

        vector<string> vc;
        while(!st.empty()){
            vc.push_back(st.top());
            st.pop();
        }

        bool f = false;

        reverse(vc.begin(), vc.end());

        for(string x: vc){
            if(f) cout << "-> ";
            else cout << "   ";

            f = true;

            cout << x << endl;
        }

        exit(0);
    }

    for(int i=0; i<s.size(); i++){
        if(s[i]=='0' or s[i]=='1') continue;

        string temp1 = s.substr(0, i);
        string temp2 = s.substr(i+1, s.size()-i-1);
        string ss = s.substr(i, 1);
        for(string x: mp[ss]){
            string y = temp1 + x + temp2;
            check(y);
        }

        break;
    }

    st.pop();
}

int main()
{
    grammarize();

    cout << "Enter input string: ";
    cin >> language;

    check("S");

    cout << "The string is NOT accepted.\n";

    return 0;
}
