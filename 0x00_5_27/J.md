设 V = 0110101

枚举LCP，如果 v' > v, 

v 某一位为 0, v' 这一位为 1 直接合法 , v' 这一位为 1，continue ;

v 某一位为 1，v' 这一位为 0，break, 不合法 ；v' 这一位为 1，continue

---

我们枚举 v' 与 v 的前缀长度 i，看 i+1 位，v' 这一位为 1,直接合法，v'这一位为 0，直接不合法。

枚举过程中，

0 1 0 1 0 0 1

0 1 1 0 0 0 0 

每次加上 lowbit ?

---

## sublime + devc++ 的 snippet 如何使用 ?

- sublime

点击工具，点击新建代码片段

```textile
<snippet>
    <content><![CDATA[
Hello, ${1:this} is a ${2:snippet}.
]]></content>
    <!-- Optional: Set a tabTrigger to define how to trigger the snippet -->
    <!-- <tabTrigger>hello</tabTrigger> -->
    <!-- Optional: Set a scope to limit where the snippet will trigger -->
    <!-- <scope>source.python</scope> -->
</snippet>
```

`<content></content>` 里面放需要生成的北荣

`<tabtTigger></tabTrigger>`  里面放快捷键

然后按 快捷键 + tab 就能生成代码

- dev c++

点击工具 + 点击编辑器选项 + 点击代码 + 点击缺省源 + 输入模板 +勾选默认插入
