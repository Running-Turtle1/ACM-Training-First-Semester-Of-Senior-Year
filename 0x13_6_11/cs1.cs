class Program

{

        static void Main(string[] args)

        {

            B b = new B();

            A a = b;

            a.F1();

            b.F1();

            a.F2();

            b.F2();

            Console.Read();

        }

}

public class A

{

        public virtual void F1()

        {

            Console.WriteLine("A.F1");

        }

        public void F2()

        {

            Console.WriteLine("A.F2");

        }

}

public class B : A

{

        public override void F1()

        {

            Console.WriteLine("B.F1");

        }

        public void F2()

        {

            Console.WriteLine("B.F2");

        }

}