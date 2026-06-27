/**
 * CSP-J 第24课：STL容器——stack与queue
 * 完整演示程序
 * 编译：g++ -std=c++14 -o lesson24 lesson24_STL容器stack与queue.cpp
 */

#include <iostream>
#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ==================== 辅助函数 ====================
void printSection(const string& title) {
    cout << "\n" << string(60, '=') << endl;
    cout << "  " << title << endl;
    cout << string(60, '=') << endl;
}

void printSub(const string& title) {
    cout << "\n--- " << title << " ---" << endl;
}

// ==================== 主程序 ====================
int main() {
    // ==========================================
    // 第一部分：Stack 基础操作
    // ==========================================
    printSection("第一部分：Stack（栈）基础操作");

    printSub("1.1 push / top / pop 基本操作");
    stack<int> s;
    cout << "创建空栈，size = " << s.size() << ", empty = "
         << (s.empty() ? "true" : "false") << endl;

    s.push(10);
    cout << "push(10) -> top = " << s.top() << ", size = " << s.size() << endl;

    s.push(20);
    cout << "push(20) -> top = " << s.top() << ", size = " << s.size() << endl;

    s.push(30);
    cout << "push(30) -> top = " << s.top() << ", size = " << s.size() << endl;

    printSub("1.2 pop() 不返回值（重要！）");
    cout << "注意：pop() 返回 void，不返回被删除的元素！" << endl;
    cout << "正确做法：先 top() 取值，再 pop() 删除" << endl;
    cout << "当前栈顶: " << s.top() << endl;
    s.pop();
    cout << "pop() 后，新栈顶: " << s.top() << endl;
    s.pop();
    cout << "再次 pop() 后，新栈顶: " << s.top() << endl;
    s.pop();
    cout << "三次 pop() 后，size = " << s.size() << ", empty = "
         << (s.empty() ? "true" : "false") << endl;

    printSub("1.3 栈的完整生命周期追踪");
    stack<int> trace;
    cout << "步骤 | 操作       | 栈内容(顶→底) | top() | size()" << endl;
    cout << "-----|------------|----------------|-------|-------" << endl;

    cout << "  0  | 创建       | []             | -     | "
         << trace.size() << endl;

    trace.push(1);
    cout << "  1  | push(1)    | [1]            | "
         << trace.top() << "     | " << trace.size() << endl;

    trace.push(2);
    cout << "  2  | push(2)    | [2,1]          | "
         << trace.top() << "     | " << trace.size() << endl;

    trace.push(3);
    cout << "  3  | push(3)    | [3,2,1]        | "
         << trace.top() << "     | " << trace.size() << endl;

    trace.pop();
    cout << "  4  | pop()      | [2,1]          | "
         << trace.top() << "     | " << trace.size() << endl;

    trace.pop();
    cout << "  5  | pop()      | [1]            | "
         << trace.top() << "     | " << trace.size() << endl;

    trace.pop();
    cout << "  6  | pop()      | []             | -     | "
         << trace.size() << endl;

    // ==========================================
    // 第二部分：Stack 应用 - 括号匹配
    // ==========================================
    printSection("第二部分：Stack 应用——括号匹配");

    auto isValidBrackets = [](const string& s) {
        stack<char> st;
        for (char ch : s) {
            if (ch == '(' || ch == '[' || ch == '{') {
                st.push(ch);
            } else if (ch == ')' || ch == ']' || ch == '}') {
                if (st.empty()) return false;
                char top = st.top();
                if ((ch == ')' && top != '(') ||
                    (ch == ']' && top != '[') ||
                    (ch == '}' && top != '{')) {
                    return false;
                }
                st.pop();
            }
        }
        return st.empty();
    };

    vector<string> testCases = {
        "()", "()[]{}", "(]", "([)]", "{[]}", "(((())))",
        "(()", ")", "((([])))", "{[()]}", "(([]){})"
    };

    cout << "测试括号匹配算法：" << endl;
    cout << "  输入          | 结果   | 说明" << endl;
    cout << "  --------------|--------|------" << endl;
    for (const auto& tc : testCases) {
        bool result = isValidBrackets(tc);
        const char* label = "";
        if (tc == "()") label = "最基本";
        else if (tc == "()[]{}") label = "多种括号";
        else if (tc == "(]") label = "类型不匹配";
        else if (tc == "([)]") label = "交叉嵌套(错误)";
        else if (tc == "{[]}") label = "正确嵌套";
        else if (tc == "(((())))") label = "深层嵌套";
        else if (tc == "(()") label = "左括号多余";
        else if (tc == ")") label = "右括号多余";
        else if (tc == "((([])))") label = "三种混合深层";
        else if (tc == "{[()]}") label = "经典嵌套";
        else if (tc == "(([]){})") label = "复杂匹配";

        printf("  %-14s | %-6s | %s\n",
               tc.c_str(), result ? "true" : "false", label);
    }

    // ==========================================
    // 第三部分：Stack 应用 - 十进制转二进制
    // ==========================================
    printSection("第三部分：Stack 应用——十进制转二进制");

    auto decToBin = [](int n) {
        if (n == 0) return string("0");
        stack<int> s;
        while (n > 0) {
            s.push(n % 2);
            n /= 2;
        }
        string result;
        while (!s.empty()) {
            result += to_string(s.top());
            s.pop();
        }
        return result;
    };

    cout << "十进制 → 二进制（使用stack反转余数）" << endl;
    cout << "  十进制 | 二进制" << endl;
    cout << "  -------|--------" << endl;
    int testNums[] = {0, 1, 2, 5, 10, 13, 42, 100, 255};
    for (int num : testNums) {
        printf("  %-7d| %s\n", num, decToBin(num).c_str());
    }
    cout << endl;
    cout << "原理：除2取余，余数压栈，最后依次弹出即得正确顺序。" << endl;

    // ==========================================
    // 第四部分：Stack 应用 - 表达式求值演示（简单后缀）
    // ==========================================
    printSection("第四部分：Stack 应用——简单后缀表达式求值");

    auto evalRPN = [](const string& expr) -> int {
        // 仅支持个位数和 + - * 运算，空格分隔
        stack<int> s;
        string token;
        for (size_t i = 0; i <= expr.size(); i++) {
            if (i == expr.size() || expr[i] == ' ') {
                if (!token.empty()) {
                    if (token == "+" || token == "-" || token == "*") {
                        // 弹出两个操作数
                        int b = s.top(); s.pop();
                        int a = s.top(); s.pop();
                        if (token == "+") s.push(a + b);
                        else if (token == "-") s.push(a - b);
                        else s.push(a * b);
                    } else {
                        // 数字
                        s.push(stoi(token));
                    }
                    token.clear();
                }
            } else {
                token += expr[i];
            }
        }
        return s.top();
    };

    cout << "后缀表达式（逆波兰表示法）求值：" << endl;
    cout << "  表达式          | 中缀等价     | 结果" << endl;
    cout << "  ----------------|-------------|-----" << endl;

    struct RPNDemo {
        const char* expr;
        const char* infix;
    };
    RPNDemo demos[] = {
        {"3 4 +", "3 + 4"},
        {"5 2 -", "5 - 2"},
        {"6 3 *", "6 * 3"},
        {"2 3 4 + *", "2 * (3 + 4)"},
        {"9 3 1 - /", "9 / (3 - 1)"}
    };
    for (auto& demo : demos) {
        int result = evalRPN(demo.expr);
        printf("  %-16s | %-11s | %d\n", demo.expr, demo.infix, result);
    }
    cout << endl;
    cout << "后缀表达式求值流程：遇到数字压栈，遇到运算符弹出两个操作数计算后压回。" << endl;

    // ==========================================
    // 第五部分：Queue 基础操作
    // ==========================================
    printSection("第五部分：Queue（队列）基础操作");

    printSub("5.1 push / front / back / pop 基本操作");
    queue<int> q;
    cout << "创建空队列，size = " << q.size() << ", empty = "
         << (q.empty() ? "true" : "false") << endl;

    q.push(10);
    cout << "push(10) -> front = " << q.front()
         << ", back = " << q.back() << ", size = " << q.size() << endl;

    q.push(20);
    cout << "push(20) -> front = " << q.front()
         << ", back = " << q.back() << ", size = " << q.size() << endl;

    q.push(30);
    cout << "push(30) -> front = " << q.front()
         << ", back = " << q.back() << ", size = " << q.size() << endl;

    printSub("5.2 pop() 也不返回值（和stack一样！）");
    cout << "注意：队列的 pop() 也是 void，必须先 front() 取值再 pop()" << endl;
    cout << "当前队首: " << q.front() << ", 队尾: " << q.back() << endl;

    q.pop();
    cout << "pop() 后 -> front = " << q.front()
         << ", back = " << q.back() << ", size = " << q.size() << endl;

    q.pop();
    cout << "再次 pop() 后 -> front = " << q.front()
         << ", back = " << q.back() << ", size = " << q.size() << endl;

    q.pop();
    cout << "三次 pop() 后 -> size = " << q.size()
         << ", empty = " << (q.empty() ? "true" : "false") << endl;

    printSub("5.3 队列的完整生命周期追踪");
    queue<int> qtrace;
    cout << "步骤 | 操作       | 队列内容(前→后) | front() | back() | size()" << endl;
    cout << "-----|------------|------------------|---------|--------|-------" << endl;

    cout << "  0  | 创建       | []               | -       | -      | "
         << qtrace.size() << endl;

    qtrace.push(1);
    cout << "  1  | push(1)    | [1]              | "
         << qtrace.front() << "       | " << qtrace.back() << "      | "
         << qtrace.size() << endl;

    qtrace.push(2);
    cout << "  2  | push(2)    | [1,2]            | "
         << qtrace.front() << "       | " << qtrace.back() << "      | "
         << qtrace.size() << endl;

    qtrace.push(3);
    cout << "  3  | push(3)    | [1,2,3]          | "
         << qtrace.front() << "       | " << qtrace.back() << "      | "
         << qtrace.size() << endl;

    qtrace.pop();
    cout << "  4  | pop()      | [2,3]            | "
         << qtrace.front() << "       | " << qtrace.back() << "      | "
         << qtrace.size() << endl;

    qtrace.pop();
    cout << "  5  | pop()      | [3]              | "
         << qtrace.front() << "       | " << qtrace.back() << "      | "
         << qtrace.size() << endl;

    qtrace.pop();
    cout << "  6  | pop()      | []               | -       | -      | "
         << qtrace.size() << endl;

    // ==========================================
    // 第六部分：Queue 应用 - 约瑟夫问题
    // ==========================================
    printSection("第六部分：Queue 应用——约瑟夫问题");

    auto josephus = [](int n, int m, bool verbose = true) -> vector<int> {
        queue<int> q;
        for (int i = 1; i <= n; i++) q.push(i);

        vector<int> order;
        while (!q.empty()) {
            for (int i = 1; i < m; i++) {
                q.push(q.front());
                q.pop();
            }
            order.push_back(q.front());
            q.pop();
        }
        return order;
    };

    cout << "约瑟夫问题：n=5, m=3（5个人，每数到3出列）" << endl;
    cout << "初始：1 2 3 4 5" << endl;

    queue<int> jq;
    for (int i = 1; i <= 5; i++) jq.push(i);

    cout << "轮数 | 报数过程                     | 出列者 | 剩余队列" << endl;
    cout << "-----|------------------------------|--------|--------" << endl;

    int round = 0;
    while (!jq.empty()) {
        round++;
        string process;
        for (int i = 1; i < 3; i++) {
            int f = jq.front();
            jq.push(f); jq.pop();
            process += to_string(f) + "→尾 ";
        }
        int out = jq.front(); jq.pop();
        process += to_string(out) + "出列";

        // Build remaining queue string
        string remaining;
        queue<int> tmp = jq;
        if (tmp.empty()) {
            remaining = "(空)";
        } else {
            while (!tmp.empty()) {
                remaining += to_string(tmp.front()) + " ";
                tmp.pop();
            }
        }

        printf("  %-3d | %-30s| %-6d | %s\n",
               round, process.c_str(), out, remaining.c_str());
    }

    cout << "\n出列顺序: ";
    vector<int> result = josephus(5, 3, false);
    for (size_t i = 0; i < result.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << result[i];
    }
    cout << endl;

    // ==========================================
    // 第七部分：Queue 应用 - 服务窗口模拟
    // ==========================================
    printSection("第七部分：Queue 应用——服务窗口模拟");

    struct Customer {
        int id;
        int arriveTime;
        int serveTime;
    };

    // 模拟数据
    vector<Customer> customers = {
        {1, 0, 5},    // 客户1: 0时刻到达，需要5分钟
        {2, 2, 3},    // 客户2: 2时刻到达，需要3分钟
        {3, 4, 4},    // 客户3: 4时刻到达，需要4分钟
        {4, 8, 2},    // 客户4: 8时刻到达，需要2分钟
        {5, 10, 6},   // 客户5: 10时刻到达，需要6分钟
    };

    queue<Customer> cq;
    for (auto& c : customers) cq.push(c);

    cout << "单窗口服务模拟（FIFO队列）：" << endl;
    cout << "客户 | 到达时间 | 开始服务 | 服务时长 | 结束时间 | 等待时间" << endl;
    cout << "-----|----------|----------|----------|----------|----------" << endl;

    int currentTime = 0;
    double totalWait = 0;
    int processedCount = 0;

    while (!cq.empty()) {
        Customer c = cq.front(); cq.pop();

        if (currentTime < c.arriveTime) {
            currentTime = c.arriveTime;
        }

        int wait = currentTime - c.arriveTime;
        totalWait += wait;
        int startTime = currentTime;
        currentTime += c.serveTime;
        int endTime = currentTime;
        processedCount++;

        printf("  %-3d | %-8d | %-8d | %-8d | %-8d | %-8d\n",
               c.id, c.arriveTime, startTime, c.serveTime, endTime, wait);
    }

    cout << "-------------------------------------------------------------" << endl;
    printf("  总等待时间: %.0f 分钟\n", totalWait);
    printf("  平均等待时间: %.2f 分钟\n", processedCount > 0 ? totalWait / processedCount : 0);

    // ==========================================
    // 第八部分：Stack vs Queue 行为对比
    // ==========================================
    printSection("第八部分：Stack（LIFO） vs Queue（FIFO）行为对比");

    stack<int> stCompare;
    queue<int> quCompare;

    cout << "对 stack 和 queue 执行相同的 push(1), push(2), push(3)：" << endl;
    stCompare.push(1); stCompare.push(2); stCompare.push(3);
    quCompare.push(1); quCompare.push(2); quCompare.push(3);

    cout << "Stack 弹出顺序（LIFO后进先出）: ";
    while (!stCompare.empty()) {
        cout << stCompare.top() << " ";
        stCompare.pop();
    }
    cout << "  ← 3最后进去，3最先出来" << endl;

    cout << "Queue 弹出顺序（FIFO先进先出）: ";
    while (!quCompare.empty()) {
        cout << quCompare.front() << " ";
        quCompare.pop();
    }
    cout << "  ← 1最先进去，1最先出来" << endl;

    // ==========================================
    // 第九部分：priority_queue 基础演示
    // ==========================================
    printSection("第九部分：priority_queue（优先队列）简介");

    printSub("9.1 大顶堆（默认，最大值在队首）");
    priority_queue<int> maxHeap;
    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(5);
    maxHeap.push(2);
    maxHeap.push(4);

    cout << "push顺序: 3, 1, 5, 2, 4" << endl;
    cout << "pop顺序（大顶堆，最大值优先）: ";
    while (!maxHeap.empty()) {
        cout << maxHeap.top() << " ";
        maxHeap.pop();
    }
    cout << endl;

    printSub("9.2 小顶堆（最小值在队首）");
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(3);
    minHeap.push(1);
    minHeap.push(5);
    minHeap.push(2);
    minHeap.push(4);

    cout << "push顺序: 3, 1, 5, 2, 4" << endl;
    cout << "pop顺序（小顶堆，最小值优先）: ";
    while (!minHeap.empty()) {
        cout << minHeap.top() << " ";
        minHeap.pop();
    }
    cout << endl;

    cout << "\npriority_queue 用法速记：" << endl;
    cout << "  priority_queue<int> pq;                                // 大顶堆" << endl;
    cout << "  priority_queue<int, vector<int>, greater<int>> pq;     // 小顶堆" << endl;
    cout << "  操作：push() 入堆, top() 看堆顶, pop() 出堆" << endl;

    // ==========================================
    // 第十部分：常见错误演示与说明
    // ==========================================
    printSection("第十部分：常见错误警示");

    cout << "【错误1】pop() 不返回值——新手最容易犯的错" << endl;
    cout << "  ❌ int x = s.pop();    // 编译错误！pop()返回void" << endl;
    cout << "  ❌ s.pop();            // 值被丢弃，不知道弹出了什么" << endl;
    cout << "  ✅ int x = s.top(); s.pop();  // 先取值，再弹出" << endl;
    cout << "  ✅ int y = q.front(); q.pop(); // 队列同理" << endl;

    cout << "\n【错误2】对空容器执行操作" << endl;
    cout << "  stack<int> s;" << endl;
    cout << "  s.top();  // ❌ 未定义行为！栈为空" << endl;
    cout << "  s.pop();  // ❌ 未定义行为！栈为空" << endl;
    cout << "  正确做法：if (!s.empty()) { s.top(); s.pop(); }" << endl;

    cout << "\n【错误3】忘记 #include 头文件" << endl;
    cout << "  stack → #include <stack>" << endl;
    cout << "  queue → #include <queue>" << endl;
    cout << "  priority_queue → #include <queue>" << endl;

    cout << "\n【错误4】stack/queue 不支持遍历" << endl;
    cout << "  stack<int> s;" << endl;
    cout << "  s[0];          // ❌ 没有下标访问" << endl;
    cout << "  s.begin();      // ❌ 没有迭代器" << endl;
    cout << "  for(auto x:s);  // ❌ 不能范围for" << endl;
    cout << "  → Stack和Queue只允许访问端点！" << endl;

    cout << "\n【错误5】队列 front() vs back() 搞混" << endl;
    cout << "  q.push(1); q.push(2); q.push(3);" << endl;
    cout << "  q.front();  // = 1 (队首，下次pop会移除的)" << endl;
    cout << "  q.back();   // = 3 (队尾，最后入队的)" << endl;
    cout << "  q.pop();    // 移除队首，1被删除" << endl;
    cout << "  q.front();  // = 2 (新的队首)" << endl;

    // ==========================================
    // 第十一部分：栈与队列的选择指南
    // ==========================================
    printSection("第十一部分：Stack vs Queue 选择指南");

    cout << "  场景                        | 数据结构 | 原因" << endl;
    cout << "  ----------------------------|----------|------------------" << endl;
    cout << "  括号匹配、HTML标签验证       | Stack    | 嵌套=后进先出" << endl;
    cout << "  函数调用/递归模拟            | Stack    | 调用栈" << endl;
    cout << "  进制转换(余数倒序)           | Stack    | 反转顺序" << endl;
    cout << "  编辑器撤销操作(Ctrl+Z)       | Stack    | 最后操作先撤销" << endl;
    cout << "  排队叫号/打印队列            | Queue    | 先来先服务" << endl;
    cout << "  约瑟夫问题/轮流报数          | Queue    | 循环处理" << endl;
    cout << "  BFS广度优先搜索              | Queue    | 逐层扩展" << endl;
    cout << "  任务调度(每次取优先级最高的)  | priority_queue | 堆结构" << endl;

    // ==========================================
    // 第十二部分：BFS预备知识预览
    // ==========================================
    printSection("第十二部分：BFS预备——队列逐层处理预览");

    cout << "广度优先搜索(BFS)的核心就是队列的逐层处理：" << endl;
    cout << endl;
    cout << "  伪代码：" << endl;
    cout << "    queue<int> q;" << endl;
    cout << "    q.push(start);" << endl;
    cout << "    visited[start] = true;" << endl;
    cout << "    while (!q.empty()) {" << endl;
    cout << "        int cur = q.front(); q.pop();" << endl;
    cout << "        处理cur;" << endl;
    cout << "        for (cur的每个邻居) {" << endl;
    cout << "            if (!visited[neighbor]) {" << endl;
    cout << "                visited[neighbor] = true;" << endl;
    cout << "                q.push(neighbor);  // 下一层" << endl;
    cout << "            }" << endl;
    cout << "        }" << endl;
    cout << "    }" << endl;
    cout << endl;
    cout << "直观理解：队列就像一个'待处理列表'，" << endl;
    cout << "同一层的节点几乎同时入队，又按顺序被处理，" << endl;
    cout << "自然实现了'一层一层向外扩展'的效果。" << endl;

    // ==========================================
    // 总结
    // ==========================================
    printSection("演示程序结束");

    cout << "\n本程序覆盖了CSP-J第24课所有核心知识点：" << endl;
    cout << "  [1] Stack基础操作（push/top/pop/empty/size）" << endl;
    cout << "  [2] Stack完整生命周期追踪" << endl;
    cout << "  [3] 括号匹配算法（含11个测试用例）" << endl;
    cout << "  [4] 十进制转二进制（stack反转余数）" << endl;
    cout << "  [5] 后缀表达式求值" << endl;
    cout << "  [6] Queue基础操作（push/front/back/pop/empty/size）" << endl;
    cout << "  [7] Queue完整生命周期追踪" << endl;
    cout << "  [8] 约瑟夫问题（含详细步骤追踪）" << endl;
    cout << "  [9] 服务窗口模拟（含等待时间统计）" << endl;
    cout << "  [10] Stack vs Queue 行为对比" << endl;
    cout << "  [11] priority_queue 优先队列（大顶堆/小顶堆）" << endl;
    cout << "  [12] 五大常见错误警示" << endl;
    cout << "  [13] 数据结构选择指南" << endl;
    cout << "  [14] BFS预备知识预览" << endl;
    cout << endl;

    return 0;
}
