/**
    
    Pumpkin.h
    Bevgraf - 3. hazi

    @author Péter Szilvácsku
    @version 1.0 2016.11.10. 
*/

#ifndef PUMPKIN_H
#define PUMPKIN_H

#include "Matrix.h"

#include <iostream>
#include <vector>

class Pumpkin
{

    typedef struct point2d
    {
        GLfloat x, y;
    } POINT2D;

    POINT2D initPoint2D(GLfloat x, GLfloat y)
    {
        POINT2D P;
        P.x = x;
        P.y = y;
        return P;
    }

  public:
    std::vector<POINT2D> pumpkin;
    std::vector<POINT2D> eye1;
    std::vector<POINT2D> eye2;
    std::vector<POINT2D> mouth;
    std::vector<POINT2D> szar;

    Matrix N, F, T, XYE;
    Matrix M;

    /* 
        A = (0, 0.512)
        B = (0.454, 0.565)
        C = (0.815, 0.33)
        C_1 = (-0.182, 0.681)
        D = (0.907, -0.313)
        D_1 = (-0.063, 0.717)
        E = (0.411, -0.7)
        E_1 = (-0.202, -0.514)
        F = (0, -0.7)
        F_1 = (-0.069, -0.518)
        G = (-0.411, -0.7)
        G_1 = (-0.069, -0.395)
        H = (-0.907, -0.313)
        H_1 = (-0.2, -0.4)
        I = (-0.815, 0.33)
        J = (-0.454, 0.565)
        K = (-0.473, 0.045)
        L = (-0.155, 0.028)
        M = (-0.208, 0.32)
        N = (0.196, 0.038)
        O = (0.52, 0.055)
        P = (0.312, 0.356)
        Q = (-0.519, -0.226)
        R = (0.59, -0.13)
        S = (0.474, -0.505)
        T = (-0.324, -0.524)
        U = (0.358, -0.151)
        V = (0.196, -0.165)
        W = (0.216, -0.286)
        Z = (0.374, -0.269)*/

    Pumpkin(Matrix N, Matrix F, Matrix T, Matrix XYE)
    {

        int N_P = 10;
        GLdouble pump[N_P][2] = {0, 0.512,
                                 0.454, 0.565,
                                 0.815, 0.33,
                                 0.907, -0.313,
                                 0.411, -0.7,
                                 0, -0.7,
                                 -0.411, -0.7,
                                 -0.907, -0.313,
                                 -0.815, 0.33,
                                 -0.454, 0.565};

        GLdouble eye2[3][2] = {0.196, 0.038,
                               0.52, 0.055,
                               0.312, 0.356};

        GLdouble eye1[3][2] = {-0.473, 0.045,
                               -0.155, 0.028,
                               -0.208, 0.32};

        GLdouble mouth[12][2] = {-0.519, -0.226,
                                 -0.324, -0.524,
                                 -0.202, -0.514,
                                 -0.2, -0.4,
                                 -0.069, -0.395,
                                 -0.069, -0.518,
                                 0.474, -0.505,
                                 0.59, -0.13,
                                 0.358, -0.151,
                                 0.374, -0.269,
                                 0.216, -0.286,
                                 0.196, -0.165};

        GLdouble szar[3][2] = {0, 0.512,
                               -0.182, 0.681,
                               -0.063, 0.717};
        //Pumpkin poly
        for (int i = 0; i < N_P; i++)
        {
            POINT2D tmp = initPoint2D(pump[i][0], pump[i][1]);
            this->pumpkin.push_back(tmp);
        }

        //eye1, eye2, szar
        for (int i = 0; i < 3; i++)
        {
            POINT2D eye_1 = initPoint2D(eye1[i][0], eye1[i][1]);
            POINT2D eye_2 = initPoint2D(eye2[i][0], eye2[i][1]);
            POINT2D szar_ = initPoint2D(szar[i][0], szar[i][1]);

            //std::cout << eye_2.x << " -- " << eye_2.y << std::endl;

            this->eye1.push_back(eye_1);
            this->eye2.push_back(eye_2);
            this->szar.push_back(szar_);
        }

        for (int i = 0; i < 12; i++)
        {
            POINT2D mouth_ = initPoint2D(mouth[i][0], mouth[i][1]);
            this->mouth.push_back(mouth_);
        }

        this->N = N;
        this->F = F;
        this->T = T;
        this->XYE = XYE;

        /*  N.display();
        F.display();
        T.display();
        XYE.display();*/

        calculateM();

        transformation(M);
    }

