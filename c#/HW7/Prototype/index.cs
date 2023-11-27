using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PrototypeFigure
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.OutputEncoding = Encoding.UTF8;

            IFigure figure = new Rectangle(10, 20);

            IFigure clonedFigure = figure.Clone();

            figure.GetInfo();

            clonedFigure.GetInfo();

            figure = new Circle(15);

            clonedFigure = figure.Clone();

            figure.GetInfo();

            clonedFigure.GetInfo();

            figure = new Triangle(2, 3, 5);

            clonedFigure = figure.Clone();

            figure.GetInfo();

            Console.Read();
        }
    }
    interface IFigure
    {
        IFigure Clone();
        void GetInfo();
    }
    class Rectangle : IFigure
    {
        int width;

        int height;

        public Rectangle(int w, int h)
        {
            width = w;

            height = h;
        }

        public IFigure Clone()
        {
            return new Rectangle(this.width, this.height);
        }

        public void GetInfo()
        {
            Console.WriteLine("Прямокутник довжиною {0} и шириною{1}", height, width);
        }
    }

    class Circle : IFigure
    {
        int radius;

        public Circle(int r)
        {
            radius = r;
        }

        public IFigure Clone()
        {
            return new Circle(this.radius);
        }

        public void GetInfo()
        {
            Console.WriteLine("Круг радіусом {0}", radius);
        }
    }
    class Triangle : IFigure
    {
        int side_a;

        int side_b;

        int side_c;

        public Triangle(int a, int b, int c)
        {
            this.side_a = a;

            this.side_b = b;

            this.side_c = c;
        }

        public IFigure Clone()
        {
            return new Triangle(this.side_a, this.side_b, this.side_c);
        }

        public void GetInfo()
        {
            Console.WriteLine("Трикутник зі сторонами {0}, {1}, {2}", this.side_a, this.side_b, this.side_c);
        }
    }
}