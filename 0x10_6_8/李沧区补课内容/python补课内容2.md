# print 语句

```py
# 打印 1
print(1)
# 打印字符串
print('Test')
# 拼接字符串
print('age: ' + '12')
```

# map 函数

`map` 是 Python 中的一个内置函数，用于将一个函数应用到一个可迭代对象（如列表、元组等）的每一个元素，并返回一个迭代器（从 Python 3 开始返回 `map` 对象）。`map` 函数通常与 `lambda` 表达式或者自定义函数一起使用。

以下是 `map` 函数的一些基本用法：

## 语法

```py
map(function, iterable, ...)
```

- `function` : 要应用到每个元素的函数

- `iterable` : 一个或多个可迭代对象

## 示例

> 将每个元素转换为整数
> 
> 假设有一个包含字符串数字的列表，想将其转换为整数列表。

```py
str_numbers = ['1', '2', '3', '45']
int_numbers = list(map(int, str_numbers))
print(int_numbers) # 打印 [1, 2, 3, 45]
```

> **使用 lambda 函数进行操作**：
> 假设有一个列表，想要将每个元素平方。

```py
str_numbers = ['1', '2', '3', '45']
int_numbers = list(map(int, str_numbers)) # 转换为整数
squared_numbers = list(map(lambda x : x ** 2, int_numbers)) # 应用 lambda 将 x 平方
print(int_numbers)
print(squared_numbers)
```

```textile
[1, 2, 3, 45]
[1, 4, 9, 2025]
```

> 应用自定义函数

定义一个函数来计算元素的两倍，然后使用 `map` 来应用这个函数。

```py
str_numbers = ['1', '2', '3', '45']
int_numbers = list(map(int, str_numbers)) # 转换为整数
squared_numbers = list(map(lambda x : x ** 2, int_numbers)) # 应用 lambda 将 x 平方
print(int_numbers)
print(squared_numbers)

# 应用自定义函数
def double(x) :
    return x * 2
doubled_numbers = list(map(double, int_numbers))
print(doubled_numbers)
```

```tex
[1, 2, 3, 45]
[1, 4, 9, 2025]
[2, 4, 6, 90]
```

> 多个可迭代对象

如果有多个可迭代对象，`map` 会并行地应用函数到这些可迭代对象的对应元素上。

```py
# 多个可迭代对象
numbers1 = [1, 2, 3, 4, -11]
numbers2 = [10, 20, 30, 40, 66, 77]
summed_numbers = list(map(lambda x, y: x + y, numbers1, numbers2))
print(summed_numbers)  # 输出: [11, 22, 33, 44]
```

# list

`list` 是 Python 中非常重要和常用的数据结构。它是一个可变的、有序的序列，允许在其中存储任意类型的对象。列表提供了多种方法来操作存储在其中的数据。

### 创建列表

1. **使用方括号**：
   
   ```python
   empty_list = []
   numbers = [1, 2, 3, 4]
   fruits = ['apple', 'banana', 'cherry']
   mixed = [1, 'apple', 3.14, True]
   ```

2. **使用 `list()` 构造函数**：
   
   ```python
   empty_list = list()
   numbers = list(range(1, 5))  # [1, 2, 3, 4]
   characters = list('hello')  # ['h', 'e', 'l', 'l', 'o']
   ```

### 访问列表元素

1. **索引访问**：
   
   ```python
   numbers = [1, 2, 3, 4]
   print(numbers[0])  # 输出: 1
   print(numbers[-1])  # 输出: 4 (负索引从末尾开始)
   ```

2. **切片**：
   
   Python 切片（slicing）是处理序列（如列表、字符串和元组）的一种强大方法。通过切片语法，可以轻松地访问、修改和复制序列中的子集。切片语法如下：

```python
切片参数说明
start：切片开始的位置（包含）。
stop：切片结束的位置（不包含）。
step：切片的步长（默认为1）。
```

```python
numbers = [1, 2, 3, 4, 5]
print(numbers[1:3])  # 输出: [2, 3] (不包括索引3)
print(numbers[:3])  # 输出: [1, 2, 3]
print(numbers[2:])  # 输出: [3, 4, 5]
print(numbers[:])  # 输出: [1, 2, 3, 4, 5]
print(numbers[::2])  # 输出: [1, 3, 5] (步长为2)
```

1. **添加元素**：
   
   ```python
   numbers = [1, 2, 3]
   numbers.append(4)  # 在末尾添加
   print(numbers)  # 输出: [1, 2, 3, 4]
   
   numbers.insert(1, 1.5)  # 在索引1位置插入
   print(numbers)  # 输出: [1, 1.5, 2, 3, 4]
   
   more_numbers = [5, 6]
   numbers.extend(more_numbers)  # 扩展列表
   print(numbers)  # 输出: [1, 1.5, 2, 3, 4, 5, 6]
   ```

2. **修改元素**：
   
   ```python
   numbers = [1, 2, 3, 4]
   numbers[1] = 10
   print(numbers)  # 输出: [1, 10, 3, 4]
   ```

3. **删除元素**：
   
   ```python
   numbers = [1, 2, 3, 4]
   del numbers[1]
   print(numbers)  # 输出: [1, 3, 4]
   
   numbers.remove(3)
   print(numbers)  # 输出: [1, 4]
   
   last_element = numbers.pop()  # 删除并返回最后一个元素
   print(last_element)  # 输出: 4
   print(numbers)  # 输出: [1]
   
   numbers.clear()  # 清空列表
   print(numbers)  # 输出: []
   ```

### 列表方法

1. **查找元素**：
   
   ```py
   numbers = [1, 2, 3, 4, 2]
   print(numbers.index(2))  # 输出: 1 (第一个出现的位置)
   print(numbers.count(2))  # 输出: 2 (元素2出现的次数)
   ```

2. **排序**：
   
   ```py
   numbers = [4, 2, 3, 1]
   numbers.sort()  # 就地排序
   print(numbers)  # 输出: [1, 2, 3, 4]
   
   numbers.sort(reverse=True)
   print(numbers)  # 输出: [4, 3, 2, 1]
   
   numbers = [4, 2, 3, 1]
   sorted_numbers = sorted(numbers)  # 返回排序后的新列表
   print(sorted_numbers)  # 输出: [1, 2, 3, 4]
   print(numbers)  # 输出: [4, 2, 3, 1] (原列表不变)
   ```

3. **反转**：
   
   ```py
   numbers = [1, 2, 3, 4]
   numbers.reverse()  # 就地反转
   print(numbers)  # 输出: [4, 3, 2, 1]
   
   numbers = [1, 2, 3, 4]
   reversed_numbers = list(reversed(numbers))  # 返回反转后的新列表
   print(reversed_numbers)  # 输出: [4, 3, 2, 1]
   print(numbers)  # 输出: [1, 2, 3, 4] (原列表不变)
   ```

### 列表推导式

列表推导式是生成列表的简洁方法：

```py
squares = [x ** 2 for x in range(10)]
print(squares)  # 输出: [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]

even_squares = [x ** 2 for x in range(10) if x % 2 == 0]
print(even_squares)  # 输出: [0, 4, 16, 36, 64]
```
