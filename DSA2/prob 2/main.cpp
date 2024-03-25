#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

struct Node {
    bool is_leaf;
    char color;
    Node* child[4];
};

Node* buildQuadTree(string& str, int& index) {
    if (index == str.size()) {
        return NULL;
    }

    Node* node = new Node;

    if (str[index] == 'p') {
        node->is_leaf = false;
        for (int i = 0; i < 4; i++) {
            index++;
            node->child[i] = buildQuadTree(str, index);
        }
    } else {
        node->is_leaf = true;
        node->color = str[index];
    }
    return node;
}

void displayQuadTree(Node* root, int indent = 0) {
    if (root == nullptr) {
        return;
    }

    if (root->is_leaf) {
        cout << string(indent, ' ') << (root->color) << endl;
        return;
    }

    cout << string(indent, ' ') << "p" << endl;

    displayQuadTree(root->child[0], indent + 4);
    displayQuadTree(root->child[1], indent + 4);
    displayQuadTree(root->child[2], indent + 4);
    displayQuadTree(root->child[3], indent + 4);
}

void calculateSum(Node* root, int level, int &sum) {
    if (root == nullptr)
        return;

    if (root->is_leaf==false) {
        calculateSum(root->child[0], level + 1, sum);
        calculateSum(root->child[1], level + 1, sum);
        calculateSum(root->child[2], level + 1, sum);
        calculateSum(root->child[3], level + 1, sum);
    }
    else if (root->color == 'b')
        sum = sum + 1024/pow(4, level);

}

string mergeQuadTrees(string str1, string str2) {
    if (str1[0] == NULL) {
        return str2;
    }
    if (str2[0] == NULL) {
        return str1;
    }
    string result="p";
    int i = 1, j = 1;

    while (i < str1.size() && j < str2.size()) {
        char c1 = str1[i];
        char c2 = str2[j];
        if (c1 == c2) {
            result += c1;
            i++;
            j++;
        }
         if (c1 == 'p' && c2 == 'p') {
            result += 'p';
            i++;
            j++;
        }
        if (c1 == 'p' && c2 == 'w') {
            j++;
            i++;
            result +='p';
            for (int k = 0; k < 4; k++) {
                    result += str1[i];
                    i++;
            }
        }
        if (c1 == 'w' && c2 == 'p') {
             j++;
             i++;
             result +='p';
            for (int k = 0; k < 4; k++) {
                if (j < str2.size()) {
                    result += str2[j];
                    j++;
                }
            }
        }
        if (c1 == 'b' && c2 == 'p') {
            j=j+5;
            i++;
            result +='b';

        }
        if (c1 == 'p' && c2 == 'b') {
            j++;
            i=i+5;
            result +='b';
        }
        if (c1 != 'p' && c2 != 'p') {

            if ((c1 == 'b' && c2 == 'w') || (c1 == 'w' && c2 == 'b'))
                    result += 'b';
            else
                result += 'w';
            i++;
            j++;
        }
    }

    if (i < str1.size()) {
        result += str1.substr(i);
    }
    else if (j < str2.size()) {
        result += str2.substr(j);
    }

    return result;
}


int main() {
    cout<<"These are some given examples: "<<endl;

    string str1, str2, str3, str4, str5, str6, str7, str8, str9;
    int index1 = 0, index2 = 0, index3=0, index4 = 0, index=0;
    cout<<"EXAMPLE 1:"<<endl;
    str1="ppwwwbpbbwwbw";
    str2="pwbwpwwbw";
    cout<<"For: "<<str1<<" and: "<<str2<<":"<<endl;
    int n=0;
    str3 = mergeQuadTrees(str1,str2);
    cout<<"The merged tree is: "<<str3<<endl;
    Node* tree1 = buildQuadTree(str3, index1);
    cout<<"And the representation is: "<<endl;
    displayQuadTree(tree1);
    cout<<"And the number of pixels is: ";
    calculateSum(tree1,0,n);
    cout<<n<<endl<<endl;


    cout<<"EXAMPLE 2:"<<endl;
    str4="ppwwwbbbpwwbw";
    str5="pwwpwbwbb";
    cout<<"For: "<<str4<<" and: "<<str5<<":"<<endl;
    int m=0;
    str6 = mergeQuadTrees(str4,str5);
    cout<<"The merged tree is: "<<str6<<endl;
    Node* tree2 = buildQuadTree(str6, index2);
    cout<<"And the representation is: "<<endl;
    displayQuadTree(tree2);
    cout<<"And the number of pixels is: ";
    calculateSum(tree2,0,m);
    cout<<m<<endl<<endl;

    int ok=0;
    cout<<"Please imput your own two graphs!"<<endl;
    cin>>str7>>str8;
    cout<<endl;
    cout<<"Great! Now choose what you want to do with them! "<<endl;
    cout<<"Choose 1 to display them!"<<endl;
    cout<<"Choose 2 to display the number of black pixels for both!"<<endl;
    cout<<"Choose 3 to merge them and display the number of black pixels for the merged graph!"<<endl;

    cin>>ok;

    Node* tree3 = buildQuadTree(str7, index3);
    Node* tree4 = buildQuadTree(str8, index4);

    switch(ok){

        case 1: {
            cout<<"The first representation: "<<endl;

            displayQuadTree(tree3);
            cout<<endl;
            cout<<"And the second representation: "<<endl;
            displayQuadTree(tree4);
            break;

        }

        case 2: {
            int k=0, l=0;
            calculateSum(tree3,0,k);
            calculateSum(tree4,0,l);
            cout<<"The numbers of pixels are "<<k<<" and "<<l<<"!";
            break;
        }

        case 3: {
            int o=0;
            str9 = mergeQuadTrees(str7,str8);
            Node* tree = buildQuadTree(str9, index);
            cout<<"The merged tree is:"<<endl;
            displayQuadTree(tree);
            cout<<endl;
            calculateSum(tree,0,o);
            cout<<"And the number of pixels is "<<o<<"!";
            break;
        }
        default:
        {
            cout << "Invalid option";
            break;
        }

    }
    cout<<endl;
    cout<<"Thank you for your attention! ^^"<<endl;

    return 0;
}
