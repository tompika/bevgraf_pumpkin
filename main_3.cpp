#include <GL/glut.h>
#include <math.h>

#include "Matrix.h"
#include "Pumpkin.h"
#define pi 3.14159265359

GLsizei winWidth = 800, winHeight = 600;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);

    //skálázás
    std::vector<std::vector<double>> N{{50, 0, 0},
                                       {0, 50, 0},
                                       {0, 0, 1}};

    //forgatás
    double alfa = 45 * (pi / 180);
    std::vector<std::vector<double>> F{{cos(alfa), -(sin(alfa)), 0},
                                       {sin(alfa), cos(alfa), 0},
                                       {0, 0, 1}};
    //eltolás
    std::vector<std::vector<double>> T{{1, 0, 200},
                                       {0, 1, 200},
                                       {0, 0, 1}};

    std::vector<std::vector<double>> T2{{1, 0, 400},
                                        {0, 1, 400},
                                        {0, 0, 1}};

    std::vector<std::vector<double>> X{{1, 0, 0},
                                       {0, -1, 0},
                                       {0, 0, 1}};

    std::vector<std::vector<double>> Y{{-1, 0, 0},
                                       {0, 1, 0},
                                       {0, 0, 1}};

    std::vector<std::vector<double>> E{{1, 0, 0},
                                       {0, 1, 0},
                                       {0, 0, 1}};

    Matrix M_N = Matrix(3, 3, N);
    Matrix M_F = Matrix(3, 3, F);
    Matrix M_T = Matrix(3, 3, T);
    Matrix M_XYE = Matrix(3, 3, Y);

    Matrix M_T2 = Matrix(3, 3, T2);

    /*
    M_N.display();
    M_F.display();
    M_T.display();
    M_.display();
    */
    Pumpkin pmp = Pumpkin(M_N, M_F, M_T, M_XYE);
    Pumpkin pmp2 = Pumpkin(M_N, M_F, M_T2, M_XYE);

    pmp.draw();
    pmp2.draw();

    glutSwapBuffers();
}

void update(int n)
{

    glutPostRedisplay();

    glutTimerFunc(5, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(40, 40);
    glutCreateWindow("Pumpkin - Szilvacsku Peter");
    init();
    glutDisplayFunc(display);
    // glutKeyboardFunc( keyboard );
    //glutTimerFunc( 5, update, 0 );
    glutMainLoop();
    return 0;
}
