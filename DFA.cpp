#include<bits/stdc++.h>
using namespace std;

int main(){
    cout << "Number of states: ";
    int numberOfStates;
    cin >> numberOfStates;

    cout << "Starting state: ";
    char startingState;
    getchar();
    cin >> startingState;

    cout << "Number of final states: ";
    int numberOfFinalState;
    cin >> numberOfFinalState;
    set<char> finalStates;
    cout << "Final states: ";
    for(int i=1; i<=numberOfFinalState; i++)
    {
        char state;
        getchar();
        cin >> state;
        finalStates.insert(state);
    }

    cout << "DFA:\n";
    map<char, char> tran0, tran1;
    for(int i=1; i<=numberOfStates; i++)
    {
        char st, a, b;
        getchar();
        cin >> st;
        getchar();
        cin >> a;
        getchar();
        cin >> b;

        tran0[st] = a;
        tran1[st] = b;
    }

    cout << "String: ";
    string s;
    getchar();
    cin >> s;

    char currentState = startingState;
    for(char x: s)
    {
        if(x == '0')
            currentState = tran0[currentState];
        else
            currentState = tran1[currentState];

        cout << x << " " << currentState << endl;
    }

    if(finalStates.find(currentState) == finalStates.end())
        cout << "Given string is rejected\n";
    else
        cout << "Given string is accepted\n";
}
