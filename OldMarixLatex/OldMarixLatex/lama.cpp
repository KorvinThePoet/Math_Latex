
#include <iostream>
#include <vector>
#include <fstream>
#include "lama.h"
using namespace lama;
#define ll long long int
ll lama::calcGCD(ll a, ll b)
{
    a = abs(a);
    b = abs(b);
    while ((a) && (b)) {
        if (a > b)
            a = a % b;
        else
            b = b % a;
    }
    return a + b;
}

Fraction::Fraction(ll a, ll b)
{
    if (b == 0)
        throw "Деление на 0";
    is_positive_ = ((a >= 0) && (b >= 0)) || ((a < 0) && (b < 0));
    a = abs(a);
    b = abs(b);
    ll g = calcGCD(a, b);
    num_ = a / g;
    denum_ = b / g;
}
Fraction::Fraction(ll a) {
    Fraction b(a, 1);
    denum_ = b.denum_;
    num_ = b.num_;
    is_positive_ = b.is_positive_;
}

void Fraction::print(bool mode_latex, std::ostream& out) const
{
    if (num_ == 0) {
        out << "0";
    }
    else
    {
        if (!is_positive_) {
            out << "-";
        }
        if (denum_ == 1) {
            out << num_;
        }
        else
            if (mode_latex)
            {
                out << "\\frac{" << num_ << "}{" << denum_ << "}";
            }
            else
            {
                out << num_ << "/" << denum_;
            }
    }
}

Fraction Fraction::operator + (Fraction other) const
{
    if (num_ == 0)
        return other;
    if (other.num_ == 0)
        if (is_positive_)
            return Fraction(num_, denum_);
        else
            return Fraction(-num_, denum_);
    ll n_denum = (denum_ * other.denum_) / calcGCD(denum_, other.denum_);
    ll n_num = 0;
    if (is_positive_)
        n_num = num_ * (n_denum / denum_);
    else
        n_num = -num_ * (n_denum / denum_);
    if (other.is_positive_)
        n_num += other.num_ * (n_denum / other.denum_);
    else
        n_num += -other.num_ * (n_denum / other.denum_);
    return Fraction(n_num, n_denum);
}
Fraction Fraction::operator - (Fraction other) const
{
    if (is_positive_)
        return Fraction(num_, denum_) + other * -1;
    else
        return Fraction(-num_, denum_) + other * -1;
}
Fraction Fraction::operator * (Fraction other) const
{
    if (is_positive_ ^ other.is_positive_) 
        return Fraction(-num_ * other.num_, denum_ * other.denum_);
    return Fraction(num_ * other.num_, denum_ * other.denum_);
}
Fraction Fraction::operator / (Fraction other) const
{
    if (is_positive_ ^ other.is_positive_)
        return Fraction(-num_ * other.denum_, denum_ * other.num_);
    return Fraction(num_ * other.denum_, denum_ * other.num_);
}

Fraction Fraction::operator += (Fraction other)
{
    if (num_ == 0)
        return other;
    if (other.num_ == 0)
        if (is_positive_)
            return Fraction(num_, denum_);
        else
            return Fraction(-num_, denum_);
    ll n_denum = (denum_ * other.denum_) / calcGCD(denum_, other.denum_);
    ll n_num = 0;
    if (is_positive_)
        n_num = num_ * (n_denum / denum_);
    else
        n_num = -num_ * (n_denum / denum_);
    if (other.is_positive_)
        n_num += other.num_ * (n_denum / other.denum_);
    else
        n_num += -other.num_ * (n_denum / other.denum_);
    *this = Fraction(n_num, n_denum);
    return Fraction(n_num, n_denum);
}
Fraction Fraction::operator -= (Fraction other)
{
    if (is_positive_) {
        *this = Fraction(num_, denum_) + other * -1;
        return Fraction(num_, denum_) + other * -1;
    }
    else {
        *this = Fraction(-num_, denum_) + other * -1;
        return Fraction(-num_, denum_) + other * -1;
    }
}
Fraction Fraction::operator *= (Fraction other)
{
    if (is_positive_ ^ other.is_positive_){
        *this = Fraction(-num_ * other.num_, denum_ * other.denum_);
        return Fraction(-num_ * other.num_, denum_ * other.denum_);
    }
    *this = Fraction(num_ * other.num_, denum_ * other.denum_);
    return Fraction(num_ * other.num_, denum_ * other.denum_);

}
Fraction Fraction::operator /= (Fraction other)
{
    if (is_positive_ ^ other.is_positive_){
        *this = Fraction(-num_ * other.denum_, denum_ * other.num_);
        return Fraction(-num_ * other.denum_, denum_ * other.num_);
    }
    *this = Fraction(num_ * other.denum_, denum_ * other.num_);
    return Fraction(num_ * other.denum_, denum_ * other.num_);
}

