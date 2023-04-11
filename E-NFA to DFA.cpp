#include<bits/stdc++.h>
using namespace std;

int main()
{
    /// freopen("enfa_dfa.txt", "r", stdin);
    /// nfa transitions
    //  state      epsilon     0              1
    map<char, pair<set<char>, pair<set<char>, set<char> > > > nfa;

    // now make the nfa transitions
    //          ch     0         1
    //printf("enter the number of transitions: ");
    int edge, node;
    cin >> node;

    for(int i=0;i<node;i++){
        char ch;
        cin >> ch;

        nfa.insert({ch, {{}, {{},{}}}});
    }

    cin >> edge;

    for(int i=0;i<edge;i++){
        char start, end, trans;
        cin >> start >> trans >> end;
        //printf("%c %c %c\n", start, trans, end);

        if(trans=='e'){
            nfa[start].first.insert(end);
        }else if(trans=='0'){
            nfa[start].second.first.insert(end);
        }else{
            nfa[start].second.second.insert(end);
        }
    }

//    for(auto itr : nfa){
//        cout << itr.first << "\t";
//
//        for(auto c : itr.second.first){
//            cout << c << " ";
//        }
//        for(auto c : itr.second.second.first){
//            cout << c << " ";
//        }
//        for(auto c : itr.second.second.second){
//            cout << c << " ";
//        }
//        cout << "\n";
//    }

    /// now dfa creating
    //        states              0             1
    vector<pair<set<char>, pair<set<char>, set<char> > > > dfa;
    map<char, set<char> > e_close;
    queue<set<char> > q;
    map<set<char>, bool> vis;

    e_close[NULL]={};

    for(auto itr : nfa){
        set<char>st;

        // insert the state itself
        st.insert(itr.first);

        queue<char>q;

        q.push(itr.first);

        while(!q.empty()){
            char ch=q.front();
            q.pop();

            for(char c : nfa[ch].first){
                q.push(c);
                st.insert(c);
            }
        }

        e_close.insert({itr.first, st});
    }

    printf("e closures are : \n");

    for(auto itr : e_close){
       cout << itr.first << "\t";

       for(auto c : itr.second){
           cout << c << " ";
       }
       cout << "\n";
    }

    char start_state, end_state;
    cin >> start_state >> end_state;

    q.push(e_close[start_state]);

    while(!q.empty()){
        set<char> get;
        char ch0=NULL, ch1=NULL;

        get=q.front();

        q.pop();
        //cout << vis[get] << "\n";

        // if it is already processed
        // then no need to process it again
        if(vis.find(get)!=vis.end() and vis[get]){
            continue;
        }

        vis[get]=true;

        for(auto itr : get){
            for(char ch : nfa[itr].second.first){
                if(ch >= 'a' and ch <= 'z'){
                    ch0=ch;
                    break;
                }
            }
        }

        for(auto itr : get){
            for(char ch : nfa[itr].second.second){
                if(ch >= 'a' and ch <= 'z'){
                    ch1=ch;
                    break;
                }
            }
        }

        //cout << ch0 << " " << ch1 << "\n";

        dfa.push_back({get, {e_close[ch0], e_close[ch1]}});

        if(ch0!=NULL){
            q.push(e_close[ch0]);
        }

        if(ch1!=NULL){
            q.push(e_close[ch1]);
        }

        // that is both are same and not NULL
        // so by the above condition
        // we have pushed them twice
        // so now pop them if they are similar
        if(ch0==ch1 and ch0!=NULL){
            q.pop();
        }
    }

    printf("The DFA table:\n\n");

    for(auto itr=dfa.begin();itr!=dfa.end();itr++){
        // print transition for 0 - -----------------------------------------------------------------------
        printf("Trans: ({");

        // print the state
        for(auto itr1=itr->first.begin();itr1!=itr->first.end();itr1++){
            cout << *itr1;
            auto itr2=itr1;
            itr2++;
            if(itr2!=itr->first.end()){
                cout << ",";
            }
        }
        cout << "}, 0) = {";

        for(auto itr1=itr->second.first.begin();itr1!=itr->second.first.end();itr1++){
            cout << *itr1;
            auto itr2=itr1;
            itr2++;
            if(itr2!=itr->second.first.end()){
                cout << ",";
            }
        }
        cout << "}\n";

        // print transition for 1 -------------------------------------------------------------------------

        printf("Trans: ({");

        // print the state
        for(auto itr1=itr->first.begin();itr1!=itr->first.end();itr1++){
            cout << *itr1;
            auto itr2=itr1;
            itr2++;
            if(itr2!=itr->first.end()){
                cout << ",";
            }
        }
        cout << "}, 1) = {";

        for(auto itr1=itr->second.second.begin();itr1!=itr->second.second.end();itr1++){
            cout << *itr1;
            auto itr2=itr1;
            itr2++;
            if(itr2!=itr->second.second.end()){
                cout << ",";
            }
        }
        cout << "}\n\n";
    }

    printf("Starting state is: { ");

    for(auto ch : e_close[start_state]){
        cout << ch << " ";
    }
    cout << "}\n\n";

    printf("Accepting states : ");

    for(auto itr : dfa){
        set<char>get;

        get=itr.first;

        bool has_ending_state=false;

        for(auto ch : get){
            if(ch == end_state){
                has_ending_state=true;
                break;
            }
        }

        if(!has_ending_state){
            continue;
        }

        cout << "{ ";

        for(auto ch : get){
            cout << ch << " ";
        }
        cout << "} ";
    }
    cout << "\n\n";
}
