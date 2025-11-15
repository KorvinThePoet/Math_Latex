// Matrix.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
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
        long long num, dem;
        bool sign;
        fraction(long long a, long long b);
        fraction(long long a);
        void print(bool f) const;
        fraction operator + (fraction p1) const;
        fraction operator - (fraction p1) const;
        fraction operator * (fraction p1) const;
        fraction operator /(fraction p1) const;
    };

    class matrix {
    public:
        std::vector< std::vector<fraction>> A;
        int n, m;

        matrix operator = (matrix p1);
        matrix operator + (matrix p1);
        matrix operator * (matrix p1);

        matrix(int n1, int m1, fraction filler);
        matrix(int n1);
        matrix(int n1, int m1, long long filler);
        matrix(std::vector<std::vector<fraction>> a);
        void swap_lines(int i, int j);
        void swap_cols(int i, int j);
        matrix transpose();

        //mode = 0 - просто вывод, mode = 1 - вывод матрицы для латеха с круглыми скобками, mode = 2 - вывод матрицы для латеха со скобками определителя
        void print(int mode) const;

        fraction det(int printmode) const;
        //printmode = 0 - не  ход решения, printmode = 1 - отображать каждый шаг хода решения, printmode = 2 - отображать только основные шаги хода решения
        matrix inverse(int printmode) const;
        matrix minor(std::vector<int> lines, std::vector<int> cols) const;
        matrix minor(std::vector<bool> lines, std::vector<bool> cols) const;
        int rank(bool verbose) const;
    };

fraction operator + (fraction c1, long long c2);
fraction operator + (long long c1, fraction c2);
};