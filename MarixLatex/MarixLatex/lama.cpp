
#include <iostream>
#include <vector>
#include <fstream>
#include "lama.h"
using namespace lama;
#define ll long long int

std::ofstream outf;
bool write_in_file = 0;
void lama::start_write_in_file(std::string outfile_path) {
    outf.open(outfile_path);
    if (!outf.is_open())
    throw "Не получилось открыть выходной файл!";
    write_in_file = 1;
}
void lama::stop_write_in_file() {
    if (write_in_file) {
    write_in_file = 0;
    outf.close();
    }
}
ll lama::gcd(ll a, ll b) 
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

fraction::fraction(ll a, ll b) 
{

    if (b == 0)
        throw "Деление на 0";
    sign = ((a >= 0) && (b >= 0)) || ((a < 0) && (b < 0));
    a = abs(a);
    b = abs(b);
    ll g = gcd(a, b);
    num = a / g;
    dem = b / g;

}
fraction::fraction(ll a) {

    fraction b1(a, 1);
    dem = b1.dem;
    num = b1.num;
    sign = b1.sign;

}

void fraction::print(bool f = 0) const 
{

    if (num == 0) {
        std::cout << "0";
        outf << "0";
    }
    else
    {
        if (!sign) {
        std::cout << "-";
        outf << "-";
        }
        if (dem == 1) {
        outf << num;
        std::cout << num;
        }
        else
        if (f)
        {
            std::cout << "\\frac{" << num << "}{" << dem << "}";
            outf << "\\frac{" << num << "}{" << dem << "}";
        }
        else
        {
            std::cout << num << "/" << dem;
            outf << num << "/" << dem;;
        }
    }

}
fraction fraction::operator + (fraction p1) const
{

    if (num == 0)
        return p1;
    if (p1.num == 0)
        if (sign)
        return fraction(num, dem);
        else
        return fraction(-num, dem);
    ll n_dem = (dem * p1.dem) / gcd(dem, p1.dem);
    ll n_num = 0;
    if (sign)
        n_num = num * (n_dem / dem);
    else
        n_num = -num * (n_dem / dem);
    if (p1.sign)
        n_num += p1.num * (n_dem / p1.dem);
    else
        n_num += -p1.num * (n_dem / p1.dem);
    return fraction(n_num, n_dem);

}
fraction fraction::operator - (fraction p1) const 
{

    if (sign)
        return fraction(num, dem) + p1 * -1;
    else
        return fraction(-num, dem) + p1 * -1;

}
fraction fraction::operator * (fraction p1) const
{
    if (sign ^ p1.sign) return fraction(-num * p1.num, dem * p1.dem);
    return fraction(num * p1.num, dem * p1.dem);

}
fraction fraction::operator /(fraction p1) const
{

    if (sign ^ p1.sign) return fraction(-num * p1.dem, dem * p1.num);
    return fraction(num * p1.dem, dem * p1.num);

}



matrix matrix::operator = (matrix p1)
{

    n = p1.n;
    m = p1.m;
    A = p1.A;
    return p1;

}

