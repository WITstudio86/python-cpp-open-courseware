/**
 * CSP-J 备考课程 — 第44课：树的基础
 *
 * 涵盖内容：
 *   1. 二叉树结构定义
 *   2. 前序 / 中序 / 后序 / 层序遍历
 *   3. 根据前序+中序重建二叉树
 *   4. 并查集（Union-Find）—— 路径压缩 + 按秩合并
 *
 * 编译运行：g++ -std=c++11 -O2 lesson44_树的基础.cpp -o tree_demo && ./tree_demo
 */

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <algorithm>
using namespace std;

// ==============================
// 二叉树节点定义
// ==============================
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ------------------------------
// 释放二叉树内存（后序遍历删除）
// ------------------------------
void deleteTree(TreeNode* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

// ==============================
// 示例1：二叉树的四种遍历
// ==============================
void preorder(TreeNode* root) {
    if (!root) return;
    cout << root->val << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

void postorder(TreeNode* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->val << " ";
}

void levelorder(TreeNode* root) {
    if (!root) return;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* cur = q.front();
        q.pop();
        cout << cur->val << " ";
        if (cur->left)  q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

void demo_tree_traversals() {
    cout << "========== 示例1：二叉树的四种遍历 ==========" << endl;

    // 构建二叉树:
    //        1
    //       / \
    //      2   3
    //     / \   \
    //    4   5   6
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);

    cout << "树结构：" << endl;
    cout << "        1" << endl;
    cout << "       / \\" << endl;
    cout << "      2   3" << endl;
    cout << "     / \\   \\" << endl;
    cout << "    4   5   6" << endl;
    cout << endl;

    cout << "前序遍历 (根左右): ";
    preorder(root);
    cout << endl;

    cout << "中序遍历 (左根右): ";
    inorder(root);
    cout << endl;

    cout << "后序遍历 (左右根): ";
    postorder(root);
    cout << endl;

    cout << "层序遍历 (逐层):   ";
    levelorder(root);
    cout << endl;
    cout << endl;

    deleteTree(root);
}

// ==============================
// 示例2：根据前序+中序重建二叉树
// ==============================
TreeNode* buildTree(const vector<int>& pre, int pl, int pr,
                    const vector<int>& in, int il, int ir) {
    if (pl > pr || il > ir) return nullptr;
    int rootVal = pre[pl];
    TreeNode* root = new TreeNode(rootVal);

    // 在中序中找根的位置
    int pos = il;
    while (pos <= ir && in[pos] != rootVal) pos++;

    int leftSize = pos - il;
    root->left  = buildTree(pre, pl + 1, pl + leftSize, in, il, pos - 1);
    root->right = buildTree(pre, pl + leftSize + 1, pr, in, pos + 1, ir);
    return root;
}

void demo_build_tree() {
    cout << "========== 示例2：根据前序+中序重建二叉树 ==========" << endl;

    // 前序: 1 2 4 5 3 6
    // 中序: 4 2 5 1 3 6
    vector<int> pre = {1, 2, 4, 5, 3, 6};
    vector<int> in  = {4, 2, 5, 1, 3, 6};

    TreeNode* root = buildTree(pre, 0, (int)pre.size() - 1,
                                in, 0, (int)in.size() - 1);

    cout << "前序序列: 1 2 4 5 3 6" << endl;
    cout << "中序序列: 4 2 5 1 3 6" << endl;
    cout << "重建后的后序遍历: ";
    postorder(root);
    cout << " (预期: 4 5 2 6 3 1)" << endl;
    cout << endl;

    deleteTree(root);
}

// ==============================
// 示例3：并查集（Union-Find）
// ==============================
const int MAXN = 100005;
int parent[MAXN];
int rnk[MAXN];

void uf_init(int n) {
    for (int i = 1; i <= n; i++) {
        parent[i] = i;
        rnk[i] = 0;
    }
}

int uf_find(int x) {
    if (parent[x] == x) return x;
    return parent[x] = uf_find(parent[x]);  // 路径压缩
}

void uf_union(int a, int b) {
    int ra = uf_find(a);
    int rb = uf_find(b);
    if (ra == rb) return;
    // 按秩合并
    if (rnk[ra] < rnk[rb]) {
        parent[ra] = rb;
    } else if (rnk[ra] > rnk[rb]) {
        parent[rb] = ra;
    } else {
        parent[rb] = ra;
        rnk[ra]++;
    }
}

void demo_union_find() {
    cout << "========== 示例3：并查集（Union-Find） ==========" << endl;

    int n = 10;
    uf_init(n);

    cout << "初始状态：每个节点自成一个集合" << endl;

    // 建立关系
    cout << "合并 (1,2), (2,3), (4,5), (6,7,8), (9,10)" << endl;
    uf_union(1, 2);
    uf_union(2, 3);   // {1,2,3}
    uf_union(4, 5);   // {4,5}
    uf_union(6, 7);
    uf_union(7, 8);   // {6,7,8}
    uf_union(9, 10);  // {9,10}

    // 查询连通性
    cout << endl;
    cout << "查询连通性：" << endl;
    cout << "  find(1) == find(3) ? " << (uf_find(1) == uf_find(3) ? "true (连通)" : "false") << endl;
    cout << "  find(1) == find(5) ? " << (uf_find(1) == uf_find(5) ? "true" : "false (不连通)") << endl;
    cout << "  find(6) == find(8) ? " << (uf_find(6) == uf_find(8) ? "true (连通)" : "false") << endl;

    // 合并两个集合
    cout << endl;
    cout << "合并 (3,4) —— 连接 {1,2,3} 和 {4,5}" << endl;
    uf_union(3, 4);
    cout << "  find(1) == find(5) ? " << (uf_find(1) == uf_find(5) ? "true (连通)" : "false") << endl;

    // 统计集合数量
    int setCount = 0;
    for (int i = 1; i <= n; i++) {
        if (uf_find(i) == i) setCount++;
    }
    cout << endl;
    cout << "当前集合数量: " << setCount << " (预期: 4个)" << endl;

    // 列出各集合
    cout << "各节点所属集合代表：" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "  节点" << i << "的代表: " << uf_find(i) << endl;
    }
    cout << endl;
}

// ==============================
// 示例4：并查集应用 — 统计连通分量
// ==============================
void demo_union_find_components() {
    cout << "========== 示例4：并查集 — 统计连通分量 ==========" << endl;

    // 模拟一个社交网络：5个用户，3对好友关系
    // 关系：(1,2), (2,3), (4,5)
    // 期望：2个朋友圈 {1,2,3} 和 {4,5}
    int n = 5;
    uf_init(n);

    uf_union(1, 2);
    uf_union(2, 3);
    uf_union(4, 5);

    // 检查1-3是否在同一个朋友圈
    cout << "用户1和3在同一朋友圈？ ";
    cout << (uf_find(1) == uf_find(3) ? "是" : "否") << endl;

    // 检查1-4是否在同一个朋友圈
    cout << "用户1和4在同一朋友圈？ ";
    cout << (uf_find(1) == uf_find(4) ? "是" : "否") << endl;

    // 朋友圈总数
    int circles = 0;
    for (int i = 1; i <= n; i++) {
        if (uf_find(i) == i) circles++;
    }
    cout << "朋友圈总数: " << circles << endl;
    cout << endl;
}

// ==============================
// main
// ==============================
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << "======================================" << endl;
    cout << "  CSP-J 第44课：树的基础 演示" << endl;
    cout << "======================================" << endl << endl;

    demo_tree_traversals();
    demo_build_tree();
    demo_union_find();
    demo_union_find_components();

    return 0;
}
