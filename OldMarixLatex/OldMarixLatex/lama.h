#pragma once

//Объявляет следующие абстракции:
//  Абстрактный класс AriphObj, имеющий виртуальный метод вывода в поток - print, предполагается, что его наследники реализуют +,-,* и +=,-=,*=,==
//  Класс рациональных дробей Fractional                                                                                                          
//  Класс матриц со значениями - рациональными дробями                                                                                            
//Все наследники AriphObj, кроме обычных операций с математическими объектами, которые они реализуют, имеют методы отображения хода вычисления    
//  в Latex                                                                                                                                       

//Нейминг:
//  Глобальные и локальные переменные, параметры функций и методов - snake_case
//  Поля классов - snake_case_                                                 
//  Функции и публичные методы - camelCase                                     
//  Приватные методы - camelCase_                                              
//  Классы - PascalCase                                                        


#include <vector>
#include <fstream>
#include <string>
namespace lama {
    //Наследники обязаны реализовать:
    //+,-,*
    //+=,-=,*=
    class AriphObj {
    public:
        virtual void print(bool mode_latex, std::ostream& out) const = 0;
    };
    class Fraction: public AriphObj {
    private:
        //Числитель
        long long num_;
        //Знаменатель
        long long denum_;
        //Оно >= 0
        bool is_positive_;
    public:
        
        Fraction(long long a, long long b);
        Fraction(long long a);

        Fraction operator + (Fraction other) const;
        Fraction operator - (Fraction other) const;
        Fraction operator * (Fraction other) const;
        Fraction operator / (Fraction other) const;

        Fraction operator += (Fraction other);
        Fraction operator -= (Fraction other);
        Fraction operator *= (Fraction other);
        Fraction operator /= (Fraction other);

        bool operator ==(Fraction other) const;

        void set_num(long long new_num);
        void set_denum(long long new_denum);
        void change_sign(bool to_positive);
        void copy(Fraction other);

        int num() const;
        int denum() const;
        int is_positive() const;

        bool is_zero() const;

        void print(bool mode_latex, std::ostream& out) const;
    };
    /*
    class Matrix {
    public:
        std::vector< std::vector<Fraction>> A;
        //Количество строк
        int n;
        //Количество столбцов
        int m;

        Matrix operator = (Matrix p1);
        Matrix operator + (Matrix p1);
        Matrix operator * (Matrix p1);
        //Матрица rows_count на cols_count заполненная filler
        Matrix(int rows_count, int cols_count, Fraction filler);
        //Единичная матрица size на size
        Matrix(int size);
        //Матрица rows_count на cols_count заполненная filler
        Matrix(int rows_count, int cols_count, long long filler);
        //Матрица из двумерного вектора a
        Matrix(std::vector<std::vector<Fraction>> a);
        void swap_rows(int i, int j);
        void swap_cols(int i, int j);
        //Возвращает транспорованную матрицу
        Matrix transpose();

        //mode = 0 - просто вывод, mode = 1 - вывод матрицы для латеха с круглыми скобками, mode = 2 - вывод матрицы для латеха со скобками определителя
        //f_mode = 0 - дроби в виде x/y, f_mode = 1 - \frac{x}{y}
        void print(int mode = 0, int f_mode = 0, std::ostream& out = std::cout) const;
        //verbose = 0 - не выводить ход решения, verbose = 1 - отображать каждый шаг хода решения.
        Fraction det(int verbose = 0, std::ostream& out = std::cout) const;
        //verbose = 0 - не выводить ход решения, verbose = 1 - отображать каждый шаг хода решения, verbose = 2 - отображать только основные шаги хода решения
        Matrix inverse(int verbose = 0, std::ostream& out = std::cout) const;
        //Возвращает минор исходной матрицы состоящий из строк и столбцов с номерами в rows и cols
        Matrix minor(std::vector<int> rows, std::vector<int> cols) const;
        //Возвращает минор исходной матрицы состоящий из строк и столбцов , в чьих индексах стоит True в rows и cols
        Matrix minor(std::vector<bool> rows, std::vector<bool> cols) const;
        //verbose = 0 - не выводить ход решения, verbose = 1 - выводить каждый шаг хода решения, 2 - отображать только основные шаги.
        int rank(int verbose = 0, std::ostream& out = std::cout) const;
    };

    Fraction operator + (Fraction c1, long long c2);
    Fraction operator + (long long c1, Fraction c2);
    //verbose = 0 - не выводить ход решения, verbose = 1 - отображать каждый шаг хода решения, verbose = 2 - отображать только основные шаги хода решения
    Matrix solve_solae(Matrix K, Matrix Y, int verbose = 0, std::ostream& out = std::cout);
    */
    long long calcGCD(long long a, long long b);

};
