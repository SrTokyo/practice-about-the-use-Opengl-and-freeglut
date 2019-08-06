
////same as gl4 with changes in reshape function to see orthographic projection
///* Global variables */
//const char* title = "3D Shapes with animation";
//GLfloat anglePyramid = 0.0f;  // Rotational angle for pyramid [NEW]
//GLfloat angleCube = 0.0f;     // Rotational angle for cube [NEW]
//int refreshMills = 15;        // refresh interval in milliseconds [NEW]
////We define two global variables to keep track of the current rotational angles of the cube and pyramid. 
////We also define the refresh period as 15 msec (66 frames per second).
///* Initialize OpenGL Graphics */
//void initGL() {
//	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
//	glClearDepth(1.0f);                   // Set background depth to farthest
//	glEnable(GL_DEPTH_TEST);   // Enable depth testing for z-culling
//	glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
//	glShadeModel(GL_SMOOTH);   // Enable smooth shading
//	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Nice perspective corrections
//}
///* Handler for window-repaint event. Called back when the window first appears and
//   whenever the window needs to be re-painted. */
//void display() {
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
//	glMatrixMode(GL_MODELVIEW);     // To operate on model-view matrix
//	// Render a color-cube consisting of 6 quads with different colors
//	glLoadIdentity();                 // Reset the model-view matrix
//	glTranslatef(1.5f, 0.0f, -7.0f);  // Move right and into the screen
//	glRotatef(angleCube, 0.0f, 0.0f, 1.0f);  // Rotate about (1,1,1)-axis [NEW]
//	//play with values above
//	glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
//	   // Top face (y = 1.0f)
//	   // Define vertices in counter-clockwise (CCW) order with normal pointing out
//	glColor3f(0.0f, 1.0f, 0.0f);     // Green
//	glVertex3f(1.0f, 1.0f, -1.0f);
//	glVertex3f(-1.0f, 1.0f, -1.0f);
//	glVertex3f(-1.0f, 1.0f, 1.0f);
//	glVertex3f(1.0f, 1.0f, 1.0f);
//	// Bottom face (y = -1.0f)
//	glColor3f(1.0f, 0.5f, 0.0f);     // Orange
//	glVertex3f(1.0f, -1.0f, 1.0f);
//	glVertex3f(-1.0f, -1.0f, 1.0f);
//	glVertex3f(-1.0f, -1.0f, -1.0f);
//	glVertex3f(1.0f, -1.0f, -1.0f);
//	// Front face  (z = 1.0f)
//	glColor3f(1.0f, 0.0f, 0.0f);     // Red
//	glVertex3f(1.0f, 1.0f, 1.0f);
//	glVertex3f(-1.0f, 1.0f, 1.0f);
//	glVertex3f(-1.0f, -1.0f, 1.0f);
//	glVertex3f(1.0f, -1.0f, 1.0f);
//	// Back face (z = -1.0f)
//	glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
//	glVertex3f(1.0f, -1.0f, -1.0f);
//	glVertex3f(-1.0f, -1.0f, -1.0f);
//	glVertex3f(-1.0f, 1.0f, -1.0f);
//	glVertex3f(1.0f, 1.0f, -1.0f);
//	// Left face (x = -1.0f)
//	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//	glVertex3f(-1.0f, 1.0f, 1.0f);
//	glVertex3f(-1.0f, 1.0f, -1.0f);
//	glVertex3f(-1.0f, -1.0f, -1.0f);
//	glVertex3f(-1.0f, -1.0f, 1.0f);
//	// Right face (x = 1.0f)
//	glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
//	glVertex3f(1.0f, 1.0f, -1.0f);
//	glVertex3f(1.0f, 1.0f, 1.0f);
//	glVertex3f(1.0f, -1.0f, 1.0f);
//	glVertex3f(1.0f, -1.0f, -1.0f);
//	glEnd();  // End of drawing color-cube
//	// Render a pyramid consists of 4 triangles
//	glLoadIdentity();                  // Reset the model-view matrix
//	glTranslatef(-1.5f, 0.0f, -6.0f);  // Move left and into the screen
//	glRotatef(anglePyramid, 1.0f, 1.0f, 0.0f);  // Rotate about the (1,1,0)-axis [NEW]
//	glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
//	   // Front
//	glColor3f(1.0f, 0.0f, 0.0f);     // Red
//	glVertex3f(0.0f, 1.0f, 0.0f);
//	glColor3f(0.0f, 1.0f, 0.0f);     // Green
//	glVertex3f(-1.0f, -1.0f, 1.0f);
//	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//	glVertex3f(1.0f, -1.0f, 1.0f);
//	// Right
//	glColor3f(1.0f, 0.0f, 0.0f);     // Red
//	glVertex3f(0.0f, 1.0f, 0.0f);
//	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//	glVertex3f(1.0f, -1.0f, 1.0f);
//	glColor3f(0.0f, 1.0f, 0.0f);     // Green
//	glVertex3f(1.0f, -1.0f, -1.0f);
//	// Back
//	glColor3f(1.0f, 0.0f, 0.0f);     // Red
//	glVertex3f(0.0f, 1.0f, 0.0f);
//	glColor3f(0.0f, 1.0f, 0.0f);     // Green
//	glVertex3f(1.0f, -1.0f, -1.0f);
//	glColor3f(0.0f, 0.0f, 1.0f);     // Blue
//	glVertex3f(-1.0f, -1.0f, -1.0f);
//	// Left
//	glColor3f(1.0f, 0.0f, 0.0f);       // Red
//	glVertex3f(0.0f, 1.0f, 0.0f);
//	glColor3f(0.0f, 0.0f, 1.0f);       // Blue
//	glVertex3f(-1.0f, -1.0f, -1.0f);
//	glColor3f(0.0f, 1.0f, 0.0f);       // Green
//	glVertex3f(-1.0f, -1.0f, 1.0f);
//	glEnd();   // Done drawing the pyramid
//	glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
//	// Update the rotational angle after each refresh [NEW]
//	anglePyramid += 0.2f;
//	angleCube -= 0.15f;
//}
///* Called back when timer expired and over again.
//To perform animation, we define a function called timer(),
//which posts a re-paint request to activate display() when the timer expired,
//and then run the timer again. In main(), we perform the first timer() call via
//glutTimerFunc(0, timer, 0).
//*/
//void timer(int value) {
//	glutPostRedisplay();      // Post re-paint request to activate display()
//	glutTimerFunc(refreshMills, timer, 0); // next timer call milliseconds later
//}
///* Handler for window re-size event. Called back when the window first appears and
//   whenever the window is re-sized with its new width and height */
//void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
//   // Compute aspect ratio of the new window
//	if (height == 0) height = 1;                // To prevent divide by 0
//	GLfloat aspect = (GLfloat)width / (GLfloat)height;
//	// Set the viewport to cover the new window
//	glViewport(0, 0, width, height);
//	// Set the aspect ratio of the clipping volume to match the viewport
//	glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
//	glLoadIdentity();             // Reset
//
//	// Enable perspective projection with fovy, aspect, zNear and zFar
//	//gluPerspective(45.0f, aspect, 0.1f, 100.0f);
//	// or using Orthographic projection, I commented line of code above to see difference
//
//	// Set up orthographic projection view [NEW]
//	//we set the cross-section of view-volume according to the aspect ratio of the viewport, 
//	//and depth from 0.1 to 100, corresponding to z=-0.1 to z=-100
//	if (width >= height) {
//		// aspect >= 1, set the height from -1 to 1, with larger width
//		glOrtho(-3.0 * aspect, 3.0 * aspect, -3.0, 3.0, 0.1, 100);
//	}
//	else {
//		// aspect < 1, set the width to -1 to 1, with larger height
//		glOrtho(-3.0, 3.0, -3.0 / aspect, 3.0 / aspect, 0.1, 100);
//	}
//}
///* Main function: GLUT runs as a console application starting at main() */
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);            // Initialize GLUT
//	glutInitDisplayMode(GLUT_DOUBLE); // Enable double buffered mode
//	glutInitWindowSize(640, 480);   // Set the window’s initial width & height
//	glutInitWindowPosition(50, 50); // Position the window’s initial top-left corner
//	glutCreateWindow(title);          // Create window with the given title
//	glutDisplayFunc(display);       // Register callback handler for window re-paint event
//	glutReshapeFunc(reshape);       // Register callback handler for window re-size event
//	initGL();                       // Our own OpenGL initialization
//	glutTimerFunc(0, timer, 0);     // First timer call immediately [NEW]
//	glutMainLoop();                 // Enter the infinite event-processing loop
//	return 0;
//}

