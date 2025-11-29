#pragma once
#include <vector>
#include <fstream>
#include <string>
namespace lama {
    long long gcd(long long a, long long b);
    class fraction {
    public:
        //Числитель
        long long num;
        //Знаменатель
        long long dem;
        bool sign;
        fraction(long long a, long long b);
        fraction(long long a);
        void print(bool f = 0, std::ostream& out = std::cout) const;
        fraction operator + (fraction p1) const;
        fraction operator - (fraction p1) const;
        fraction operator * (fraction p1) const;
        fraction operator /(fraction p1) const;
    };

    class matrix {
    public:
        std::vector< std::vector<fraction>> A;
        //Количество строк
        int n;
        //Количество столбцов
        int m;

        matrix operator = (matrix p1);
        matrix operator + (matrix p1);
        matrix operator * (matrix p1);
        //Матрица rows_count на cols_count заполненная filler
        matrix(int rows_count, int cols_count, fraction filler);
        //Единичная матрица size на size
        matrix(int size);
        //Матрица rows_count на cols_count заполненная filler
        matrix(int rows_count, int cols_count, long long filler);
        //Матрица из двумерного вектора a
        matrix(std::vector<std::vector<fraction>> a);
        void swap_rows(int i, int j);
        void swap_cols(int i, int j);
        //Возвращает транспорованную матрицу
        matrix transpose();

        //mode = 0 - просто вывод, mode = 1 - вывод матрицы для латеха с круглыми скобками, mode = 2 - вывод матрицы для латеха со скобками определителя
        //f_mode = 0 - дроби в виде x/y, f_mode = 1 - \frac{x}{y}
        void print(int mode = 0, int f_mode = 0, std::ostream& out = std::cout) const;
        //verbose = 0 - не выводить ход решения, verbose = 1 - отображать каждый шаг хода решения.
        fraction det(int verbose = 0, std::ostream& out = std::cout) const;
        //verbose = 0 - не выводить ход решения, verbose = 1 - отображать каждый шаг хода решения, verbose = 2 - отображать только основные шаги хода решения
        matrix inverse(int verbose = 0, std::ostream& out = std::cout) const;
        //Возвращает минор исходной матрицы состоящий из строк и столбцов с номерами в rows и cols
        matrix minor(std::vector<int> rows, std::vector<int> cols) const;
        //Возвращает минор исходной матрицы состоящий из строк и столбцов , в чьих индексах стоит True в rows и cols
        matrix minor(std::vector<bool> rows, std::vector<bool> cols) const;
        //verbose = 0 - не выводить ход решения, verbose = 1 - выводить каждый шаг хода решения, 2 - отображать только основные шаги.
        int rank(int verbose = 0, std::ostream& out = std::cout) const;
    };

    fraction operator + (fraction c1, long long c2);
    fraction operator + (long long c1, fraction c2);
    //verbose = 0 - не выводить ход решения, verbose = 1 - отображать каждый шаг хода решения, verbose = 2 - отображать только основные шаги хода решения
    matrix solve_solae(matrix K, matrix Y, int verbose = 0, std::ostream& out = std::cout);
};
