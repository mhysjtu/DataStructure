#include <iostream>
using namespace std;

#include "BinarySearchTree.h"

int main(int argc, char **argv)
{
    int a[] = {10,8,6,21,87,56,4,0,11,3,22,7,5,34,1,2,9};
    BinarySearchTree<int> tree;
    for (int i = 0; i < 17; ++i)
    {
        tree.insert(a[i]);
    }

    tree.midOrder();

    cout<<"find 2 is "<<(tree.find(2)?"true":"false")<<endl;
    tree.remove(2);
    cout<<"after delete 2, find 2 is "<<(tree.find(2)?"true":"false")<<endl;

    cout<<"find 3 is "<<(tree.find(3)?"true":"false")<<endl;
    tree.remove(3);
    cout<<"after delete 3, find 3 is "<<(tree.find(3)?"true":"false")<<endl;

    cout<<"find 21 is "<<(tree.find(21)?"true":"false")<<endl;
    tree.remove(21);
    cout<<"after delete 21, find 21 is "<<(tree.find(21)?"true":"false")<<endl;

    cout<<"find 1 is "<<(tree.find(1)?"true":"false")<<endl;
    cout<<"find 22 is "<<(tree.find(22)?"true":"false")<<endl;
    cout<<"find 56 is "<<(tree.find(56)?"true":"false")<<endl;
    
    cout<<"find 100 is "<<(tree.find(100)?"true":"false")<<endl;
    tree.insert(100);
    cout<<"after insert 100, find 100 is "<<(tree.find(100)?"true":"false")<<endl;

    tree.midOrder();
    tree.clear();
    tree.midOrder();

    return 0;
}



