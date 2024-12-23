using System;

class HelloWorld
{
    static string ConvertIntToBinary(int n)
    {
        string binary = string.Empty;
        while (n != 0)
        {
            binary += (n % 2).ToString();
            n /= 2;
        }
        return binary;
    }

    static void Pro2()
    {
        string str = "The C# preprocessor is a macro processor that the C# compiler automatically uses to transform your\r\nprogram before actual compilation. The C# preprocessor allows you to define macros, which are brief\r\nabbreviations for longer constructs.";
        string[] words = str.Split(' ');
        int cnt = 0;
        for(int i = 0; i < words.Length; i++)
        {
            Console.WriteLine(words[i]);
            if (words[i] == "C#")
            {
                cnt++;
            }
        }
        Console.WriteLine("出现了 " +  cnt.ToString() + " 次 C#");
    }
    static void Main(string[] args)
    {
        Pro2();
    }
}
