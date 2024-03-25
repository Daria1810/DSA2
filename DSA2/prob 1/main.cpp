#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>
#include <cstring>

using namespace std;

ifstream in("index.in");
ofstream out("index.out");

struct Graph
{
    int N; ///the number of vertices in the graph
    int A[26][26]; ///the matrix for the graph
};


void dfs( Graph& g, bool visited[], stack<int>& result, int x)
{
    visited[x] = true;

    for (int y = 0; y < g.N; y++)
    {
        if (g.A[x][y] && !visited[y])
        {
            dfs(g, visited, result, y);
        }
    }

    result.push(x);
}


void topologicalSort( Graph& g,  string & alphabet)
{
    int numVertices = alphabet.size();
    bool visited[26] = {false}; ///marks all vertices as not visited
    stack<int> result; ///stack the sorted order

    for (int i = 0; i < numVertices; i++)
    {
        if (!visited[i])
        {
            dfs(g, visited, result, i);
        }
    }


    while (!result.empty())
    {
        out << alphabet[result.top()];
        result.pop();
    }
    /* ///display the adjacency matrix in order to verify the graph to be correctly build
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            cout << g.A[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;*/

}

int main()
{
    ///the uniqueChars is used to store the appearances of the characters if order of appearance
    ///alphabet string is where is going to be stored the correct order in index.out
    int constant=-1; /// we need to get a constant variable used for the end of a string
    string words[26]; ///this array stores the words from index.in
    string word, uniqueChars, alphabet;
    int nr = 0;/// the number of words read

    while (in >> word && word != ".")///reading from the index.in without knowing the number of words
    {
        words[nr++] = word;
    }


    for (int i = 0; i < nr; i++)
    {
        for (int j=0; j<words[i].length(); j++)
        {
            char c= words[i][j];
            if (uniqueChars.find(c) == constant)///checks if the current character is unique
            {
                uniqueChars += c;
            }
        }
    }

    sort(uniqueChars.begin(), uniqueChars.end());///sort in ascending order
    alphabet = uniqueChars;

    int vertices = alphabet.size();
    Graph g;
    g.N = vertices;
    ///for the adjancency matrix value to 0 in
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            g.A[i][j] = 0;
        }
    }

    for (int i = 0; i < nr - 1; i++)
    {
        string currWord = words[i];///current word
        string nextWord = words[i + 1];///next word

        int j = 0;
        while (j < currWord.length() && j < nextWord.length() && currWord[j] == nextWord[j])
        {
            j++; ///find the position where the two words differ
        }

        if (j < currWord.length() && j < nextWord.length())
        {
            int currChar = alphabet.find(currWord[j]);
            int nextChar = alphabet.find(nextWord[j]);
            g.A[currChar][nextChar] = 1;///marks the edge in the matrix between the two characters
        }
    }

    topologicalSort(g, alphabet);
    return 0;
}
