
/* Derived from scene.c in the The OpenGL Programming Guide */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* Linux Headers */
/*
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
*/

/* OSX Headers */
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "Shape.h"

	/* number of lines in the input file */
int numberLevels = 0;

	/* flags used to control the appearance of the image */
int lineDrawing = 1;	// draw polygons as solid or lines
int lighting = 0;	// use diffuse and specular lighting
int smoothShading = 0;  // smooth or flat shading
Shape * shapeList;


/*  Initialize material property and light source.
 */
void init (void)
{
   GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
   GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat light_full_off[] = {0.0, 0.0, 0.0, 1.0};
   GLfloat light_full_on[] = {1.0, 1.0, 1.0, 1.0};

   GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	/* if lighting is turned on then use ambient, diffuse and specular
	   lights, otherwise use ambient lighting only */
   if (lighting == 1) {
      glLightfv (GL_LIGHT0, GL_AMBIENT, light_ambient);
      glLightfv (GL_LIGHT0, GL_DIFFUSE, light_diffuse);
      glLightfv (GL_LIGHT0, GL_SPECULAR, light_specular);
   } else {
      glLightfv (GL_LIGHT0, GL_AMBIENT, light_full_on);
      glLightfv (GL_LIGHT0, GL_DIFFUSE, light_full_off);
      glLightfv (GL_LIGHT0, GL_SPECULAR, light_full_off);
   }
   glLightfv (GL_LIGHT0, GL_POSITION, light_position);
   
   glEnable (GL_LIGHTING);
   glEnable (GL_LIGHT0);
   glEnable(GL_DEPTH_TEST);
	/* needed to correct lightin when glScalef() isn't == 1 */
   glEnable(GL_NORMALIZE);
}

/* level is number of entries in the file, numits is the number of interations for each entry (column 3 on each
	line in the file  */
void drawObjects(int level, int numits) {
GLfloat blue[]  = {0.0, 0.0, 1.0, 1.0};
GLfloat red[]   = {1.0, 0.0, 0.0, 1.0};
GLfloat green[] = {0.0, 1.0, 0.0, 1.0};
GLfloat white[] = {1.0, 1.0, 1.0, 1.0};

	/* example of drawing an object */
	/* remove the code after this line and replace it with assignment code */
	/* set colour of sphere */
   glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
   glMaterialfv(GL_FRONT, GL_SPECULAR, white);
	/* move to location for object then draw it */
   glPushMatrix ();
   glTranslatef (0.75, 0.0, -1.0);
   glutSolidSphere (1.0, 30, 15);
    
   glTranslatef (2.0, 4.0, -2.0);
   glutSolidCube(2);
    
   glTranslatef (2.0, -4.0, 2.0);
   glutSolidSphere (1.0, 30, 15);
   
   glPopMatrix ();

}


void display (void) {

   glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* draw surfaces as either smooth or flat shaded */
   if (smoothShading == 1)
      glShadeModel(GL_SMOOTH);
   else
      glShadeModel(GL_FLAT);

	/* draw polygons as either solid or outlines */
   if (lineDrawing == 1)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
   else 
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/* give all objects the same shininess value */
   glMaterialf(GL_FRONT, GL_SHININESS, 30.0);

	/* set starting location of objects */
   glPushMatrix ();
   glRotatef(180.0, 1.0, 0.0, 0.0);
   glRotatef(180.0, 0.0, 1.0, 0.0);
   glRotatef(180.0, 0.0, 0.0, 1.0);
   glTranslatef(0.0, 0.0, -15.0);

	/* function which calls transformations and drawing of objects */
   drawObjects(0, 0);

   glPopMatrix ();

   glFlush ();
}

void reshape(int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   gluPerspective(45.0, (GLfloat)w/(GLfloat)h, 1.0, 50.0);
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ();
}

void keyboard(unsigned char key, int x, int y)
{
   switch (key) {
      case 27:
      case 'q':
         exit(0);
         break;
      case '1':		// draw polygons as outlines
         lineDrawing = 1;
         lighting = 0;
         smoothShading = 0;
         init();
         display();
         break;
      case '2':		// draw polygons as filled
         lineDrawing = 0;
         lighting = 0;
         smoothShading = 0;
         init();
         display();
         break;
      case '3':		// diffuse and specular lighting, flat shading
         lineDrawing = 0;
         lighting = 1;
         smoothShading = 0;
         init();
         display();
         break;
      case '4':		// diffuse and specular lighting, smooth shading
         lineDrawing = 0;
         lighting = 1;
         smoothShading = 1;
         init();
         display();
         break;
   }
}


	/* read data file and store in arrays */
void readFile(char **argv) {
FILE *fp;
char instr[1024];
int count = 0;

	/* open file and print error message if name incorrect */
   if ((fp = fopen(argv[1], "r")) == NULL) {
      printf("ERROR, could not open file.\n");
      printf("Usage: %s <filename>\n", argv[0]);
      exit(1);
   }

	/* the code to read the input file goes here */
	/* numlevels is set to the number of lines in the file not including the first comment line */
   else {
       while (fgets(instr, sizeof(instr), fp)) {
//           if (instr[0] == '#') {
//               //skip reading in line
//           }
//           else {
               printf("%s", instr);
               count++;
//           }
       }
       
   }
   fclose(fp);
    numberLevels = count;
    
}


/*  Main Loop
 *  Open window with initial window size, title bar, 
 *  RGBA display mode, and handle input events.
 */
int main(int argc, char** argv)
{
    
   readFile(argv);

   glutInit(&argc, argv);
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize (1024, 768);
   glutCreateWindow (argv[0]);

   init();

   glutReshapeFunc (reshape);
   glutDisplayFunc(display);
   glutKeyboardFunc (keyboard);

   glutMainLoop();
   return 0; 
}

