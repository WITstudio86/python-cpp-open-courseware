/*
 * ============================================================
 * CSP-S 备考课程 — 第08课：二叉搜索树与平衡树
 *
 * 对应考纲知识点：
 *   - 二叉搜索树（BST）的插入、查找、删除操作
 *   - BST 删除的三种情况：叶子节点、单子节点、双子节点
 *   - AVL 树的四种旋转（LL右旋、RR左旋、LR左右旋、RL右左旋）
 *   - AVL 树的插入与删除（含平衡维护）
 *   - Treap 的原理与实现（Tree+Heap，随机优先级）
 *   - Treap 的插入、删除、分裂、合并操作
 *
 * 本文件包含：
 *   1. BST 完整实现（插入/查找/删除）
 *   2. AVL 树完整实现（四种旋转 + 插入 + 删除 + 高度维护）
 *   3. Treap 完整实现（插入/删除/查找/分裂/合并）
 *   4. 完整的 main 函数演示所有功能
 * ============================================================
 */

#include <bits/stdc++.h>
using namespace std;

// ==================== BST（二叉搜索树）====================

// BST 节点定义：只有键值和左右孩子指针
struct BSTNode {
    int val;
    BSTNode *left, *right;
    BSTNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// BST 插入（递归版）
// 如果 key 已存在则不做操作
BSTNode* bstInsert(BSTNode* root, int key) {
    if (!root) return new BSTNode(key);
    if (key < root->val)
        root->left = bstInsert(root->left, key);
    else if (key > root->val)
        root->right = bstInsert(root->right, key);
    // key == root->val：忽略重复
    return root;
}

// BST 查找（迭代版，效率更高，无递归栈开销）
BSTNode* bstSearch(BSTNode* root, int key) {
    while (root) {
        if (root->val == key) return root;
        root = (key < root->val) ? root->left : root->right;
    }
    return nullptr;
}

// BST 删除（递归版）—— 处理三种情况
BSTNode* bstDelete(BSTNode* root, int key) {
    if (!root) return nullptr;
    if (key < root->val) {
        root->left = bstDelete(root->left, key);
    } else if (key > root->val) {
        root->right = bstDelete(root->right, key);
    } else {
        // 找到了要删除的节点

        // 情况1 & 2：零个或一个孩子
        if (!root->left) {
            BSTNode* tmp = root->right;
            delete root;
            return tmp;
        }
        if (!root->right) {
            BSTNode* tmp = root->left;
            delete root;
            return tmp;
        }

        // 情况3：有两个孩子
        // 找后继：右子树的最小值节点
        BSTNode* succ = root->right;
        while (succ->left) succ = succ->left;
        // 用后继的值覆盖当前节点
        root->val = succ->val;
        // 删除后继节点（后继最多有一个右孩子，退化为情况1/2）
        root->right = bstDelete(root->right, succ->val);
    }
    return root;
}

// BST 中序遍历（验证 BST 的有序性）
void bstInorder(BSTNode* root, vector<int>& result) {
    if (!root) return;
    bstInorder(root->left, result);
    result.push_back(root->val);
    bstInorder(root->right, result);
}

// ==================== AVL 树 ====================

// AVL 节点定义：比 BST 多了 height 字段，用于计算平衡因子
struct AVLNode {
    int val, height;
    AVLNode *left, *right;
    AVLNode(int x) : val(x), height(1), left(nullptr), right(nullptr) {}
};

// 获取节点高度（空节点高度为 0）
int getHeight(AVLNode* node) {
    return node ? node->height : 0;
}

// 更新节点高度：height = max(左高, 右高) + 1
void updateHeight(AVLNode* node) {
    if (node)
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

// 获取平衡因子：左子树高度 - 右子树高度
int getBalanceFactor(AVLNode* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

// -------------------- AVL 四种旋转操作 --------------------

// 右旋（LL 型失衡）：解决左子树的左子树插入导致的失衡
//   A (BF=2)          B
//  /          →      / \
// B                 C   A
/// \
//C   *
AVLNode* rotateRight(AVLNode* A) {
    AVLNode* B = A->left;
    AVLNode* B_right = B->right;  // B 的右子树（中间部分）

    B->right = A;                  // A 挂到 B 的右孩子
    A->left = B_right;            // B 的原有右子树成为 A 的左子树

    // 注意：必须先更新 A（下层），再更新 B（新根的上层）
    updateHeight(A);
    updateHeight(B);

    return B;                      // B 成为新的子树根
}

// 左旋（RR 型失衡）：解决右子树的右子树插入导致的失衡
//  A (BF=-2)            B
//   \          →       / \
//    B                A   C
//   / \                \
//  *   C                *
AVLNode* rotateLeft(AVLNode* A) {
    AVLNode* B = A->right;
    AVLNode* B_left = B->left;     // B 的左子树（中间部分）

    B->left = A;                   // A 挂到 B 的左孩子
    A->right = B_left;            // B 的原有左子树成为 A 的右子树

    updateHeight(A);
    updateHeight(B);

    return B;                      // B 成为新的子树根
}

// AVL 树插入 —— BST 插入 + 回溯更新高度 + 平衡修复
AVLNode* avlInsert(AVLNode* root, int key) {
    // 步骤1：普通 BST 插入
    if (!root) return new AVLNode(key);

    if (key < root->val) {
        root->left = avlInsert(root->left, key);
    } else if (key > root->val) {
        root->right = avlInsert(root->right, key);
    } else {
        return root;  // 不允许重复元素
    }

    // 步骤2：更新当前节点的高度
    updateHeight(root);

    // 步骤3：计算平衡因子，判断是否需要旋转
    int bf = getBalanceFactor(root);

    // LL 型：左子树高 + 插入在左子树的左子树 → 右旋
    if (bf > 1 && key < root->left->val) {
        return rotateRight(root);
    }
    // RR 型：右子树高 + 插入在右子树的右子树 → 左旋
    if (bf < -1 && key > root->right->val) {
        return rotateLeft(root);
    }
    // LR 型：左子树高 + 插入在左子树的右子树 → 先左旋左孩子，再右旋根
    if (bf > 1 && key > root->left->val) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // RL 型：右子树高 + 插入在右子树的左子树 → 先右旋右孩子，再左旋根
    if (bf < -1 && key < root->right->val) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;  // 平衡，无需旋转
}

// AVL 树删除 —— 比插入复杂，可能引起多次旋转沿路径传播
AVLNode* avlDelete(AVLNode* root, int key) {
    // 步骤1：普通 BST 删除
    if (!root) return nullptr;

    if (key < root->val) {
        root->left = avlDelete(root->left, key);
    } else if (key > root->val) {
        root->right = avlDelete(root->right, key);
    } else {
        // 找到了要删除的节点
        if (!root->left || !root->right) {
            AVLNode* tmp = root->left ? root->left : root->right;
            if (!tmp) {          // 叶子节点
                tmp = root;
                root = nullptr;
            } else {             // 单子节点
                *root = *tmp;    // 注意：这里用拷贝赋值简化处理
            }
            delete tmp;
        } else {
            // 双子节点：找后继（右子树最小值）
            AVLNode* succ = root->right;
            while (succ->left) succ = succ->left;
            root->val = succ->val;
            root->right = avlDelete(root->right, succ->val);
        }
    }

    // 如果树变空了
    if (!root) return nullptr;

    // 步骤2：更新高度
    updateHeight(root);

    // 步骤3：检查并修复平衡
    int bf = getBalanceFactor(root);

    // LL
    if (bf > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);
    // LR
    if (bf > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // RR
    if (bf < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);
    // RL
    if (bf < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

// 验证 AVL 树是否平衡（递归检查每个节点的平衡因子）
bool isAVLBalanced(AVLNode* root) {
    if (!root) return true;
    int bf = getBalanceFactor(root);
    if (bf < -1 || bf > 1) return false;
    return isAVLBalanced(root->left) && isAVLBalanced(root->right);
}

// AVL 中序遍历
void avlInorder(AVLNode* root, vector<int>& result) {
    if (!root) return;
    avlInorder(root->left, result);
    result.push_back(root->val);
    avlInorder(root->right, result);
}

// ==================== Treap（树堆）====================

// 使用更高质量的随机数生成器
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// Treap 节点定义：key（BST键值）+ priority（堆优先级，随机）
struct TreapNode {
    int key, priority;
    TreapNode *left, *right;
    TreapNode(int k) : key(k), priority(rng()), left(nullptr), right(nullptr) {}
};

// Treap 右旋（与 AVL 的右旋完全一样，只是节点类型不同）
TreapNode* treapRotateRight(TreapNode* A) {
    TreapNode* B = A->left;
    A->left = B->right;
    B->right = A;
    return B;
}

// Treap 左旋
TreapNode* treapRotateLeft(TreapNode* A) {
    TreapNode* B = A->right;
    A->right = B->left;
    B->left = A;
    return B;
}

// Treap 插入：
// 1. 先按 BST 规则插入（作为叶子）
// 2. 如果新节点的 priority 大于父节点，通过旋转将新节点"上浮"
//    （维护大根堆性质：父 priority ≥ 子 priority）
TreapNode* treapInsert(TreapNode* root, int key) {
    if (!root) return new TreapNode(key);

    if (key < root->key) {
        root->left = treapInsert(root->left, key);
        // 左孩子的优先级大于根 → 需要右旋让左孩子上来
        if (root->left->priority > root->priority)
            root = treapRotateRight(root);
    } else if (key > root->key) {
        root->right = treapInsert(root->right, key);
        // 右孩子的优先级大于根 → 需要左旋让右孩子上来
        if (root->right->priority > root->priority)
            root = treapRotateLeft(root);
    }
    // key == root->key：忽略重复

    return root;
}

// Treap 删除：
// 1. 找到待删除节点
// 2. 如果该节点有左右孩子，旋转让 priority 较小的孩子上来，将待删节点下沉
// 3. 重复直到待删节点只有一个或零个孩子，直接删除
TreapNode* treapDelete(TreapNode* root, int key) {
    if (!root) return nullptr;

    if (key < root->key) {
        root->left = treapDelete(root->left, key);
    } else if (key > root->key) {
        root->right = treapDelete(root->right, key);
    } else {
        // 找到了要删除的节点
        // 叶子节点：直接删除
        if (!root->left && !root->right) {
            delete root;
            return nullptr;
        }

        // 通过旋转将待删除节点下沉
        // 选择 priority 较大的孩子旋转上来（维护大根堆）
        if (!root->left || (root->right && root->right->priority > root->left->priority)) {
            // 右孩子 priority 更大 → 左旋让右孩子上来，待删节点沉到左子树
            root = treapRotateLeft(root);
            root->left = treapDelete(root->left, key);  // 在左子树中继续删除
        } else {
            // 左孩子 priority 更大 → 右旋让左孩子上来，待删节点沉到右子树
            root = treapRotateRight(root);
            root->right = treapDelete(root->right, key); // 在右子树中继续删除
        }
    }

    return root;
}

// Treap 查找（同 BST，因为 Treap 也是 BST）
TreapNode* treapSearch(TreapNode* root, int key) {
    while (root) {
        if (root->key == key) return root;
        root = (key < root->key) ? root->left : root->right;
    }
    return nullptr;
}

// ---------- Treap 高级操作：分裂（Split）与合并（Merge）----------
// 这两个操作是 Treap 支持区间操作的基石，也是实现"无旋 Treap"的核心

// 分裂：按 key 值 k 将 Treap 分裂成两棵树
//   left  → 所有 key ≤ k 的节点
//   right → 所有 key > k 的节点
void treapSplit(TreapNode* root, int k, TreapNode*& left, TreapNode*& right) {
    if (!root) { left = right = nullptr; return; }
    if (root->key <= k) {
        left = root;
        treapSplit(root->right, k, left->right, right);
    } else {
        right = root;
        treapSplit(root->left, k, left, right->left);
    }
}

// 合并：将两棵 Treap 合并为一棵
//   前提条件：left 中所有 key 都必须小于 right 中所有 key
//   按 priority 选择根：大的 priority 作为根
TreapNode* treapMerge(TreapNode* left, TreapNode* right) {
    if (!left)  return right;
    if (!right) return left;

    if (left->priority > right->priority) {
        // left 的 priority 更大 → left 作为根
        left->right = treapMerge(left->right, right);
        return left;
    } else {
        // right 的 priority 更大 → right 作为根
        right->left = treapMerge(left, right->left);
        return right;
    }
}

// 使用 split + merge 实现插入（替代旋转版本）
TreapNode* treapInsertBySplitMerge(TreapNode* root, int key) {
    TreapNode *left = nullptr, *right = nullptr;
    treapSplit(root, key, left, right);
    TreapNode* newNode = new TreapNode(key);
    return treapMerge(treapMerge(left, newNode), right);
}

// 使用 split + merge 实现删除
TreapNode* treapDeleteBySplitMerge(TreapNode* root, int key) {
    TreapNode *left = nullptr, *mid = nullptr, *right = nullptr;
    // split 成 ≤ key-1 和 > key-1（即 ≥ key）两部分
    treapSplit(root, key - 1, left, mid);
    // 再从 mid 中 split 出 key 以及 > key 的部分
    treapSplit(mid, key, mid, right);
    // mid 此时包含所有 key == k 的节点（这里假设只有一个）
    if (mid) delete mid;  // 删除目标节点
    return treapMerge(left, right);
}

// Treap 中序遍历
void treapInorder(TreapNode* root, vector<int>& result) {
    if (!root) return;
    treapInorder(root->left, result);
    result.push_back(root->key);
    treapInorder(root->right, result);
}

// 打印 Treap 的优先级（用于验证堆性质）
void treapPrintWithPriority(TreapNode* root, int depth = 0) {
    if (!root) return;
    treapPrintWithPriority(root->right, depth + 1);
    for (int i = 0; i < depth; i++) cout << "    ";
    cout << root->key << " (p:" << root->priority << ")\n";
    treapPrintWithPriority(root->left, depth + 1);
}

// ==================== 辅助输出 ====================

void printVec(const vector<int>& v, const string& label) {
    cout << label << ": ";
    for (size_t i = 0; i < v.size(); i++) {
        if (i > 0) cout << ' ';
        cout << v[i];
    }
    cout << '\n';
}

// 释放树内存的辅助函数
void freeBST(BSTNode* root) {
    if (!root) return;
    freeBST(root->left);
    freeBST(root->right);
    delete root;
}
void freeAVL(AVLNode* root) {
    if (!root) return;
    freeAVL(root->left);
    freeAVL(root->right);
    delete root;
}
void freeTreap(TreapNode* root) {
    if (!root) return;
    freeTreap(root->left);
    freeTreap(root->right);
    delete root;
}

// ==================== 主函数演示 ====================

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    // ---------- 演示1：BST 基本操作 ----------
    cout << "========================================\n";
    cout << "  演示1：二叉搜索树（BST）操作\n";
    cout << "========================================\n";

    BSTNode* bstRoot = nullptr;
    // 插入：5, 3, 8, 1, 4, 7, 9
    vector<int> bstVals = {5, 3, 8, 1, 4, 7, 9};
    for (int v : bstVals) bstRoot = bstInsert(bstRoot, v);

    vector<int> inorderRes;
    bstInorder(bstRoot, inorderRes);
    printVec(inorderRes, "BST 中序（应递增）");

    cout << "查找 4: " << (bstSearch(bstRoot, 4) ? "找到" : "未找到") << '\n';
    cout << "查找 6: " << (bstSearch(bstRoot, 6) ? "找到" : "未找到") << '\n';

    cout << "删除 3（双子节点）...\n";
    bstRoot = bstDelete(bstRoot, 3);
    inorderRes.clear();
    bstInorder(bstRoot, inorderRes);
    printVec(inorderRes, "删除 3 后中序  ");

    cout << "删除 1（叶子节点）...\n";
    bstRoot = bstDelete(bstRoot, 1);
    inorderRes.clear();
    bstInorder(bstRoot, inorderRes);
    printVec(inorderRes, "删除 1 后中序  ");

    freeBST(bstRoot);

    // ---------- 演示2：AVL 树操作 ----------
    cout << "\n========================================\n";
    cout << "  演示2：AVL 树操作\n";
    cout << "========================================\n";

    AVLNode* avlRoot = nullptr;
    // 按升序插入（如果是不平衡的 BST 会退化为链）
    cout << "按升序插入 1~7（测试 AVL 自平衡能力）...\n";
    for (int i = 1; i <= 7; i++) {
        avlRoot = avlInsert(avlRoot, i);
        cout << "  插入 " << i << " 后: 高度=" << getHeight(avlRoot)
             << ", 平衡=" << (isAVLBalanced(avlRoot) ? "是" : "否") << '\n';
    }

    vector<int> avlRes;
    avlInorder(avlRoot, avlRes);
    printVec(avlRes, "AVL 中序（应1~7）");

    cout << "AVL 树高度: " << getHeight(avlRoot)
         << " (完美平衡: ceil(log2(7+1))=" << (int)ceil(log2(8)) << ")\n";

    cout << "删除 4...\n";
    avlRoot = avlDelete(avlRoot, 4);
    avlRes.clear();
    avlInorder(avlRoot, avlRes);
    printVec(avlRes, "删除 4 后中序");
    cout << "删除后高度: " << getHeight(avlRoot)
         << ", 平衡=" << (isAVLBalanced(avlRoot) ? "是" : "否") << '\n';

    cout << "删除 1...\n";
    avlRoot = avlDelete(avlRoot, 1);
    avlRes.clear();
    avlInorder(avlRoot, avlRes);
    printVec(avlRes, "删除 1 后中序");
    cout << "删除后高度: " << getHeight(avlRoot)
         << ", 平衡=" << (isAVLBalanced(avlRoot) ? "是" : "否") << '\n';

    freeAVL(avlRoot);

    // ---------- 演示3：Treap 操作 ----------
    cout << "\n========================================\n";
    cout << "  演示3：Treap（树堆）操作\n";
    cout << "========================================\n";

    TreapNode* treapRoot = nullptr;
    // 插入数据
    vector<int> treapVals = {10, 5, 15, 3, 7, 12, 18};
    for (int v : treapVals) treapRoot = treapInsert(treapRoot, v);

    cout << "Treap 结构（含优先级）：\n";
    treapPrintWithPriority(treapRoot);
    cout << '\n';

    vector<int> treapRes;
    treapInorder(treapRoot, treapRes);
    printVec(treapRes, "Treap 中序（应有序）");

    cout << "查找 7: " << (treapSearch(treapRoot, 7) ? "找到" : "未找到") << '\n';
    cout << "查找 20: " << (treapSearch(treapRoot, 20) ? "找到" : "未找到") << '\n';

    cout << "删除 5（双子节点）...\n";
    treapRoot = treapDelete(treapRoot, 5);
    treapRes.clear();
    treapInorder(treapRoot, treapRes);
    printVec(treapRes, "删除 5 后中序");

    freeTreap(treapRoot);

    // ---------- 演示4：Treap 分裂与合并 ----------
    cout << "\n========================================\n";
    cout << "  演示4：Treap 分裂（Split）与合并（Merge）\n";
    cout << "========================================\n";

    TreapNode* splitRoot = nullptr;
    for (int v : vector<int>{8, 3, 11, 1, 6, 9, 14})
        splitRoot = treapInsert(splitRoot, v);

    cout << "原始 Treap：\n";
    treapPrintWithPriority(splitRoot);
    cout << '\n';

    // 按 key=7 分裂
    TreapNode *left = nullptr, *right = nullptr;
    treapSplit(splitRoot, 7, left, right);

    cout << "分裂（k=7）后：\n";
    cout << "左树（key ≤ 7）：\n";
    treapPrintWithPriority(left);
    cout << "右树（key > 7）：\n";
    treapPrintWithPriority(right);

    // 合并回去
    TreapNode* merged = treapMerge(left, right);
    vector<int> mergedRes;
    treapInorder(merged, mergedRes);
    printVec(mergedRes, "合并后中序（应与原始一致）");

    freeTreap(merged);

    // ---------- 演示5：使用 Split+Merge 插入/删除 ----------
    cout << "\n========================================\n";
    cout << "  演示5：Split+Merge 实现插入和删除\n";
    cout << "========================================\n";

    TreapNode* smRoot = nullptr;
    smRoot = treapInsertBySplitMerge(smRoot, 50);
    smRoot = treapInsertBySplitMerge(smRoot, 30);
    smRoot = treapInsertBySplitMerge(smRoot, 70);
    smRoot = treapInsertBySplitMerge(smRoot, 20);
    smRoot = treapInsertBySplitMerge(smRoot, 40);

    cout << "插入 50,30,70,20,40 后：\n";
    treapPrintWithPriority(smRoot);
    cout << '\n';

    smRoot = treapDeleteBySplitMerge(smRoot, 30);
    cout << "删除 30 后：\n";
    treapPrintWithPriority(smRoot);

    freeTreap(smRoot);

    cout << "\n所有演示完成！\n";
    return 0;
}