matrix matrix::operator + (matrix p1)
{

    if ((n != p1.n) || (m != p1.m)) throw "Разные размеры слагаемых";
    matrix res(n, m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        res.A[i][j] = A[i][j] + p1.A[i][j];
    return res;

}
matrix matrix::operator * (matrix p1)
{

    if (m != p1.n) throw "Неверные размеры множителей";
    matrix res(n, p1.m, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < p1.m; j++)
        for (int q = 0; q < m; q++)
            res.A[i][j] = res.A[i][j] + A[i][q] * p1.A[q][j];
    return res;

}

matrix::matrix(int n1, int m1, fraction filler) 
{

    n = n1;
    m = m1;
    for (int i = 0; i < n; i++) {
        A.push_back({});
        for (int j = 0; j < m; j++) {
        A[i].push_back(filler);
        }
    }

}

matrix::matrix(int n1) 
{

    matrix a(n1, n1, 0);
    for (int i = 0; i < n1; i++)
        a.A[i][i] = 1;
    A = a.A;
    n = n1;
    m = n1;

}
matrix::matrix(int n1, int m1, ll filler) 
{

    n = n1;
    m = m1;
    for (int i = 0; i < n; i++) {
        A.push_back({});
        for (int j = 0; j < m; j++) {
        A[i].push_back(fraction(filler));
        }
    }

}
matrix::matrix(std::vector<std::vector<fraction>> a) 
{

    n = a.size();
    if (n == 0) {
        m = 1;
        n = 1;
        A = matrix(1, 1, 0).A;
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
void matrix::swap_lines(int i, int j) 
{

    if ((i < 0) || (j < 0) || (i >= n) || (j >= n))
        throw "Выход за границы матрицы";
    std::vector<fraction> c;
    c = A[i];
    A[i] = A[j];
    A[j] = c;

}
void matrix::swap_cols(int i, int j) 
{

    if ((i < 0) || (j < 0) || (i >= m) || (j >= m))
        throw "Выход за границы матрицы";
    std::vector<fraction> c;
    for (int q = 0; q < n; q++)
        c.push_back(A[q][i]);
    for (int q = 0; q < n; q++) {
        A[q][i] = A[q][j];
        A[q][j] = c[q];
    }

}

matrix matrix::transpose() 
{

    matrix res(m, n, 0);
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
        res.A[i][j] = A[j][i];
    return res;

}

void matrix::print(int mode = 0) const 
{

    if (mode)
    {
        if (mode == 2)
        {
        std::cout << "\\begin{vmatrix}\n";
        outf << "\\begin{vmatrix}\n";
        }
        else
        {
        std::cout << "\\begin{pmatrix}\n";
        outf << "\\begin{pmatrix}\n";
        }
        for (int i = 0; i < n; i++) {
        A[i][0].print();
        for (int j = 1; j < m; j++) {
            std::cout << " & ";
            outf << " & ";
            A[i][j].print();
        }
        std::cout << "\\\\ \n";
        outf << "\\\\ \n";
        }
        if (mode == 2)
        {
        std::cout << "\\end{vmatrix}\n";
        outf << "\\end{vmatrix}\n";
        }
        else
        {
        std::cout << "\\end{pmatrix}\n";
        outf << "\\end{pmatrix}\n";
        }
    }
    else
        for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
        {
            A[i][j].print();
            std::cout << " ";
            outf << " ";
        }
        std::cout << '\n';
        outf << '\n';
        }

}
fraction matrix::det(int printmode = 0) const 
{

    if (n != m)
        throw "Нельзя найти определитель прямоугольной матрицы";
    if (!((0 <= printmode) || (printmode <= 1)))
        throw "Неизвестный способ вывода хода решения";
    matrix a(A);
    fraction d1(1);
    bool sign = false;
    if (printmode==1) { a.print(2); std::cout << "=\n"; outf << '\n'; }

    for (int i = 0; i < n - 1; i++) {
        if (a.A[i][i].num == 0) { //Три if пытаются сделать, чтобы диагональный элемент !=0
        for (int q = i; q < n; q++)
            if (a.A[q][i].num != 0) {
            a.swap_lines(i, q);
            sign = sign ^ (((q - i) % 2) == 1);
            if (printmode==1) {
                if (sign) {
                std::cout << "-\n";
                outf << "-\n";
                }
                a.print(2);
                outf << "=\n";
                std::cout << "=\n";
            }
            break;
            }
        }
        if (a.A[i][i].num == 0) {
        for (int q = i; q < n; q++)
            if (a.A[i][q].num != 0) {
            a.swap_cols(i, q);
            sign = sign ^ (((q - i) % 2) == 0);
            if (printmode==1) {
                if (sign) {
                std::cout << "-\n";
                outf << "-\n";
                }
                a.print(2);
                outf << "=\n";
                std::cout << "=\n";
            }
            break;
            }
        }
        if (a.A[i][i].num == 0) {
        if (printmode==1) {
            outf << "0"; 
            std::cout << "0";
        }
        return 0;
        }
        for (int q = i + 1; q < n; q++) {
        d1 = a.A[q][i] / a.A[i][i];
        for (int j = i; j < n; j++)
            a.A[q][j] = a.A[q][j] - d1 * a.A[i][j];
        }
        //if (verbose) { if (sign) std::cout << "-\n"; a.print(2); std::cout << "=\n"; }
        if (printmode) {
        if (sign) {
            std::cout << "-\n";
            outf << "-\n";
        }
        a.print(2);
        outf << "=\n";
        std::cout << "=\n";
        }
    }
    fraction res(1);
    for (int i = 0; i < n; i++)
        res = res * a.A[i][i];
    if (sign) 
        res = res * -1;
    if (printmode) 
        res.print(1);

    return res;

}
    
matrix matrix::inverse(int printmode = 0) const {
    if (n != m) 
        throw "Нельзя найти обратную прямоугольную матрицу";
    if (!((0 <= printmode) || (printmode <= 2)))
        throw "Неизвестный способ вывода хода решения";
    matrix a(A);
    matrix res(n);
    fraction d1(1);
    if (printmode!=0) 
    {
        a.print(1);
        std::cout << "^{-1}\n: \\\\ \n";
        outf << "^{-1}\n: \\\\ \n";
        a.print(1);
        std::cout << "|";
        outf << "|";
        res.print(1);
        std::cout << "=\n";
        outf << "=\n";
    }

    //Прямой ход Гаусса
    for (int i = 0; i < n; i++) 
    {
        if (a.A[i][i].num == 0)
        {
            for (int q = i; q < n; q++)
                if (a.A[q][i].num != 0) {
                    a.swap_lines(i, q);
                    res.swap_lines(i, q);
                    if (printmode == 1) {
                        a.print(1);
                        std::cout << "|";
                        outf << "|";
                        res.print(1);
                        outf << "=\n";
                        std::cout << "=\n";
                    }
                    break;
                }
        }
        if (a.A[i][i].num == 0)
            throw "Вырожденная матрица. Поиск обратной невозможен";
        d1 = fraction(1) / a.A[i][i];
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
        if (printmode == 1) 
        {
            a.print(1);
            std::cout << "|";
            outf << "|";
            res.print(1);
            std::cout << "=\n";
            outf << "=\n";
        }
    } //Конец прямого хода

    if (printmode == 2) 
    {
        a.print(1);
        std::cout << "|";
        outf << "|";
        res.print(1);
        std::cout << "=\n";
        outf << "=\n";
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
            if ((printmode == 1)) 
            {
                a.print(1);
                std::cout << "|";
                outf << "|";
                res.print(1);
                if ((q + i) > 1) 
                {
                    std::cout << "=\n";
                    outf << "=\n";
                }
            }
        }
    } //Конец обратного хода

    if (printmode == 2) 
    {
        a.print(1);
        std::cout << "|";
        outf << "|";
        res.print(1);
    }
    if (printmode != 0)
        std::cout << ": \\\\ \n";
    outf << ": \\\\ \n";
    res.print(1);
    return res;
    }
matrix matrix::minor(std::vector<int> lines, std::vector<int> cols) const {
    matrix res(lines.size(), cols.size(), 0);
    for (int i = 0; i < res.n; i++) {
        if ((lines[i] < 0) || (lines[i] >= n))
        throw "Выход за пределы матрицы";
        for (int j = 0; j < res.m; j++)
        {
        if ((cols[j] < 0) || (cols[j] >= m))
            throw "Выход за пределы матрицы";
        res.A[i][j] = A[lines[i]][cols[j]];
        }
    }
    return res;
    }
matrix matrix::minor(std::vector<bool> lines, std::vector<bool> cols) const {
    if ((lines.size() != n) || (cols.size() != m))
        throw "Неправильно задан минор";
    std::vector<int> c, l;
    for (int i = 0; i < n; i++)
        if (lines[i])
        l.push_back(i);
    for (int i = 0; i < m; i++)
        if (cols[i])
        c.push_back(i);
    return minor(l, c);
    }
int matrix::rank(bool verbose = 0) const {
    std::vector<bool> lines(n);
    std::vector<bool> cols(m);
    bool b1 = false;
    if (verbose) {
        std::cout << "rank ";
        outf << "rank ";
        print(1);
        std::cout << ": \\\\ \n";
        outf << ": \\\\ \n";
    }
    for (int i = 0; i < n; i++)
    {
        if (b1)
        break;
        for (int j = 0; j < m; j++)
        if (A[i][j].num != 0) {
            lines[i] = 1;
            cols[i] = 1;
            b1 = true;
            if (verbose) {
            std::cout << "\\Delta_{" << i + 1 << "|" << j + 1 << "}=";
            outf << "\\Delta_{" << i + 1 << "|" << j + 1 << "}=";
            A[i][j].print(1);
            }
            break;
        }
    }
    std::cout << "\\\\ \n";
    outf << "\\\\ \n";
    if (!b1)
        return 1;
    b1 = 0;
    fraction de(1);
    std::vector<int> c, l;

    int k = std::min(n, m);
    for (int q = 2; q < k; q++) {
        b1 = 0;
        //for 
        for (int i = 0; i < n; i++) {
        if (b1)
            break;
        for (int j = 0; j < m; j++)
            if (!(cols[j] || lines[i])) { //Не включено в минор
            lines[i] = 1;
            cols[j] = 1;
            de = minor(lines, cols).det(0);
            if (verbose) {
                std::cout << "\\Delta_{";
                outf << "\\Delta_{";
                l = {};
                c = {};
                for (int di = 0; di < n; di++)
                if (lines[di])
                    l.push_back(di);
                for (int di = 0; di < m; di++)
                if (cols[di])
                    c.push_back(di);
                for (int di = 0; di < (int)l.size(); di++) {
                std::cout << l[di] + 1;
                outf << l[di] + 1;
                if (di < ((int)l.size() - 1)) {
                    outf << ",";
                    std::cout << ",";
                }
                }
                std::cout << "|";
                outf << "|";
                for (int di = 0; di < (int)c.size(); di++) {
                std::cout << c[di] + 1;
                if (di < ((int)c.size() - 1)) {
                    outf << ",";
                    std::cout << ",";
                }
                }
                std::cout << "} = ";
                outf << "} = ";
                de.print(1);
                std::cout << "; ";
                outf << "; ";
            }
            if (minor(lines, cols).det(0).num != 0)
            {
                b1 = 1;
                if (verbose) {
                std::cout << "\\\\ \n";
                outf << "\\\\ \n";
                }
                break;
            }
            lines[i] = 0;
            cols[j] = 0;
            }
        }

        if (!b1)
        {
        if (verbose) {
            std::cout << "\\\\\nrank = " << q - 1;
            outf << "\\\\\nrank = " << q - 1;
        }
        return q - 1;
        }
    }
    if (verbose) {
        std::cout << "rank = " << k;
        outf << "rank = " << k;
    }
    return k;
    }

fraction operator + (fraction c1, ll c2) { return c1 + fraction(c2); }
fraction operator + (ll c1, fraction c2) { return c2 + fraction(c1); }


