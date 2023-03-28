#include<bits/stdc++.h>
using namespace std;

void initializeDFA(vector<char> &states, map<char, pair<char, char> > &DFA, char &initialState, set<char> &finalStates)
{
    cout << "Enter the number of states: ";
    int numberOfStates;
    cin >> numberOfStates;

    cout << "Enter the DFA states and transitions:\n";
    for(int i=1; i<=numberOfStates; i++)
    {
        getchar();
        char state;
        cin >> state;
        states.push_back(state);
        getchar();
        char tran1;
        cin >> tran1;
        getchar();
        char tran2;
        cin >> tran2;
        DFA[state] = {tran1, tran2};
    }

    cout << "Enter initial state: ";
    getchar();
    cin >> initialState;

    cout << "Enter number of final states: ";
    int numberOfFinalStates;
    cin >> numberOfFinalStates;
    cout << "Enter final states:\n";
    for(int i=1; i<=numberOfFinalStates; i++)
    {
        getchar();
        char state;
        cin >> state;
        finalStates.insert(state);
    }
}

bool checkFinalState(set<char> finalStates, char state)
{
    return (finalStates.find(state) != finalStates.end());
}

pair<char, char> transformation(map<char, pair<char, char> > &DFA, char state, int freq)
{
    string s;
    while(freq--) s = s + "0";

    char zeroTransition = state;
    for(char x: s)
    {
        zeroTransition = DFA[zeroTransition].first;
    }

    char oneTransition = state;
    for(char x: s)
    {
        oneTransition = DFA[oneTransition].second;
    }

    return {zeroTransition, oneTransition};
}

int getStateIdx(vector<char> states, char state)
{
    for(int i=0; i<states.size(); i++)
    {
        if(states[i] == state)
            return i;
    }

    return -1;
}

int main()
{
    freopen("in.txt", "r", stdin);

    vector<char> states;
    map<char, pair<char, char> > DFA;
    char initialState;
    set<char> finalStates;
    initializeDFA(states, DFA, initialState, finalStates);

    int numberOfStates = states.size();
    char table[numberOfStates][numberOfStates];

    for(int i=0; i<numberOfStates; i++)
    {
        for(int j=0; j<numberOfStates; j++)
        {
            table[i][j] = '*';
        }
    }

    for(int i=0; i<numberOfStates; i++)
    {
        table[i][i] = '=';
        for(int j=i+1; j<numberOfStates; j++)
        {
            if(checkFinalState(finalStates, states[i]) != checkFinalState(finalStates, states[j]))
                table[i][j] = 'X';
        }
    }

    int freq = 1;
    while(true)
    {
        bool done = true;
        for(int i=0; i<numberOfStates; i++)
        {
            for(int j=i+1; j<numberOfStates; j++)
            {
                if(table[i][j] == '=' or table[i][j] == 'X')
                    continue;

                done = false;

                pair<char, char> tran1 = transformation(DFA, states[i], freq);
                pair<char, char> tran2 = transformation(DFA, states[j], freq);

                int a = getStateIdx(states, tran1.first);
                int b = getStateIdx(states, tran1.second);
                int c = getStateIdx(states, tran2.first);
                int d = getStateIdx(states, tran2.second);

                if(table[a][c] == '*' || table[b][d] == '*')
                    continue;

                if(table[a][c] == table[b][d])
                    table[i][j] = '=';
                else
                    table[i][j] = 'X';
            }
        }

        if(done)
            break;

        freq++;
    }

    map<char, char> mirror;
    for(int i=0; i<numberOfStates; i++)
    {
        mirror[states[i]] = states[i];
    }

    cout << "\nEquivalance table:\n";
    for(int i=numberOfStates-2; i>=0; i--)
    {
        for(int j=numberOfStates-1; j>=0; j--)
        {
            if(j > i)
            {
                cout << table[i][j];

                if(table[i][j] == '=')
                {
                    mirror[states[j]] = states[i];
                }
            }
            else cout << " ";
        }
        cout << endl;
    }

    cout << "\nSmallest DFA:\n";
    for(int i=0; i<numberOfStates; i++)
    {
        if(mirror[states[i]] != states[i]) continue;

        cout << states[i] << " ";
        cout << mirror[DFA[states[i]].first] << " ";
        cout << mirror[DFA[states[i]].second];
        cout << endl;
    }

    return 0;
}
