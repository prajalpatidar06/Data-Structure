#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
#define ll long long int

class matrix
{
private:
    vector<vector<ll>> mat;
    ll rows;
    ll cols;

public:
    matrix(ll rows, ll cols, char type);
    // modify matrix functions
    void set(ll val, ll x, ll y);
    void set(ll **arr, ll rows, ll cols);
    void fill(ll val);
    // read matrix
    ll get(ll x, ll y);
    void print();

    // conditional operator overloading
    void operator=(matrix temp);
    bool operator==(matrix temp);
    bool operator>(matrix temp);
    bool operator<(matrix temp);
    bool operator>=(matrix temp);
    bool operator<=(matrix temp);

    // arithmetic operator overloading
    friend matrix operator+(matrix a, matrix b);
    friend matrix operator-(matrix a, matrix b);
    friend matrix operator*(matrix a, matrix b);
    friend matrix operator/(matrix a, matrix b);

    // Some build in functions
    friend matrix transpose();
    friend matrix adjoint();
    friend matrix inverse();
};

matrix::matrix(ll rows, ll cols, char type = '0')
{
    this->rows = rows;
    this->cols = cols;
    vector<ll> temp(cols, 0);
    for (ll i = 0; i < rows; i++)
        mat.push_back(temp);
    if (type == 'i')
    {
        try
        {
            if (rows == cols)
            {
                for (ll i = 0; i < rows; i++)
                    mat[i][i] = 1;
            }
            else
                throw "exception";
        }
        catch (...)
        {
            cout << "Error: Identity matrix should me sqaure matrix.\n";
        }
    }
}

void matrix::set(ll val, ll x, ll y)
{
    try
    {
        if (x >= 0 && x < rows && y >= 0 && y < cols)
            mat[x][y] = val;
        else
            throw "exception";
    }
    catch (...)
    {
        cout << "Error: Can't access unauthourise memory location\n";
    }
}

void matrix::set(ll **arr, ll rows, ll cols)
{
    try
    {
        if (rows < this->rows && cols < this->cols && rows > 0 && cols > 0)
            for (ll i = 0; i < rows; i++)
                for (ll j = 0; j < cols; j++)
                    set(arr[i][j], i, j);
        else
            throw "exception";
    }
    catch (...)
    {
        cout << "Error: Can't access unauthourise memory location\n";
    }
}

void matrix::fill(ll val)
{
    for (auto &itr : mat)
        for (auto &jtr : itr)
            jtr = val;
}

ll matrix::get(ll x, ll y)
{
    try
    {
        if (x >= 0 && x < rows && y >= 0 && y < cols)
            return mat[x][y];
        else
            throw "exception";
    }
    catch (...)
    {
        cout << "Error: Can't access unauthourise memory location\n";
    }
    return -1;
}

void matrix::print()
{
    for (ll i = 0; i < rows; i++)
    {
        for (ll j = 0; j < cols; j++)
        {
            cout << mat[i][j] << " ";
        }
        cout << "\n";
    }
}

void matrix::operator=(matrix temp){
    mat = temp.mat;
    rows = temp.rows;
    cols = temp.cols;
}

bool matrix::operator==(matrix temp){
    if(rows != temp.rows || cols != temp.cols)
        return false;
    
    for(ll i = 0 ; i < rows ; i++)
        for(ll j = 0 ; j < cols ; j++)
            if(mat[i][j] != temp.mat[i][j])
                return false;
    return true;
}

// bool matrix::operator>(matrix temp);
// bool matrix::operator<(matrix temp);
// bool matrix::operator>=(matrix temp);
// bool matrix::operator<=(matrix temp);

matrix operator+(matrix a , matrix b){
    matrix c(max(a.rows , b.rows) , max(a.cols , b.cols));
    try{
        if(a.rows == b.rows && a.cols == b.cols)
            for(ll i = 0 ; i < c.rows ; i++)
                for(ll j = 0 ; j < c.cols ; j++)
                    c.mat[i][j] = a.mat[i][j] + b.mat[i][j];
        else
            throw "exception";
    }
    catch(...){
        cout<<"Error: could not apply arithematic operation on matrixes have diffrrent dimension.\n";
    }
    return c;
}

matrix operator-(matrix a , matrix b){
    matrix c(max(a.rows , b.rows) , max(a.cols , b.cols));
    try{
        if(a.rows == b.rows && a.cols == b.cols)
            for(ll i = 0 ; i < c.rows ; i++)
                for(ll j = 0 ; j < c.cols ; j++)
                    c.mat[i][j] = a.mat[i][j] - b.mat[i][j];
        else
            throw "exception";
    }
    catch(...){
        cout<<"Error: could not apply arithematic operation on matrixes have diffrrent dimension.\n";
    }
    return c;
}

matrix operator*(matrix a , matrix b){
    matrix c(a.rows , b.cols);
    try{
        if(a.cols == b.rows){
            for(ll i = 0 ; i < c.rows ; i++)
                for(ll j = 0 ; j < c.cols ; j++)
                    for(ll k = 0 ; k < a.cols ; k++)
                        c.mat[i][j] += a.mat[i][k] * b.mat[k][j];
        }
        else 
            throw "exception";
    }
    catch(...){
        cout<<"Error: could not apply arithematic operation on matrixes have diffrrent dimension.\n";
    }
    return c;
}

matrix operator/(matrix a , matrix b){
    matrix c(a.rows , b.cols);
    try{
        if(a.cols == b.rows){
            for(ll i = 0 ; i < c.rows ; i++)
                for(ll j = 0 ; j < c.cols ; j++)
                    for(ll k = 0 ; k < a.cols ; k++)
                        c.mat[i][j] += a.mat[i][k] / b.mat[k][j];
        }
        else 
            throw "exception";
    }
    catch(...){
        cout<<"Error: could not apply arithematic operation on matrixes have diffrrent dimension.\n";
    }
    return c;
}
