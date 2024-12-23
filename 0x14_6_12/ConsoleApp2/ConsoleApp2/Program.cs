using System;

public class Person
{
    protected string name;
    protected int age;
    protected string[] courses;

    /// <summary>
    /// 姓名
    /// </summary>
    public string Name
    {
        get { return name; } // 访问
        set { name = value; } // 设置
    }

    /// <summary>
    /// 年龄
    /// </summary>
    public int Age
    {
        get { return age; }
        set { age = value; }
    }

    /// <summary>
    /// 初始化姓名和年龄
    /// </summary>
    /// <param name="name"></param>
    /// <param name="age"></param>
    public Person(string name, int age)
    {
        this.name = name;
        this.age = age;
    }

    /// <summary>
    /// 初始化姓名、年龄和课程列表
    /// </summary>
    /// <param name="name"></param>
    /// <param name="age"></param>
    /// <param name="courses"></param>
    public Person(string name, int age, string[] courses)
    {
        this.name = name;
        this.age = age;

        if (courses == null || courses.Length <= 0)
        {
            throw new Exception("参数错误");
        }
        this.courses = new string[courses.Length];
        Array.Copy(courses, this.courses, courses.Length);
    }

    /// <summary>
    /// 显示姓名、年龄和课程列表
    /// </summary>
    public virtual void ShowInfo()
    {
        Console.WriteLine($"姓名：{name}");
        Console.WriteLine($"年龄：{age}");
        Console.WriteLine("课程如下：");

        if (courses == null) return;
        for (int i = 0; i < courses.Length; i++)
        {
            if (i < courses.Length - 1)
            {
                Console.Write($"{courses[i]},");
            }
            else
            {
                Console.WriteLine(courses[i]);
            }
        }
        Console.WriteLine();
    }
}

/// <summary>
/// Teacher类，包含姓名、年龄、职务和课程列表等信息，并显示这些信息
/// </summary>
public class Teacher : Person
{
    private string duty;

    /// <summary>
    /// 职务
    /// </summary>
    public string Duty
    {
        get { return duty; }
        set { duty = value; }
    }

    /// <summary>
    /// 初始化姓名、年龄和职务
    /// </summary>
    /// <param name="name"></param>
    /// <param name="age"></param>
    /// <param name="duty"></param>
    public Teacher(string name, int age, string duty)
        : base(name, age)
    {
        this.duty = duty;
    }

    /// <summary>
    /// 初始化姓名、年龄、职务和课程列表
    /// </summary>
    /// <param name="name"></param>
    /// <param name="age"></param>
    /// <param name="courses"></param>
    /// <param name="duty"></param>
    public Teacher(string name, int age, string[] courses, string duty)
        : base(name, age, courses)
    {
        this.duty = duty;
    }

    /// <summary>
    /// 显示姓名、年龄、职务和课程列表
    /// </summary>
    public override void ShowInfo()
    {
        Console.WriteLine($"姓名：{name}");
        Console.WriteLine($"年龄：{age}");
        Console.WriteLine($"职务：{duty}");
        Console.WriteLine("课程如下：");

        if (courses == null) return;
        for (int i = 0; i < courses.Length; i++)
        {
            if (i < courses.Length - 1)
            {
                Console.Write($"{courses[i]},");
            }
            else
            {
                Console.WriteLine(courses[i]);
            }
        }
        Console.WriteLine();
    }
}

/// <summary>
/// Student类，包含姓名、年龄、班级和课程列表等信息，并显示这些信息
/// </summary>
public class Student : Person
{
    private string className;

    /// <summary>
    /// 班级
    /// </summary>
    public string ClassName
    {
        get { return className; }
        set { className = value; }
    }

    /// <summary>
    /// 初始化姓名、年龄和班级
    /// </summary>
    /// <param name="name"></param>
    /// <param name="age"></param>
    /// <param name="className"></param>
    public Student(string name, int age, string className)
        : base(name, age)
    {
        this.className = className;
    }

    /// <summary>
    /// 初始化姓名、年龄、班级和课程列表
    /// </summary>
    /// <param name="name"></param>
    /// <param name="age"></param>
    /// <param name="courses"></param>
    /// <param name="className"></param>
    public Student(string name, int age, string[] courses, string className)
        : base(name, age, courses)
    {
        this.className = className;
    }

    /// <summary>
    /// 显示姓名、年龄、班级和课程列表
    /// </summary>
    public override void ShowInfo()
    {
        Console.WriteLine($"姓名：{name}");
        Console.WriteLine($"年龄：{age}");
        Console.WriteLine($"班级：{className}");
        Console.WriteLine("课程如下：");

        if (courses == null) return;
        for (int i = 0; i < courses.Length; i++)
        {
            if (i < courses.Length - 1)
            {
                Console.Write($"{courses[i]},");
            }
            else
            {
                Console.WriteLine(courses[i]);
            }
        }
        Console.WriteLine();
    }
}

class Program
{
    static void Main(string[] args)
    {
        string[] tcourses = new string[] { "C#语言", "数据结构" };
        Teacher teacher = new Teacher("张老师", 35, tcourses, "系主任");

        string[] s1courses = new string[] { "C#语言", "数据结构", "离散数学" };
        Student s1 = new Student("学生1", 20, s1courses, "200701班");

        string[] s2courses = new string[] { "C#语言", "数据结构", "汇编语言" };
        Student s2 = new Student("学生2", 21, s2courses, "200702班");

        teacher.ShowInfo(); // 显示教师的信息
        s1.ShowInfo();      // 显示学生1的信息
        s2.ShowInfo();      // 显示学生2的信息

        Console.ReadLine();
    }
}