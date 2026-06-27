/*
 * ============================================================
 * CSP-S 备考课程 — 第07课：二叉树基础与遍历
 *
 * 对应考纲知识点：
 *   - 二叉树的基本概念与性质（满二叉树、完全二叉树）
 *   - 前序/中序/后序遍历（递归与非递归实现）
 *   - 层序遍历（BFS）
 *   - 根据前序 + 中序序列重建二叉树
 *   - 根据后序 + 中序序列重建二叉树
 *
 * 本文件包含：
 *   1. 二叉树节点定义（链式存储）
 *   2. 递归遍历：前序、中序、后序
 *   3. 非递归遍历（栈实现）：前序、中序、后序（双栈法）
 *   4. 层序遍历（队列 BFS）
 *   5. 前序 + 中序 → 重建二叉树
 *   6. 后序 + 中序 → 重建二叉树
 *   7. 完整的 main 函数演示所有功能
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ==================== 二叉树节点定义 ====================
// 链式存储：每个节点包含数据域、左孩子指针、右孩子指针
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// ==================== 工具函数 ====================

// 根据数组构建一棵示例二叉树
// 使用层序输入，-1 表示空节点
// 返回根节点指针
TreeNode* buildDemoTree() {
    // 示例树结构：
    //         1
    //       /   \
    //      2     3
    //     / \   / \
    //    4   5 6   7
    vector<int> vals = {1, 2, 3, 4, 5, 6, 7};
    if (vals.empty()) return nullptr;
    vector<TreeNode*> nodes;
    for (int v : vals) nodes.push_back(new TreeNode(v));
    int n = nodes.size();
    for (int i = 0; i < n; i++) {
        int l = 2 * i + 1, r = 2 * i + 2;
        if (l < n) nodes[i]->left = nodes[l];
        if (r < n) nodes[i]->right = nodes[r];
    }
    return nodes[0];
}

// 释放二叉树内存（后序遍历删除所有节点）
void freeTree(TreeNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// ==================== 1. 递归遍历 ====================

// 前序遍历（递归）：根 → 左 → 右
void preorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    result.push_back(root->val);       // 访问根
    preorder(root->left, result);      // 遍历左子树
    preorder(root->right, result);     // 遍历右子树
}

// 中序遍历（递归）：左 → 根 → 右
void inorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    inorder(root->left, result);       // 遍历左子树
    result.push_back(root->val);       // 访问根
    inorder(root->right, result);      // 遍历右子树
}

// 后序遍历（递归）：左 → 右 → 根
void postorder(TreeNode* root, vector<int>& result) {
    if (!root) return;
    postorder(root->left, result);     // 遍历左子树
    postorder(root->right, result);    // 遍历右子树
    result.push_back(root->val);       // 访问根
}

// ==================== 2. 非递归遍历（栈实现）====================

// 前序遍历（非递归）：借助栈，先压右孩子再压左孩子
vector<int> preorderIterative(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* cur = st.top(); st.pop();
        result.push_back(cur->val);
        // 先压右，后压左，保证左孩子先出栈
        if (cur->right) st.push(cur->right);
        if (cur->left)  st.push(cur->left);
    }
    return result;
}

// 中序遍历（非递归）：一路向左，到底后弹出访问并转向右子树
vector<int> inorderIterative(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur || !st.empty()) {
        // 走到最左边，沿途节点全部入栈
        while (cur) {
            st.push(cur);
            cur = cur->left;
        }
        // 左子树已空，弹出栈顶访问
        cur = st.top(); st.pop();
        result.push_back(cur->val);
        // 转向右子树
        cur = cur->right;
    }
    return result;
}

// 后序遍历（非递归 — 双栈法）：
// 利用前序（根→右→左）的逆序 = 后序（左→右→根）
vector<int> postorderIterative(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    stack<TreeNode*> st1, st2;
    st1.push(root);
    while (!st1.empty()) {
        TreeNode* cur = st1.top(); st1.pop();
        st2.push(cur);                       // 压入辅助栈
        // 注意这里是先左后右（因为 st1 的弹出顺序是反的）
        if (cur->left)  st1.push(cur->left);
        if (cur->right) st1.push(cur->right);
    }
    // st2 的弹出顺序即为后序遍历
    while (!st2.empty()) {
        result.push_back(st2.top()->val);
        st2.pop();
    }
    return result;
}

// ==================== 3. 层序遍历（队列 BFS）====================

vector<int> levelorder(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        TreeNode* cur = q.front(); q.pop();
        result.push_back(cur->val);
        if (cur->left)  q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
    return result;
}

// 层序遍历（分层输出）：每一层的节点单独一行
vector<vector<int>> levelorderByLevel(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    queue<TreeNode*> q;
    q.push(root);
    while (!q.empty()) {
        int sz = q.size();          // 当前层的节点数
        vector<int> curLevel;
        for (int i = 0; i < sz; i++) {
            TreeNode* cur = q.front(); q.pop();
            curLevel.push_back(cur->val);
            if (cur->left)  q.push(cur->left);
            if (cur->right) q.push(cur->right);
        }
        result.push_back(curLevel);
    }
    return result;
}

// ==================== 4. 前序 + 中序 → 重建二叉树 ====================

// 存储中序遍历中每个值对应的下标，用于 O(1) 查找根节点位置
unordered_map<int, int> inMap;

// 递归构建
// pre[preL..preR] 是当前子树的前序序列
// in[inL..inR]     是当前子树的中序序列
TreeNode* buildFromPreIn(vector<int>& pre, int preL, int preR,
                          vector<int>& in,  int inL,  int inR) {
    if (preL > preR) return nullptr;
    int rootVal = pre[preL];                 // 前序第一个是根
    int rootPos = inMap[rootVal];            // 根在中序中的位置
    int leftSize = rootPos - inL;            // 左子树的节点数

    TreeNode* root = new TreeNode(rootVal);
    // 左子树：前序 [preL+1 .. preL+leftSize]，中序 [inL .. rootPos-1]
    root->left = buildFromPreIn(pre, preL + 1, preL + leftSize,
                                 in,  inL, rootPos - 1);
    // 右子树：前序 [preL+leftSize+1 .. preR]，中序 [rootPos+1 .. inR]
    root->right = buildFromPreIn(pre, preL + leftSize + 1, preR,
                                  in,  rootPos + 1, inR);
    return root;
}

// 入口函数：给定前序和中序，返回重建的二叉树根节点
TreeNode* buildTreeFromPreIn(vector<int>& preorder, vector<int>& inorder) {
    int n = inorder.size();
    inMap.clear();
    // 建立值 → 中序下标的映射
    for (int i = 0; i < n; i++) {
        inMap[inorder[i]] = i;
    }
    return buildFromPreIn(preorder, 0, n - 1, inorder, 0, n - 1);
}

// ==================== 5. 后序 + 中序 → 重建二叉树 ====================

// 递归构建
// post[postL..postR] 是当前子树的后序序列
// in[inL..inR]         是当前子树的中序序列
TreeNode* buildFromPostIn(vector<int>& post, int postL, int postR,
                           vector<int>& in,   int inL,   int inR) {
    if (postL > postR) return nullptr;
    int rootVal = post[postR];               // 后序最后一个是根
    int rootPos = inMap[rootVal];            // 根在中序中的位置
    int leftSize = rootPos - inL;            // 左子树的节点数

    TreeNode* root = new TreeNode(rootVal);
    // 左子树：后序 [postL .. postL+leftSize-1]，中序 [inL .. rootPos-1]
    root->left = buildFromPostIn(post, postL, postL + leftSize - 1,
                                  in,   inL, rootPos - 1);
    // 右子树：后序 [postL+leftSize .. postR-1]，中序 [rootPos+1 .. inR]
    root->right = buildFromPostIn(post, postL + leftSize, postR - 1,
                                   in,   rootPos + 1, inR);
    return root;
}

// 入口函数
TreeNode* buildTreeFromPostIn(vector<int>& postorder, vector<int>& inorder) {
    int n = inorder.size();
    inMap.clear();
    for (int i = 0; i < n; i++) {
        inMap[inorder[i]] = i;
    }
    return buildFromPostIn(postorder, 0, n - 1, inorder, 0, n - 1);
}

// ==================== 辅助输出 ====================

void printVector(const vector<int>& v, const string& label) {
    cout << label << ": ";
    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) cout << ' ';
        cout << v[i];
    }
    cout << '\n';
}

// ==================== 主函数演示 ====================

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    // ---------- 演示1：递归与非递归遍历 ----------
    cout << "========================================\n";
    cout << "  演示1：二叉树的四种遍历\n";
    cout << "========================================\n";
    cout << "示例二叉树（层序：1 2 3 4 5 6 7）：\n";
    cout << "        1\n";
    cout << "      /   \\\n";
    cout << "     2     3\n";
    cout << "    / \\   / \\\n";
    cout << "   4   5 6   7\n\n";

    TreeNode* root = buildDemoTree();

    vector<int> res;
    preorder(root, res);
    printVector(res, "前序（递归）  ");
    printVector(preorderIterative(root), "前序（非递归）");

    res.clear();
    inorder(root, res);
    printVector(res, "中序（递归）  ");
    printVector(inorderIterative(root), "中序（非递归）");

    res.clear();
    postorder(root, res);
    printVector(res, "后序（递归）  ");
    printVector(postorderIterative(root), "后序（非递归）");

    printVector(levelorder(root), "层序          ");

    // 分层输出
    cout << "\n层序遍历（按层）：\n";
    auto levels = levelorderByLevel(root);
    for (size_t i = 0; i < levels.size(); i++) {
        cout << "  第" << (i + 1) << "层: ";
        for (size_t j = 0; j < levels[i].size(); j++) {
            if (j > 0) cout << ' ';
            cout << levels[i][j];
        }
        cout << '\n';
    }

    // 释放演示树的内存
    freeTree(root);

    // ---------- 演示2：前序 + 中序重建 ----------
    cout << "\n========================================\n";
    cout << "  演示2：前序 + 中序 → 重建二叉树\n";
    cout << "========================================\n";

    vector<int> pre = {1, 2, 4, 5, 3, 6, 7};
    vector<int> in  = {4, 2, 5, 1, 6, 3, 7};
    cout << "前序序列: "; for (int x : pre) cout << x << ' '; cout << '\n';
    cout << "中序序列: "; for (int x : in)  cout << x << ' '; cout << '\n';

    TreeNode* rebuilt = buildTreeFromPreIn(pre, in);
    cout << "重建后验证 → 后序遍历: ";
    vector<int> postCheck;
    postorder(rebuilt, postCheck);
    for (int x : postCheck) cout << x << ' ';
    cout << "(期望: 4 5 2 6 7 3 1)\n";
    freeTree(rebuilt);

    // ---------- 演示3：后序 + 中序重建 ----------
    cout << "\n========================================\n";
    cout << "  演示3：后序 + 中序 → 重建二叉树\n";
    cout << "========================================\n";

    vector<int> post = {4, 5, 2, 6, 7, 3, 1};
    cout << "后序序列: "; for (int x : post) cout << x << ' '; cout << '\n';
    cout << "中序序列: "; for (int x : in)   cout << x << ' '; cout << '\n';

    TreeNode* rebuilt2 = buildTreeFromPostIn(post, in);
    cout << "重建后验证 → 前序遍历: ";
    vector<int> preCheck;
    preorder(rebuilt2, preCheck);
    for (int x : preCheck) cout << x << ' ';
    cout << "(期望: 1 2 4 5 3 6 7)\n";
    freeTree(rebuilt2);

    cout << "\n所有演示完成！\n";
    return 0;
}
