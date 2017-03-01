/*
  END SEMESTER PROJECT:  GAME CALLED TAKE OVER PANKHAS
  GROUP MEMBERS:
  1. MUHAMMAD IBTESAM
  2. HAMZA JAVED
  3. ASAD SALMAN

  CLASS: BESE-5B
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "glut.h"
#include <Windows.h>
#include <conio.h>


//for drawing circle
void DrawCircle(float cx, float cy, float r, int num_segments, float re, float gr, float bl)
{
	glColor3f(re, gr, bl);
	glBegin(GL_LINE_LOOP);
	for (int ii = 0; ii < num_segments; ii++)
	{
		float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);  //get the current angle 

		float x = r * cosf(theta);  //calculate the x component 
		float y = r * sinf(theta);  //calculate the y component 

		glVertex2f(x + cx, y + cy);//output vertex 

	}
	glEnd();
}


//for drawing rectangles
void DrawRectangle(int x, int y, int length, int breadth, float re, float gr, float bl){
	glColor3f(re, gr, bl);
	glBegin(GL_LINE_LOOP);

	glVertex2f(x, y);
	glVertex2f(x + length, y);
	glVertex2f(x + length, y + breadth);
	glVertex2f(x, y + breadth);

	glEnd();

}

float increase(float place, float destin, float loops){
	destin = destin - place;
	destin = destin / loops;
	return destin;
}


//for printing things in window
void renderBitmapString(float x, float y, float z, void *font, char *string) {
	char *c;
	glRasterPos3f(x, y, z);
	for (c = string; *c != '\0'; c++) {
		glutBitmapCharacter(font, *c);
	}
}


int g_Width = 400;		//define size of the window
int g_Height = 400;


int mouse_X = 0;	 //for storing mouse position
int mouse_Y = 0;


void init();
void myMouseFunction(int button, int state, int mouseX, int mouseY);
void myKeyboardFunction(unsigned char key, int mouseX, int mouseY);
void mySpecialKeysFunction(int key, int x, int y);
void myReshapeFunction(int width, int height);
void myTimerFunction(int val);
void myDisplayFunction();




int main(int argc, char** argv)
{
	glutInit(&argc, argv);		//initilize the GLUT libraray

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);		//has four colour components red, green,blue, and alpha 
	glutInitWindowSize(800, 600);	//size of window
	glutInitWindowPosition(200, 100);		//poistion of window
	glutCreateWindow("Take Over Pankhas");

	//PlaySound(L"C:\\Users\\EXTRA\\Desktop\\darthgimp.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	 
	init();

	glutMouseFunc(myMouseFunction);
	glutKeyboardFunc(myKeyboardFunction);
	glutSpecialFunc(mySpecialKeysFunction);

	glutReshapeFunc(myReshapeFunction);


	glutDisplayFunc(myDisplayFunction);


	glutTimerFunc(33, myTimerFunction, 0);

	glutMainLoop();

	return 0;
}



void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);		//background color of openGl window
	//			 ^red, green, blue, alpha(opaquenss) 
	glMatrixMode(GL_PROJECTION);		//glMatrixMode ? specify which matrix is the current matrix ????
	glLoadIdentity();		//glLoadIdentity ? replace the current matrix with the identity matrix	????

	glOrtho(0.0, g_Width, 0.0, g_Height, -1.0, 1.0);	//set (0,0) on left top
}


void myMouseFunction(int button, int state, int mouseX, int mouseY)
{
	mouse_X = mouseX;
	mouse_Y = mouseY;


	if (state == 0) //Click
	{
		printf("mouse clicked \n");
		printf("\nmouseX: %d mouseY: %d, State: %d", mouseX, mouseY, state);
	}

}


void myKeyboardFunction(unsigned char key, int mouseX, int mouseY)
{
	//if( key == '4' ) // i.e.left
	//{
	//	mouse_X=mouse_X-5;
	//	mouse_Y=mouse_Y;
	//	printf("\nmouseX: %d mouseY: %d",mouseX,mouseY);
	//}

}


void mySpecialKeysFunction(int key, int x, int y)
{
	/*switch( key )
	{
	case GLUT_KEY_UP:
	mouse_X=mouse_X;
	mouse_Y=mouse_Y-5;

	break;
	}*/
}


void myReshapeFunction(int width, int height)
{
	glClear(GL_COLOR_BUFFER_BIT);

	g_Width = width;
	g_Height = height;

	glViewport(0, 0, g_Width, g_Height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, g_Width, g_Height, 0.0, -1.0, 1.0);	//change the (0,0) to top left
}


void myTimerFunction(int val)
{
	glutTimerFunc(50, myTimerFunction, 0);

	myDisplayFunction();

}


int time = 0;   //used for timing things like growth rate etc.   


struct circle{
	int stay; //value that stays in circle
	int transfer; //value that is transferred
	float stayX;  //XY-Coordinate of stay
	float stayY;
	float transX;  //XY-Coordinate of transfer
	float transY;
	int vanish;  //checks if a circle is active
	int path; //checks path
};


struct feature{
	float featX;
	float featY;
};


struct ClickCir{
	int activate;
	int target;
	int activate2;
};


circle Cir1 = { 100, 50, 200, 200, 200, 200, 0, 0 };

circle Cir2 = { 80, 25, 450, 450, 450, 450, 0, 0 };

circle Cir3 = { 60, 30, 490, 255, 490, 255, 0, 0 };

circle Cir4;

ClickCir Circl1;
ClickCir Circl3;

int level = 0, tutorial = 1, tucheck = 1;

int compturn = 1;

feature Dualc1, Dualc3, Dualc2, Dualc4;