    /* POINT2D skalaz(GLdouble x, GLdouble y, GLdouble n)
    {

        float M[3][3] = {n, 0, 0,
                         0, n, 0,
                         0, 0, 1};

        float temp[3] = {x, y, 1};

        float sum = 0;

        for (int i = 0; i < 3; i++)
            sum += M[0][i] * temp[i];

        x = sum;

        x = x / temp[2];

        sum = 0;

        for (int i = 0; i < 3; i++)
            sum += M[1][i] * temp[i];

        y = sum;
        y = y / temp[2];

        return initPoint2D(x, y);
    }

    POINT2D eltol(GLdouble x, GLdouble y, GLdouble u, GLdouble v)
    {

        float M[3][3] = {1, 0, u,
                         0, 1, v,
                         0, 0, 1};

        float temp[3] = {x, y, 1};

        float sum = 0;

        for (int i = 0; i < 3; i++)
            sum += M[0][i] * temp[i];

        x = sum;
        sum = 0;

        for (int i = 0; i < 3; i++)
            sum += M[1][i] * temp[i];

        y = sum;

        return initPoint2D(x, y);
    }
*/

    void calculateM()
    {

        M = T * (F * N * XYE);

        /*   
        F.display();
        N.display();
        XYE.display();
        T.display();
        */
    }

    void transformation(Matrix _M)
    {

        for (int i = 0; i < pumpkin.size(); i++)
        {

            double x = pumpkin[i].x;
            double y = pumpkin[i].y;

            double temp[3] = {x, y, 1};
            double sum = 0;

            for (int i = 0; i < 3; i++)
                sum += _M.data[0][i] * temp[i];

            x = sum;
            sum = 0;

            for (int i = 0; i < 3; i++)
                sum += _M.data[1][i] * temp[i];

            y = sum;

            pumpkin[i].x = x;
            pumpkin[i].y = y;
        }
        for (int i = 0; i < szar.size(); i++)
        {

            double x = szar[i].x;
            double y = szar[i].y;

            double temp[3] = {x, y, 1};
            double sum = 0;

            for (int i = 0; i < 3; i++)
                sum += _M.data[0][i] * temp[i];

            x = sum;
            sum = 0;

            for (int i = 0; i < 3; i++)
                sum += _M.data[1][i] * temp[i];

            y = sum;

            szar[i].x = x;
            szar[i].y = y;
        }

        for (int i = 0; i < eye1.size(); i++)
        {

            double x = eye1[i].x;
            double y = eye1[i].y;

            double temp[3] = {x, y, 1};
            double sum = 0;

            for (int i = 0; i < 3; i++)
                sum += _M.data[0][i] * temp[i];

            x = sum;
            sum = 0;

            for (int i = 0; i < 3; i++)
                sum += _M.data[1][i] * temp[i];

            y = sum;

            eye1[i].x = x;
            eye1[i].y = y;
        }

        for (int i = 0; i < eye2.size(); i++)
        {

            double x = eye2[i].x;
            double y = eye2[i].y;

            double temp[3] = {x, y, 1};
            double sum = 0;

            for (int i = 0; i < 3; i++)
                sum += _M.data[0][i] * temp[i];

            x = sum;

            sum = 0;

            for (int i = 0; i < 3; i++)
                sum += _M.data[1][i] * temp[i];

            y = sum;

            eye2[i].x = x;
            eye2[i].y = y;
        }

        for (int i = 0; i < mouth.size(); i++)
        {

            double x = mouth[i].x;
            double y = mouth[i].y;

            double temp[3] = {x, y, 1};
            double sum = 0;

            for (int i = 0; i < 3; i++)
                sum += _M.data[0][i] * temp[i];

            x = sum;
            sum = 0;

            for (int i = 0; i < 3; i++)
                sum += _M.data[1][i] * temp[i];

            y = sum;

            mouth[i].x = x;
            mouth[i].y = y;
        }
    }

    void draw()
    {
        //glColor3f(0.0, 0.0, 0.1);

        glLineWidth(1);

        glColor3f(1.000, 0.549, 0.000);
        glBegin(GL_POLYGON);

        for (int i = 0; i < pumpkin.size(); i++)
        {

            glVertex2d(pumpkin[i].x, pumpkin[i].y);
        }
        glEnd();

        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_POLYGON);
        for (int i = 0; i < eye1.size(); i++)
        {

            glVertex2d(eye1[i].x, eye1[i].y);
        }

        glEnd();

        glBegin(GL_POLYGON);
        for (int i = 0; i < eye2.size(); i++)
        {

            glVertex2d(eye2[i].x, eye2[i].y);
        }

        glEnd();

        glBegin(GL_POLYGON);
        for (int i = 0; i < mouth.size(); i++)
        {

            glVertex2d(mouth[i].x, mouth[i].y);
        }

        glEnd();

        //szár
        glColor3f(1.000, 0.549, 0.000);
        glBegin(GL_POLYGON);
        for (int i = 0; i < szar.size(); i++)
        {

            glVertex2d(szar[i].x, szar[i].y);
        }
        glEnd();

        glColor3f(0.000, 0.000, 0.000);
    }
};

#endif
