# Binary Search Tree 二叉搜索树
动态查找需要既方便插入删除，也方便查找

满足条件：
- 左子树所有元素的键值都比根节点的键值小
- 右子树所有元素的键值都比根节点的键值大
- 左右子树也都是二叉搜索树

重要性质：
- **中序遍历一棵二叉搜索树所得到的访问序列是按键值的递增次序排列的，因此二叉搜索树也可以用于排序**
- 没有创建二叉搜索树的操作，要从空树开始经反复地插入或删除后动态形成

操作：查找、插入、删除
- 递归实现（因为二叉搜索树是递归定义的）
- **最复杂的是删除操作**
- 删除最终可以归结到两种情况：删除叶节点和删除只有一个儿子的节点
- 二叉树的平均高度为logN，操作的时间复杂度也是logN
  - 最好情况（完全平衡二叉树）：O(logN)
  - 最坏情况（退化为链表）：O(N)
  - 平均情况：O(1.38*logN)——**有公式推导**