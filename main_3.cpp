#include <GL/glut.h>
#include <math.h>

#include "Matrix.h"
#include "Pumpkin.h"
#define pi 3.14159265359

GLsizei winWidth = 800, winHeight = 600;

std::vector<Pumpkin> all;

void init()
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0, winWidth, 0.0, winHeight);
    glShadeModel(GL_FLAT);
}

double rand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
};

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);

    for(int i = 0; i< all.size(); i++)
        all[i].draw();

    glutSwapBuffers();
}

void update(int n)
{

    //skálázás
    double NN = (int)rand(10,100);
    std::vector<std::vector<double>> N{{NN, 0, 0},
                                       {0, NN, 0},
                                       {0, 0, 1}};

    //forgatás
    double szog = rand(90,-90);
    double alfa = szog * (pi / 180);
    std::vector<std::vector<double>> F{{cos(alfa), -(sin(alfa)), 0},
                                       {sin(alfa), cos(alfa), 0},
                                       {0, 0, 1}};
    //eltolás
    double TT = rand(50,700);
    double TT2 = rand(50,500);
    std::vector<std::vector<double>> T{{1, 0, TT},
                                       {0, 1, TT2},
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

    Matrix N_ = Matrix(3, 3, N);
    Matrix F_ = Matrix(3, 3, F);
    Matrix T_ = Matrix(3, 3, T);

    Matrix XYE_ ;

    int num = rand()%3+1;

    if(num == 1){
        XYE_ = Matrix(3, 3, E);
    }
    else if(num == 2){
        XYE_ = Matrix(3, 3, X);
    }
    else
    {
        XYE_ = Matrix(3, 3, Y);
    }

    

    all.push_back(Pumpkin(N_, F_, T_, XYE_));
    std::cout << all.size() << std::endl;






    glutPostRedisplay();

    glutTimerFunc(500, update, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        all.clear();
        std::cout << ">> RESET <<" << std::endl;
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
    glutKeyboardFunc( keyboard );
    glutTimerFunc( 500, update, 0 );
    glutMainLoop();
    return 0;
}