void myDisplayFunction()
{


	glClear(GL_COLOR_BUFFER_BIT);		//clears the screen after display

	if (level == 0){
		//Main Menu
		
		glColor3f(5, 4, 3);
		renderBitmapString(250, 60, 0, GLUT_BITMAP_TIMES_ROMAN_24, "TAKE OVER PANKHAS");

		//draws rectangles for stuff
		DrawRectangle(250, 140, 200, 50, 1, 1, 0);
		DrawRectangle(250, 200, 200, 50, 1, 1, 0);
		DrawRectangle(250, 260, 200, 50, 1, 1, 0);
		DrawRectangle(250, 320, 200, 50, 1, 1, 0);
	

		glColor3f(0, 0, 1);
		renderBitmapString(310, 90, 0, GLUT_BITMAP_TIMES_ROMAN_24, "DEMO!");

		glColor3f(3, 0, 0);
		renderBitmapString(270, 180, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Tutorial Level.");  //writes this in the box

		renderBitmapString(310, 230, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Level  1"); //writes this in the other box

		renderBitmapString(310, 290, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Level  2"); //writes this in the other box

		renderBitmapString(310, 350, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Level  3"); //writes this in the other box

		if (mouse_X > 250 && mouse_X < 450 && mouse_Y>140 && mouse_Y < 190)
			level = 1; //gives value on clicking

		if (mouse_X > 250 && mouse_X < 450 && mouse_Y>200 && mouse_Y < 250){
			level = 2; //gives value on clicking

			Cir1 = { 80, 50, 200, 350, 200, 350, 0, 0 };

			Cir2 = { 120, 25, 420, 490, 420, 490, 0, 0 };

			Cir3 = { 60, 30, 520, 195, 520, 195, 0, 0 };


		}

		if (mouse_X > 250 && mouse_X < 450 && mouse_Y>260 && mouse_Y < 310){
			level = 3;

			Cir1 = { 100, 50, 300, 200, 300, 200, 0, 0 };

			Cir2 = { 320, 25, 450, 450, 450, 450, 0, 0 };

			Cir3 = { 80, 30, 470, 240, 470, 240, 0, 0 };



		}

		if (mouse_X > 250 && mouse_X < 450 && mouse_Y>320 && mouse_Y < 370){
			level = 4;

			Cir1 = { 110, 50, 300, 190, 300, 190, 0, 0 };

			Cir2 = { 120, 25, 450, 450, 450, 450, 0, 1 };

			Cir3 = { 120, 30, 470, 240, 470, 240, 0, 0 };

			Cir4 = { 100, 50, 320, 460, 320, 460, 0, 1 };


		}

		
	}

	if (level == 1){  //if level is 1, it goes to this, this is the code for the tutorial


		glColor3f(5, 0, 3);
		renderBitmapString(350, 60, 0, GLUT_BITMAP_TIMES_ROMAN_24, "TUTORIAL!");

		if (tutorial == 1){
			glColor3f(5, 4, 3);

			renderBitmapString(45, 80, 0, GLUT_BITMAP_9_BY_15, "Click the green circle, and then the red circle to see what happens.");

			if (Cir1.vanish == 0)         //draws first circle if it's not gone
				DrawCircle(210, 196, 30, 50, 0, 5, 0);

			if (Cir2.vanish == 0)   //draws second circle if it's not gone
				DrawCircle(465, 446, 30, 50, 4, 0, 0);

			if (Cir1.vanish == 0){
				char printC1[] = "foo";     //prints values for first circle if it still exists
				sprintf(printC1, "%3d", Cir1.stay);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir1.stayX, Cir1.stayY, 0, GLUT_BITMAP_8_BY_13, printC1);
			}


			if (Cir2.vanish == 0){
				char printC2[] = "foo";    //prints value for second circle if it still exists
				sprintf(printC2, "%3d", Cir2.stay);
				glColor3f(2, 0, 2);
				renderBitmapString(Cir2.stayX, Cir2.stayY, 0, GLUT_BITMAP_8_BY_13, printC2);
			}

			if (mouse_X > 180 && mouse_X < 250 && mouse_Y>160 && mouse_Y < 230 && Cir1.vanish == 0 && Cir1.path == 0){
				Circl1.activate = 1; //sensing first click                           ^Checks if it exists
				//Circl1.activate2 = 1;
			}

			if (Circl1.activate == 1){
				if (mouse_X > 430 && mouse_X < 500 && mouse_Y>415 && mouse_Y < 470 && Cir2.vanish == 0){
					Circl1.target = 1;  //sensing second click                          ^checks if it exists
					Cir1.path = 1;
				}
			}

			if (Circl1.target == 1 && Cir1.vanish == 0)
				Circl1.activate = 0;  //re initialises this bad boy.


			if (Circl1.target == 1 && Cir1.path == 1 && Cir1.vanish == 0){    //if target has been pressed, this happens

				if (Cir1.transX != Cir2.stayX){  //checks if the moving point, is the same as the target point

					if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
						Cir1.transfer = Cir1.stay / 2;


					char printC1trans[] = "foo";        //for printing values on glwindow
					sprintf(printC1trans, "%3d", Cir1.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

					if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
						Cir1.stay = Cir1.stay / 2;

					Cir1.transX += increase(Cir1.stayX, Cir2.stayX, 100);   //for moving the moving point trans
					Cir1.transY += increase(Cir1.stayY, Cir2.stayY, 100);
				}

				else {   //otherwise if moving point reaches target this happens

					Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
					Cir1.transY = Cir1.stayY;

					Circl1.target = 0;  //turns the click target back 0, so that we can attack again              

					Cir2.stay = Cir2.stay - Cir1.transfer;   //reduces the value of target.

					if (Cir2.stay < 1){
						Cir2.vanish = 1;   //if target value is less than 1, it is vanished.
					}

					Cir1.path = 0;

					tucheck = 2;
				}
			}


			if (tucheck == 2){
				DrawRectangle(150, 500, 150, 50, 0, 4, 2);
				renderBitmapString(151, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "NEXT");

				if (mouse_X > 150 && mouse_X < 300 && mouse_Y>500 && mouse_Y < 550){

					Cir1 = { 100, 50, 200, 200, 200, 200, 0, 0 };

					Cir2 = { 80, 25, 450, 450, 450, 450, 0, 0 };

					Cir3 = { 60, 30, 490, 255, 490, 255, 0, 0 };

					tutorial = 2;
					tucheck = 1;
					compturn = 1;

					Circl1 = { 0, 0, 0 };
					Circl3 = { 0, 0, 0 };
				}
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////// FOR               RETURN                   BUTTON                /////////////////////////
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			DrawRectangle(500, 500, 150, 50, 0, 4, 2);
			renderBitmapString(520, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "RETURN");


			if (mouse_X > 500 && mouse_X < 650 && mouse_Y>500 && mouse_Y < 550){
				level = 0;

				Cir1 = { 100, 50, 200, 200, 200, 200, 0, 0 };

				Cir2 = { 80, 25, 450, 450, 450, 450, 0, 0 };

				Cir3 = { 60, 30, 490, 255, 490, 255, 0, 0 };
				tucheck = 1;
				compturn = 1;
				tutorial = 1;

				Circl1 = { 0, 0, 0 };
				Circl3 = { 0, 0, 0 };

			}
		}

		if (tutorial == 2){
			glColor3f(5, 4, 3);

			renderBitmapString(45, 80, 0, GLUT_BITMAP_9_BY_15, "Click circle 1 and then circle 2, and see what happens.");

			renderBitmapString(200, 160, 0, GLUT_BITMAP_9_BY_15, "1");

			renderBitmapString(500, 195, 0, GLUT_BITMAP_9_BY_15, "2");

			if (Cir1.vanish == 0)         //draws first circle if it's not gone
				DrawCircle(210, 196, 30, 50, 0, 5, 0);

			if (Cir3.vanish == 0)  //draws third circle if it's not gone
				DrawCircle(506, 245, 45, 50, 0, 5, 0);

			if (Cir1.vanish == 0){
				char printC1[] = "foo";     //prints values for first circle if it still exists
				sprintf(printC1, "%3d", Cir1.stay);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir1.stayX, Cir1.stayY, 0, GLUT_BITMAP_8_BY_13, printC1);
			}



			if (Cir3.vanish == 0){
				char printC3[] = "foo";   //print value for third circle if it still exists
				sprintf(printC3, "%3d", Cir3.stay);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir3.stayX, Cir3.stayY, 0, GLUT_BITMAP_8_BY_13, printC3);
			}



			if (mouse_X > 180 && mouse_X < 250 && mouse_Y>160 && mouse_Y < 230 && Cir1.vanish == 0 && Cir1.path == 0){
				Circl1.activate = 1; //sensing first click                           ^Checks if it exists
				//Circl1.activate2 = 1;
			}

			if (Circl1.activate == 1){
				if (mouse_X > 460 && mouse_X < 550 && mouse_Y>200 && mouse_Y < 290 && Cir3.vanish == 0){
					Circl1.target = 1;  //sensing second click                          ^checks if it exists
					Cir1.path = 2;
				}
			}

			if (Circl1.target == 1 && Cir1.vanish == 0)
				Circl1.activate = 0;  //re initialises this bad boy.


			if (Circl1.target == 1 && Cir1.path == 2 && Cir1.vanish == 0){    //if target has been pressed, this happens

				if ((int)Cir1.transX < (int)Cir3.stayX){  //checks if the moving point, is the same as the target point

					if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
						Cir1.transfer = Cir1.stay / 2;


					char printC1trans[] = "foo";        //for printing values on glwindow
					sprintf(printC1trans, "%3d", Cir1.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

					if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
						Cir1.stay = Cir1.stay / 2;

					Cir1.transX += increase(Cir1.stayX, Cir3.stayX, 50);   //for moving the moving point trans
					Cir1.transY += increase(Cir1.stayY, Cir3.stayY, 50);
				}

				else {   //otherwise if moving point reaches target this happens

					Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
					Cir1.transY = Cir1.stayY;

					Circl1.target = 0;  //turns the click target back 0, so that we can attack again              

					Cir3.stay = Cir3.stay + Cir1.transfer;   //reduces the value of target.

					Cir1.path = 0;

					tucheck = 3;
				}
			}

			if (tucheck == 3){
				DrawRectangle(150, 500, 150, 50, 0, 4, 2);
				renderBitmapString(151, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "NEXT");

				if (mouse_X > 150 && mouse_X < 300 && mouse_Y>500 && mouse_Y < 550){

					Cir1 = { 100, 50, 200, 200, 200, 200, 0, 0 };

					Cir2 = { 80, 25, 450, 450, 450, 450, 0, 0 };

					Cir3 = { 60, 30, 490, 255, 490, 255, 0, 0 };

					tutorial = 3;
					tucheck = 1;
					compturn = 1;

					Circl1 = { 0, 0, 0 };
					Circl3 = { 0, 0, 0 };
				}
			}

			DrawRectangle(500, 500, 150, 50, 0, 4, 2);
			renderBitmapString(520, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "RETURN");


			if (mouse_X > 500 && mouse_X < 650 && mouse_Y>500 && mouse_Y < 550){
				level = 0;

				Cir1 = { 100, 50, 200, 200, 200, 200, 0, 0 };

				Cir2 = { 80, 25, 450, 450, 450, 450, 0, 0 };

				Cir3 = { 60, 30, 490, 255, 490, 255, 0, 0 };

				compturn = 1;
				tutorial = 1;

				Circl1 = { 0, 0, 0 };
				Circl3 = { 0, 0, 0 };

			}
		}





		if (tutorial == 3){
			glColor3f(5, 4, 3);

			renderBitmapString(45, 80, 0, GLUT_BITMAP_9_BY_15, "Click circle 1 and then circle 2 and then either circle 1 for support");
			renderBitmapString(45, 97, 0, GLUT_BITMAP_9_BY_15, "Or the red circle for attack.");
			renderBitmapString(200, 160, 0, GLUT_BITMAP_9_BY_15, "1");

			renderBitmapString(500, 195, 0, GLUT_BITMAP_9_BY_15, "2");


			if (Cir1.vanish == 0)         //draws first circle if it's not gone
				DrawCircle(210, 196, 30, 50, 0, 5, 0);

			if (Cir2.vanish == 0)   //draws second circle if it's not gone
				DrawCircle(465, 446, 30, 50, 4, 0, 0);

			if (Cir3.vanish == 0)  //draws third circle if it's not gone
				DrawCircle(506, 245, 45, 50, 0, 5, 0);


			if (Cir1.vanish == 0){
				char printC1[] = "foo";     //prints values for first circle if it still exists
				sprintf(printC1, "%3d", Cir1.stay);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir1.stayX, Cir1.stayY, 0, GLUT_BITMAP_8_BY_13, printC1);
			}


			if (Cir2.vanish == 0){
				char printC2[] = "foo";    //prints value for second circle if it still exists
				sprintf(printC2, "%3d", Cir2.stay);
				glColor3f(2, 0, 2);
				renderBitmapString(Cir2.stayX, Cir2.stayY, 0, GLUT_BITMAP_8_BY_13, printC2);
			}


			if (Cir3.vanish == 0){
				char printC3[] = "foo";   //print value for third circle if it still exists
				sprintf(printC3, "%3d", Cir3.stay);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir3.stayX, Cir3.stayY, 0, GLUT_BITMAP_8_BY_13, printC3);
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////FROM     CIRCLE 1     TO    CIRCLE    2 //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (mouse_X > 180 && mouse_X < 250 && mouse_Y>160 && mouse_Y < 230 && Cir1.vanish == 0 && Cir1.path == 0){
				Circl1.activate = 1; //sensing first click                           ^Checks if it exists
				//Circl1.activate2 = 1;
			}

			if (Circl1.activate == 1){
				if (mouse_X > 430 && mouse_X < 500 && mouse_Y>415 && mouse_Y < 470 && Cir2.vanish == 0){
					Circl1.target = 1;  //sensing second click                          ^checks if it exists
					Cir1.path = 1;
				}
			}

			if (Circl1.target == 1 && Cir1.vanish == 0)
				Circl1.activate = 0;  //re initialises this bad boy.


			if (Circl1.target == 1 && Cir1.path == 1 && Cir1.vanish == 0){    //if target has been pressed, this happens

				if (Cir1.transX != Cir2.stayX){  //checks if the moving point, is the same as the target point

					if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
						Cir1.transfer = Cir1.stay / 2;


					char printC1trans[] = "foo";        //for printing values on glwindow
					sprintf(printC1trans, "%3d", Cir1.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

					if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
						Cir1.stay = Cir1.stay / 2;

					Cir1.transX += increase(Cir1.stayX, Cir2.stayX, 100);   //for moving the moving point trans
					Cir1.transY += increase(Cir1.stayY, Cir2.stayY, 100);
				}

				else {   //otherwise if moving point reaches target this happens

					Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
					Cir1.transY = Cir1.stayY;

					Circl1.target = 0;  //turns the click target back 0, so that we can attack again              

					Cir2.stay = Cir2.stay - Cir1.transfer;   //reduces the value of target.

					if (Cir2.stay < 1){
						Cir2.vanish = 1;   //if target value is less than 1, it is vanished.
					}

					Cir1.path = 0;
				}
			}


			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////FROM     CIRCLE 1     TO    CIRCLE    3 //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



			if (mouse_X > 180 && mouse_X < 250 && mouse_Y>160 && mouse_Y < 230 && Cir1.vanish == 0 && Cir1.path == 0){
				Circl1.activate = 1; //sensing first click                           ^Checks if it exists
				//Circl1.activate2 = 1;
			}

			if (Circl1.activate == 1){
				if (mouse_X > 460 && mouse_X < 550 && mouse_Y>200 && mouse_Y < 290 && Cir3.vanish == 0){
					Circl1.target = 1;  //sensing second click                          ^checks if it exists
					Cir1.path = 2;
				}
			}

			if (Circl1.target == 1 && Cir1.vanish == 0)
				Circl1.activate = 0;  //re initialises this bad boy.


			if (Circl1.target == 1 && Cir1.path == 2 && Cir1.vanish == 0){    //if target has been pressed, this happens

				if ((int)Cir1.transX < (int)Cir3.stayX){  //checks if the moving point, is the same as the target point

					if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
						Cir1.transfer = Cir1.stay / 2;


					char printC1trans[] = "foo";        //for printing values on glwindow
					sprintf(printC1trans, "%3d", Cir1.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

					if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
						Cir1.stay = Cir1.stay / 2;

					Cir1.transX += increase(Cir1.stayX, Cir3.stayX, 50);   //for moving the moving point trans
					Cir1.transY += increase(Cir1.stayY, Cir3.stayY, 50);
				}

				else {   //otherwise if moving point reaches target this happens

					Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
					Cir1.transY = Cir1.stayY;

					Circl1.target = 0;  //turns the click target back 0, so that we can attack again              

					Cir3.stay = Cir3.stay + Cir1.transfer;   //reduces the value of target.

					Cir1.path = 0;
				}
			}


			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////FROM     CIRCLE 3     TO    CIRCLE    1 //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			if (mouse_X > 460 && mouse_X < 550 && mouse_Y>200 && mouse_Y < 290 && Cir3.vanish == 0 && Cir3.path == 0){
				Circl3.activate = 1;
				tucheck = 4;
			}

			if (Circl3.activate == 1){ //this is to prevent the activation with the previous circle's clicks
				if (mouse_X > 180 && mouse_X < 250 && mouse_Y>160 && mouse_Y < 230 && Cir1.vanish == 0){
					Circl3.target = 1;  //sensing second click
					Cir3.path = 2;
				}
			}

			if (Circl3.target == 1 && Cir3.vanish == 0)
				Circl3.activate = 0;  //re initialises activator.


			if (Circl3.target == 1 && Cir3.path == 2 && Cir3.vanish == 0){

				if ((int)Cir3.transX > (int)Cir1.stayX){

					if (Cir3.transX == Cir3.stayX)   //when they're at the same place, trans gets half of stay
						Cir3.transfer = Cir3.stay / 2;


					char printC3trans[] = "foo";
					sprintf(printC3trans, "%3d", Cir3.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

					if (Cir3.stayX == Cir3.transX)
						Cir3.stay = Cir3.stay / 2;

					Cir3.transX += increase(Cir3.stayX, Cir1.stayX, 50);   //for moving the moving point trans
					Cir3.transY += increase(Cir3.stayY, Cir1.stayY, 50);
				}

				else {
					Cir3.transX = Cir3.stayX;
					Cir3.transY = Cir3.stayY;
					Circl3.target = 0;
					Cir1.stay = Cir1.stay + Cir3.transfer;


					Cir3.path = 0;
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////FROM     CIRCLE 3     TO    CIRCLE    2 //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			if (mouse_X > 460 && mouse_X < 550 && mouse_Y>200 && mouse_Y < 290 && Cir3.vanish == 0 && Cir3.path == 0){
				Circl3.activate = 1; //sensing first click
				//Circl3.activate2 = 1;
			}

			if (Circl3.activate == 1){ //this is to prevent the activation with the previous circle's clicks
				if (mouse_X > 430 && mouse_X < 500 && mouse_Y>415 && mouse_Y < 470 && Cir2.vanish == 0){
					Circl3.target = 1;  //sensing second click
					Cir3.path = 1;
				}
			}

			if (Circl3.target == 1 && Cir3.vanish == 0)
				Circl3.activate = 0;  //re initialises activator.


			if (Circl3.target == 1 && Cir3.path == 1 && Cir3.vanish == 0){

				if ((int)Cir3.transX != (int)Cir2.stayX){

					if (Cir3.transX == Cir3.stayX)   //when they're at the same place, trans gets half of stay
						Cir3.transfer = Cir3.stay / 2;


					char printC3trans[] = "foo";
					sprintf(printC3trans, "%3d", Cir3.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

					if (Cir3.stayX == Cir3.transX)
						Cir3.stay = Cir3.stay / 2;

					Cir3.transX += increase(Cir3.stayX, Cir2.stayX, 75);
					Cir3.transY += increase(Cir3.stayY, Cir2.stayY, 75);
				}

				else {
					Cir3.transX = Cir3.stayX;
					Cir3.transY = Cir3.stayY;
					Circl3.target = 0;
					Cir2.stay = Cir2.stay - Cir3.transfer;
					if (Cir2.stay < 1){
						Cir2.vanish = 1;
					}

					Cir3.path = 0;
				}
			}

			if (tucheck == 4){
				DrawRectangle(150, 500, 150, 50, 0, 4, 2);
				renderBitmapString(151, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "NEXT");

				if (mouse_X > 150 && mouse_X < 300 && mouse_Y>500 && mouse_Y < 550){

					Cir1 = { 100, 50, 200, 200, 200, 200, 0, 0 };

					Cir2 = { 80, 25, 450, 450, 450, 450, 0, 0 };

					Cir3 = { 60, 30, 490, 255, 490, 255, 0, 0 };

					tutorial = 4;
					tucheck = 1;
					compturn = 1;

					Circl1 = { 0, 0, 0 };
					Circl3 = { 0, 0, 0 };
				}
			}



			DrawRectangle(500, 500, 150, 50, 0, 4, 2);
			renderBitmapString(520, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "RETURN");


			if (mouse_X > 500 && mouse_X < 650 && mouse_Y>500 && mouse_Y < 550){
				level = 0;

				Cir1 = { 100, 50, 200, 200, 200, 200, 0, 0 };

				Cir2 = { 80, 25, 450, 450, 450, 450, 0, 0 };

				Cir3 = { 60, 30, 490, 255, 490, 255, 0, 0 };

				compturn = 1;
				tutorial = 1;

				Circl1 = { 0, 0, 0 };
				Circl3 = { 0, 0, 0 };

			}

		}





		if (tutorial == 4){

			glColor3f(5, 4, 3);

			renderBitmapString(45, 80, 0, GLUT_BITMAP_9_BY_15, "You are the green circles. Take over the red circle(s) by reducing it's value to 0.");
			renderBitmapString(45, 97, 0, GLUT_BITMAP_9_BY_15, "Click on green circle, then on target red circle, to transfer half of green circle's");
			renderBitmapString(35, 114, 0, GLUT_BITMAP_9_BY_15, "value. If all the red circles' value reaches 0, you win. If all the green circles'");
			renderBitmapString(35, 131, 0, GLUT_BITMAP_9_BY_15, "value reaches 0, you lose. You can only send one element from a particular circle");
			renderBitmapString(35, 148, 0, GLUT_BITMAP_9_BY_15, "at a time. You can also increase your circle's value by passing elements there.");
			renderBitmapString(55, 168, 0, GLUT_BITMAP_9_BY_15, "NOTE:Larger circles have higher growth rates. Surprise Circles appear too.");

			if (Cir1.vanish == 0)         //draws first circle if it's not gone
				DrawCircle(210, 196, 30, 50, 0, 5, 0);

			if (Cir2.vanish == 0)   //draws second circle if it's not gone
				DrawCircle(465, 446, 30, 50, 4, 0, 0);

			if (Cir3.vanish == 0)  //draws third circle if it's not gone
				DrawCircle(506, 245, 45, 50, 0, 5, 0);


			if (Cir1.vanish == 0){
				char printC1[] = "foo";     //prints values for first circle if it still exists
				sprintf(printC1, "%3d", Cir1.stay);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir1.stayX, Cir1.stayY, 0, GLUT_BITMAP_8_BY_13, printC1);
			}


			if (Cir2.vanish == 0){
				char printC2[] = "foo";    //prints value for second circle if it still exists
				sprintf(printC2, "%3d", Cir2.stay);
				glColor3f(2, 0, 2);
				renderBitmapString(Cir2.stayX, Cir2.stayY, 0, GLUT_BITMAP_8_BY_13, printC2);
			}


			if (Cir3.vanish == 0){
				char printC3[] = "foo";   //print value for third circle if it still exists
				sprintf(printC3, "%3d", Cir3.stay);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir3.stayX, Cir3.stayY, 0, GLUT_BITMAP_8_BY_13, printC3);
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////FROM     CIRCLE 1     TO    CIRCLE    2 //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

			if (mouse_X > 180 && mouse_X < 250 && mouse_Y>160 && mouse_Y < 230 && Cir1.vanish == 0 && Cir1.path == 0){
				Circl1.activate = 1; //sensing first click                           ^Checks if it exists
				//Circl1.activate2 = 1;
			}

			if (Circl1.activate == 1){
				if (mouse_X > 430 && mouse_X < 500 && mouse_Y>415 && mouse_Y < 470 && Cir2.vanish == 0){
					Circl1.target = 1;  //sensing second click                          ^checks if it exists
					Cir1.path = 1;
				}
			}

			if (Circl1.target == 1 && Cir1.vanish == 0)
				Circl1.activate = 0;  //re initialises this bad boy.


			if (Circl1.target == 1 && Cir1.path == 1 && Cir1.vanish == 0){    //if target has been pressed, this happens

				if (Cir1.transX != Cir2.stayX){  //checks if the moving point, is the same as the target point

					if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
						Cir1.transfer = Cir1.stay / 2;


					char printC1trans[] = "foo";        //for printing values on glwindow
					sprintf(printC1trans, "%3d", Cir1.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

					if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
						Cir1.stay = Cir1.stay / 2;

					Cir1.transX++;   //for moving the moving point trans
					Cir1.transY++;
				}

				else {   //otherwise if moving point reaches target this happens

					Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
					Cir1.transY = Cir1.stayY;

					Circl1.target = 0;  //turns the click target back 0, so that we can attack again              

					Cir2.stay = Cir2.stay - Cir1.transfer;   //reduces the value of target.

					if (Cir2.stay < 1){
						Cir2.vanish = 1;   //if target value is less than 1, it is vanished.
					}

					Cir1.path = 0;
				}
			}


			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////FROM     CIRCLE 1     TO    CIRCLE    3 //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



			if (mouse_X > 180 && mouse_X < 250 && mouse_Y>160 && mouse_Y < 230 && Cir1.vanish == 0 && Cir1.path == 0){
				Circl1.activate = 1; //sensing first click                           ^Checks if it exists
				//Circl1.activate2 = 1;
			}

			if (Circl1.activate == 1){
				if (mouse_X > 460 && mouse_X < 550 && mouse_Y>200 && mouse_Y < 290 && Cir3.vanish == 0){
					Circl1.target = 1;  //sensing second click                          ^checks if it exists
					Cir1.path = 2;
				}
			}

			if (Circl1.target == 1 && Cir1.vanish == 0)
				Circl1.activate = 0;  //re initialises this bad boy.


			if (Circl1.target == 1 && Cir1.path == 2 && Cir1.vanish == 0){    //if target has been pressed, this happens

				if ((int)Cir1.transX != (int)Cir3.stayX){  //checks if the moving point, is the same as the target point

					if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
						Cir1.transfer = Cir1.stay / 2;


					char printC1trans[] = "foo";        //for printing values on glwindow
					sprintf(printC1trans, "%3d", Cir1.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

					if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
						Cir1.stay = Cir1.stay / 2;

					Cir1.transX += 2.32;   //for moving the moving point trans
					Cir1.transY += 0.44;
				}

				else {   //otherwise if moving point reaches target this happens

					Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
					Cir1.transY = Cir1.stayY;

					Circl1.target = 0;  //turns the click target back 0, so that we can attack again              

					Cir3.stay = Cir3.stay + Cir1.transfer;   //reduces the value of target.

					Cir1.path = 0;
				}
			}


			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////FROM     CIRCLE 3     TO    CIRCLE    1 //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			if (mouse_X > 460 && mouse_X < 550 && mouse_Y>200 && mouse_Y < 290 && Cir3.vanish == 0 && Cir3.path == 0){
				Circl3.activate = 1; //sensing first click
				//Circl3.activate2 = 1;
			}

			if (Circl3.activate == 1){ //this is to prevent the activation with the previous circle's clicks
				if (mouse_X > 180 && mouse_X < 250 && mouse_Y>160 && mouse_Y < 230 && Cir1.vanish == 0){
					Circl3.target = 1;  //sensing second click
					Cir3.path = 2;
				}
			}

			if (Circl3.target == 1 && Cir3.vanish == 0)
				Circl3.activate = 0;  //re initialises activator.


			if (Circl3.target == 1 && Cir3.path == 2 && Cir3.vanish == 0){

				if ((int)Cir3.transX > (int)Cir1.stayX){

					if (Cir3.transX == Cir3.stayX)   //when they're at the same place, trans gets half of stay
						Cir3.transfer = Cir3.stay / 2;


					char printC3trans[] = "foo";
					sprintf(printC3trans, "%3d", Cir3.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

					if (Cir3.stayX == Cir3.transX)
						Cir3.stay = Cir3.stay / 2;

					Cir3.transX -= 2.32;   //for moving the moving point trans
					Cir3.transY -= 0.44;
				}

				else {
					Cir3.transX = Cir3.stayX;
					Cir3.transY = Cir3.stayY;
					Circl3.target = 0;
					Cir1.stay = Cir1.stay + Cir3.transfer;


					Cir3.path = 0;
				}
			}

			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////FROM     CIRCLE 3     TO    CIRCLE    2 //////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			if (mouse_X > 460 && mouse_X < 550 && mouse_Y>200 && mouse_Y < 290 && Cir3.vanish == 0 && Cir3.path == 0){
				Circl3.activate = 1; //sensing first click
				//Circl3.activate2 = 1;
			}

			if (Circl3.activate == 1){ //this is to prevent the activation with the previous circle's clicks
				if (mouse_X > 430 && mouse_X < 500 && mouse_Y>415 && mouse_Y < 470 && Cir2.vanish == 0){
					Circl3.target = 1;  //sensing second click
					Cir3.path = 1;
				}
			}

			if (Circl3.target == 1 && Cir3.vanish == 0)
				Circl3.activate = 0;  //re initialises activator.


			if (Circl3.target == 1 && Cir3.path == 1 && Cir3.vanish == 0){

				if ((int)Cir3.transX != (int)Cir2.stayX){

					if (Cir3.transX == Cir3.stayX)   //when they're at the same place, trans gets half of stay
						Cir3.transfer = Cir3.stay / 2;


					char printC3trans[] = "foo";
					sprintf(printC3trans, "%3d", Cir3.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

					if (Cir3.stayX == Cir3.transX)
						Cir3.stay = Cir3.stay / 2;

					Cir3.transX += increase(Cir3.stayX, Cir2.stayX, 100);
					Cir3.transY += increase(Cir3.stayY, Cir2.stayY, 100);
				}

				else {
					Cir3.transX = Cir3.stayX;
					Cir3.transY = Cir3.stayY;
					Circl3.target = 0;
					Cir2.stay = Cir2.stay - Cir3.transfer;
					if (Cir2.stay < 1){
						Cir2.vanish = 1;
					}

					Cir3.path = 0;
				}
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			if (time % 30 == 0 && Cir1.vanish == 0) //timer for smaller circle 1
				Cir1.stay++;


			if (time % 30 == 0 && Cir2.vanish == 0) //timer for smaller circle 2
				Cir2.stay++;



			if (time % 20 == 0){   //timer for bigger circle 3
				Cir3.stay++;
			}


			time++;

			//This is the Opponent Computer's code, it uses similar coding, just an algorithm for target switch has been added.
			if (Cir2.vanish == 0){
				if (compturn == 2 && Cir3.vanish == 0){
					if ((int)Cir2.transX != (int)Cir3.stayX){
						if (Cir2.transX == Cir2.stayX){
							Cir2.transfer = Cir2.stay / 2;
							Cir2.stay = Cir2.stay / 2;
						}

						char printC2tran[] = "foo";
						sprintf(printC2tran, "%3d", Cir2.transfer);
						glColor3f(2, 0, 0);
						renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2tran);

						Cir2.transX = Cir2.transX + 0.2;
						Cir2.transY = Cir2.transY - 0.975;

					}

					else {
						Cir2.transX = Cir2.stayX;
						Cir2.transY = Cir2.stayY;
						Cir3.stay = Cir3.stay - Cir2.transfer;
						compturn = 1;
						if (Cir3.stay < 1){
							Cir3.vanish = 1;
						}
					}
				}

				else if (compturn == 1 && Cir1.vanish == 0){
					if ((int)Cir2.transX != (int)Cir1.stayX){
						if (Cir2.transX == Cir2.stayX){
							Cir2.transfer = Cir2.stay / 2;
							Cir2.stay = Cir2.stay / 2;
						}

						char printC2tran[] = "foo";
						sprintf(printC2tran, "%3d", Cir2.transfer);
						glColor3f(2, 0, 0);
						renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2tran);

						Cir2.transX = Cir2.transX - 1;
						Cir2.transY = Cir2.transY - 1;

					}

					else {
						Cir2.transX = Cir2.stayX;
						Cir2.transY = Cir2.stayY;
						Cir1.stay = Cir1.stay - Cir2.transfer;
						compturn = 2;
						if (Cir1.stay < 1){
							Cir1.vanish = 1;
						}
					}
				}
				//bug fix, now computer still attacks one in case the other vanishes.
				else if (Cir1.vanish != 0){
					if ((int)Cir2.transX != (int)Cir3.stayX){
						if (Cir2.transX == Cir2.stayX){
							Cir2.transfer = Cir2.stay / 2;
							Cir2.stay = Cir2.stay / 2;
						}

						char printC2tran[] = "foo";
						sprintf(printC2tran, "%3d", Cir2.transfer);
						glColor3f(2, 0, 0);
						renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2tran);

						Cir2.transX = Cir2.transX + 0.2;
						Cir2.transY = Cir2.transY - 0.975;

					}

					else {
						Cir2.transX = Cir2.stayX;
						Cir2.transY = Cir2.stayY;
						Cir3.stay = Cir3.stay - Cir2.transfer;
						compturn = 1;
						if (Cir3.stay < 1){
							Cir3.vanish = 1;
						}
					}
				}

				else if (Cir3.vanish != 0){
					if ((int)Cir2.transX != (int)Cir1.stayX){
						if (Cir2.transX == Cir2.stayX){
							Cir2.transfer = Cir2.stay / 2;
							Cir2.stay = Cir2.stay / 2;
						}

						char printC2tran[] = "foo";
						sprintf(printC2tran, "%3d", Cir2.transfer);
						glColor3f(2, 0, 0);
						renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2tran);

						Cir2.transX = Cir2.transX - 1;
						Cir2.transY = Cir2.transY - 1;

					}

					else {
						Cir2.transX = Cir2.stayX;
						Cir2.transY = Cir2.stayY;
						Cir1.stay = Cir1.stay - Cir2.transfer;
						compturn = 2;
						if (Cir1.stay < 1){
							Cir1.vanish = 1;
						}

					}

				}
			}


			if (Cir2.vanish != 0 && (Cir1.vanish == 0 || Cir3.vanish == 0)){
				glColor3f(0, 4, 5);
				renderBitmapString(350, 320, 0, GLUT_BITMAP_TIMES_ROMAN_24, "YOU WIN!");

				DrawRectangle(150, 500, 150, 50, 0, 4, 2);
				renderBitmapString(151, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "NEXT LEVEL");

				if (mouse_X > 150 && mouse_X < 300 && mouse_Y>500 && mouse_Y < 550){
					level = 2;
					Cir1 = { 80, 50, 200, 350, 200, 350, 0, 0 };

					Cir2 = { 120, 25, 420, 490, 420, 490, 0, 0 };

					Cir3 = { 60, 30, 520, 195, 520, 195, 0, 0 };
					tutorial = 1;
					compturn = 1;
					tucheck = 1;
					Circl1 = { 0, 0, 0 };
					Circl3 = { 0, 0, 0 };
				}
			}

			if (Cir1.vanish != 0 && Cir3.vanish != 0 && Cir2.vanish == 0){
				glColor3f(5, 0, 0);
				renderBitmapString(350, 320, 0, GLUT_BITMAP_TIMES_ROMAN_24, "YOU LOSE!");

			}

			if (Cir1.vanish != 0 && Cir3.vanish != 0 && Cir2.vanish != 0){
				glColor3f(5, 0, 0);
				renderBitmapString(350, 320, 0, GLUT_BITMAP_TIMES_ROMAN_24, "-- DRAW!");
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			//////////////////////////////// FOR               RETURN                   BUTTON                /////////////////////////
			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


			DrawRectangle(500, 500, 150, 50, 0, 4, 2);
			renderBitmapString(520, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "RETURN");


			if (mouse_X > 500 && mouse_X < 650 && mouse_Y>500 && mouse_Y < 550){
				level = 0;

				Cir1 = { 100, 50, 200, 200, 200, 200, 0, 0 };

				Cir2 = { 80, 25, 450, 450, 450, 450, 0, 0 };

				Cir3 = { 60, 30, 490, 255, 490, 255, 0, 0 };

				tutorial = 1;
				compturn = 1;
				tucheck = 1;

				Circl1 = { 0, 0, 0 };
				Circl3 = { 0, 0, 0 };

			}

		}
	}
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////    L E V E L                1    ////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	if (level == 2){

		if (Cir1.vanish == 0)         //draws first circle if it's not gone
			DrawCircle(210, 350, 30, 50, 0, 5, 0);

		if (Cir2.vanish == 0)   //draws second circle if it's not gone
			DrawCircle(430, 490, 30, 50, 4, 0, 0);

		if (Cir3.vanish == 0)  //draws third circle if it's not gone
			DrawCircle(536, 195, 45, 50, 0, 5, 0);


		glColor3f(5, 0, 3);
		renderBitmapString(350, 60, 0, GLUT_BITMAP_TIMES_ROMAN_24, "LEVEL 1!");

		if (Cir1.vanish == 0){
			char printC1[] = "foo";     //prints values for first circle if it still exists
			sprintf(printC1, "%3d", Cir1.stay);
			glColor3f(0, 0, 2);
			renderBitmapString(Cir1.stayX, Cir1.stayY, 0, GLUT_BITMAP_8_BY_13, printC1);
		}


		if (Cir2.vanish == 0){
			char printC2[] = "foo";    //prints value for second circle if it still exists
			sprintf(printC2, "%3d", Cir2.stay);
			glColor3f(2, 0, 2);
			renderBitmapString(Cir2.stayX, Cir2.stayY, 0, GLUT_BITMAP_8_BY_13, printC2);
		}


		if (Cir3.vanish == 0){
			char printC3[] = "foo";   //print value for third circle if it still exists
			sprintf(printC3, "%3d", Cir3.stay);
			glColor3f(0, 0, 2);
			renderBitmapString(Cir3.stayX, Cir3.stayY, 0, GLUT_BITMAP_8_BY_13, printC3);
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 1     TO    CIRCLE    2 //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mouse_X > 180 && mouse_X < 240 && mouse_Y > 315 && mouse_Y < 380 && Cir1.vanish == 0 && Cir1.path == 0){
			Circl1.activate = 1; //sensing first click                           ^Checks if it exists
			//Circl1.activate2 = 1;
		}

		if (Circl1.activate == 1){
			if (mouse_X > 400 && mouse_X < 460 && mouse_Y > 460 && mouse_Y < 520 && Cir2.vanish == 0){
				Circl1.target = 1;  //sensing second click                          ^checks if it exists
				Cir1.path = 1;
			}
		}

		if (Circl1.target == 1 && Cir1.vanish == 0)
			Circl1.activate = 0;  //re initialises this bad boy.


		if (Circl1.target == 1 && Cir1.path == 1 && Cir1.vanish == 0){    //if target has been pressed, this happens

			if ((int)Cir1.transX < (int)Cir2.stayX){  //checks if the moving point, is the same as the target point

				if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
					Cir1.transfer = Cir1.stay / 2;


				char printC1trans[] = "foo";        //for printing values on glwindow
				sprintf(printC1trans, "%3d", Cir1.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

				if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
					Cir1.stay = Cir1.stay / 2;

				Cir1.transX += increase(Cir1.stayX,Cir2.stayX,75);   //for moving the moving point trans
				Cir1.transY += increase(Cir1.stayY, Cir2.stayY, 75);
			}

			else {   //otherwise if moving point reaches target this happens

				Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
				Cir1.transY = Cir1.stayY;

				Circl1.target = 0;  //turns the click target back 0, so that we can attack again              

				Cir2.stay = Cir2.stay - Cir1.transfer;   //reduces the value of target.

				if (Cir2.stay < 1){
					Cir2.vanish = 1;   //if target value is less than 1, it is vanished.
				}

				Cir1.path = 0;
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 1     TO    CIRCLE    3 //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		if (mouse_X > 180 && mouse_X < 240 && mouse_Y > 315 && mouse_Y < 380 && Cir1.vanish == 0 && Cir1.path == 0){
			Circl1.activate = 1; //sensing first click                           ^Checks if it exists
			//Circl1.activate2 = 1;
		}

		if (Circl1.activate == 1){
			if (mouse_X > 490 && mouse_X < 580 && mouse_Y > 150 && mouse_Y < 240 && Cir3.vanish == 0){
				Circl1.target = 1;  //sensing second click                          ^checks if it exists
				Cir1.path = 2;
			}
		}

		if (Circl1.target == 1 && Cir1.vanish == 0)
			Circl1.activate = 0;  //re initialises this bad boy.


		if (Circl1.target == 1 && Cir1.path == 2 && Cir1.vanish == 0){    //if target has been pressed, this happens

			if ((int)Cir1.transX < (int)Cir3.stayX){  //checks if the moving point, is the same as the target point

				if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
					Cir1.transfer = Cir1.stay / 2;


				char printC1trans[] = "foo";        //for printing values on glwindow
				sprintf(printC1trans, "%3d", Cir1.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

				if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
					Cir1.stay = Cir1.stay / 2;

				Cir1.transX += increase(Cir1.stayX, Cir3.stayX, 100);   //for moving the moving point trans
				Cir1.transY += increase(Cir1.stayY, Cir3.stayY, 100);
			}

			else {   //otherwise if moving point reaches target this happens

				Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
				Cir1.transY = Cir1.stayY;

				Circl1.target = 0;  //turns the click target back 0, so that we can attack again              

				Cir3.stay = Cir3.stay + Cir1.transfer;   //reduces the value of target.

				Cir1.path = 0;
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 3     TO    CIRCLE    1 //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (mouse_X > 490 && mouse_X < 580 && mouse_Y > 150 && mouse_Y < 240 && Cir3.vanish == 0 && Cir3.path == 0){
			Circl3.activate = 1; //sensing first click
			//Circl3.activate2 = 1;
		}

		if (Circl3.activate == 1){ //this is to prevent the activation with the previous circle's clicks
			if (mouse_X > 180 && mouse_X < 240 && mouse_Y > 315 && mouse_Y < 380 && Cir1.vanish == 0){
				Circl3.target = 1;  //sensing second click
				Cir3.path = 2;
			}
		}

		if (Circl3.target == 1 && Cir3.vanish == 0)
			Circl3.activate = 0;  //re initialises activator.


		if (Circl3.target == 1 && Cir3.path == 2 && Cir3.vanish == 0){

			if ((int)Cir3.transX > (int)Cir1.stayX){

				if (Cir3.transX == Cir3.stayX)   //when they're at the same place, trans gets half of stay
					Cir3.transfer = Cir3.stay / 2;


				char printC3trans[] = "foo";
				sprintf(printC3trans, "%3d", Cir3.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

				if (Cir3.stayX == Cir3.transX)
					Cir3.stay = Cir3.stay / 2;

				Cir3.transX += increase(Cir3.stayX, Cir1.stayX, 100);   //for moving the moving point trans
				Cir3.transY += increase(Cir3.stayY, Cir1.stayY, 100);
			}

			else {
				Cir3.transX = Cir3.stayX;
				Cir3.transY = Cir3.stayY;
				Circl3.target = 0;
				Cir1.stay = Cir1.stay + Cir3.transfer;


				Cir3.path = 0;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 3     TO    CIRCLE    2 //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (mouse_X > 490 && mouse_X < 580 && mouse_Y > 150 && mouse_Y < 240 && Cir3.vanish == 0 && Cir3.path == 0){
			Circl3.activate = 1; //sensing first click
			//Circl3.activate2 = 1;
		}

		if (Circl3.activate == 1){ //this is to prevent the activation with the previous circle's clicks
			if (mouse_X > 400 && mouse_X < 460 && mouse_Y > 460 && mouse_Y < 520 && Cir2.vanish == 0){
				Circl3.target = 1;  //sensing second click
				Cir3.path = 1;
			}
		}

		if (Circl3.target == 1 && Cir3.vanish == 0)
			Circl3.activate = 0;  //re initialises activator.


		if (Circl3.target == 1 && Cir3.path == 1 && Cir3.vanish == 0){

			if ((int)Cir3.transX != (int)Cir2.stayX){

				if (Cir3.transX == Cir3.stayX)   //when they're at the same place, trans gets half of stay
					Cir3.transfer = Cir3.stay / 2;


				char printC3trans[] = "foo";
				sprintf(printC3trans, "%3d", Cir3.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

				if (Cir3.stayX == Cir3.transX)
					Cir3.stay = Cir3.stay / 2;

				Cir3.transX += increase(Cir3.stayX, Cir2.stayX, 125);
				Cir3.transY += increase(Cir3.stayY, Cir2.stayY, 125);
			}

			else {
				Cir3.transX = Cir3.stayX;
				Cir3.transY = Cir3.stayY;
				Circl3.target = 0;
				Cir2.stay = Cir2.stay - Cir3.transfer;
				if (Cir2.stay < 1){
					Cir2.vanish = 1;
				}

				Cir3.path = 0;
			}
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (time % 30 == 0 && Cir1.vanish == 0) //timer for smaller circle 1
			Cir1.stay++;


		if (time % 30 == 0 && Cir2.vanish == 0) //timer for smaller circle 2
			Cir2.stay++;



		if (time % 20 == 0){   //timer for bigger circle 3
			Cir3.stay++;
		}


		time++;

		//This is the Opponent Computer's code, it uses similar coding, just an algorithm for target switch has been added.
		if (Cir2.vanish == 0){
			if (compturn == 2 && Cir3.vanish == 0){
				if ((int)Cir2.transX != (int)Cir3.stayX){
					if (Cir2.transX == Cir2.stayX){
						Cir2.transfer = Cir2.stay / 2;
						Cir2.stay = Cir2.stay / 2;
					}

					char printC2tran[] = "foo";
					sprintf(printC2tran, "%3d", Cir2.transfer);
					glColor3f(2, 0, 0);
					renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2tran);

					Cir2.transX += increase(Cir2.stayX, Cir3.stayX, 125);
					Cir2.transY += increase(Cir2.stayY, Cir3.stayY, 125);

				}

				else {
					Cir2.transX = Cir2.stayX;
					Cir2.transY = Cir2.stayY;
					Cir3.stay = Cir3.stay - Cir2.transfer;
					compturn = 1;
					if (Cir3.stay < 1){
						Cir3.vanish = 1;
					}
				}
			}

			else if (compturn == 1 && Cir1.vanish == 0){
				if ((int)Cir2.transX > (int)Cir1.stayX){
					if (Cir2.transX == Cir2.stayX){
						Cir2.transfer = Cir2.stay / 2;
						Cir2.stay = Cir2.stay / 2;
					}

					char printC2tran[] = "foo";
					sprintf(printC2tran, "%3d", Cir2.transfer);
					glColor3f(2, 0, 0);
					renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2tran);

					Cir2.transX += increase(Cir2.stayX, Cir1.stayX, 75);
					Cir2.transY += increase(Cir2.stayY, Cir1.stayY, 75);

				}

				else {
					Cir2.transX = Cir2.stayX;
					Cir2.transY = Cir2.stayY;
					Cir1.stay = Cir1.stay - Cir2.transfer;
					compturn = 2;
					if (Cir1.stay < 1){
						Cir1.vanish = 1;
					}
				}
			}
			//bug fix, now computer still attacks one in case the other vanishes.
			else if (Cir1.vanish != 0){
				if ((int)Cir2.transX != (int)Cir3.stayX){
					if (Cir2.transX == Cir2.stayX){
						Cir2.transfer = Cir2.stay / 2;
						Cir2.stay = Cir2.stay / 2;
					}

					char printC2tran[] = "foo";
					sprintf(printC2tran, "%3d", Cir2.transfer);
					glColor3f(2, 0, 0);
					renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2tran);

					Cir2.transX = Cir2.transX + 0.40;
					Cir2.transY = Cir2.transY - 1.18;

				}

				else {
					Cir2.transX = Cir2.stayX;
					Cir2.transY = Cir2.stayY;
					Cir3.stay = Cir3.stay - Cir2.transfer;
					compturn = 1;
					if (Cir3.stay < 1){
						Cir3.vanish = 1;
					}
				}
			}

			else if (Cir3.vanish != 0){
				if ((int)Cir2.transX != (int)Cir1.stayX){
					if (Cir2.transX == Cir2.stayX){
						Cir2.transfer = Cir2.stay / 2;
						Cir2.stay = Cir2.stay / 2;
					}

					char printC2tran[] = "foo";
					sprintf(printC2tran, "%3d", Cir2.transfer);
					glColor3f(2, 0, 0);
					renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2tran);

					Cir2.transX = Cir2.transX - 0.88;
					Cir2.transY = Cir2.transY - 0.56;

				}

				else {
					Cir2.transX = Cir2.stayX;
					Cir2.transY = Cir2.stayY;
					Cir1.stay = Cir1.stay - Cir2.transfer;
					compturn = 2;
					if (Cir1.stay < 1){
						Cir1.vanish = 1;
					}

				}

			}
		}


		if (Cir2.vanish != 0 && (Cir1.vanish == 0 || Cir3.vanish == 0)){
			glColor3f(0, 4, 5);
			renderBitmapString(350, 320, 0, GLUT_BITMAP_TIMES_ROMAN_24, "YOU WIN!");

			DrawRectangle(150, 500, 150, 50, 0, 4, 2);
			renderBitmapString(151, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "NEXT LEVEL");

			if (mouse_X > 150 && mouse_X < 300 && mouse_Y>500 && mouse_Y < 550){
				level = 3;
				Cir1 = { 100, 50, 300, 200, 300, 200, 0, 0 };

				Cir2 = { 320, 25, 450, 450, 450, 450, 0, 0 };

				Cir3 = { 80, 30, 470, 240, 470, 240, 0, 0 };

				compturn = 1;

				Circl1 = { 0, 0, 0 };
				Circl3 = { 0, 0, 0 };
			}
		}

		if (Cir1.vanish != 0 && Cir3.vanish != 0 && Cir2.vanish == 0){
			glColor3f(5, 0, 0);
			renderBitmapString(350, 320, 0, GLUT_BITMAP_TIMES_ROMAN_24, "YOU LOSE!");
		}

		if (Cir1.vanish != 0 && Cir3.vanish != 0 && Cir2.vanish != 0){
			glColor3f(5, 0, 0);
			renderBitmapString(350, 320, 0, GLUT_BITMAP_TIMES_ROMAN_24, "-- DRAW!");
		}



		DrawRectangle(500, 500, 150, 50, 0, 4, 2);
		renderBitmapString(520, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "RETURN");


		if (mouse_X > 500 && mouse_X < 650 && mouse_Y>500 && mouse_Y < 550){
			level = 0;

			Cir1 = { 100, 50, 200, 200, 200, 200, 0, 0 };

			Cir2 = { 80, 25, 450, 450, 450, 450, 0, 0 };

			Cir3 = { 60, 30, 490, 255, 490, 255, 0, 0 };

			compturn = 1;

			Circl1 = { 0, 0, 0 };
			Circl3 = { 0, 0, 0 };


		}

	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////    L E V E L                2    ////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	if (level == 3){

		glColor3f(5, 0, 3);
		renderBitmapString(350, 60, 0, GLUT_BITMAP_TIMES_ROMAN_24, "LEVEL 2!");
		glColor3f(5, 4, 3);

		renderBitmapString(180, 100, 0, GLUT_BITMAP_TIMES_ROMAN_24, "HINT: In Unity, You Might Find Strength.");



		if (Cir1.vanish == 0){
			char printC1[] = "foo";     //prints values for first circle if it still exists
			sprintf(printC1, "%3d", Cir1.stay);
			glColor3f(0, 0, 2);
			renderBitmapString(Cir1.stayX, Cir1.stayY, 0, GLUT_BITMAP_8_BY_13, printC1);
		}


		if (Cir2.vanish == 0){
			char printC2[] = "foo";    //prints value for second circle if it still exists
			sprintf(printC2, "%3d", Cir2.stay);
			glColor3f(2, 0, 2);
			renderBitmapString(Cir2.stayX, Cir2.stayY, 0, GLUT_BITMAP_8_BY_13, printC2);
		}


		if (Cir3.vanish == 0){
			char printC3[] = "foo";   //print value for third circle if it still exists
			sprintf(printC3, "%3d", Cir3.stay);
			glColor3f(0, 0, 2);
			renderBitmapString(Cir3.stayX, Cir3.stayY, 0, GLUT_BITMAP_8_BY_13, printC3);
		}



		if (Cir1.vanish == 0)
			DrawCircle(310, 195, 50, 50, 0, 5, 0);


		if (Cir2.vanish == 0)
			DrawCircle(460, 445, 50, 50, 5, 0, 0);


		if (Cir3.vanish == 0)
			DrawCircle(485, 235, 70, 50, 0, 5, 0);



		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 1     TO    CIRCLE    2 //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mouse_X > 260 && mouse_X < 360 && mouse_Y>140 && mouse_Y < 240 && Cir1.vanish == 0 && Cir1.path == 0){
			Circl1.activate = 1; //sensing first click                           ^Checks if it exists
			//Circl1.activate2 = 1;
		}

		if (Circl1.activate == 1){
			if (mouse_X > 400 && mouse_X < 500 && mouse_Y>390 && mouse_Y < 490 && Cir2.vanish == 0){
				Circl1.target = 1;  //sensing second click                          ^checks if it exists
				Cir1.path = 1;
			}
		}

		if (Circl1.target == 1 && Cir1.vanish == 0)
			Circl1.activate = 0;  //re initialises this bad boy.


		if (Circl1.target == 1 && Cir1.path == 1 && Cir1.vanish == 0){    //if target has been pressed, this happens

			if (Cir1.transX != Cir2.stayX){  //checks if the moving point, is the same as the target point

				if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
					Cir1.transfer = Cir1.stay / 2;


				char printC1trans[] = "foo";        //for printing values on glwindow
				sprintf(printC1trans, "%3d", Cir1.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

				if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
					Cir1.stay = Cir1.stay / 2;

				Cir1.transX += 0.75;   //for moving the moving point trans
				Cir1.transY++;
			}

			else {   //otherwise if moving point reaches target this happens

				Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
				Cir1.transY = Cir1.stayY;

				Circl1.target = 0;  //turns the click target back 0, so that we can attack again              

				Cir2.stay = Cir2.stay - Cir1.transfer;   //reduces the value of target.

				if (Cir2.stay < 1){
					Cir2.vanish = 1;   //if target value is less than 1, it is vanished.
				}

				Cir1.path = 0;
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 1     TO    CIRCLE    3 //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		if (mouse_X > 260 && mouse_X < 360 && mouse_Y>140 && mouse_Y < 240 && Cir1.vanish == 0 && Cir1.path == 0){
			Circl1.activate = 1; //sensing first click                           ^Checks if it exists
			//Circl1.activate2 = 1;
		}

		if (Circl1.activate == 1){
			if (mouse_X > 415 && mouse_X < 550 && mouse_Y>160 && mouse_Y < 300 && Cir3.vanish == 0){
				Circl1.target = 1;  //sensing second click                          ^checks if it exists
				Cir1.path = 2;
			}
		}

		if (Circl1.target == 1 && Cir1.vanish == 0)
			Circl1.activate = 0;  //re initialises this bad boy.


		if (Circl1.target == 1 && Cir1.path == 2 && Cir1.vanish == 0){    //if target has been pressed, this happens

			if ((int)Cir1.transX < (int)Cir3.stayX){  //checks if the moving point, is the same as the target point

				if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
					Cir1.transfer = Cir1.stay / 2;


				char printC1trans[] = "foo";        //for printing values on glwindow
				sprintf(printC1trans, "%3d", Cir1.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

				if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
					Cir1.stay = Cir1.stay / 2;

				Cir1.transX += 2.832;   //for moving the moving point trans
				Cir1.transY += 0.52;
			}

			else {   //otherwise if moving point reaches target this happens

				Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
				Cir1.transY = Cir1.stayY;

				Circl1.target = 0;  //turns the click target back 0, so that we can attack again              

				Cir3.stay = Cir3.stay + Cir1.transfer;   //reduces the value of target.

				Cir1.path = 0;
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 3     TO    CIRCLE    1 //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (mouse_X > 415 && mouse_X < 550 && mouse_Y>160 && mouse_Y < 300 && Cir3.vanish == 0 && Cir3.path == 0){
			Circl3.activate = 1; //sensing first click
			//Circl3.activate2 = 1;
		}

		if (Circl3.activate == 1){ //this is to prevent the activation with the previous circle's clicks
			if (mouse_X > 260 && mouse_X < 360 && mouse_Y>140 && mouse_Y < 240 && Cir1.vanish == 0){
				Circl3.target = 1;  //sensing second click
				Cir3.path = 2;
			}
		}

		if (Circl3.target == 1 && Cir3.vanish == 0)
			Circl3.activate = 0;  //re initialises activator.


		if (Circl3.target == 1 && Cir3.path == 2 && Cir3.vanish == 0){

			if ((int)Cir3.transX > (int)Cir1.stayX){

				if (Cir3.transX == Cir3.stayX)   //when they're at the same place, trans gets half of stay
					Cir3.transfer = Cir3.stay / 2;


				char printC3trans[] = "foo";
				sprintf(printC3trans, "%3d", Cir3.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

				if (Cir3.stayX == Cir3.transX)
					Cir3.stay = Cir3.stay / 2;

				Cir3.transX -= 2.832;   //for moving the moving point trans
				Cir3.transY -= 0.52;
			}

			else {
				Cir3.transX = Cir3.stayX;
				Cir3.transY = Cir3.stayY;
				Circl3.target = 0;
				Cir1.stay = Cir1.stay + Cir3.transfer;


				Cir3.path = 0;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 3     TO    CIRCLE    2 //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (mouse_X > 415 && mouse_X < 550 && mouse_Y>160 && mouse_Y < 300 && Cir3.vanish == 0 && Cir3.path == 0){
			Circl3.activate = 1; //sensing first click
			//Circl3.activate2 = 1;
		}

		if (Circl3.activate == 1){ //this is to prevent the activation with the previous circle's clicks
			if (mouse_X > 400 && mouse_X < 500 && mouse_Y>390 && mouse_Y < 490 && Cir2.vanish == 0){
				Circl3.target = 1;  //sensing second click
				Cir3.path = 1;
			}
		}

		if (Circl3.target == 1 && Cir3.vanish == 0)
			Circl3.activate = 0;  //re initialises activator.


		if (Circl3.target == 1 && Cir3.path == 1 && Cir3.vanish == 0){

			if ((int)Cir3.transX > (int)Cir2.stayX){

				if (Cir3.transX == Cir3.stayX)   //when they're at the same place, trans gets half of stay
					Cir3.transfer = Cir3.stay / 2;


				char printC3trans[] = "foo";
				sprintf(printC3trans, "%3d", Cir3.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

				if (Cir3.stayX == Cir3.transX)
					Cir3.stay = Cir3.stay / 2;

				Cir3.transX = Cir3.transX - 0.1;
				Cir3.transY = Cir3.transY + 1.05;
			}

			else {
				Cir3.transX = Cir3.stayX;
				Cir3.transY = Cir3.stayY;
				Circl3.target = 0;
				Cir2.stay = Cir2.stay - Cir3.transfer;
				if (Cir2.stay < 1){
					Cir2.vanish = 1;
				}

				Cir3.path = 0;
			}
		}

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		if (time % 30 == 0 && Cir1.vanish == 0) //timer for smaller circle 1
			Cir1.stay++;


		if (time % 30 == 0 && Cir2.vanish == 0) //timer for smaller circle 2
			Cir2.stay++;



		if (time % 20 == 0){   //timer for bigger circle 3
			Cir3.stay++;
		}





		time++;

		//This is the Opponent Computer's code, it uses similar coding, just an algorithm for target switch has been added.
		if (Cir2.vanish == 0){
			if (compturn == 2 && Cir3.vanish == 0){
				if ((int)Cir2.transX != (int)Cir3.stayX){
					if (Cir2.transX == Cir2.stayX){
						Cir2.transfer = Cir2.stay / 2;
						Cir2.stay = Cir2.stay / 2;
					}

					char printC2tran[] = "foo";
					sprintf(printC2tran, "%3d", Cir2.transfer);
					glColor3f(2, 0, 0);
					renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2tran);

					Cir2.transX = Cir2.transX + 0.1;
					Cir2.transY = Cir2.transY - 1.05;

				}

				else {
					Cir2.transX = Cir2.stayX;
					Cir2.transY = Cir2.stayY;
					Cir3.stay = Cir3.stay - Cir2.transfer;
					compturn = 1;
					if (Cir3.stay < 1){
						Cir3.vanish = 1;
					}
				}
			}

			else if (compturn == 1 && Cir1.vanish == 0){
				if ((int)Cir2.transX != (int)Cir1.stayX){
					if (Cir2.transX == Cir2.stayX){
						Cir2.transfer = Cir2.stay / 2;
						Cir2.stay = Cir2.stay / 2;
					}

					char printC2tran[] = "foo";
					sprintf(printC2tran, "%3d", Cir2.transfer);
					glColor3f(2, 0, 0);
					renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2tran);

					Cir2.transX = Cir2.transX - 0.75;
					Cir2.transY = Cir2.transY - 1;

				}

				else {
					Cir2.transX = Cir2.stayX;
					Cir2.transY = Cir2.stayY;
					Cir1.stay = Cir1.stay - Cir2.transfer;
					compturn = 2;
					if (Cir1.stay < 1){
						Cir1.vanish = 1;
					}
				}
			}
			//bug fix, now computer still attacks one in case the other vanishes.
			else if (Cir1.vanish != 0){
				if ((int)Cir2.transX != (int)Cir3.stayX){
					if (Cir2.transX == Cir2.stayX){
						Cir2.transfer = Cir2.stay / 2;
						Cir2.stay = Cir2.stay / 2;
					}

					char printC2tran[] = "foo";
					sprintf(printC2tran, "%3d", Cir2.transfer);
					glColor3f(2, 0, 0);
					renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2tran);

					Cir2.transX = Cir2.transX + 0.1;
					Cir2.transY = Cir2.transY - 1.05;

				}

				else {
					Cir2.transX = Cir2.stayX;
					Cir2.transY = Cir2.stayY;
					Cir3.stay = Cir3.stay - Cir2.transfer;
					compturn = 1;
					if (Cir3.stay < 1){
						Cir3.vanish = 1;
					}
				}
			}

			else if (Cir3.vanish != 0){
				if ((int)Cir2.transX != (int)Cir1.stayX){
					if (Cir2.transX == Cir2.stayX){
						Cir2.transfer = Cir2.stay / 2;
						Cir2.stay = Cir2.stay / 2;
					}

					char printC2tran[] = "foo";
					sprintf(printC2tran, "%3d", Cir2.transfer);
					glColor3f(2, 0, 0);
					renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2tran);

					Cir2.transX = Cir2.transX - 0.75;
					Cir2.transY = Cir2.transY - 1;

				}

				else {
					Cir2.transX = Cir2.stayX;
					Cir2.transY = Cir2.stayY;
					Cir1.stay = Cir1.stay - Cir2.transfer;
					compturn = 2;
					if (Cir1.stay < 1){
						Cir1.vanish = 1;
					}

				}

			}
		}
		if (Cir2.vanish != 0 && (Cir1.vanish == 0 || Cir3.vanish == 0)){
			glColor3f(0, 4, 5);
			renderBitmapString(350, 320, 0, GLUT_BITMAP_TIMES_ROMAN_24, "YOU WIN!");

			DrawRectangle(150, 500, 150, 50, 0, 4, 2);
			renderBitmapString(151, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "NEXT LEVEL");

			if (mouse_X > 150 && mouse_X < 300 && mouse_Y>500 && mouse_Y < 550){
				level = 4;

				Cir1 = { 110, 50, 300, 190, 300, 190, 0, 0 };

				Cir2 = { 120, 25, 450, 450, 450, 450, 0, 1 };

				Cir3 = { 120, 30, 470, 240, 470, 240, 0, 0 };

				Cir4 = { 100, 50, 320, 460, 320, 460, 0, 1 };

				compturn = 1;

				Circl1 = { 0, 0, 0 };
				Circl3 = { 0, 0, 0 };
			}

		}

		if (Cir1.vanish != 0 && Cir3.vanish != 0 && Cir2.vanish == 0){
			glColor3f(5, 0, 0);
			renderBitmapString(350, 320, 0, GLUT_BITMAP_TIMES_ROMAN_24, "YOU LOSE!");
		}

		if (Cir1.vanish != 0 && Cir3.vanish != 0 && Cir2.vanish != 0){
			glColor3f(5, 0, 0);
			renderBitmapString(350, 320, 0, GLUT_BITMAP_TIMES_ROMAN_24, "-- DRAW!");
		}


		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////// FOR                   RETURN                 BUTTON  /////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		DrawRectangle(500, 500, 150, 50, 0, 4, 2);
		renderBitmapString(520, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "RETURN");


		if (mouse_X > 500 && mouse_X < 650 && mouse_Y>500 && mouse_Y < 550){
			level = 0;

			Cir1 = { 100, 50, 200, 200, 200, 200, 0, 0 };

			Cir2 = { 80, 25, 450, 450, 450, 450, 0, 0 };

			Cir3 = { 60, 30, 490, 255, 490, 255, 0, 0 };

			compturn = 1;

			Circl1 = { 0, 0, 0 };
			Circl3 = { 0, 0, 0 };

		}

	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////    L E V E L                3   ////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




	if (level == 4){

		//PlaySound(L"C:\\Users\\EXTRA\\Desktop\\darthgimp.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
		glColor3f(5, 0, 3);
		renderBitmapString(350, 60, 0, GLUT_BITMAP_TIMES_ROMAN_24, "LEVEL 3!");
		glColor3f(5, 4, 3);

		renderBitmapString(180, 100, 0, GLUT_BITMAP_TIMES_ROMAN_24, "Let's make more enemies!");



		if (Cir1.vanish == 0){
			char printC1[] = "foo";     //prints values for first circle if it still exists
			sprintf(printC1, "%3d", Cir1.stay);
			glColor3f(0, 0, 2);
			renderBitmapString(Cir1.stayX, Cir1.stayY, 0, GLUT_BITMAP_8_BY_13, printC1);
		}


		if (Cir2.vanish == 0){
			char printC2[] = "foo";    //prints value for second circle if it still exists
			sprintf(printC2, "%3d", Cir2.stay);
			glColor3f(2, 0, 2);
			renderBitmapString(Cir2.stayX, Cir2.stayY, 0, GLUT_BITMAP_8_BY_13, printC2);
		}


		if (Cir3.vanish == 0){
			char printC3[] = "foo";   //print value for third circle if it still exists
			sprintf(printC3, "%3d", Cir3.stay);
			glColor3f(0, 0, 2);
			renderBitmapString(Cir3.stayX, Cir3.stayY, 0, GLUT_BITMAP_8_BY_13, printC3);
		}

		if (Cir4.vanish == 0){
			char printC4[] = "foo";   //print value for third circle if it still exists
			sprintf(printC4, "%3d", Cir4.stay);
			glColor3f(2, 0, 2);
			renderBitmapString(Cir4.stayX, Cir4.stayY, 0, GLUT_BITMAP_8_BY_13, printC4);
		}



		if (Cir1.vanish == 0)
			DrawCircle(310, 185, 30, 50, 0, 5, 0);


		if (Cir2.vanish == 0)
			DrawCircle(465, 445, 30, 50, 5, 0, 0);


		if (Cir3.vanish == 0)
			DrawCircle(485, 235, 30, 50, 0, 5, 0);


		if (Cir4.vanish == 0)
			DrawCircle(330, 455, 30, 50, 5, 0, 0);



		////////////////////////////////////////FOR        FEATURE! //////////////////////////////////////////////////////////////////

		DrawCircle(400, 340, 30, 50, 1, 1, 1);

		renderBitmapString(390, 345, 0, GLUT_BITMAP_8_BY_13, ":o:    Double Attack Feature!");


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 1     TO    CIRCLE    2 //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mouse_X > 280 && mouse_X < 340 && mouse_Y > 150 && mouse_Y < 210 && Cir1.vanish == 0 && Cir1.path == 0){
			Circl1.activate = 1; //sensing first click                           ^Checks if it exists
			//Circl1.activate2 = 1;
		}

		if (Circl1.activate == 1){
			if (mouse_X > 430 && mouse_X < 490 && mouse_Y > 410 && mouse_Y < 470 && Cir2.vanish == 0){
				Circl1.target = 1;  //sensing second click                          ^checks if it exists
				Cir1.path = 1;
			}
		}

		if (Circl1.target == 1 && Cir1.vanish == 0)
			Circl1.activate = 0;  //re initialises this bad boy.


		if (Circl1.target == 1 && Cir1.path == 1 && Cir1.vanish == 0){    //if target has been pressed, this happens

			if ((int)Cir1.transX != (int)Cir2.stayX){  //checks if the moving point, is the same as the target point

				if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
					Cir1.transfer = Cir1.stay / 2;


				char printC1trans[] = "foo";        //for printing values on glwindow
				sprintf(printC1trans, "%3d", Cir1.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

				if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
					Cir1.stay = Cir1.stay / 2;

				Cir1.transX += increase(300, 450, 150);   //for moving the moving point trans
				Cir1.transY += increase(190, 450, 150);
			}

			else {   //otherwise if moving point reaches target this happens

				Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
				Cir1.transY = Cir1.stayY;

				Circl1.target = 0;  //turns the click target back 0, so that we can attack again              

				Cir2.stay = Cir2.stay - Cir1.transfer;   //reduces the value of target.

				if (Cir2.stay < 1){
					Cir2.vanish = 1;   //if target value is less than 1, it is vanished.
				}

				Cir1.path = 0;
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 1     TO    CIRCLE    3 //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		if (mouse_X > 280 && mouse_X < 340 && mouse_Y > 150 && mouse_Y < 210 && Cir1.vanish == 0 && Cir1.path == 0){
			Circl1.activate = 1; //sensing first click                           ^Checks if it exists
			//Circl1.activate2 = 1;
		}

		if (Circl1.activate == 1){
			if (mouse_X > 450 && mouse_X < 510 && mouse_Y > 200 && mouse_Y < 260 && Cir3.vanish == 0){
				Circl1.target = 1;  //sensing second click                          ^checks if it exists
				Cir1.path = 2;
			}
		}

		if (Circl1.target == 1 && Cir1.vanish == 0)
			Circl1.activate = 0;  //re initialises this bad boy.


		if (Circl1.target == 1 && Cir1.path == 2 && Cir1.vanish == 0){    //if target has been pressed, this happens

			if ((int)Cir1.transX < (int)Cir3.stayX){  //checks if the moving point, is the same as the target point

				if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
					Cir1.transfer = Cir1.stay / 2;


				char printC1trans[] = "foo";        //for printing values on glwindow
				sprintf(printC1trans, "%3d", Cir1.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

				if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
					Cir1.stay = Cir1.stay / 2;

				Cir1.transX += increase(300, 470, 60);   //for moving the moving point trans
				Cir1.transY += increase(190, 240, 60);
			}

			else {   //otherwise if moving point reaches target this happens

				Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
				Cir1.transY = Cir1.stayY;

				Circl1.target = 0;  //turns the click target back 0, so that we can attack again

				Cir3.stay = Cir3.stay + Cir1.transfer;   //reduces the value of target.

				Cir1.path = 0;
			}
		}



		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 1     TO    CIRCLE    4 //////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mouse_X > 280 && mouse_X < 340 && mouse_Y > 150 && mouse_Y < 210 && Cir1.vanish == 0 && Cir1.path == 0){
			Circl1.activate = 1; //sensing first click                           ^Checks if it exists
			//Circl1.activate2 = 1;
		}

		if (Circl1.activate == 1){
			if (mouse_X > 300 && mouse_X < 360 && mouse_Y > 420 && mouse_Y < 480 && Cir4.vanish == 0){
				Circl1.target = 1;  //sensing second click                          ^checks if it exists
				Cir1.path = 3;
			}
		}

		if (Circl1.target == 1 && Cir1.vanish == 0)
			Circl1.activate = 0;  //re initialises this bad boy.


		if (Circl1.target == 1 && Cir1.path == 3 && Cir1.vanish == 0){    //if target has been pressed, this happens

			if ((int)Cir1.transX < (int)Cir4.stayX){  //checks if the moving point, is the same as the target point

				if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
					Cir1.transfer = Cir1.stay / 2;


				char printC1trans[] = "foo";        //for printing values on glwindow
				sprintf(printC1trans, "%3d", Cir1.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

				if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
					Cir1.stay = Cir1.stay / 2;

				Cir1.transX += increase(300, 320, 150);   //for moving the moving point trans
				Cir1.transY += increase(190, 460, 150);
			}

			else {   //otherwise if moving point reaches target this happens

				Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
				Cir1.transY = Cir1.stayY;

				Circl1.target = 0;  //turns the click target back 0, so that we can attack again

				Cir4.stay = Cir4.stay - Cir1.transfer;   //reduces the value of target.

				if (Cir4.stay < 1)
					Cir4.vanish = 1;

				Cir1.path = 0;
			}
		}


		if (time % 30 == 0){
			Cir1.stay++;
			Cir2.stay++;
			Cir3.stay++;
			Cir4.stay++;
		}

		time++;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 1     TO    FEATURE //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mouse_X > 280 && mouse_X < 340 && mouse_Y > 150 && mouse_Y < 210 && Cir1.vanish == 0 && Cir1.path == 0){
			Circl1.activate = 1; //sensing first click                           ^Checks if it exists
			//Circl1.activate2 = 1;
		}

		if (Circl1.activate == 1){
			if (mouse_X > 370 && mouse_X < 430 && mouse_Y > 310 && mouse_Y < 370){
				Circl1.target = 1;  //sensing second click                          
				Cir1.path = 4;

			}
		}

		if (Circl1.target == 1 && Cir1.vanish == 0)
			Circl1.activate = 0;  //re initialises this bad boy.


		if (Circl1.target == 1 && Cir1.path == 4 && Cir1.vanish == 0){    //if target has been pressed, this happens

			if ((int)Cir1.transX < 400){  //checks if the moving point, is the same as the target point

				if (Cir1.transX == Cir1.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
					Cir1.transfer = Cir1.stay / 2;


				char printC1trans[] = "foo";        //for printing values on glwindow
				sprintf(printC1trans, "%3d", Cir1.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

				if (Cir1.stayX == Cir1.transX)  //when moving and initial are in the same place, stay becomes half
					Cir1.stay = Cir1.stay / 2;

				Cir1.transX += increase(300, 400, 80);   //for moving the moving point trans
				Cir1.transY += increase(190, 340, 80);
				Dualc1.featX = 400;
				Dualc1.featY = 340;
			}

			else {   //otherwise if moving point reaches target this happens

				if ((int)Cir1.transX < (int)Cir2.stayX){  //checks if the moving point, is the same as the target point

					char printC1trans[] = "foo";        //for printing values on glwindow
					sprintf(printC1trans, "%3d", Cir1.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Cir1.transX, Cir1.transY, 0, GLUT_BITMAP_8_BY_13, printC1trans);

					Cir1.transX += increase(400, Cir2.stayX, 70);   //for moving the moving point trans
					Cir1.transY += increase(340, Cir2.stayY, 70);
				}

				else {   //otherwise if moving point reaches target this happens

					Circl1.target = 0;  //turns the click target back 0, so that we can attack again

					Cir2.stay = Cir2.stay - Cir1.transfer;   //reduces the value of target.

					if (Cir2.stay < 1)
						Cir2.vanish = 1;

					Cir1.path = 0;

				}

				if ((int)Dualc1.featX >(int)Cir4.stayX){  //checks if the moving point, is the same as the target point

					char printF1trans[] = "foo";        //for printing values on glwindow
					sprintf(printF1trans, "%3d", Cir1.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Dualc1.featX, Dualc1.featY, 0, GLUT_BITMAP_8_BY_13, printF1trans);


					Dualc1.featX += increase(400, Cir4.stayX, 70);   //for moving the moving point trans
					Dualc1.featY += increase(340, Cir4.stayY, 70);
				}

				else {   //otherwise if moving point reaches target this happens

					Cir1.transX = Cir1.stayX;  //gives the initial coordinates to the moving point
					Cir1.transY = Cir1.stayY;

					Circl1.target = 0;  //turns the click target back 0, so that we can attack again

					Cir4.stay = Cir4.stay - Cir1.transfer;   //reduces the value of target.

					if (Cir4.stay < 1)
						Cir4.vanish = 1;

					Cir1.path = 0;
				}


			}
		}





		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 3     TO    CIRCLE    2 //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mouse_X > 450 && mouse_X < 510 && mouse_Y > 200 && mouse_Y < 260 && Cir3.vanish == 0 && Cir3.path == 0){
			Circl3.activate = 1; //sensing first click                           ^Checks if it exists
			//Circl1.activate2 = 1;
		}

		if (Circl3.activate == 1){
			if (mouse_X > 430 && mouse_X < 490 && mouse_Y > 410 && mouse_Y < 470 && Cir2.vanish == 0){
				Circl3.target = 1;  //sensing second click                          ^checks if it exists
				Cir3.path = 1;
			}
		}

		if (Circl3.target == 1 && Cir3.vanish == 0)
			Circl3.activate = 0;  //re initialises this bad boy.


		if (Circl3.target == 1 && Cir3.path == 1 && Cir3.vanish == 0){    //if target has been pressed, this happens

			if ((int)Cir3.transX > (int)Cir2.stayX){  //checks if the moving point, is the same as the target point

				if (Cir3.transX == Cir3.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
					Cir3.transfer = Cir3.stay / 2;


				char printC3trans[] = "foo";        //for printing values on glwindow
				sprintf(printC3trans, "%3d", Cir3.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

				if (Cir3.stayX == Cir3.transX)  //when moving and initial are in the same place, stay becomes half
					Cir3.stay = Cir3.stay / 2;

				Cir3.transX += increase(Cir3.stayX, Cir2.stayX, 150);   //for moving the moving point trans
				Cir3.transY += increase(Cir3.stayY, Cir2.stayY, 150);
			}

			else {   //otherwise if moving point reaches target this happens

				Cir3.transX = Cir3.stayX;  //gives the initial coordinates to the moving point
				Cir3.transY = Cir3.stayY;

				Circl3.target = 0;  //turns the click target back 0, so that we can attack again              

				Cir2.stay = Cir2.stay - Cir3.transfer;   //reduces the value of target.

				if (Cir2.stay < 1){
					Cir2.vanish = 1;   //if target value is less than 1, it is vanished.
				}

				Cir3.path = 0;
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 3     TO    CIRCLE    1 //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



		if (mouse_X > 450 && mouse_X < 510 && mouse_Y > 200 && mouse_Y < 260 && Cir3.vanish == 0 && Cir3.path == 0){
			Circl3.activate = 1; //sensing first click                           ^Checks if it exists
			//Circl1.activate2 = 1;
		}

		if (Circl3.activate == 1){
			if (mouse_X > 280 && mouse_X < 340 && mouse_Y > 150 && mouse_Y < 210 && Cir1.vanish == 0){
				Circl3.target = 1;  //sensing second click                          ^checks if it exists
				Cir3.path = 2;
			}
		}

		if (Circl3.target == 1 && Cir3.vanish == 0)
			Circl3.activate = 0;  //re initialises this bad boy.


		if (Circl3.target == 1 && Cir3.path == 2 && Cir3.vanish == 0){    //if target has been pressed, this happens

			if ((int)Cir3.transX > (int)Cir1.stayX){  //checks if the moving point, is the same as the target point

				if (Cir3.transX == Cir3.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
					Cir3.transfer = Cir3.stay / 2;


				char printC3trans[] = "foo";        //for printing values on glwindow
				sprintf(printC3trans, "%3d", Cir3.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

				if (Cir3.stayX == Cir3.transX)  //when moving and initial are in the same place, stay becomes half
					Cir3.stay = Cir3.stay / 2;

				Cir3.transX += increase(Cir3.stayX, Cir1.stayX, 60);   //for moving the moving point trans
				Cir3.transY += increase(Cir3.stayY, Cir1.stayY, 60);
			}

			else {   //otherwise if moving point reaches target this happens

				Cir3.transX = Cir3.stayX;  //gives the initial coordinates to the moving point
				Cir3.transY = Cir3.stayY;

				Circl3.target = 0;  //turns the click target back 0, so that we can attack again

				Cir1.stay = Cir1.stay + Cir3.transfer;   //reduces the value of target.

				Cir3.path = 0;
			}
		}



		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 3     TO    CIRCLE    4 //////////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mouse_X > 450 && mouse_X < 510 && mouse_Y > 200 && mouse_Y < 260 && Cir3.vanish == 0 && Cir3.path == 0){
			Circl3.activate = 1; //sensing first click                           ^Checks if it exists
			//Circl1.activate2 = 1;
		}

		if (Circl3.activate == 1){
			if (mouse_X > 300 && mouse_X < 360 && mouse_Y > 420 && mouse_Y < 480 && Cir4.vanish == 0){
				Circl3.target = 1;  //sensing second click                          ^checks if it exists
				Cir3.path = 3;
			}
		}

		if (Circl3.target == 1 && Cir3.vanish == 0)
			Circl3.activate = 0;  //re initialises this bad boy.


		if (Circl3.target == 1 && Cir3.path == 3 && Cir3.vanish == 0){    //if target has been pressed, this happens

			if ((int)Cir3.transX > (int)Cir4.stayX){  //checks if the moving point, is the same as the target point

				if (Cir3.transX == Cir3.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
					Cir3.transfer = Cir3.stay / 2;


				char printC3trans[] = "foo";        //for printing values on glwindow
				sprintf(printC3trans, "%3d", Cir3.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

				if (Cir3.stayX == Cir3.transX)  //when moving and initial are in the same place, stay becomes half
					Cir3.stay = Cir3.stay / 2;

				Cir3.transX += increase(Cir3.stayX, Cir4.stayX, 150);   //for moving the moving point trans
				Cir3.transY += increase(Cir3.stayY, Cir4.stayY, 150);
			}

			else {   //otherwise if moving point reaches target this happens

				Cir3.transX = Cir3.stayX;  //gives the initial coordinates to the moving point
				Cir3.transY = Cir3.stayY;

				Circl3.target = 0;  //turns the click target back 0, so that we can attack again

				Cir4.stay = Cir4.stay - Cir3.transfer;   //reduces the value of target.

				Cir3.path = 0;
			}
		}


		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////////FROM     CIRCLE 3     TO    FEATURE //////////////////////////////////////////////////
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		if (mouse_X > 450 && mouse_X < 510 && mouse_Y > 200 && mouse_Y < 260 && Cir3.vanish == 0 && Cir3.path == 0){
			Circl3.activate = 1; //sensing first click                           ^Checks if it exists
			//Circl1.activate2 = 1;
		}

		if (Circl3.activate == 1){
			if (mouse_X > 370 && mouse_X < 430 && mouse_Y > 310 && mouse_Y < 370){
				Circl3.target = 1;  //sensing second click                          
				Cir3.path = 4;

			}
		}

		if (Circl3.target == 1 && Cir3.vanish == 0)
			Circl3.activate = 0;  //re initialises this bad boy.


		if (Circl3.target == 1 && Cir3.path == 4 && Cir3.vanish == 0){    //if target has been pressed, this happens

			if ((int)Cir3.transY < 340){  //checks if the moving point, is the same as the target point

				if (Cir3.transX == Cir3.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
					Cir3.transfer = Cir3.stay / 2;


				char printC3trans[] = "foo";        //for printing values on glwindow
				sprintf(printC3trans, "%3d", Cir3.transfer);
				glColor3f(0, 0, 2);
				renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

				if (Cir3.stayX == Cir3.transX)  //when moving and initial are in the same place, stay becomes half
					Cir3.stay = Cir3.stay / 2;

				Cir3.transX += increase(Cir3.stayX, 400, 80);   //for moving the moving point trans
				Cir3.transY += increase(Cir3.stayY, 340, 80);
				Dualc3.featX = 400;
				Dualc3.featY = 340;
			}

			else {   //otherwise if moving point reaches target this happens

				if ((int)Cir3.transX < (int)Cir2.stayX){  //checks if the moving point, is the same as the target point

					char printC3trans[] = "foo";        //for printing values on glwindow
					sprintf(printC3trans, "%3d", Cir3.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Cir3.transX, Cir3.transY, 0, GLUT_BITMAP_8_BY_13, printC3trans);

					Cir3.transX += increase(400, Cir2.stayX, 70);   //for moving the moving point trans
					Cir3.transY += increase(340, Cir2.stayY, 70);
				}

				else {   //otherwise if moving point reaches target this happens

					Circl3.target = 0;  //turns the click target back 0, so that we can attack again

					Cir2.stay = Cir2.stay - Cir3.transfer;   //reduces the value of target.

					if (Cir2.stay < 1)
						Cir2.vanish = 1;

					Cir3.path = 0;

				}

				if ((int)Dualc3.featX >(int)Cir4.stayX){  //checks if the moving point, is the same as the target point

					char printF3trans[] = "foo";        //for printing values on glwindow
					sprintf(printF3trans, "%3d", Cir3.transfer);
					glColor3f(0, 0, 2);
					renderBitmapString(Dualc3.featX, Dualc3.featY, 0, GLUT_BITMAP_8_BY_13, printF3trans);


					Dualc3.featX += increase(400, Cir4.stayX, 70);   //for moving the moving point trans
					Dualc3.featY += increase(340, Cir4.stayY, 70);
				}

				else {   //otherwise if moving point reaches target this happens

					Cir3.transX = Cir3.stayX;  //gives the initial coordinates to the moving point
					Cir3.transY = Cir3.stayY;

					Circl3.target = 0;  //turns the click target back 0, so that we can attack again

					Cir4.stay = Cir4.stay - Cir3.transfer;   //reduces the value of target.

					if (Cir4.stay < 1)
						Cir4.vanish = 1;

					Cir3.path = 0;
				}


			}

		}

		////////////////////////////////////////  COMPUTER'S   CODE /////////////////////////////////////////////////////////////////////////

		if (compturn < 5){
			if (Cir4.vanish == 0){
				if ((int)Cir4.transX < (int)Cir2.stayX){
					if (Cir4.transX == Cir4.stayX){
						Cir4.transfer = Cir4.stay / 2;
						Cir4.stay = Cir4.stay / 2;
					}

					char printC4tran[] = "foo";
					sprintf(printC4tran, "%3d", Cir4.transfer);
					glColor3f(2, 0, 0);
					renderBitmapString(Cir4.transX, Cir4.transY, 0, GLUT_BITMAP_8_BY_13, printC4tran);


					Cir4.transX += increase(Cir4.stayX, Cir2.stayX, 30);
					Cir4.transY += increase(Cir4.stayY, Cir2.stayY, 30);
				}

				else {
					Cir4.transX = Cir4.stayX;
					Cir4.transY = Cir4.stayY;
					Cir2.stay = Cir2.stay + Cir4.transfer;
					compturn++;
				}
			}
		}
		else {
			if (Cir2.vanish == 0 && (Cir1.vanish == 0 || Cir3.vanish == 0)){
				if ((int)Cir2.transY > 340){  //checks if the moving point, is the same as the target point

					if (Cir2.transX == Cir2.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
						Cir2.transfer = Cir2.stay / 2;


					char printC2trans[] = "foo";        //for printing values on glwindow
					sprintf(printC2trans, "%3d", Cir2.transfer);
					glColor3f(2, 0, 0);
					renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2trans);

					if (Cir2.stayX == Cir2.transX)  //when moving and initial are in the same place, stay becomes half
						Cir2.stay = Cir2.stay / 2;

					Cir2.transX += increase(Cir2.stayX, 380, 80);   //for moving the moving point trans
					Cir2.transY += increase(Cir2.stayY, 340, 80);
					Dualc2.featX = 380;
					Dualc2.featY = 340;
				}

				else {   //otherwise if moving point reaches target this happens

					if ((int)Cir2.transX < (int)Cir3.stayX){  //checks if the moving point, is the same as the target point

						char printC2trans[] = "foo";        //for printing values on glwindow
						sprintf(printC2trans, "%3d", Cir2.transfer);
						glColor3f(2, 0, 0);
						renderBitmapString(Cir2.transX, Cir2.transY, 0, GLUT_BITMAP_8_BY_13, printC2trans);

						Cir2.transX += increase(380, Cir3.stayX, 70);   //for moving the moving point trans
						Cir2.transY += increase(340, Cir3.stayY, 70);
					}

					if ((int)Dualc2.featX > (int)Cir1.stayX){  //checks if the moving point, is the same as the target point

						char printF2trans[] = "foo";        //for printing values on glwindow
						sprintf(printF2trans, "%3d", Cir2.transfer);
						glColor3f(2, 0, 0);
						renderBitmapString(Dualc2.featX, Dualc2.featY, 0, GLUT_BITMAP_8_BY_13, printF2trans);


						Dualc2.featX += increase(380, Cir1.stayX, 70);   //for moving the moving point trans
						Dualc2.featY += increase(340, Cir1.stayY, 70);
					}

					else {   //otherwise if moving point reaches target this happens

						Cir2.transX = Cir2.stayX;  //gives the initial coordinates to the moving point
						Cir2.transY = Cir2.stayY;

						Cir1.stay = Cir1.stay - Cir2.transfer;   //reduces the value of target.
						Cir3.stay = Cir3.stay - Cir2.transfer;   //reduces the value of target.

						if (Cir1.stay < 1)
							Cir1.vanish = 1;

						if (Cir3.stay < 1)
							Cir3.vanish = 1;

					}
				}

				if (Cir4.vanish == 0 && (Cir1.vanish == 0 || Cir3.vanish == 0)){
					if ((int)Cir4.transY > 340){  //checks if the moving point, is the same as the target point

						if (Cir4.transX == Cir4.stayX)   //when moving and initial points are at the same place, trans(moving) gets half of stay(initial)
							Cir4.transfer = Cir4.stay / 2;


						char printC4trans[] = "foo";        //for printing values on glwindow
						sprintf(printC4trans, "%3d", Cir4.transfer);
						glColor3f(2, 0, 0);
						renderBitmapString(Cir4.transX, Cir4.transY, 0, GLUT_BITMAP_8_BY_13, printC4trans);

						if (Cir4.stayX == Cir4.transX)  //when moving and initial are in the same place, stay becomes half
							Cir4.stay = Cir4.stay / 2;

						Cir4.transX += increase(Cir4.stayX, 380, 80);   //for moving the moving point trans
						Cir4.transY += increase(Cir4.stayY, 340, 80);
						Dualc4.featX = 380;
						Dualc4.featY = 340;
					}

					else {   //otherwise if moving point reaches target this happens

						if ((int)Cir4.transX < (int)Cir3.stayX){  //checks if the moving point, is the same as the target point

							char printC4trans[] = "foo";        //for printing values on glwindow
							sprintf(printC4trans, "%3d", Cir4.transfer);
							glColor3f(2, 0, 0);
							renderBitmapString(Cir4.transX, Cir4.transY, 0, GLUT_BITMAP_8_BY_13, printC4trans);

							Cir4.transX += increase(380, Cir3.stayX, 70);   //for moving the moving point trans
							Cir4.transY += increase(340, Cir3.stayY, 70);
						}


						if ((int)Dualc4.featX > (int)Cir1.stayX){  //checks if the moving point, is the same as the target point

							char printF4trans[] = "foo";        //for printing values on glwindow
							sprintf(printF4trans, "%3d", Cir4.transfer);
							glColor3f(2, 0, 0);
							renderBitmapString(Dualc4.featX, Dualc4.featY, 0, GLUT_BITMAP_8_BY_13, printF4trans);


							Dualc4.featX += increase(380, Cir1.stayX, 70);   //for moving the moving point trans
							Dualc4.featY += increase(340, Cir1.stayY, 70);
						}

						else {   //otherwise if moving point reaches target this happens

							Cir4.transX = Cir4.stayX;  //gives the initial coordinates to the moving point
							Cir4.transY = Cir4.stayY;

							Cir1.stay = Cir1.stay - Cir4.transfer;   //reduces the value of target.
							Cir3.stay = Cir3.stay - Cir4.transfer;   //reduces the value of target.

							if (Cir1.stay < 1)
								Cir1.vanish = 1;

							if (Cir3.stay < 1)
								Cir3.vanish = 1;

						}
					}

				}
			}
		}


		if (Cir2.vanish != 0 && Cir4.vanish != 0 && (Cir1.vanish == 0 || Cir3.vanish == 0)){
			glColor3f(0, 4, 5);
			renderBitmapString(350, 320, 0, GLUT_BITMAP_TIMES_ROMAN_24, "YOU WIN!");

		}

		if (Cir1.vanish != 0 && Cir3.vanish != 0 && (Cir2.vanish == 0 || Cir4.vanish == 0)){
			glColor3f(5, 0, 0);
			renderBitmapString(350, 320, 0, GLUT_BITMAP_TIMES_ROMAN_24, "YOU LOSE!");
		}

		if (Cir1.vanish != 0 && Cir3.vanish != 0 && Cir2.vanish != 0 && Cir4.vanish != 0){
			glColor3f(5, 0, 0);
			renderBitmapString(350, 320, 0, GLUT_BITMAP_TIMES_ROMAN_24, "-- DRAW!");
		}



		if (time % 30 == 0){
			Cir1.stay++;
			Cir2.stay++;
			Cir3.stay++;
			Cir4.stay++;
		}

		time++;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////////////////////////// FOR                   RETURN                 BUTTON  /////////////////////////////////////////////
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


		DrawRectangle(500, 500, 150, 50, 0, 4, 2);
		renderBitmapString(520, 540, 0, GLUT_BITMAP_TIMES_ROMAN_24, "RETURN");


		if (mouse_X > 500 && mouse_X < 650 && mouse_Y>500 && mouse_Y < 550){
			level = 0;

			Cir1 = { 100, 50, 200, 200, 200, 200, 0, 0 };

			Cir2 = { 80, 25, 450, 450, 450, 450, 0, 0 };

			Cir3 = { 60, 30, 490, 255, 490, 255, 0, 0 };

			compturn = 1;

			Circl1 = { 0, 0, 0 };
			Circl3 = { 0, 0, 0 };

		}
		
	}
	

	Sleep(0.5);
	glEnd();


	glutSwapBuffers();		//brings the openGl window on the front

}