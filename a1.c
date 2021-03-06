
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
#include <String.h>

	/* number of lines in the input file */
int numberLevels = 0;

	/* flags used to control the appearance of the image */
int lineDrawing = 1;	// draw polygons as solid or lines
int lighting = 0;	// use diffuse and specular lighting
int smoothShading = 0;  // smooth or flat shading
double shapeList[10][22] = {{-1}};


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
	int currentIterator = 0, xRotate = 0, yRotate = 0, zRotate = 0;
	double xModifier = 0.0, yModifier = 0.0, zModifier = 0.0;

	/* example of drawing an object */
	/* remove the code after this line and replace it with assignment code */
	/* set colour of sphere */

	/* move to location for object then draw it */

	//write scale, rotate, then translate
	if(level >= 0 && level < numberLevels) {

		switch((int)shapeList[level][1]) {
			case 0:
				//blue
				//printf("Blue\n");
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);
				glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
				break;
			case 1:
				//red
				//printf("red\n");
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);
				glMaterialfv(GL_FRONT, GL_SPECULAR, red);
				break;
			case 2:
				//green
				//printf("green\n");
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, green);
				glMaterialfv(GL_FRONT, GL_SPECULAR, green);
				break;
			case 3:
				//white
				//printf("white\n");
				glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
				glMaterialfv(GL_FRONT, GL_SPECULAR, white);
				break;
		}

		glPushMatrix();


		glScalef(shapeList[level][16], shapeList[level][18], shapeList[level][20]);

		if(shapeList[level][10] != 0.0) {
			glRotatef(shapeList[level][10], 1, 0, 0);
		}
		if(shapeList[level][12] != 0.0) {
			glRotatef(shapeList[level][12], 0, 1, 0);
		}
		if(shapeList[level][14] != 0.0) {
			glRotatef(shapeList[level][14], 0, 0, 1);
		}
		

		glTranslatef(shapeList[level][4], shapeList[level][6], shapeList[level][8]);

		switch((int)shapeList[level][0]) {
			case 0:
				//Sphere
				//printf("Sphere\n\n");
				glutSolidSphere (shapeList[level][3], 30, 15);
				break;
			case 1:
				//cube
				//printf("Cube\n\n");
				glutSolidCube(shapeList[level][3]);
				break;
			case 2:
				//Torus
				//printf("Torus\n\n");
				glutSolidTorus(shapeList[level][3]/2, shapeList[level][3], 30, 30);
				break;
			case 3:
				//cone
				//printf("Cone\n\n");
				glutSolidCone(shapeList[level][3], shapeList[level][3], 30, 30);
				break;
		}

		drawObjects(level + 1, shapeList[level + 1][2]);
		currentIterator++;

		//This executes the iterators in each line (if any)
		while (currentIterator < numits) {

			glPushMatrix();

			xModifier = shapeList[level][16] + (shapeList[level][17] * currentIterator);
			yModifier = shapeList[level][18] + (shapeList[level][19] * currentIterator);
			zModifier = shapeList[level][20] + (shapeList[level][21] * currentIterator);
			glScalef(xModifier, yModifier, zModifier);

			xModifier = shapeList[level][10] + (shapeList[level][11] * currentIterator);
			yModifier = shapeList[level][12] + (shapeList[level][13] * currentIterator);
			zModifier = shapeList[level][14] + (shapeList[level][15] * currentIterator);
			if(xModifier != 0.0) {
				glRotatef(xModifier, 1, 0, 0);
			}
			if(yModifier != 0.0) {
				glRotatef(yModifier, 0, 1, 0);
			}
			if(zModifier != 0.0) {
				glRotatef(zModifier, 0, 0, 1);
			}
			
			xModifier = shapeList[level][4] + (shapeList[level][5] * currentIterator);
			yModifier = shapeList[level][6] + (shapeList[level][7] * currentIterator);
			zModifier = shapeList[level][8] + (shapeList[level][9] * currentIterator);
			glTranslatef(xModifier, yModifier, zModifier);

			switch((int)shapeList[level][0]) {
				case 0:
					//Sphere
					//printf("Sphere\n\n");
					glutSolidSphere (shapeList[level][3], 30, 15);
					break;
				case 1:
					//cube
					//printf("Cube\n\n");
					glutSolidCube(shapeList[level][3]);
					break;
				case 2:
					//Torus
					//printf("Torus\n\n");
					glutSolidTorus(shapeList[level][3]/2, shapeList[level][3], 30, 30);
					break;
				case 3:
					//cone
					//printf("Cone\n\n");
					glutSolidCone(shapeList[level][3], shapeList[level][3], 30, 30);
					break;
			}

			drawObjects(level + 1, shapeList[level + 1][2]);
			currentIterator++;
			glPopMatrix();
		}//end while
		glPopMatrix();
	}//end if

	else {
		//printf("\n\nEnd Reached!!!!!\n\n");
	}


}


void display (void) {

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	int level = 0;

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
	drawObjects(0,shapeList[0][2]);

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
char * buffer;
int count = 0, entry;

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
			if (instr[0] == '#') {
				//skip reading in line
			}

			else {
					entry = 0;
					buffer = strtok(instr, "\t ");

					while (buffer != NULL){
						shapeList[count][entry] = atof(buffer);
						//printf("%f\n", shapeList[count][entry]);
						entry++;
						buffer = strtok(NULL, "\t ");
					}
					//printf("\n");

					count++;
			}//end else
		}//end while
		
	}//end else
	fclose(fp);
	numberLevels = count;
	//printf("Count: %d\n", numberLevels);
	
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

