# KSP
## 程式架構
```
此程式分為 main function 以及 SP_graph 之 class 兩個部分
main funtion 主要負責輸入的部分
SP_graph 之 class 則負責建構 adjacency lists 以及 shortest path 的運算及輸出
```
## 程式邏輯
```
class 中有 int v_num 負責儲存 vertices 的數量, 存放 adjacency lists 的結構
以及 dis,pre,visited 等三個 vector
dis 負責儲存路徑的長度
pre 負責儲存 parent node
vidited 負責儲存是否已經是最點路徑的 bool

memberfunction 則有四個, 分別是:
void add_edge 負責增加 graph 的 edge
void output 負責輸出的部分
void relax 負責比較路經長短
void dijkstra 負責sp演算法
int cut 負責切斷路經
void recover 負責復原路經

程式運算邏輯為
1.
先將輸入的 vertices 及 edge 的數量存入
再依 edge 的數量做迭代讓使用者做 edge 的輸入
完成整個 graph 的結構(使用 adjcency lists 實現)

2.
主要利用 Dijkstra's Algorithm 的邏輯尋找最短路徑
並利用 yen's Algorithm 的邏輯尋找前 k 短的路徑
其演算法為分別斷開最短路徑的每條 edge 找尋可能的第二短路徑
再比較其中最短者為第二短
再來為第三短...
此程式碼只能實現第一層找查
若 k-1 > 最短路徑邊數則會出現錯誤

3.
將找到的前 k 短路徑存到 vector 中
接著一次輸出即所求ksp
```
## 程式執行流程
```
在terminal輸入 g++ ksp.cpp -o ksp
即可編譯並得到名為 ksp.exe 的執行檔
在terminal輸入 ./ksp.exe 即可執行檔案
(程式輸入必須皆為合法且輸入邊時數字中間必須有空格)
```
