template < class DataType >
class BinarySearchTree
{
private:
    struct BinaryNode
    {
        DataType data;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode(const DataType &thedata, BinaryNode *lp, BinaryNode *rp)
        :data(thedata), left(lp), right(rp){}
    };

    BinaryNode *root;

    void _insert(const DataType &x, BinaryNode *&t);
    void _remove(const DataType &x, BinaryNode *&t);
    bool _find(const DataType &x, BinaryNode *t) const;
    void _makeEmpty(BinaryNode *t);

    void _midOrder(BinaryNode *t) const //中序遍历递归实现
    {
        if (t!=nullptr)
        {
            _midOrder(t->left);
            cout<<t->data<<" ";
            _midOrder(t->right);
        }
    }

public:
    BinarySearchTree(BinaryNode *t = nullptr){root = t;}
    ~BinarySearchTree(){} //注意这里不能();否则会报错未定义的析构函数

    bool find(const DataType &x) const;
    void insert(const DataType &x);
    void remove(const DataType &x);
    void clear()
    {
        if(root!=nullptr) _makeEmpty(root); 
        root = nullptr;
    }

    void midOrder() const
    {
        cout<< "mid order traverse:"<<endl;
        if (root==nullptr)
        {
            cout<< "empty tree!"<<endl;
            return;
        }
        _midOrder(root);
        cout<<endl;
    }

};

template<class DataType>
void BinarySearchTree<DataType>::_makeEmpty(BinaryNode *t) //这里的*t不需要加&，因为该函数并不修改t的指向(加了&效果也一样)
{
    if (t->left!=nullptr) _makeEmpty(t->left);
    if (t->right!= nullptr) _makeEmpty(t->right);
    delete t;
}

/**insert
 * 二叉搜索树插入函数
 * 递归实现
 */
template<class DataType>
void BinarySearchTree<DataType>::insert(const DataType &x)
{
    _insert(x, root);
}

template<class DataType>
void BinarySearchTree<DataType>::_insert(const DataType &x, BinaryNode *&t)
{
    if (t==nullptr)
        t = new BinaryNode(x, nullptr, nullptr);
    else if (x < t->data)
        _insert(x, t->left);
    else if (x > t->data)
        _insert(x, t->right);
}

/**remove
 * 二叉搜索树删除函数
 * 递归实现，BST中最为复杂的步骤
 */
template<class DataType>
void BinarySearchTree<DataType>::remove(const DataType &x)
{
    _remove(x, root);
}

template<class DataType>
void BinarySearchTree<DataType>::_remove(const DataType &x, BinaryNode *&t)
{
    if (t==nullptr)
        return; //未找到需要删除的节点
    if (x < t->data)
        _remove(x, t->left);
    else if (x > t->data)
        _remove(x, t->right);
    else if (t->left!=nullptr && t->right!=nullptr) //找到了要删除的节点，先把特殊情况处理了，即删除有两个儿子的节点
    {
        //删除该节点会使其他节点从树上脱离，因此要寻找替身
        //为了保证二叉搜索树的有序性，需要选中序遍历中紧挨着被删节点的节点(因为中序遍历二叉搜索树的序列是递增排列的)
        //即被删节点左子树中最大的节点或被删节点右子树中最小的节点
        //而左子树最大节点没有右儿子，右子树最小节点没有左儿子，因此删除它们是比较简单的
        
        //首先找到替身节点，假设要找右子树的最小节点
        //则沿右子树的左儿子链找下去，直到遇到没有左儿子的节点
        BinaryNode *tmp = t->right;
        while (tmp->left != nullptr)
            tmp = tmp->left;
        t->data = tmp->data;
        //删除该替身节点，继续用递归，精妙！
        _remove(t->data, t->right);
    }
    else //被删节点是叶节点或只有一个儿子
    {
        BinaryNode* oldNode = t;
        t = (t->left == nullptr)?t->right:t->left; 
        delete oldNode;
    }
}

/**find
 * 二叉搜索树查找函数
 * 递归实现
 */
template<class DataType>
bool BinarySearchTree<DataType>::find(const DataType &x) const
{
    return _find(x, root);
}

template<class DataType>
bool BinarySearchTree<DataType>::_find(const DataType &x, BinaryNode *t)const
{
    if (t==nullptr) //未找到
        return false;
    else if (x < t->data)
        return _find(x, t->left);
    else if (x > t->data)
        return _find(x, t->right);
    else 
        return true; //找到了
}
