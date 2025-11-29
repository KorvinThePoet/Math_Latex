// Matrix.cpp : Ётот файл содержит функцию "main". «десь начинаетс€ и заканчиваетс€ выполнение программы.
//
#pragma once
#include <vector>
#include <fstream>
#include <string>
namespace lama {
    long long gcd(long long a, long long b);
    void start_write_in_file(std::string outfile_path);
    void stop_write_in_file();
    class fraction {
    public:
        //„ислитель
        long long num;
        //«наменатель
        long long dem;
        bool sign;
        fraction(long long a, long long b);
        fraction(long long a);
        void print(bool f = 0) const;
        fraction operator + (fraction p1) const;
        fraction operator - (fraction p1) const;
        fraction operator * (fraction p1) const;
        fraction operator /(fraction p1) const;
    };

    class matrix {
    public:
        std::vector< std::vector<fraction>> A;
        // оличество строк
        int n;
        // оличество столбцов
        int m;

        matrix operator = (matrix p1);
        matrix operator + (matrix p1);
        matrix operator * (matrix p1);
        //ћатрица rows_count на cols_count заполненна€ filler
        matrix(int rows_count, int cols_count, fraction filler);
        //≈динична€ матрица size на size
        matrix(int size);
        //ћатрица rows_count на cols_count заполненна€ filler
        matrix(int rows_count, int cols_count, long long filler);
        //ћатрица из двумерного вектора a
        matrix(std::vector<std::vector<fraction>> a);
        void swap_rows(int i, int j);
        void swap_cols(int i, int j);
        //¬озвращает транспорованную матрицу
        matrix transpose();

        //mode = 0 - просто вывод, mode = 1 - вывод матрицы дл€ латеха с круглыми скобками, mode = 2 - вывод матрицы дл€ латеха со скобками определител€
        //f_mode = 0 - дроби в виде x/y, f_mode = 1 - \frac{x}{y}
        void print(int mode = 0,int f_mode=0) const;
        //verbose = 0 - не выводить ход решени€, verbose = 1 - отображать каждый шаг хода решени€.
        fraction det(int verbose = 0) const;
        //verbose = 0 - не выводить ход решени€, verbose = 1 - отображать каждый шаг хода решени€, verbose = 2 - отображать только основные шаги хода решени€
        matrix inverse(int verbose = 0) const;
        //¬озвращает минор исходной матрицы состо€щий из строк и столбцов с номерами в rows и cols
        matrix minor(std::vector<int> rows, std::vector<int> cols) const;
        //¬озвращает минор исходной матрицы состо€щий из строк и столбцов , в чьих индексах стоит True в rows и cols
        matrix minor(std::vector<bool> rows, std::vector<bool> cols) const;
        //verbose = 0 - не выводить ход решени€, verbose = 1 - выводить каждый шаг хода решени€, 2 - отображать только основные шаги.
        int rank(int verbose = 0) const;
    };

fraction operator + (fraction c1, long long c2);
fraction operator + (long long c1, fraction c2);
//verbose = 0 - не выводить ход решени€, verbose = 1 - отображать каждый шаг хода решени€, verbose = 2 - отображать только основные шаги хода решени€
matrix solve_solae(matrix K, matrix Y,int verbose = 0);
};