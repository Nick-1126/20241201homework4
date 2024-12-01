#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;

// 定義二元搜尋樹的節點
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// 替代 std::to_string 的函數，將整數轉換為字串
string intToString(int val) {
    ostringstream oss;
    oss << val;  // 將整數轉換為字符串
    return oss.str();
}

// 插入節點到二元搜尋樹 (BST)
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) return new TreeNode(val);  // 若樹為空，創建新節點

    // 按照BST的規則進行插入
    if (val < root->val)
        root->left = insertBST(root->left, val);  // 小於當前節點，插入左子樹
    else
        root->right = insertBST(root->right, val);  // 大於等於當前節點，插入右子樹

    return root;
}

// 收集二元搜尋樹 (BST) 各層的節點，並儲存於二維向量中
vector<vector<string>> collectLevels(TreeNode* root) {
    vector<vector<string>> levels;  // 用來儲存每層節點的值
    if (!root) return levels;  // 若樹為空，直接返回空結果

    queue<TreeNode*> q;  // 使用隊列來進行層次遍歷
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();  // 當前層的節點數量
        vector<string> level;  // 儲存當層的節點值

        // 遍歷當層的每一個節點
        for (int i = 0; i < levelSize; ++i) {
            TreeNode* node = q.front();
            q.pop();
            if (node) {
                level.push_back(intToString(node->val));  // 若節點不為空，儲存其值
                q.push(node->left);  // 將左子樹節點加入隊列
                q.push(node->right);  // 將右子樹節點加入隊列
            }
            else {
                level.push_back("");  // 若節點為空，則記為空字串
                q.push(nullptr);  // 加入空節點
                q.push(nullptr);  // 加入空節點
            }
        }

        // 檢查該層是否全為空節點，若是，則結束遍歷
        bool allEmpty = all_of(level.begin(), level.end(), [](const string& s) { return s.empty(); });
        if (allEmpty) break;
        levels.push_back(level);  // 儲存該層的節點
    }
    return levels;
}

// 打印樹的結構（以樹狀圖形式顯示）
void printTreeStructure(const vector<vector<string>>& levels) {
    int depth = levels.size();  // 樹的層數
    int maxWidth = pow(2, depth) - 1;  // 計算最大節點數對應的寬度

    // 遍歷每一層並打印
    for (int i = 0; i < depth; ++i) {
        int spaceBetween = pow(2, depth - i) - 1;  // 計算該層節點間的間距
        int leadingSpaces = spaceBetween / 2;      // 計算該層節點前的空白，以便對齊

        // 打印前導空白
        cout << string(leadingSpaces, ' ');
        for (int j = 0; j < levels[i].size(); ++j) {
            cout << levels[i][j];  // 打印當前節點的值
            if (j < levels[i].size() - 1)
                cout << string(spaceBetween, ' ');  // 打印節點之間的空白
        }
        cout << endl;  // 換行，開始打印下一層
    }
}

// 建立 Max-Heap (大頂堆)
void buildMaxHeap(vector<int>& heap) {
    make_heap(heap.begin(), heap.end());  // 使用 STL 函數將數組轉換為堆
}

// 收集 Max-Heap 每層的節點，並儲存於二維向量中
vector<vector<string>> collectHeapLevels(const vector<int>& heap) {
    vector<vector<string>> levels;
    int n = heap.size();  // 堆的大小
    int levelsCount = log2(n) + 1;  // 計算堆的層數
    int idx = 0;

    // 遍歷每層的節點
    for (int i = 0; i < levelsCount; ++i) {
        int nodesInLevel = pow(2, i);  // 該層最多有 2^i 個節點
        vector<string> level;
        for (int j = 0; j < nodesInLevel && idx < n; ++j, ++idx) {
            level.push_back(intToString(heap[idx]));  // 將該層節點的值加入到該層中
        }
        levels.push_back(level);  // 儲存該層
    }
    return levels;
}

int main() {
    vector<int> values;
    cout << "請輸入整數 (以非數字結束輸入): ";
    int num;
    while (cin >> num) {
        values.push_back(num);  // 讀取用戶輸入的整數並儲存到 vector 中
    }

    // Binary Search Tree (BST) 部分
    TreeNode* bstRoot = nullptr;
    for (int val : values) {
        bstRoot = insertBST(bstRoot, val);  // 將每個值插入到 BST 中
    }

    cout << "\nBinary Search Tree (樹狀圖):\n";
    vector<vector<string>> bstLevels = collectLevels(bstRoot);  // 收集 BST 的每層節點
    printTreeStructure(bstLevels);  // 打印 BST 的樹狀圖

    // Max-Heap 部分
    vector<int> heap = values;  // 將數值傳入堆中
    buildMaxHeap(heap);  // 建立 Max-Heap

    cout << "\nMax-Heap (樹狀圖):\n";
    vector<vector<string>> heapLevels = collectHeapLevels(heap);  // 收集 Max-Heap 的每層節點
    printTreeStructure(heapLevels);  // 打印 Max-Heap 的樹狀圖

    return 0;
}