//#include <GL/freeglut.h>
//
//
//enum class ProjectionType
//{
//	Default3D,
//	My2D,
//	My3D
//};
//ProjectionType myProjectionType;//to know what kind of drawing positions should be considered
////The idea is to initialize always first
//void init()
//{
//	glClearColor(1.0, 1.0, 1.0, 0.0);//Set display window color to white
//	glPointSize(10);//Setting the size of points, must be here otherwise not working
//	switch (myProjectionType)
//	{
//	case ProjectionType::My2D:
//	{
//		glMatrixMode(GL_PROJECTION);
//		gluOrtho2D(0, 200, 0, 150);//note here dimensions of ortho not similar to window but it resizes
//		break;
//	}
//	case ProjectionType::My3D:
//	{
//		break;
//	}
//	case ProjectionType::Default3D:
//	default:
//		break;
//	}
//}
//void square()
//{
//	// Draw a Red 1x1 Square centered at origin
//	glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
//		glColor3f(1.0f, 0.0f, 0.0f); // Red color 
//		switch (myProjectionType)
//		{
//		case ProjectionType::My2D:
//		{
//			glVertex2i(10, 145);    // x, y
//			glVertex2i(180, 145);
//			glVertex2i(180, 15);
//			glVertex2i(10, 15);
//			break;
//		}
//
//		case ProjectionType::My3D:
//			break;
//		case ProjectionType::Default3D:
//		default:
//		{
//			glVertex2f(-0.5f, -0.5f);    // x, y
//			glVertex2f(0.5f, -0.5f);
//			glVertex2f(0.5f, 0.5f);
//			glVertex2f(-0.5f, 0.5f);
//			break;
//		}
//		}
//
//	glEnd();
//	glFlush();  // Render now, processing all OPENGL routines ASAP
//}
//void lineSegment()
//{
//	// Draw a line 
//	glBegin(GL_LINES);
//		glColor3f(0.0f, 0.0f, 1.0f);
//		switch (myProjectionType)
//		{
//		case ProjectionType::My2D:
//		{
//			glVertex2i(180, 15); // x, y
//			glVertex2i(10, 145);    // Specify line segment geometry 
//			break;
//		}
//		case ProjectionType::My3D:
//			break;
//		case ProjectionType::Default3D:
//		default:
//		{
//			glVertex2f(-0.5f, -0.5f); // x, y
//			glVertex2f(0.5f, 0.5f);    // Specify line segment geometry 
//			break;
//		}
//		}
//
//	glEnd();
//	glFlush();  // Render now, processing all OPENGL routines ASAP
//}
//void point()
//{
//		// Draw a point with the center of the screen as origin
//		glBegin(GL_POINTS);
//			glColor3f(0.0f, 1.0f, 0.0f);
//			switch (myProjectionType)
//			{
//			case ProjectionType::My2D:
//			{
//				glVertex2i(10, 145);
//				glVertex2i(0, 0);
//				break;
//			}
//			case ProjectionType::My3D:
//				break;
//			case ProjectionType::Default3D:
//			default:
//			{
//				glVertex2f(-0.5f, -0.5f);
//				glVertex2f(0.0, 0.0f);
//				break;
//			}
//			}
//		glEnd();
//		glFlush();  // Render now, processing all OPENGL routines ASAP
//	}
//void display()
//{
//	glClear(GL_COLOR_BUFFER_BIT);//Clear display window with the color we set in the init procedure. 
//
//	square();
//
//	lineSegment();
//	point();
//}
//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);// Initialize GLUT
//	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Enable single buffered mode
//	glutCreateWindow("Primero");//Window with title);
//
//	glutInitWindowPosition(0, 0); // Position the window’s initial top-left corner
//	glutInitWindowSize(640, 480);   // Set the window’s initial width & height
//	myProjectionType = ProjectionType::My2D;
//	init();//execute initilization procedure
//	glutDisplayFunc(display);// Register callback handler for window re-paint event
//	glutMainLoop();// Enter the infinite event-processing loop
//	return 0;
//}
//int main(int argc, char** argv) {
//	glutInit(&argc, argv);            // Initialize GLUT
//	glutInitDisplayMode(GLUT_SINGLE); // Enable double buffered mode
//	glutInitWindowSize(640, 480);   // Set the window’s initial width & height
//	glutInitWindowPosition(0, 0); // Position the window’s initial top-left corner
//	glutCreateWindow("Primero"); 
//	myProjectionType = ProjectionType::Default3D;
//	init();
//	glutDisplayFunc(display);
//	glutMainLoop();
//	return 0;
// }