bool Fraction::operator == (Fraction other) const {
    return (num_ == other.num_) && (denum_ == other.denum_) && (is_positive_ == other.is_positive_);
}

void Fraction::set_num(long long new_num)
{
    if (new_num >= 0) {
        num_ = new_num;
    }
    else {
        num_ = -new_num;
    }
}
void Fraction::set_denum(long long new_denum) 
{
    if (new_denum >= 0) {
        denum_ = new_denum;
    }
    else {
        denum_ = -new_denum;
    }
}
void Fraction::change_sign(bool shall_to_positive) 
{
    is_positive_ = shall_to_positive;
}
void Fraction::copy(Fraction other) {
    num_ = other.num_;
    denum_ = other.denum_;
    is_positive_ = other.is_positive_;
}


int Fraction::num() const 
{
    return num_;
}
int Fraction::denum() const
{
    return denum_;
}
int Fraction::is_positive() const 
{
    return is_positive_;
}

bool Fraction::is_zero() const
{
    return num_ == 0;
}
/*

Matrix Matrix::operator = (Matrix p1)
{

    n = p1.n;
    m = p1.m;
    A = p1.A;
    return p1;

}

Matrix Matrix::operator + (Matrix p1)
{

    if ((n != p1.n) || (m != p1.m)) throw "Разные размеры слагаемых";
    Matrix res(n, m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            res.A[i][j] = A[i][j] + p1.A[i][j];
    return res;

}
Matrix Matrix::operator * (Matrix p1)
{

    if (m != p1.n) throw "Неверные размеры множителей";
    Matrix res(n, p1.m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p1.m; j++)
            for (int q = 0; q < m; q++)
                res.A[i][j] = res.A[i][j] + A[i][q] * p1.A[q][j];
    return res;

}

Matrix::Matrix(int rows_count, int cols_count, Fraction filler)
{

    n = rows_count;
    m = cols_count;
    for (int i = 0; i < n; i++) {
        A.push_back({});
        for (int j = 0; j < m; j++) {
            A[i].push_back(filler);
        }
    }

}

Matrix::Matrix(int size)
{

    Matrix a(size, size, 0);
    for (int i = 0; i < size; i++)
        a.A[i][i] = 1;
    A = a.A;
    n = size;
    m = size;

}
Matrix::Matrix(int rows_count, int cols_count, ll filler)
{

    n = rows_count;
    m = cols_count;
    for (int i = 0; i < n; i++) {
        A.push_back({});
        for (int j = 0; j < m; j++) {
            A[i].push_back(Fraction(filler));
        }
    }

}
Matrix::Matrix(std::vector<std::vector<Fraction>> a)
{

    n = a.size();
    if (n == 0) {
        m = 1;
        n = 1;
        A = Matrix(1, 1, 0).A;
    }
    else
    {
        m = a[0].size();
        for (int i = 1; i < n; i++)
            if (m != a[i].size())
                throw "Неправильные входные данные при создании матрицы";
    }
    A = a;

}
void Matrix::swap_rows(int i, int j)
{

    if ((i < 0) || (j < 0) || (i >= n) || (j >= n))
        throw "Выход за границы матрицы";
    std::vector<Fraction> c;
    c = A[i];
    A[i] = A[j];
    A[j] = c;

}
void Matrix::swap_cols(int i, int j)
{

    if ((i < 0) || (j < 0) || (i >= m) || (j >= m))
        throw "Выход за границы матрицы";
    std::vector<Fraction> c;
    for (int q = 0; q < n; q++)
        c.push_back(A[q][i]);
    for (int q = 0; q < n; q++) {
        A[q][i] = A[q][j];
        A[q][j] = c[q];
    }

}

Matrix Matrix::transpose()
{

    Matrix res(m, n, 0);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            res.A[i][j] = A[j][i];
    return res;

}

void Matrix::print(int mode, int f_mode, std::ostream& out) const
{

    if (mode)
    {
        if (mode == 2)
        {
            out << "\\begin{vMatrix}\n";
        }
        else
        {
            out << "\\begin{pMatrix}\n";
        }
        for (int i = 0; i < n; i++) {
            if (f_mode == 0) {
                A[i][0].print(0, out);
            }
            else {
                A[i][0].print(1, out);
            }
            for (int j = 1; j < m; j++) {
                out << " & ";
                if (f_mode == 0) {
                    A[i][j].print(0, out);
                }
                else {
                    A[i][j].print(1, out);
                }

            }
            out << "\\\\ \n";
        }
        if (mode == 2)
        {
            out << "\\end{vMatrix}\n";
        }
        else
        {
            out << "\\end{pMatrix}\n";
        }
    }
    else
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
            {
                if (f_mode == 0) {
                    A[i][j].print(0, out);
                }
                else {
                    A[i][j].print(1, out);
                }
                out << " ";
            }
            out << '\n';
        }

}
Fraction Matrix::det(int verbose, std::ostream& out) const
{

    if (n != m)
        throw "Нельзя найти определитель прямоугольной матрицы";
    if (!((0 <= verbose) || (verbose <= 1)))
        throw "Неизвестный способ вывода хода решения";
    Matrix a(A);
    Fraction d1(1);
    bool sign = false;
    if (verbose == 1) { a.print(2,0, out); out << "=\n";}

    for (int i = 0; i < n - 1; i++) {
        if (a.A[i][i].num_ == 0) { //Три if пытаются сделать, чтобы диагональный элемент !=0
            for (int q = i; q < n; q++)
                if (a.A[q][i].num_ != 0) {
                    a.swap_rows(i, q);
                    sign = sign ^ (((q - i) % 2) == 1);
                    if (verbose == 1) {
                        if (sign) {
                            out << "-\n";
                        }
                        a.print(2,0, out);
                        out << "=\n";
                    }
                    break;
                }
        }
        if (a.A[i][i].num_ == 0) {
            for (int q = i; q < n; q++)
                if (a.A[i][q].num_ != 0) {
                    a.swap_cols(i, q);
                    sign = sign ^ (((q - i) % 2) == 0);
                    if (verbose == 1) {
                        if (sign) {
                            out << "-\n";
                        }
                        a.print(2,0, out);
                        out << "=\n";
                    }
                    break;
                }
        }
        if (a.A[i][i].num_ == 0) {
            if (verbose == 1) {
                out << "0";
            }
            return 0;
        }
        for (int q = i + 1; q < n; q++) {
            d1 = a.A[q][i] / a.A[i][i];
            for (int j = i; j < n; j++)
                a.A[q][j] = a.A[q][j] - d1 * a.A[i][j];
        }
        //if (verbose) { if (sign) std::cout << "-\n"; a.print(2); std::cout << "=\n"; }
        if (verbose) {
            if (sign) {
                out << "-\n";
            }
            a.print(2,0, out);
            out << "=\n";
        }
    }
    Fraction res(1);
    for (int i = 0; i < n; i++)
        res = res * a.A[i][i];
    if (sign)
        res = res * -1;
    if (verbose != 0)
        res.print(1, out);

    return res;

}

Matrix Matrix::inverse(int verbose, std::ostream& out) const {
    if (n != m)
        throw "Нельзя найти обратную прямоугольную матрицу";
    if (!((0 <= verbose) || (verbose <= 2)))
        throw "Неизвестный способ вывода хода решения";
    Matrix a(A);
    Matrix res(n);
    Fraction d1(1);
    if (verbose != 0)
    {
        a.print(1,0, out);
        out << "^{-1}\n: \\\\ \n";
        a.print(1,0, out);
        out << "|";
        res.print(1,0, out);
        out << "=\n";
    }

    //Прямой ход Гаусса
    for (int i = 0; i < n; i++)
    {
        if (a.A[i][i].num_ == 0)
        {
            for (int q = i; q < n; q++)
                if (a.A[q][i].num_ != 0) {
                    a.swap_rows(i, q);
                    res.swap_rows(i, q);
                    if (verbose == 1) {
                        a.print(1,0, out);
                        out << "|";
                        res.print(1,0, out);
                        out << "=\n";
                    }
                    break;
                }
        }
        if (a.A[i][i].num_ == 0)
            throw "Вырожденная матрица. Поиск обратной невозможен";
        d1 = Fraction(1) / a.A[i][i];
        for (int j = 0; j < n; j++)
        {
            a.A[i][j] = a.A[i][j] * d1;
            res.A[i][j] = res.A[i][j] * d1;
        }
        for (int q = i + 1; q < n; q++)
        {
            d1 = a.A[q][i] / a.A[i][i];
            for (int j = 0; j < n; j++)
            {
                a.A[q][j] = a.A[q][j] - a.A[i][j] * d1;
                res.A[q][j] = res.A[q][j] - res.A[i][j] * d1;
            }
        }
        if (verbose == 1)
        {
            a.print(1,0, out);
            out << "|";
            res.print(1,0, out);
            out << "=\n";
        }
    } //Конец прямого хода

    if (verbose == 2)
    {
        a.print(1,0, out);
        out << "|";
        res.print(1,0, out);
        out << "=\n";
    }

    //Обратный ход
    for (int i = (n - 1); i >= 0; i--)
    {
        for (int q = i - 1; q >= 0; q--)
        {
            d1 = a.A[q][i];
            for (int j = 0; j < n; j++)
            {
                a.A[q][j] = a.A[q][j] - a.A[i][j] * d1;
                res.A[q][j] = res.A[q][j] - res.A[i][j] * d1;
            }
            if ((verbose == 1))
            {
                a.print(1,0, out);
                out << "|";
                res.print(1,0, out);
                if ((q + i) > 1)
                {
                    out << "=\n";
                }
            }
        }
    } //Конец обратного хода

    if (verbose == 2)
    {
        a.print(1,0, out);
        out << "|";
        res.print(1,0, out);
    }
    if (verbose != 0)
    { 
        out << ": \\\\ \n";
        res.print(1,0, out);
    }
    return res;
}
Matrix Matrix::minor(std::vector<int> rows, std::vector<int> cols) const {
    Matrix res(rows.size(), cols.size(), 0);
    for (int i = 0; i < res.n; i++) {
        if ((rows[i] < 0) || (rows[i] >= n))
            throw "Выход за пределы матрицы";
        for (int j = 0; j < res.m; j++)
        {
            if ((cols[j] < 0) || (cols[j] >= m))
                throw "Выход за пределы матрицы";
            res.A[i][j] = A[rows[i]][cols[j]];
        }
    }
    return res;
}
Matrix Matrix::minor(std::vector<bool> rows, std::vector<bool> cols) const {
    if ((rows.size() != n) || (cols.size() != m))
        throw "Неправильно задан минор";
    std::vector<int> c, l;
    for (int i = 0; i < n; i++)
        if (rows[i])
            l.push_back(i);
    for (int i = 0; i < m; i++)
        if (cols[i])
            c.push_back(i);
    return minor(l, c);
}
int Matrix::rank(int verbose, std::ostream& out) const {
    std::vector<bool> lines(n);
    std::vector<bool> cols(m);
    bool b1 = false;
    if (verbose != 0) {
        out << "rank ";
        print(1,0, out);
        out << ": \\\\ \n";
    }
    for (int i = 0; i < n; i++)
    {
        if (b1)
            break;
        for (int j = 0; j < m; j++)
            if (A[i][j].num_ != 0) {
                lines[i] = 1;
                cols[i] = 1;
                b1 = true;
                if (verbose != 0) {
                    out << "\\Delta_{" << i + 1 << "|" << j + 1 << "}=";
                    A[i][j].print(1, out);
                }
                break;
            }
    }
    out << "\\\\ \n";
    if (!b1)
        return 1;
    b1 = 0;
    Fraction de(1);
    std::vector<int> c, l;

    int k = std::min(n, m);
    for (int q = 2; q < k; q++) {
        b1 = 0;
        for (int i = 0; i < n; i++) {
            if (b1)
                break;
            for (int j = 0; j < m; j++)
                if (!(cols[j] || lines[i])) { //Не включено в минор
                    lines[i] = 1;
                    cols[j] = 1;
                    if (verbose != 0) {
                        if ((verbose == 1) && (q > 3)) {
                            de = minor(lines, cols).det(1, out);
                            out << "\\\\ \n";
                        }
                        else {
                            de = minor(lines, cols).det(0);
                        }
                    }
                    if (verbose != 0) {
                        out << "\\Delta_{";
                        l = {};
                        c = {};
                        for (int di = 0; di < n; di++) {
                            if (lines[di])
                                l.push_back(di);
                        }
                        for (int di = 0; di < m; di++) {
                            if (cols[di])
                                c.push_back(di);
                        }
                        for (int di = 0; di < (int)l.size(); di++) {
                            out << l[di] + 1;
                            if (di < ((int)l.size() - 1)) {
                                out << ",";
                            }
                        }
                        std::cout << "|";
                        for (int di = 0; di < (int)c.size(); di++) {
                            out << c[di] + 1;
                            if (di < ((int)c.size() - 1)) {
                                out << ",";
                            }
                        }
                        out << "} = ";
                        de.print(1, out);
                        out << "; ";
                    }
                    if (minor(lines, cols).det(0).num_ != 0)
                    {
                        b1 = 1;
                        if (verbose != 0) {
                            out << "\\\\ \n";
                        }
                        break;
                    }
                    lines[i] = 0;
                    cols[j] = 0;
                }
        }

        if (!b1)
        {
            if (verbose != 0) {
                out << "\\\\\nrank = " << q - 1;
            }
            return q - 1;
        }
    }
    if (verbose != 0) {
        out << "rank = " << k;
    }
    return k;
}

Fraction operator + (Fraction c1, ll c2) { return c1 + Fraction(c2); }
Fraction operator + (ll c1, Fraction c2) { return c2 + Fraction(c1); }

Matrix lama::solve_solae(Matrix K, Matrix Y, int verbose, std::ostream& out)
{

    if ((Y.m != 1) || (Y.n != K.n)) {
        throw "Неверно задана система";
    }

    bool fl = false;
    Fraction tmp(0);
    int nowcol = 0;
    int nowrow = 0;
    Matrix R(K.n, K.m + 1, -1);

    for (int i = 0; i < K.n; ++i) {
        for (int j = 0; j < K.m; ++j) {
            R.A[i][j] = K.A[i][j];
        }
        R.A[i][R.m - 1] = Y.A[i][0];
    }
    if (verbose != 0) {
        out << "$\\bar A$ =";
        R.print(1, 1, out);
        out << ": \\\\ \n";

    }
    if (verbose != 0) {
        R.print(1, 1, out);
    }
    while ((nowrow < K.n) && (nowcol < K.m)) { //Прямой ход начало
        if (R.A[nowrow][nowcol].num_ == 0) {
            fl = false;
            for (int i = nowrow; i < K.n; ++i) {
                if (R.A[i][nowcol].num_ != 0) {
                    fl = true;
                    R.swap_rows(i, nowrow);
                    break;
                }
            }
            if (!fl) {
                ++nowcol;
            }
        }
        else {
            for (int i = nowrow + 1; i < R.n; ++i) {
                tmp = R.A[i][nowcol] / R.A[nowrow][nowcol];
                for (int j = nowcol; j < R.m; ++j) {
                    R.A[i][j] = R.A[i][j] - R.A[nowrow][j] * tmp;
                }
            }
            tmp = R.A[nowrow][nowcol];
            for (int i = 0; i < R.m; ++i) {
                R.A[nowrow][i] = R.A[nowrow][i] / tmp;
            }
            ++nowcol;
            ++nowrow;
        }
        if (verbose == 1) {
            out << "\\sim \n";
            R.print(1, 1, out);
        }
    } //Прямой ход конец
    if (verbose == 2) {
        out << "\\sim \n";
        R.print(1, 1, out);
    }
    fl = false;
    nowcol = 0;
    nowrow = 0;
    for (int r = R.n - 1; r > 0; --r) {
        for (int c = 0; c < R.m; ++c) {
            if (R.A[r][c].num_ != 0) {
                for (int i = r - 1; i >= 0; --i) {
                    tmp = R.A[i][c];
                    for (int j = c; j < R.m; ++j) {
                        R.A[i][j] = R.A[i][j] - tmp * R.A[r][j];
                    }
                }
                break;
            }
        }
        if (verbose == 1) {
            out << "\\sim \n";
            R.print(1, 1, out);
        }
    }
    if (verbose == 2) {
        out << "\\sim \n";
        R.print(1, 1, out);
    }
    return R;
}
*/

