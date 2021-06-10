using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace mnk
{
    public class Matrix
    {
        public double[,] Args { get; set; }
        public int Row { get; set; }
        public int Col { get; set; }

        public Matrix(double[] x)
        {
            Row = x.Length;
            Col = 1;
            Args = new double[Row, Col];
            for (int i = 0; i < Args.GetLength(0); i++)
                for (int j = 0; j < Args.GetLength(1); j++)
                    Args[i, j] = x[i];
        }

        public Matrix(double[,] x)
        {
            Row = x.GetLength(0);
            Col = x.GetLength(1);
            Args = new double[Row, Col];
            for (int i = 0; i < Args.GetLength(0); i++)
                for (int j = 0; j < Args.GetLength(1); j++)
                    Args[i, j] = x[i, j];
        }

        public Matrix(Matrix other)
        {
            this.Row = other.Row;
            this.Col = other.Col;
            Args = new double[Row, Col];
            for (int i = 0; i < Row; i++)
                for (int j = 0; j < Col; j++)
                    this.Args[i, j] = other.Args[i, j];
        }

        public override string ToString()
        {
            string s = string.Empty;
            for (int i = 0; i < Args.GetLength(0); i++)
            {
                for (int j = 0; j < Args.GetLength(1); j++)
                {
                    s += string.Format("{0} ", Args[i, j]);
                }
                s += "\n";
            }
            return s;
        }

        public Matrix Transposition()
        {
            double[,] t = new double[Col, Row];
            for (int i = 0; i < Row; i++)
                for (int j = 0; j < Col; j++)
                    t[j, i] = Args[i, j];
            return new Matrix(t);
        }

        public static Matrix operator *(Matrix m, double k)
        {
            Matrix ans = new Matrix(m);
            for (int i = 0; i < ans.Row; i++)
                for (int j = 0; j < ans.Col; j++)
                    ans.Args[i, j] = m.Args[i, j] * k;
            return ans;
        }

        public static Matrix operator *(Matrix m1, Matrix m2)
        {
            if (m1.Col != m2.Row) throw new ArgumentException("Multiplication of these two matrices can't be done!");
            double[,] ans = new double[m1.Row, m2.Col];
            for (int i = 0; i < m1.Row; i++)
            {
                for (int j = 0; j < m2.Col; j++)
                {
                    for (int k = 0; k < m2.Row; k++)
                    {
                        ans[i, j] += m1.Args[i, k] * m2.Args[k, j];
                    }
                }
            }
            return new Matrix(ans);
        }

        private Matrix getMinor(int row, int column)
        {
            if (Row != Col) throw new ArgumentException("Matrix should be square!");
            double[,] minor = new double[Row - 1, Col - 1];
            for (int i = 0; i < this.Row; i++)
            {
                for (int j = 0; j < this.Col; j++)
                {
                    if ((i != row) || (j != column))
                    {
                        if (i > row && j < column) minor[i - 1, j] = this.Args[i, j];
                        if (i < row && j > column) minor[i, j - 1] = this.Args[i, j];
                        if (i > row && j > column) minor[i - 1, j - 1] = this.Args[i, j];
                        if (i < row && j < column) minor[i, j] = this.Args[i, j];
                    }
                }
            }
            return new Matrix(minor);
        }

        public static double Determ(Matrix m)
        {
            if (m.Row != m.Col) throw new ArgumentException("Matrix should be square!");
            double det = 0;
            int length = m.Row;

            if (length == 1) det = m.Args[0, 0];
            if (length == 2) det = m.Args[0, 0] * m.Args[1, 1] - m.Args[0, 1] * m.Args[1, 0];

            if (length > 2)
                for (int i = 0; i < m.Col; i++)
                    det += Math.Pow(-1, 0 + i) * m.Args[0, i] * Determ(m.getMinor(0, i));

            return det;
        }

        public Matrix MinorMatrix()
        {
            double[,] ans = new double[Row, Col];

            for (int i = 0; i < Row; i++)
                for (int j = 0; j < Col; j++)
                    ans[i, j] = Math.Pow(-1, i + j) * Determ(this.getMinor(i, j));

            return new Matrix(ans);
        }

        public Matrix InverseMatrix()
        {
            if (Math.Abs(Determ(this)) <= 0.000000001) throw new ArgumentException("Inverse matrix does not exist!");

            double k = 1 / Determ(this);

            Matrix minorMatrix = this.MinorMatrix();

            return minorMatrix * k;
        }
    }
    class Program
    {
        static void Main(string[] args)
        {
            double z = 0;
            int r = 1;//количество входных переменных a
            int n = 5;//количество входных переменных Х
            int l = 5;//количество входных переменных b
            int N = 100;//количество циклов
            double noise = 0;
            bool s;
            double[,] E_kof = new double[6, 6];
            double[,] rez_matx = new double[6, 6];
            double[,] inver_matx = new double[6, 6];
            double[,] rez3_matx = new double[6, 6];
            double[] A_vect = new double[6];//результирующий вектор
            double[] A = new double[1];
            double[] B = new double[5];
            double[] Z = new double[100];
            double[] X = new double[5];
            double[,] X_matx = new double[100, 6];
            double[,] XT_matx = new double[6, 100];
            double[] rez_vect = new double[6];

            A[0] = 0.75;
            B[0] = 0.3;
            B[1] = -0.65;
            B[2] = 0.8;
            B[3] = -0.75;
            B[4] = 0.35;
            Random rnd = new Random();
            for (int i = 0; i < 100; i++)
                Z[i] = 0;
            X[0] = rnd.Next(-1, 1) + rnd.NextDouble();
            X[1] = rnd.Next(-1, 1) + rnd.NextDouble();
            X[2] = rnd.Next(-1, 1) + rnd.NextDouble();
            X[3] = rnd.Next(-1, 1) + rnd.NextDouble();
            X[4] = rnd.Next(-1, 1) + rnd.NextDouble();
            for (int k = 0; k < 100; k++)
            {
                //генерирование шума
                for (int i = 0; i < 11; i++)
                {
                    noise = rnd.Next(-1, 1) + rnd.NextDouble();
                    noise += noise;
                }

                if (k % 3 == 0)
                    X[0] = rnd.Next(-1, 1) + rnd.NextDouble();
                if (k % 5 == 0)
                    X[1] = rnd.Next(-1, 1) + rnd.NextDouble();
                if (k % 7 == 0)
                    X[2] = rnd.Next(-1, 1) + rnd.NextDouble();
                if (k % 11 == 0)
                    X[3] = rnd.Next(-1, 1) + rnd.NextDouble();
                if (k % 13 == 0)
                    X[4] = rnd.Next(-1, 1) + rnd.NextDouble();

                //вычисление вектора Z
                if (k != 0)
                {
                    Z[k] = A[0] * Z[k - 1] + noise;
                    for (int i = 0; i < n; i++)
                        Z[k] += B[i] * X[i];
                }


                //заполнение матрицы X
                for (int i = 0; i < 6; i++)
                {
                    if (i == 0)
                        X_matx[k, i] = Z[k];
                    if (i > 0)
                        X_matx[k, i] = X[i - 1];
                }
            }

            //транспонирование матрицы X
            Matrix X_matxM = new Matrix(X_matx);
            Matrix XT_matxM = X_matxM.Transposition();
            //Умножение матриц
            Matrix rez_matxM = XT_matxM * X_matxM;
            //Обратная матрица
            Matrix obr_rezmatxM = rez_matxM.InverseMatrix();
            Matrix prov = obr_rezmatxM * rez_matxM;
            //получение результирующего вектора
            Matrix ZM = new Matrix(Z);
            Matrix rez_vectM = XT_matxM * ZM;
            //выходные данные
            Matrix A_vectM = rez_matxM * rez_vectM;

        }
    }
}