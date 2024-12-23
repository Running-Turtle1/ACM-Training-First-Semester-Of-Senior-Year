## Trick : pair 的二分问题

对于 `pair<int, int>` 的二分，由于 pair 是一个双元素，就容易出现一些锅。

通常来说，第二个元素一般来说没有什么用，可能是元素的编号，下面就以编号为例讲一下 pair 的二分

## 第一个 > x 的 pair

这个很容易出错，第二维设为 $+\infty$ ，保证 $pr.first=x$ 的不会被找到。

```cpp
upper_bound(vc.begin(), vc.end(), make_pair(x, LLONG_MAX));
```

## 第一个 >= x 的 pair

第二维传 $-\infty$ 

```cpp
lower_bound(vc.begin(), vc.end(), make_pair(x, LLONG_MIN));
```

## 第一个 < x 的 pair

第一个 $\geq x$ 的左边。

## 第一个 <= x 的 pair

第一个 $>x$ 的左边。
