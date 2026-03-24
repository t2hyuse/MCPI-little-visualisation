//a little project to pass time
#include <iomanip>
#include <iostream>
#include <GLFW/glfw3.h>
#include <cmath>
#include <GL/gl.h>
#include <random>

#define PI 3.14159265358979323846

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;
constexpr double radius = 1;

double norm(const double x, const double y) {
    return sqrt(x*x+y*y);
}

void createCircle(int const segments, double const rad, const double x, const double y) {
    glBegin(GL_LINE_LOOP);
    glColor3d(0.0,1.0,0.0);
    for (int i = 0; i < segments; ++i) {
        glVertex2d(x+rad*std::cos(2*PI*i/segments),y+rad*std::sin(2*PI*i/segments));
    }
    glEnd();
}
using vecPair = std::vector<std::pair<double,double>>;

void addPoints(vecPair &points,double &success, double &total) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(0.0, 1.0) ;

    double x = dis(gen);
    double y = dis(gen);
    if (norm(x,y) < radius) {
        success++;
    }
    total++;
    points.insert(points.end(),{x,y});
}

void drawPoints(vecPair const &points) {
    for (const auto &[fst, snd] : points) {
        glBegin(GL_POINTS);
        glColor3d(1.0,0.0,0.0);
        glVertex2d(fst,snd);
        glEnd();
    }
}


int main() {

    vecPair pointsList;
    double total;
    double success;

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW3" << std::endl;
        return 1;
    }
        GLFWwindow* window{glfwCreateWindow(WIDTH,HEIGHT,"MCPI",nullptr,nullptr)};
        if (!window) {
            std::cerr << "Failed to create GLFW3" << std::endl;
            glfwTerminate();
            return -1;
        }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);
    int fbWidth{WIDTH}, fbHeight{HEIGHT};
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    glViewport(0, 0, fbWidth, fbHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    while (!glfwWindowShouldClose(window)) {
        glColor3d(0.0,0.0,0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        createCircle(100, 0.5, 0.5, 0.5);
        addPoints(pointsList,success,total);
        drawPoints(pointsList);
        if (static_cast<int>(total) % 5000 == 0 && total != 0) {
            std::cout << std::fixed << std::setprecision(10)
                      << 4.0 * success / total << std::endl;
        }
        if (static_cast<int>(total) % 40000 == 0 && total != 0) {
            pointsList.clear();
        }
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;


}