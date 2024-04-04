#define GL_SILENCE_DEPRECATION // GL library is outdated on my mac, use this to silence warnings
#include <GLUT/glut.h> // Macbook specific
// #include <GL/glut.h> // use if running from windows
#include <cmath>
#include <vector>


// Function to compute drag coefficient (cd) as a function of alpha
double computeCD(double alpha) {
    double epsilon = 1.0 / 1.0; // t/c = 1/1 = 1
    double M = 1.2; // Mach number
    return 4 * (pow(alpha, 2) + pow(epsilon, 2)) / sqrt(pow(M, 2) - 1);
}

// Function to display
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.53, 0.81, 0.98); // Light sky blue color
    glLoadIdentity();

    // Adjust window size to fit CD values
    gluOrtho2D(-2.0, 22.0, -2.0, 2000.0);

    // Draw x-axis
    glBegin(GL_LINES);
    glVertex2f(0.1, 0.1);
    glVertex2f(20.1, 0.1);
    glEnd();

    // Draw y-axis
    glBegin(GL_LINES);
    glVertex2f(0.1, 0.1);
    glVertex2f(0.1, 2000.1);
    glEnd();

    // Draw axis labels
    glColor3f(1.0, 1.0, 1.0); // Set color to white
    glRasterPos2f(20.0, -1.5); // Adjusted x-axis label position
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'a'); // Label for x-axis

    glRasterPos2f(-1.5, 1900.0); // Adjusted y-axis label position
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'c'); // Label for y-axis
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, 'd');

    // Compute CD values for alpha from 0 to 18 degrees
    glBegin(GL_LINE_STRIP);
    for (int alpha = 0; alpha <= 18; ++alpha) {
        double CD = computeCD(alpha);
        glVertex2f(alpha, CD);
    }
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600); // Set initial window size
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Question 4: cd vs. alpha");

    // Set the display function
    glutDisplayFunc(display);

    // Start the GLUT event loop
    glutMainLoop();

    return 0;
}