/**
 * lesson43_trie.cpp
 * 第43课：Trie 树（字典树）—— 代码模板与真题 AC 代码
 *
 * 包含：
 *   1. 普通 Trie 结构体（insert / query / countPrefix）
 *   2. 01Trie 结构体（insert / queryMaxXor / remove）
 *   3. 真题：前缀统计 + 最大异或对
 *
 * CSP-S 考点：Trie 树的插入与查询，01Trie 求最大异或对
 */

#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

// ============================================================
// 一、普通 Trie 树（小写字母，字符集大小 26）
// ============================================================
const int MAXN = 100010;  // 节点总数，根据题目数据范围调整

struct Trie {
    int son[MAXN][26];   // son[p][c]：节点 p 的字符 c 子节点编号
    int cnt[MAXN];       // cnt[p]：以节点 p 结尾的字符串数量
    int pass[MAXN];      // pass[p]：经过节点 p 的字符串数量（用于前缀统计）
    int idx;             // 当前节点编号，0 为根节点

    /**
     * 初始化 Trie
     * 如果有多组测试数据，需要清空数组
     */
    void init() {
        memset(son, 0, sizeof(son));
        memset(cnt, 0, sizeof(cnt));
        memset(pass, 0, sizeof(pass));
        idx = 0;
    }

    /**
     * 插入一个字符串 s
     * 时间复杂度：O(|s|)
     */
    void insert(const string &s) {
        int p = 0;  // 从根节点开始
        for (char ch : s) {
            int c = ch - 'a';           // 映射到 0~25
            if (!son[p][c]) {
                son[p][c] = ++idx;      // 不存在则新建节点
            }
            p = son[p][c];
            pass[p]++;                  // 记录经过次数
        }
        cnt[p]++;  // 标记字符串结束
    }

    /**
     * 查询完整字符串 s 是否存在
     * 返回：字符串出现的次数（>0 表示存在）
     * 时间复杂度：O(|s|)
     */
    int query(const string &s) {
        int p = 0;
        for (char ch : s) {
            int c = ch - 'a';
            if (!son[p][c]) return 0;   // 路径不存在
            p = son[p][c];
        }
        return cnt[p];  // 返回以该节点结尾的字符串数量
    }

    /**
     * 查询以 prefix 为前缀的单词数量
     * 返回：前缀出现的次数
     * 时间复杂度：O(|prefix|)
     */
    int countPrefix(const string &prefix) {
        int p = 0;
        for (char ch : prefix) {
            int c = ch - 'a';
            if (!son[p][c]) return 0;
            p = son[p][c];
        }
        return pass[p];
    }
};

// ============================================================
// 二、01Trie（二进制 Trie，字符集大小 2）
// ============================================================
const int MAXB = 100010 * 31;  // 每个整数最多 31 个节点

struct Trie01 {
    int son[MAXB][2];    // son[p][0/1]：0/1 子节点编号
    int cnt[MAXB];       // cnt[p]：经过节点 p 的数的个数
    int idx;             // 当前节点编号

    void init() {
        memset(son, 0, sizeof(son));
        memset(cnt, 0, sizeof(cnt));
        idx = 0;
    }

    /**
     * 向 01Trie 中插入整数 x
     * 从高位到低位依次插入（高位优先，因为高位对数值影响大）
     * 位数根据数据范围确定：0 <= ai <= 2^31 - 1，使用 30 位（bit 30 ~ bit 0）
     * 时间复杂度：O(log MAX)
     */
    void insert(int x) {
        int p = 0;
        for (int i = 30; i >= 0; i--) {   // 从最高位开始
            int bit = (x >> i) & 1;        // 当前位的值
            if (!son[p][bit]) {
                son[p][bit] = ++idx;
            }
            p = son[p][bit];
            cnt[p]++;  // 该节点被经过的次数 +1
        }
    }

    /**
     * 查询与 x 异或能得到的最大值
     * 贪心策略：每一位都尽量走与 x 当前位相反的边
     * 返回：最大异或值（不是节点编号）
     * 时间复杂度：O(log MAX)
     */
    int queryMaxXor(int x) {
        int p = 0, res = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            // 尽量走相反的位（bit ^ 1），这样异或结果为 1
            if (son[p][bit ^ 1]) {
                res |= (1 << i);           // 这一位异或结果是 1
                p = son[p][bit ^ 1];
            } else {
                p = son[p][bit];           // 只能走相同的位
            }
        }
        return res;
    }

    /**
     * 从 01Trie 中删除整数 x
     * 利用 cnt 数组判断节点是否还需要保留
     * 时间复杂度：O(log MAX)
     */
    void remove(int x) {
        int p = 0;
        for (int i = 30; i >= 0; i--) {
            int bit = (x >> i) & 1;
            int nxt = son[p][bit];
            cnt[nxt]--;
            if (cnt[nxt] == 0) {
                // 没有数再经过该节点，断开连接
                son[p][bit] = 0;
            }
            p = nxt;
        }
    }
};

// ============================================================
// 三、真题 AC 代码
// ============================================================

// ---------- 真题1：统计以某字符串为前缀的单词数量 ----------
// 题目：维护字符串集合，支持插入和前缀查询
// 来源：AcWing 835. Trie 字符串统计（扩展版）

Trie trie;

void solve_problem1() {
    cout << "========== 真题1：前缀统计 ==========" << endl;
    trie.init();

    // 样例数据
    trie.insert("abc");
    trie.insert("abcdef");
    trie.insert("ab");

    cout << "插入: abc, abcdef, ab" << endl;
    cout << "以 'ab' 为前缀的单词数: " << trie.countPrefix("ab") << endl;   // 期望: 3
    cout << "以 'abc' 为前缀的单词数: " << trie.countPrefix("abc") << endl; // 期望: 2
    cout << "查询 'abc' 是否存在: " << (trie.query("abc") > 0 ? "存在" : "不存在") << endl;
    cout << "查询 'xyz' 是否存在: " << (trie.query("xyz") > 0 ? "存在" : "不存在") << endl;
}

// ---------- 真题2：最大异或对 ----------
// 题目：给定 N 个数，求两两异或的最大值
// 来源：AcWing 143. 最大异或对

Trie01 t01;

void solve_problem2() {
    cout << "\n========== 真题2：最大异或对 ==========" << endl;
    t01.init();

    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;

    // 先全部插入
    for (int i = 0; i < n; i++) {
        t01.insert(arr[i]);
    }

    // 对每个数查询最大异或值
    int maxXor = 0;
    for (int i = 0; i < n; i++) {
        maxXor = max(maxXor, t01.queryMaxXor(arr[i]));
    }

    cout << "数组: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n最大异或值: " << maxXor << endl;
    // 期望: 7 (4 ^ 3 = 100 ^ 011 = 111)

    // 验证：找出是哪两个数
    cout << "各数之间的异或值:\n";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << arr[i] << " ^ " << arr[j] << " = " << (arr[i] ^ arr[j]) << endl;
        }
    }
}

// ============================================================
// 四、综合测试
// ============================================================

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cout << "========================================" << endl;
    cout << "第43课：Trie 树（字典树）—— 代码模板测试" << endl;
    cout << "========================================\n" << endl;

    solve_problem1();
    solve_problem2();

    cout << "\n========================================" << endl;
    cout << "所有测试完成！" << endl;
    cout << "========================================" << endl;

    return 0;
}
