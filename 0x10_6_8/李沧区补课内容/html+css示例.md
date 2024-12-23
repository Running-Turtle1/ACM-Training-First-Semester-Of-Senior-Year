# HTML

HTML（超文本标记语言）和CSS（层叠样式表）是构建和设计网页的两种主要技术。HTML用于创建网页的结构和内容，而CSS用于控制其外观和布局。

## HTML基础

HTML使用标签来标记网页中的不同部分。每个标签通常有一个开始标签和一个结束标签，内容放在这两个标签之间。例如：

```html
<!DOCTYPE html>
<html>
<head>
    <title>我的第一个网页</title>
</head>
<body>
    <h1>欢迎来到我的网站</h1>
    <p>这是一个段落。</p>
    <a href="https://example.com">这是一个链接</a>
</body>
</html>
```

- `<!DOCTYPE html>`: 声明文档类型，告诉浏览器这是一个HTML5文档。
- `<html>`: HTML文档的根元素。
- `<head>`: 包含网页的元数据，比如标题和引用的样式表。
- `<title>`: 网页的标题，会显示在浏览器标签上。
- `<body>`: 包含网页的主要内容。
- `<h1>`: 标题标签，`<h1>`到`<h6>`表示不同级别的标题。
- `<p>`: 段落标签。
- `<a>`: 链接标签，`href`属性指定链接目标。

## CSS基础

CSS用于为HTML元素添加样式。CSS可以直接嵌入到HTML中，也可以作为独立的文件引用。以下是CSS的几种用法：

**内联样式（Inline CSS）**：直接在HTML标签内使用`style`属性。

```html
<p style="color: red;">这是一个红色的段落。</p>
```

**内部样式表（Internal CSS）**：在HTML文档的`<head>`部分使用`<style>`标签。

```html
<head>
    <style>
        body {
            background-color: lightblue;
        }
        p {
            color: red;
        }
    </style>
</head>
```

**外部样式表（External CSS）**：在独立的CSS文件中定义样式，并在HTML中引用。

```html
<head>
    <link rel="stylesheet" href="styles.css">
</head>
```

在`styles.css`文件中：

```css
body {
    background-color: lightblue;
}
p {
    color: red;
}
```

## CSS选择器和属性

**标签选择器**：选择特定的HTML标签。

```css
p {
    color: red;
}
```

**类选择器**：选择特定类的元素，使用`.`表示。

```css
.my-class {
    color: blue;
}
```

在HTML中：

```html
<p class="my-class">这是一个蓝色的段落。</p>
```



**ID选择器**：选择特定ID的元素，使用`#`表示。

```css
#my-id {
    font-size: 20px;
}
```

在HTML中：

```html
<p id="my-id">这是一个大号字体的段落。</p>
```

## 实际示例

以下是一个完整的示例，包括HTML和CSS：

HTML（index.html）

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>我的网页</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
    <h1>欢迎</h1>
    <p class="intro">这是一个介绍段落。</p>
    <p>这是另一个段落。</p>
    <a href="https://example.com" id="example-link">点击这里</a>
</body>
</html>
```

CSS（styles.css）

```css
body {
    font-family: Arial, sans-serif;
    background-color: #f0f0f0;
}

h1 {
    color: #333;
}

.intro {
    color: #555;
    font-size: 18px;
}

p {
    color: #666;
}

#example-link {
    color: #0088cc;
    text-decoration: none;
}

#example-link:hover {
    text-decoration: underline;
}
```
















