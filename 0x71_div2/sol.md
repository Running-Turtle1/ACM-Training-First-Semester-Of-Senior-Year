## D1

发现一个数组能提供的最大值的是固定的，对于 $i\leq mx$ 的，按照 $mx$ 处理 ；对于 $i>mx$ 的，按照 $i$ 处理。

## D2

设 $D1$ 的每个数组的求 $mex$ 为 $u，v$ ，如果对于 $u\rightarrow v$ 连一条边，设 $f_i$ 表示 $i$ 在图中能到达的最大值，那么只用处理 $\max _i v_i$ 这些点即可。

倒序 DP ，DAG，记忆化搜索求出所有 $f_i$ 。

发现操作有以下两种 :

- 从 $u$ 到所有出边 $v$ 

- 来到任意一个 $u$ ，并断掉一条 $u$ 的出边

所以每个 $i$ 的答案至少是 $f_i$ ，同时至少是 $\max v_i$ ，同时对于每个出度 $\geq 2$ 的点 $x$ ，设 $mx=\max f_x$ ，每个点还至少是 $mx$ 。

如此一来处理完所有点即可。

对于 $\leq \max v$ 的询问，枚举回答 。

对于 $> \max v$ 的，取自身，等差数列 $O(1)$ 处理查询即可。


