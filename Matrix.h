/**
    
    Matrix.h
    Bevgraf - 3. hazi

    @author Péter Szilvácsku
    @version 1.0 2016.11.10. 
*/

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>

class Matrix
{

  public:
    double **data;
    int m, n;

    Matrix()
    {
        this->n = 3;
        this->m = 3;

        data = new double *[n];
        for (int i = 0; i < n; i++)
            data[i] = new double[m];
    }

    Matrix(int n, int m, std::vector<std::vector<double>> data_)
    {
        this->n = n;
        this->m = m;
        data = new double *[n];
        for (int i = 0; i < n; i++)
            data[i] = new double[m];

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                data[i][j] = data_[i][j];
            }
        }
    }

    /*  ~Matrix()
    {
        for (int i = 0; i < n; i++)
            delete data[i];
        delete data;
    }*/

    Matrix operator*(const Matrix &T)
    {

        Matrix A;
        Matrix B;
        Matrix C;

        A.data = data;

        B.data = T.data;

        int i, j, k;

        float sum;

        for (i = 0; i < 3; i++)
            for (j = 0; j < 3; j++)
            {
                sum = 0;
                for (k = 0; k < 3; k++)
                    sum = sum + A.data[i][k] * B.data[k][j];
                C.data[i][j] = sum;
            }

        return C;
    }

    void display()
    {

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                std::cout << data[i][j] << "\t";
            }
            std::cout << std::endl;
        }
    }
};

#endif
