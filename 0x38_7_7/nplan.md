| 学习问题                                                                 | 学习顺序 | 状态  |
| -------------------------------------------------------------------- | ---- | --- |
| 理解树剖 (Tree Decomposition) 和重链剖分 (Heavy-Light Decomposition) 的原理和应用场景 | 1    |     |
| 学习如何使用 LCA 解决树上的路径查询问题                                               | 2    |     |
| 掌握通过 LCA 求解树的直径问题                                                    | 3    |     |
| bdfs 求直径路径                                                           | 4    |     |

atcoder 补题

[F - x = a^b (atcoder.jp)](https://atcoder.jp/contests/abc361/tasks/abc361_f)

[P9118 [春季测试 2023] 幂次 - 洛谷 | 计算机科学教育新生态 (luogu.com.cn)](https://www.luogu.com.cn/problem/P9118)

---

[牛客练习赛127_ACM/NOI/CSP/CCPC/ICPC算法编程高难度练习赛_牛客竞赛OJ (nowcoder.com) ](https://ac.nowcoder.com/acm/contest/188#submit)

atcoder E， F

[牛客练习赛27_ACM/NOI/CSP/CCPC/ICPC算法编程高难度练习赛_牛客竞赛OJ (nowcoder.com) ](https://ac.nowcoder.com/acm/contest/188)            **Rejected** 

---

理解你的需求了，这里是一个表格形式的总结，展示了不同方法求解树的直径的特点：

| 方法   | 描述                | 时间复杂度 | 空间复杂度 | 优点                  | 缺点                 |
| ---- | ----------------- | ----- | ----- | ------------------- | ------------------ |
| BFS  | 使用广度优先搜索寻找树的直径。   | O(n)  | O(n)  | 实现简单，易于理解和实现。       | 需要多次遍历树来确定直径。      |
| DFS  | 使用深度优先搜索寻找树的直径。   | O(n)  | O(n)  | 直观，可以在一次遍历中完成。      | 需要额外的空间记录节点距离。     |
| 动态规划 | 使用动态规划思想优化树的直径计算。 | O(n)  | O(n)  | 只需一次遍历即可完成，节省了计算时间。 | 实现稍复杂，需要理解动态规划的思想。 |

A.cpp

[Tasks - Denso Create Programming Contest 2024（AtCoder Beginner Contest 361）](https://atcoder.jp/contests/abc361/tasks)

[牛客练习赛27_ACM/NOI/CSP/CCPC/ICPC算法编程高难度练习赛_牛客竞赛OJ (nowcoder.com)](https://ac.nowcoder.com/acm/contest/188#rank)

[AtCoder Beginner Contest 361 补题记录（A~F） - yhbqwq - 博客园 (cnblogs.com)](https://www.cnblogs.com/yhbqwq/p/18288032)

[牛客练习赛127_ACM/NOI/CSP/CCPC/ICPC算法编程高难度练习赛_牛客竞赛OJ (nowcoder.com)](https://ac.nowcoder.com/acm/contest/85350#description)
