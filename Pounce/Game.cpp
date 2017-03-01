//
///*
//OBJECT ORIENTED PROGRAMMING
//END SEMESTER PROJECT
//POUNCE!   THE GAME
//
//Group Members:
//
//MUHAMMAD IBTESAM (NUST201432141BSEECS60514F)
//
//HAMZA JAVED (NUST201432976BSEECS60514F)
//
//FAIZAN ZAFAR (NUST201433125BSEECS60514F)
//
//
//Class:   BESE-5B
//
//*/
//
//
//
//#include <iostream>
//#include <conio.h>
//#include "GL/glut.h"
//#include "SOIL.h"   //for image loading 
//#include <Windows.h>
//
//using namespace std;
//
//GLuint myTexture;     //for image loading
//
//int g_Width = 400;		//define size of the window
//int g_Height = 400;
//
////global mouse position
//int mouse_X = 0;	//xcod
//int mouse_Y = 0;	//ycod
//
//
//
//GLuint _mainMenuTextureId;//The id of the background texture on main menu screen
//
//
//GLuint loadtexture(char *name)  //for image loading
//{
//	GLuint temp;
//
//	glGenTextures(1, &temp);
//
//	temp = SOIL_load_OGL_texture
//		(name, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_DDS_LOAD_DIRECT
//		);
//
//	return temp;
//}
//
//
//
//void background()   //also for image loading
//{
//	glEnable(GL_TEXTURE_2D);
//	glBindTexture(GL_TEXTURE_2D, _mainMenuTextureId);
//
//	//Bottom
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//	glColor3f(1.0f, 1.0f, 1.0f);
//	//glPushMatrix();
//	glScalef(1, 1, 1);
//	glColor4ub(255, 255, 255, 255);
//
//	glBegin(GL_POLYGON);
//
//	glTexCoord2f(0.0, 0.0);
//	glVertex3f(0, 0, 0.0);//draw square for menu
//	glTexCoord2f(1.0, 0.0);
//	glVertex2f(1350, 0.0);//2nd
//	glTexCoord2f(1.0, 1.0);
//	glVertex2f(1350, 700);//3rd 
//	glTexCoord2f(0.0, 1.0);
//	glVertex2f(0.0, 700);//4th
//
//	glEnd();
//	//glPopMatrix();
//
//	glDisable(GL_TEXTURE_2D);
//
//
//}
//
//
//
//
//
////////////////////////////////////////                 Ball Class               ///////////////////////////
//
//class Ball{   //The main Ball class, for the ball controlled by the user
//
//protected:    //because ball class is inherited ahead
//
//	float Xco;    //for Xco-ordinate
//	float Yco;     //for Y co-ordinate
//	float r, g, b;  //for color
//	float radius;  //for radius
//	float inertia;   //Using this for inertia feature
//	float life;    //for life status
//
//public:
//
//	Ball(){         //constructor
//
//		radius = 15;   //will create the ball
//		r = 2; g = 0; b = 0;
//
//		Xco = 200;  //positioning the ball
//		Yco = 415;
//
//		inertia = 0;  //initially inertia is 0
//
//		life = 1;   //Player has only one life
//
//	}
//
//	void set(float x, float y);   //for resetting the values
//
//	float surfaceS();  //return the Xcoordinates
//
//	float height();    //returns the Y coordinate
//
//	void moveRight();   //makes the ball move right
//
//	void moveLeft();  //makes the ball move left
//
//	float Radius(){  //returns the radius of ball
//
//		return radius;
//
//	}
//
//	void DrawCircle();   //draws the ball
//
//	float Inertia();   //returns inertia
//
//	void increaseInertia();   //increases inertia
//
//	void decreaseInertia();  //decreases inertia
//
//	void Jump(float *add, float surface);   //used for jumping
//
//	void fall();  //used when not in the vicinity of a platform
//
//	int Life(){   //returns the value of life
//
//		return life;
//
//	}
//
//	void changeLoc(float X, float Y){ Xco = X + 50; Yco = Y + 30; }    //for resetting location of ball
//
//	void death();   //for setting life to 0, when ball is killed/falls out of screen.
//
//};
//
//
//void Ball::death(){   //sets life to 0
//
//	life = 0;
//
//}
//
//
//void Ball::set(float x, float y){ //for resetting the values of ball
//
//	Xco = x;
//
//	Yco = y;
//
//	life = 1;
//
//}
//
//float Ball::surfaceS(){ //returns X coordinate of ball
//
//	return Xco;
//
//}
//
//float Ball::height(){  //returns Y coordinate of ball
//
//	return Yco + radius;
//
//}
//
//void Ball::moveRight(){  //makes the ball move right
//
//	try{
//
//		if (Xco > 1320)   //if X coordinate is going outside the screen towards the right, the exception is thrown
//			throw Xco;
//
//		Xco += 3;  //otherwise ball moves right through this
//
//	}
//
//	catch (float a){
//
//		Xco = 1319;  //if exception is thrown, ball stays at this point
//
//	}
//
//	increaseInertia();  //inertia is increased so that the ball remains going right when the user does not press the button
//
//}
//
//
//void Ball::moveLeft(){  //makes the ball move left
//
//	try{
//
//		if (Xco < 15)   //if the ball is going behind 15, exception is thrown
//			throw Xco;
//
//		Xco -= 3;  //makes the boll go left
//
//	}
//
//	catch (float b){
//
//		Xco = 14;  //if exception is thrown, the ball will stay on these coordinates
//
//	}
//
//	decreaseInertia();  //decreases inertia, so that the ball continues going left after user leaves the button
//
//}
//
//
//float Ball::Inertia(){  //returns the value of inertia
//
//	return inertia;
//
//}
//
//void Ball::increaseInertia(){  //sets inertia to 1
//
//	inertia = 1;
//
//}
//
//void Ball::decreaseInertia(){  //sets inertia to -1
//
//	inertia = -1;
//
//}
//
//
//int halt = 0;  //aids in jumping
//
//void Ball::Jump(float *add, float jumpPoint){  //used for jumping
//
//	if (*add == 0 && halt == 0){   //if up key isn't pressed and for motion upward  
//
//		Yco -= 4;   //this causes the jump animation
//
//		if (height() < (jumpPoint - 50))  //when it reaches this height, halt becomes 1 and the ball starts falling
//			halt = 1;
//
//	}
//
//	if (*add == 0 && halt == 1){   //if up key isn't pressed and for motion downward
//
//		Yco += 4;  //for the falling animation
//
//		if (height() > jumpPoint)
//			halt = 0;  //when the jumppoint is reached, it continues back to jumping
//
//	}
//
//	if (*add == 1 && halt == 0){  //if up key is pressed
//
//		Yco -= 6.2;   //the remaining code is similar to the upper one
//
//		if (height() < (jumpPoint - 100)){
//
//			halt = 1;
//
//			*add = 0;  //once highest point is reached, the jump which is passed to this, is set to 0 by reference
//
//		}
//
//	}
//
//	if (*add == 1 && halt == 1){  //if up key is pressed and ball is going down
//
//		Yco += 6;
//
//		if (Yco > jumpPoint - 20){
//
//			halt = 0;
//		}
//	}
//}
//
//void Ball::fall(){  //acts somewhat like gravity once the ball is outside the vicinity of the platforms
//
//	try{
//
//		if (Yco < 720)
//			Yco += 5;   //used for falling
//
//		else throw Yco;   //if ball goes outside the screen, this exception is thrown
//
//	}
//
//	catch (float c){
//
//		death();  //exception gets caught here and death of ball occurs.
//
//	}
//}
//
//void Ball::DrawCircle(){
//
//	if (life == 1){   //if ball is alive, colored ball is drawn.
//
//		glColor3f(r, g, b);
//
//		glBegin(GL_POLYGON);   //draws the circle
//
//		for (int ii = 0; ii < 50; ii++)  //draws the circle
//		{
//			float theta = 2.0f * 3.1415926f * float(ii) / float(50);  //get the current angle 
//
//			float x = radius * cosf(theta);  //calculate the x component 
//			float y = radius * sinf(theta);  //calculate the y component 
//
//			glVertex2f(x + Xco, y + Yco);//output vertex 
//
//		}
//
//		glEnd();
//
//	}
//
//	if (life == 0){  //if ball has died, black ball is drawn
//
//		glColor3f(0, 0, 0);
//
//		glBegin(GL_POLYGON);  //for drawing the circle
//
//		for (int ii = 0; ii < 50; ii++)
//		{
//			float theta = 2.0f * 3.1415926f * float(ii) / float(50);  //get the current angle 
//
//			float x = radius * cosf(theta);  //calculate the x component 
//			float y = radius * sinf(theta);  //calculate the y component 
//
//			glVertex2f(x + Xco, y + Yco);//output vertex 
//
//		}
//
//		glEnd();
//	}
//}
//
//
//
//
//
////////////////////////////////////////                 Platform Class               ///////////////////////////
//
//class Platform{   //platform class
//
//protected:  //class is inherited later
//
//	float Xco;   //for coordinates
//	float Yco;
//	float width;  //for width
//	float height;  //for height
//
//public:
//
//	Platform(float a, float b, float c, float d) :Xco(a), Yco(b), width(c), height(d){};  //constructor
//
//	void set(float x, float y, float w, float h);  //for resetting the values
//
//	void DrawPlatform();  //for drawing the platform
//
//	bool compareX(float X);  //for comparing the Xcoordinates
//
//	bool compareY(float Y);  //for comparing the Y coordinates
//
//	float Surface();  //returns Y coordinates
//
//	float XC(){  //returns Xcoordinate
//
//		return Xco;
//
//	}
//
//};
//
//void Platform::set(float x, float y, float w, float h){  //for resetting values
//
//	Xco = x;
//
//	Yco = y;
//
//	width = w;
//
//	height = h;
//
//}
//
//void Platform::DrawPlatform(){  //draws the rectangle for the platform
//
//	glColor3f(0, 0, 1);
//
//	glBegin(GL_POLYGON);  //draws the platform
//
//	glVertex2f(Xco, Yco);
//	glVertex2f(Xco + width, Yco);
//	glVertex2f(Xco + width, Yco + height);
//	glVertex2f(Xco, Yco + height);
//
//	glEnd();
//
//}
//
//bool Platform::compareX(float X){
//
//	if ((X > Xco - 6) && X < (Xco + width + 6))  //compares the X coordinate with passed value of ball
//		return true;
//
//	else return false;
//
//}
//
//bool Platform::compareY(float Y){
//
//	if ((Y < (Yco + height)))  //compares Y coordinate
//		return true;
//
//	else return false;
//
//}
//
//float Platform::Surface(){ //returns Y coordinate
//
//	return Yco;
//
//}
//
//
//
//
////////////////////////////////////////                 Moving Platform Class               ///////////////////////////
//
//class movingPlatform :public Platform{  //moving platform class derived from platform
//
//private:
//
//	float beginPoint;  //used for the movement
//	float endPoint;
//	int c;
//
//public:
//
//	movingPlatform(float a, float b, float c, float d, float begin, float end) :Platform(a, b, c, d), beginPoint(begin), endPoint(end){}
//
//	void set(float x, float y, float begin, float end); //for resetting the values
//
//	void Behaviour();  //this function controls the motion of the platform
//
//};
//
//
//void movingPlatform::set(float x, float y, float begin, float end){  //resets the values
//
//	Xco = x;
//
//	Yco = y;
//
//	beginPoint = begin;
//
//	endPoint = end;
//
//}
//
//
//void movingPlatform::Behaviour(){  //controls the motion of the ball
//
//	if (c == 0){
//
//		Xco += 3;  //moves right until the below point is reached, c turns 1 there and then it moves left
//
//		if ((Xco > endPoint - 4))
//			c = 1;
//
//	}
//
//	if (c == 1){
//
//		Xco -= 3;  //moves left until below point is reached, c turns 0 and then it moves right
//
//		if (Xco < (beginPoint + 4))
//			c = 0;
//
//	}
//
//}
//
//
//
////////////////////////////////////////                 Coin Class               ///////////////////////////
//
//class Coin{  //coin class
//
//protected:  //is inherited by supercoin class
//
//	int vanish;   //checks if coin has been collided with
//	static int score;     //for score
//	float Xco;        //coordinates
//	float Yco;
//	float rad;      //radius
//
//public:
//
//	Coin(float X, float Y, float r) :Xco(X), Yco(Y), rad(r){ score = 0; }  //constructor
//
//	void set(float x, float y);  //for resetting the values
//
//	void drawRing(int segments);  //for drawing ring of coin
//
//	void incScore();  //increases score
//
//	void VanishCoin(){
//
//		vanish = 1;
//
//	}  //makes the ball vanish on collision
//
//	int Van(){
//
//		return vanish;
//
//	}  //returns value of vanish
//
//	bool Collision(Ball a);  //collision algorithm
//
//	float X(){ //returns X coordinate
//
//		return Xco;
//
//	}
//
//	float Y(){ //returns Y coordinate
//
//		return Yco;
//
//	}
//
//	int retScore(){  //returns score
//
//		return score;
//
//	}
//
//};
//
//int Coin::score = 0;  //sets value of score to 0
//
//void Coin::set(float x, float y){  //for resetting the values
//
//	Xco = x;
//
//	Yco = y;
//
//	vanish = 0;
//
//}
//
//void Coin::drawRing(int segments){  //for drawing coin
//
//	glColor3f(1.0, 2.0, 0.0);  //red color
//
//	glBegin(GL_LINE_LOOP);
//	glVertex2f(Xco, Yco);
//
//	for (int n = 0; n <= segments; ++n) {
//		float const t = 2 * 3.1415926*(float)n / (float)segments;
//		glVertex2f(Xco + sin(t)*rad, Yco + cos(t)*rad);
//	}
//
//	glEnd();
//
//}
//
//void Coin::incScore(){ //increases score
//
//	score++;
//
//}
//
//bool Coin::Collision(Ball a){  //checks if it collided with the ball
//
//	if (((a.surfaceS() + a.Radius() > Xco)) && (a.surfaceS() + a.Radius() < (Xco + 2 * rad)) && (a.height() > (Yco - rad)) && (a.height() < (Yco + rad))){
//
//		return true;
//
//	}
//
//	else return false;
//
//}
//
//
////////////////////////////////////////                 Door Class               ///////////////////////////
//
//class Door{  //class door used as portal
//
//protected:  //inherited by nextleveldoor
//
//	float Xco;  //for coordinates
//	float Yco;
//	float height;  //for height
//	float width;  //for width
//
//public:
//	Door(float a, float b, float c, float d) :Xco(a), Yco(b), width(c), height(d){};  //constructor
//
//	void drawDoor();  //draws door
//
//	void set(float x, float y);  //resets the value
//
//	bool Collision(Ball); //checks collision
//
//	float retX(){  //returns X coordinate
//
//		return Xco;
//
//	}
//
//	float retY(){ //returns Y coordinate
//
//		return Yco;
//	}
//
//};
//
//void Door::set(float x, float y){ //for resetting the coordinates
//
//	Xco = x;
//	Yco = y;
//
//}
//
//void Door::drawDoor(){  //for drawing door
//
//	glColor3f(1, 0, 1);
//
//	glBegin(GL_POLYGON);  //draws ze door
//	glVertex2f(Xco, Yco);
//	glVertex2f(Xco + width, Yco);
//	glVertex2f(Xco + width, Yco + height);
//	glVertex2f(Xco, Yco + height);
//
//	glEnd();
//
//}
//
//bool Door::Collision(Ball ball){ //checks if door and ball collide
//
//	if (ball.surfaceS() > Xco && ball.surfaceS() < Xco + width && ball.height() > Yco && ball.height() < Yco + height)
//		return true;
//
//	else return false;
//
//}
//
//class NextLevelDoor : public Door{  //nextleveldoor class derived from class door
//
//private:
//
//	int nextLevel;
//
//public:
//
//	NextLevelDoor(float a, float b, float c, float d) :Door(a, b, c, d){}  //constructor
//
//	void drawDoor(); //draws door
//
//};
//
//void NextLevelDoor::drawDoor(){  //for drawing door
//
//	glColor3f(1, 1, 0);  //different color than before
//
//	glBegin(GL_POLYGON);
//	glVertex2f(Xco, Yco);
//	glVertex2f(Xco + width, Yco);
//	glVertex2f(Xco + width, Yco + height);
//	glVertex2f(Xco, Yco + height);
//
//	glEnd();
//}
//
//
//
////////////////////////////////////////                 SuperCoin Class               ///////////////////////////
//
//class superCoin :public Coin{
//
//private:
//
//	int power;
//
//public:
//
//	superCoin(int a, float X, float Y, float r) :power(a), Coin(X, Y, r){ vanish = 0; }  //constructor
//
//	int getPower();  //returns value of Power
//
//	void setPower(int);  //sets value to power
//
//	void drawRing(int segments);  //draws the coin
//
//	void Collision(Ball &ball);   //checks the collision with the ball
//
//};
//
//void superCoin::drawRing(int segments){  //for drawing the superCoin
//
//	glBegin(GL_POLYGON);
//
//	glColor3f(2, 1, 0);   //for drawing the circle
//	glVertex2f(Xco, Yco);
//	for (int n = 0; n <= segments; ++n) {
//		float const t = 2 * 3.1415926*(float)n / (float)segments;
//		glVertex2f(Xco + sin(t)*rad, Yco + cos(t)*rad);
//	}
//
//	glEnd();
//
//}
//
//int superCoin::getPower(){  //returns value of power
//
//	return power;
//
//}
//
//void superCoin::setPower(int x){  //sets value to power
//
//	power = x;
//
//}
//
//
//void superCoin::Collision(Ball &ball){   //checks if coin and ball collided, if they did, super coin vanishes
//
//	if (((Xco > ball.surfaceS()) && (Xco<(ball.surfaceS() + 2 * ball.Radius())) && (Yco>ball.height()) && (Yco < (ball.height() + 2 * ball.Radius())))){
//
//		vanish = 1;
//
//	}
//}
//
//
//
//
////////////////////////////////////////                 Enemy Class               ///////////////////////////
//
//class Enemy :public Ball{
//
//	float beginPoint;   //used for moving the enemy on platform
//	float endPoint;
//	bool eatable;  //checks if it is eatable
//	int vanish;  //vanishes enemy once eate,
//	int c;  //used in movement
//	static int count;  //for counting enemies
//
//public:
//
//	Enemy(float x, float y, float begin, float end);  //contsructor
//
//	void set(float x, float y, float begin, float end);  //for setting values of enemy
//
//	void Collision(Ball &ball);  //for checking collision
//
//	void state();  //for changing state from not eatable to eatable
//
//	int Count(){   //returns value of count
//
//		return count;
//
//	}
//
//	void Draw();  //draws enemy
//
//	int Van(){   //returns value of vanish
//
//		return vanish;
//
//	}
//
//	void Behaviour();  //causes the movement of enemy
//
//};
//
//int Enemy::count = 0;  //sets value of count to 0
//
//
//Enemy::Enemy(float x, float y, float begin, float end){  //constructor
//
//	Xco = x;
//	Yco = y;
//	c = 0;
//	beginPoint = begin;
//	endPoint = end;
//	r = 0;
//	g = 2;
//	b = 0;
//	radius = 10;
//	eatable = false;   //initially not eatable
//	vanish = 0;  //not vanishing initially
//
//}
//
//
//void Enemy::set(float x, float y, float begin, float end){  //for resetting values
//
//	Xco = x;
//	Yco = y;
//	c = 0;
//	beginPoint = begin;
//	endPoint = end;
//	r = 0;
//	g = 2;
//	b = 0;
//	radius = 10;
//	eatable = false;  //sets eatable to false, hence not eatable
//	vanish = 0;  //not vanishing
//
//}
//
//
//void Enemy::Draw(){   //draws enemy
//
//	if (vanish == 0){   //if it has not vanished, the enemy is drawn
//
//		glColor3f(r, g, b);
//
//		glBegin(GL_POLYGON);    //for drawing enemy circle
//
//		for (int ii = 0; ii < 50; ii++)
//		{
//			float theta = 2.0f * 3.1415926f * float(ii) / float(50);  //get the current angle 
//			float x = radius * cosf(theta);  //calculate the x component 
//			float y = radius * sinf(theta);  //calculate the y component 
//
//			glVertex2f(x + Xco, y + Yco);//output vertex 
//
//		}
//
//		glEnd();
//	}
//}
//
//
//void Enemy::state(){  //makes it go from not eatable to eatable
//
//	eatable = true;
//
//}
//
//
//void Enemy::Collision(Ball &ball){
//
//	if (!eatable){  //if the enemy is not eatable, the collision ends in the ball being killed
//
//		if (((Xco>ball.surfaceS()) && (Xco<(ball.surfaceS() + 2 * ball.Radius())) && (Yco>ball.height()) && (Yco < (ball.height() + 2 * ball.Radius()))))
//			ball.death();  // ^ checks collision
//
//	}
//
//	if (eatable){  //if the enemy is eatable, the collision ends in the enemy being eaten
//
//		r = 2;   //if eatable, color changes to yellow. 
//		g = 1;
//		b = 0;
//
//		if (((Xco>ball.surfaceS()) && (Xco<(ball.surfaceS() + 2 * ball.Radius())) && (Yco>ball.height()) && (Yco < (ball.height() + 2 * ball.Radius())))){
//
//			count++;
//			vanish = 1;  //for making enemy vanish
//
//		}
//
//	}
//
//}
//
//
//void Enemy::Behaviour(){  //for making enemy move over platform
//
//	if (c == 0){
//
//		Xco += 3;   //goes right till below point is reached, then moves left
//
//		if ((Xco > endPoint - 4))
//			c = 1;
//
//	}
//
//	if (c == 1){
//
//		Xco -= 3;  //moves left till below point is reached, then moves right
//
//		if (Xco < (beginPoint + 4))
//			c = 0;
//
//	}
//
//}
//
//
//
////////////////////////////////////////                 Boss Class               ///////////////////////////
//
//class Boss :public Ball{  //derived from ball
//
//	bool eatable;  //checks if eatable
//	int halt;  //used for jump
//	int vanish;  //checks if vanished
//
//public:
//
//	Boss(float x, float y){ //constructor
//
//		radius = 15;   //will create the boss
//		r = 0; g = 0; b = 0;
//		Xco = x;
//		Yco = y;
//		eatable = false;  //initially not eatable
//		vanish = 0;  //initially not vanishing
//
//	}
//
//	void set(float x, float y);  //for resetting values
//
//	void moveLeft();  //for moving left
//
//	void moveRight();  //for moving right
//
//	void Jump(float);  //for jump
//
//	int Vanish(){
//
//		return vanish;  //returns jump
//
//	}
//
//	void Behavior(Ball a);  //for moving (this follows the main Ball)
//
//	void Collision(Ball &);  //for checking collision
//
//	void state();  //for converting to eatable from not eatable
//
//};
//
//void Boss::set(float x, float y){  //for resetting the values of the coordinates
//
//	Xco = x;
//	Yco = y;
//	eatable = false;  //not eatable
//	vanish = 0;  //not vanishing
//
//}
//
//void Boss::moveLeft(){
//
//	try{   //moves left until reaches end of screen
//
//		if (Xco < 15)  //throws exception if it reaches left end of screen
//			throw Xco;
//
//		Xco -= 3;
//
//	}
//
//	catch (float a){
//
//		Xco = 14;  //if exception thrown, boss stays here or moves right depending on behaviour
//
//	}
//
//
//}
//
//void Boss::moveRight(){  //for moving right
//
//	try{
//
//		if (Xco > 1320)  //throws exception if boss reaches right end of screen
//			throw Xco;
//
//		Xco += 3;
//
//	}
//
//	catch (float a){
//
//		Xco = 1319;  //boss stayes here or moves left depending on behavior
//
//	}
//
//
//}
//
//void Boss::Behavior(Ball a){  //controls behaviour of boss
//
//	if (a.surfaceS() > Xco){  //if mainball is to the right of boss, boss moves right
//
//		moveRight();
//
//	}
//
//	if (a.surfaceS() < Xco){  //if mainball is to the left of boss, boss moves left
//
//		moveLeft();
//
//	}
//
//}
//
//void Boss::state(){  //for turning boss from not eatable to eatable
//
//	eatable = true;
//
//}
//
//
//void Boss::Collision(Ball &ball){  //for collision with the boss
//
//	if (!eatable){
//		if (((Xco > ball.surfaceS() - 5) && (Xco<(ball.surfaceS() + 2 * ball.Radius() + 5)) && (Yco + 4>ball.height()) && (Yco - 4 < (ball.height() + 2 * ball.Radius()))))
//			ball.death();
//	}
//
//	// This code is very similar to the enemy class collision, refer to that for understanding this
//
//	if (eatable){
//		r = 2;
//		g = 1;
//		b = 0;
//		if (((Xco>ball.surfaceS() - 5) && (Xco<(ball.surfaceS() + 2 * ball.Radius() + 5)) && (Yco + 4>ball.height()) && (Yco - 4< (ball.height() + 2 * ball.Radius())))){
//			vanish = 1;
//		}
//
//	}
//
//}
//
//
//void Boss::Jump(float jumpPoint){  //for making boss jump
//
//	if (halt == 0){
//
//		Yco -= 4;  //for jump animation
//
//		if (height() < (jumpPoint - 30))  //boss will go up until it reaches this point
//
//			halt = 1;
//
//	}
//
//	if (halt == 1){
//
//		Yco += 4;  //for downward animation
//
//		if (height() > jumpPoint)  //boss will go down until reaching this point
//
//			halt = 0;
//
//	}
//
//}
//
//
//
//float jump = 0;  //used for calling jump function of main ball
//
//
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////                                                           Creating OBJECTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//Ball mainB;
//
//Platform p1(50, 630, 400, 10);
//Platform p2(320, 590, 150, 10);
//Platform p3(500, 550, 400, 10);
//Platform p4(1024, 390, 200, 10);
//Platform p5(900, 470, 220, 10);
//Platform p6(700, 400, 200, 10);
//Platform p7(450, 370, 200, 10);
//Platform p8(550, 270, 220, 10);
//Platform p9(50, 100, 220, 10);
//
//Platform BossP(0, 690, 1350, 10);
//
//movingPlatform m1(400, 370, 220, 10, 350, 750);
//
//Coin coins(200, 600, 10);
//Coin coins1(200, 500, 10);
//Coin coins2(300, 600, 10);
//Coin coins3(150, 80, 10);
//
//superCoin s1(1, 1110, 370, 6.5);
//
//Door door1(650, 170, 50, 100);
//Door door2(60, 10, 50, 90);
//
//Enemy e1(500, 540, 500, 900);
//Enemy e2(450, 360, 450, 650);
//
//Boss Boss1(800, 680);
//
//
//
//////////////////////////////////////////              GAME CLASS                 ///////////////////////////////////////////////
//
//
//class Game{
//
//	int menu;   //for navigating between menus and levels
//	int level;
//
//public:
//
//	Game() :menu(1), level(0){};   //constructor, initially menu is 1 and level is 0, main menu state
//
//	void playGame();  //this will be called in the display function
//
//	void select(int a){ level = a; }  //for selecting level
//
//};
//
//
//void Game::playGame(){   //this is called in the display function
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////          MAIN      MENU     /////////////////////////////////////////////////////
//	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	if (menu == 1 && level == 0){
//
//		_mainMenuTextureId = loadtexture("Game Menu Main.png");   //loads main menu image
//		background();
//
//		if (mouse_X > 480 && mouse_X < 860 && mouse_Y > 235 && mouse_Y < 370){   //if new game option is selected
//
//			level = 1;  //goes to level 1
//			menu = 0;
//			mouse_X = 0;
//			mouse_Y = 0;
//
//		}
//
//		if (mouse_X > 480 && mouse_X < 860 && mouse_Y > 400 && mouse_Y < 540){  //if level selection option is selected
//
//			level = 0;
//			menu = 2;   //goes to the level selection menu
//			mouse_X = 0;
//			mouse_Y = 0;
//
//		}
//
//		if (mouse_X > 480 && mouse_X < 860 && mouse_Y > 575 && mouse_Y < 700){  //if exit is selected
//
//			exit(EXIT_SUCCESS);
//
//		}
//
//	}
//
//
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////    LEVEL SELECTION   MENU     /////////////////////////////////////////////////////
//	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//
//	if (menu == 2 && level == 0){
//
//		_mainMenuTextureId = loadtexture("Levels.png");   //loads image
//		background();
//
//			if (mouse_X > 100 && mouse_X < 360 && mouse_Y > 530 && mouse_Y < 630){
//					level = 0;
//					menu = 1;
//					mouse_X = 0;
//					mouse_Y = 0;
//			}
//
//
//
//		if (mouse_X > 525 && mouse_X < 830 && mouse_Y > 115 && mouse_Y < 220){  //if level 1 is selected
//
//			level = 1;  //for going to level 1
//			menu = 0;
//			mouse_X = 0;
//			mouse_Y = 0;
//
//
//			///////////////////////////////////////////////////// RE SETTING ALL VALUES  //////////////////////////////////////////////////////
//
//			p1.set(50, 630, 400, 10);   //re setting platforms
//
//			p2.set(320, 590, 150, 10);
//
//			p3.set(500, 550, 400, 10);
//
//			p4.set(1024, 390, 200, 10);
//
//			p5.set(900, 470, 220, 10);
//
//			p6.set(700, 400, 200, 10);
//
//			p7.set(450, 370, 200, 10);
//
//			p8.set(550, 270, 220, 10);
//
//			p9.set(50, 100, 220, 10);
//
//
//			coins.set(200, 600);    //resetting coins
//
//			coins1.set(200, 500);
//
//			coins2.set(300, 600);
//
//			coins3.set(150, 80);
//
//
//			s1.set(1110, 370);   //resetting super coin
//
//
//			door1.set(650, 170);  //resetting doors
//
//			door2.set(60, 10);
//
//
//			e1.set(500, 540, 500, 900);  //resetting enemies
//
//			e2.set(450, 360, 450, 650);
//
//		}
//
//
//		if (mouse_X > 525 && mouse_X < 830 && mouse_Y > 270 && mouse_Y < 370){  //when level 2 is clicked
//
//
//			///////////////////////////////////////////////// RESETTING ALL VALUES //////////////////////////////////// 
//
//			mainB.set(220, 500);  //resets ball position
//
//
//			p1.set(200, 550, 200, 10);  //resetting platforms
//
//			p2.set(650, 550, 200, 10);
//
//			p3.set(330, 515, 200, 10);
//
//			p4.set(850, 470, 200, 10);
//
//			p5.set(600, 420, 200, 10);
//
//			p6.set(870, 300, 200, 10);
//
//			p7.set(450, 170, 200, 10);
//
//			p8.set(680, 240, 200, 10);
//
//			p9.set(940, 95, 200, 10);
//
//
//			m1.set(400, 370, 350, 750);  //resetting movable platform
//
//
//			coins.set(900, 680);    //resetting coins
//
//			coins1.set(900, 280);
//
//			coins2.set(500, 350);
//
//			coins3.set(1100, 50);
//
//
//			s1.set(690, 410);  //resetting super coin
//
//
//			door1.set(470, 70);  //resetting door
//
//			door2.set(980, 10);
//
//
//			e1.set(430, 360, m1.XC(), m1.XC() + 400);  //resetting enemies
//
//			e2.set(870, 290, 870, 1070);
//
//			////////////////////////////////////////////////////////////
//
//			level = 2;   //moves to level 2
//			menu = 0;
//			mouse_X = 0;
//			mouse_Y = 0;
//		}
//
//		/////////////////FOR LEVEL 3////////////////////////
//
//		/*if (mouse_X > 525 && mouse_X < 830 && mouse_Y > 420 && mouse_Y < 520){
//
//		level = 3;
//		menu = 0;
//		mouse_X = 0;
//		mouse_Y = 0;
//
//		}*/
//
//		
//	}
//
//
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////          WHEN DEAD, THIS IS DISPLAYED     ///////////////////////////////////////////////////
//	/////////////////////////////////////////////////////////////////////////////?//////////////////////////////////////////////////
//
//	if (menu == 3 && level == 0){
//
//		_mainMenuTextureId = loadtexture("Dead.png");  //loads image
//		background();
//
//		if (mouse_X > 530 && mouse_X < 810 && mouse_Y > 400 && mouse_Y < 520){  //when return option is selected
//
//			level = 0;   //goes back to main menu
//			menu = 1;
//			mouse_X = 0;
//			mouse_Y = 0;
//
//		}
//
//	}
//
//	if (menu == 0 && level == 3){
//			_mainMenuTextureId = loadtexture("Level3.png");
//			background();
//	}
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////          LEVEL       1    /////////////////////////////////////////////////////
//	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	if (menu == 0 && level == 1){
//
//		_mainMenuTextureId = loadtexture("Volcano.png");   //loads image
//		background();
//
//		////////////////////////////////////////////////////Drawing     Doors  //////////////////////////////////////////////////////
//		door1.drawDoor();
//
//		door2.drawDoor();
//
//		if (coins.Van() == 1 && coins1.Van() == 1 && coins2.Van() == 1 && coins3.Van() == 1 && e1.Van() == 1 && e2.Van() == 1){
//
//			NextLevelDoor d1(55, 540, 50, 100);  //if coins and enemies vanish, this door appears
//
//			d1.drawDoor();
//
//			if (d1.Collision(mainB))    //if ball collides with this door, ball goes to next level
//			{
//				/////////////////////////////////////// RESETTING VALUES FOR NEXT LEVEL  /////////////////////////////////////
//				mainB.set(220, 500);
//
//				p1.set(200, 550, 200, 10);
//				p2.set(650, 550, 200, 10);
//				p3.set(330, 515, 200, 10);
//				p4.set(850, 470, 200, 10);
//				p5.set(600, 420, 200, 10);
//				p6.set(870, 300, 200, 10);
//				p7.set(450, 170, 200, 10);
//				p8.set(680, 240, 200, 10);
//				p9.set(940, 95, 200, 10);
//
//				m1.set(400, 370, 350, 750);
//
//				coins.set(900, 680);
//				coins1.set(900, 280);
//				coins2.set(500, 350);
//				coins3.set(1100, 50);
//
//				s1.set(690, 410);
//
//				door1.set(470, 70);
//				door2.set(980, 10);
//
//				e1.set(430, 360, m1.XC(), m1.XC() + 400);
//				e2.set(870, 290, 870, 1070);
//				////////////////////////////////////////////////////////////
//
//				level = 2;   //for going to next level
//				menu = 0;
//
//			}
//		}
//
//		mainB.DrawCircle();   //draws main ball
//
//		p1.DrawPlatform();     //drawing all platforms
//
//		p2.DrawPlatform();
//
//		p3.DrawPlatform();
//
//		p4.DrawPlatform();
//
//		p5.DrawPlatform();
//
//		p6.DrawPlatform();
//
//		p7.DrawPlatform();
//
//		p8.DrawPlatform();
//
//		p9.DrawPlatform();
//
//
//		e1.Draw();   //for drawing and using enemies
//
//		e1.Behaviour();
//
//		e1.Collision(mainB);
//
//		e2.Draw();
//
//		e2.Behaviour();
//
//		e2.Collision(mainB);
//
//
//		if (coins.Van() == 0)     //for drawing and using coins
//			coins.drawRing(250);
//
//		if (coins1.Van() == 0)
//			coins1.drawRing(250);
//
//		if (coins2.Van() == 0)
//			coins2.drawRing(250);
//
//		if (coins3.Van() == 0)
//			coins3.drawRing(250);
//
//
//
//		s1.Collision(mainB);   //for drawing and using supercoin
//
//		if (s1.Van() == 0)
//			s1.drawRing(250);
//
//		if (s1.Van() == 1){
//			e1.state(); //enemies turn eatable
//			e2.state();
//		}
//
//
//
//		if (coins.Collision(mainB))   //Checking collisions with coins
//		{
//			coins.incScore();
//			coins.VanishCoin();
//		}
//
//
//		if (coins1.Collision(mainB))
//
//		{
//			coins1.incScore();
//			coins1.VanishCoin();
//		}
//
//
//		if (coins2.Collision(mainB))
//		{
//			coins2.incScore();
//			coins2.VanishCoin();
//		}
//
//
//		if (coins3.Collision(mainB))
//		{
//			coins3.incScore();
//			coins3.VanishCoin();
//		}
//
//
//
//		if (door1.Collision(mainB))   //for portal collision
//		{
//			mainB.changeLoc(door2.retX(), door2.retY());
//		}
//
//
//
//		///////////////////////// CODE FOR STAYING ON PLATFORM   /////////////////////////////////////////////////////////////////////////
//
//		if ((p9.compareX(mainB.surfaceS())) && (p9.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p9.Surface());
//
//		}
//
//		else if ((p8.compareX(mainB.surfaceS())) && (p8.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p8.Surface());
//
//		}
//
//		else if ((p7.compareX(mainB.surfaceS())) && (p7.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p7.Surface());
//
//		}
//
//		else if ((p6.compareX(mainB.surfaceS())) && (p6.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p6.Surface());
//
//		}
//
//		else if ((p4.compareX(mainB.surfaceS())) && (p4.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p4.Surface());
//
//		}
//
//		else if ((p5.compareX(mainB.surfaceS())) && (p5.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p5.Surface());
//
//		}
//
//		else if ((p3.compareX(mainB.surfaceS())) && (p3.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p3.Surface());
//
//		}
//
//
//		else if ((p2.compareX(mainB.surfaceS())) && (p2.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p2.Surface());
//
//		}
//
//		else if ((p1.compareX(mainB.surfaceS())) && (p1.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p1.Surface());
//
//		}
//
//
//		else mainB.fall();  //for gravity effect
//
//		if (mainB.Inertia() > 0){   //for inertia effects
//			mainB.moveRight();
//		}
//
//		if (mainB.Inertia() < 0){
//			mainB.moveLeft();
//		}
//
//		if (mainB.Life() == 0){  //incase ball dies
//
//			menu = 3;   //goes to death menu
//
//			mouse_X = 0;
//			mouse_Y = 0;
//
//			level = 0;
//
//			mainB.set(0, 0);  //resets b to 0,0
//		}
//
//
//	}
//
//
//	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	//////////////////////////////////          LEVEL              2   /////////////////////////////////////////////////////
//	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	if (menu == 0 && level == 2){
//
//		_mainMenuTextureId = loadtexture("Level2.png");  //loads background image
//		background();
//
//		door1.drawDoor();   //drawing doors
//
//		door2.drawDoor();
//
//		if (coins.Van() == 1 && coins1.Van() == 1 && coins2.Van() == 1 && coins3.Van() == 1){
//
//			Boss1.state();   //if coins vanish, boss state turns eatable
//
//		}
//
//
//
//
//		if (coins.Van() == 1 && coins1.Van() == 1 && coins2.Van() == 1 && coins3.Van() == 1 && e1.Van() == 1 && e2.Van() == 1 && Boss1.Vanish() == 1){
//
//			NextLevelDoor d1(55, 540, 50, 100);  // if coins, enemies, and boss vanishes this door appears
//
//			d1.drawDoor();  //draws the door
//
//			if (d1.Collision(mainB))  //collision leads to main menu
//			{
//				level = 0;
//				menu = 1;
//
//				mouse_X = 0;
//				mouse_Y = 0;
//
//			}
//
//		}
//
//
//		mainB.DrawCircle();  //draws main ball
//
//		p1.DrawPlatform();  //draws platform
//
//		p2.DrawPlatform();
//
//		p3.DrawPlatform();
//
//		p4.DrawPlatform();
//
//		p5.DrawPlatform();
//
//		p6.DrawPlatform();
//
//		p7.DrawPlatform();
//
//		p8.DrawPlatform();
//
//		p9.DrawPlatform();
//
//
//
//		m1.DrawPlatform();   //drawing and using moving platform   
//
//		m1.Behaviour();
//
//
//		BossP.DrawPlatform();  //draw platform for boss
//
//
//		if (Boss1.Vanish() == 0)  //if boss is visible draw him
//			Boss1.DrawCircle();
//
//		Boss1.Behavior(mainB);  //controls boss behavior
//
//		Boss1.Jump(BossP.Surface());   //for boss's jump
//
//		Boss1.Collision(mainB);   // for boss's collision
//
//
//
//		e1.Draw();   //for drawing and using enemies
//
//		e1.Behaviour();
//
//		e1.Collision(mainB);
//
//		e2.Draw();
//
//		e2.Behaviour();
//
//		e2.Collision(mainB);
//
//
//
//		if (coins.Van() == 0)   //for drawing coins
//			coins.drawRing(250);
//
//		if (coins1.Van() == 0)
//			coins1.drawRing(250);
//
//		if (coins2.Van() == 0)
//			coins2.drawRing(250);
//
//		if (coins3.Van() == 0)
//			coins3.drawRing(250);
//
//
//		s1.Collision(mainB);  //for colliding with supercoin
//
//		if (s1.Van() == 0)  //for drawing supercoin
//			s1.drawRing(250);
//
//
//		if (s1.Van() == 1){
//			//for making enemies eatable
//			e1.state();
//			e2.state();
//
//		}
//
//
//		if (coins.Collision(mainB))   //for collision with coins
//
//		{
//			coins.incScore();
//			coins.VanishCoin();
//		}
//
//		if (coins1.Collision(mainB))
//
//		{
//			coins1.incScore();
//			coins1.VanishCoin();
//		}
//
//		if (coins2.Collision(mainB))
//		{
//			coins2.incScore();
//			coins2.VanishCoin();
//		}
//
//		if (coins3.Collision(mainB))
//		{
//			coins3.incScore();
//			coins3.VanishCoin();
//		}
//
//
//
//		if (door1.Collision(mainB))   //for portal collision
//		{
//			mainB.changeLoc(door2.retX(), door2.retY());
//		}
//
//
//		////////////////////////////////////////// For platform jumps and stuff ////////////////////////////////////////////
//
//		if ((p9.compareX(mainB.surfaceS())) && (p9.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p9.Surface());
//
//		}
//
//		else if ((p8.compareX(mainB.surfaceS())) && (p8.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p8.Surface());
//
//		}
//
//		else if ((p7.compareX(mainB.surfaceS())) && (p7.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p7.Surface());
//
//		}
//
//		else if ((p6.compareX(mainB.surfaceS())) && (p6.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p6.Surface());
//
//		}
//
//		else if ((m1.compareX(mainB.surfaceS())) && (m1.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, m1.Surface());
//
//		}
//
//		else if ((p4.compareX(mainB.surfaceS())) && (p4.compareY(mainB.height()))){
//
//			mainB.Jump(&jump, p4.Surface());
//
//		}
//
//		else if ((p5.compareX(mainB.surfaceS())) && (p5.compareY(mainB.height()))){
//			mainB.Jump(&jump, p5.Surface());
//		}
//
//		else if ((p3.compareX(mainB.surfaceS())) && (p3.compareY(mainB.height()))){
//			mainB.Jump(&jump, p3.Surface());
//		}
//
//
//		else if ((p2.compareX(mainB.surfaceS())) && (p2.compareY(mainB.height()))){
//			mainB.Jump(&jump, p2.Surface());
//		}
//
//		else if ((p1.compareX(mainB.surfaceS())) && (p1.compareY(mainB.height()))){
//			mainB.Jump(&jump, p1.Surface());
//		}
//
//		else if ((BossP.compareX(mainB.surfaceS())) && (BossP.compareY(mainB.height()))){
//			mainB.Jump(&jump, BossP.Surface());
//		}
//
//
//		else mainB.fall();    // for gravity effect
//
//		if (mainB.Inertia() > 0){  //for inertia effect
//
//			mainB.moveRight();
//
//		}
//
//		if (mainB.Inertia() < 0){
//
//			mainB.moveLeft();
//
//		}
//
//		if (mainB.Life() == 0){  //if ball dies
//
//			menu = 3;   //goes to death menu
//
//			level = 0;
//
//			mainB.set(0, 0);
//		}
//	}
//
//}
//
//
//void init();
//void myMouseFunction(int button, int state, int mouseX, int mouseY);
//void myKeyboardFunction(unsigned char key, int mouseX, int mouseY);
//void mySpecialKeysFunction(int key, int x, int y);
//void myReshapeFunction(int width, int height);
//void myTimerFunction(int val);
//void myDisplayFunction();
//
//
//int main(int argc, char** argv)
//{
//	glutInit(&argc, argv);		//initilize the GLUT libraray
//
//	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);		//has four colour components red, green,blue, and alpha 
//	glutInitWindowSize(1350, 700);	//size of window
//	glutInitWindowPosition(0, 0);		//position of window
//	glutCreateWindow("Pounce! The Game!");
//
//	init();
//	PlaySound("Bounce.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
//	glutMouseFunc(myMouseFunction);
//	glutKeyboardFunc(myKeyboardFunction);
//	glutSpecialFunc(mySpecialKeysFunction);
//
//	glutReshapeFunc(myReshapeFunction);
//	glutDisplayFunc(myDisplayFunction);
//	glutTimerFunc(33, myTimerFunction, 0);
//
//	//	glutFullScreen();	// make the screen fullscreen
//	glutSetCursor(GLUT_CURSOR_INFO);	//Displays the type of cursor u want
//
//	glutMainLoop();
//
//	return 0;
//}
//
//void init(void)
//{
//	glClearColor(0.0, 0.0, 0.0, 0.0);		//background color of openGl window
//	//			 ^red, green, blue, alpha(opaquenss) 
//	glMatrixMode(GL_PROJECTION);		//glMatrixMode — specify which matrix is the current matrix ????
//	glLoadIdentity();		//glLoadIdentity — replace the current matrix with the identity matrix	????
//
//	glOrtho(0.0, g_Width, 0.0, g_Height, -1.0, 1.0);	//set (0,0) on left top
//}
//
//void myMouseFunction(int button, int state, int mouseX, int mouseY)
//{
//	mouse_X = mouseX;
//	mouse_Y = mouseY;
//
//	if (state == 0) //Click
//	{
//		cout << "mouse clicked \n";
//		cout << "\nmouseX:" << mouseX << "mouseY:" << mouseY << "State: " << state;
//	}
//
//
//}
//
//void myKeyboardFunction(unsigned char key, int mouseX, int mouseY){
//	switch (key)
//	{
//	case 27: // Escape key
//		exit(0);
//		break;
//	}
//}
//
//
//
//void mySpecialKeysFunction(int key, int x, int y){
//
//	switch (key){
//
//	case GLUT_KEY_UP:
//		//for jumping higher
//		if (jump == 0){
//			jump = 1;
//		}
//
//		break;
//
//	case GLUT_KEY_DOWN:
//		break;
//
//	case GLUT_KEY_LEFT:
//		//for moving left
//		mainB.moveLeft();
//
//		break;
//
//	case GLUT_KEY_RIGHT:
//		//for moving right
//		mainB.moveRight();
//
//		break;
//	case GLUT_KEY_HOME:
//		break;
//	case GLUT_KEY_END:
//		break;
//	case GLUT_KEY_PAGE_UP:
//		break;
//	case GLUT_KEY_PAGE_DOWN:
//		break;
//	}
//}
//
//void myReshapeFunction(int width, int height)
//{
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	g_Width = width;
//	g_Height = height;
//
//	glViewport(0, 0, g_Width, g_Height);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity();
//	glOrtho(0.0, g_Width, g_Height, 0.0, -1.0, 1.0);	//change the (0,0) to top left
//}
//
//void myTimerFunction(int val)
//{
//	glutTimerFunc(33, myTimerFunction, 0);
//	myDisplayFunction();
//}
//
//
//Game Pounce;
//
//void myDisplayFunction()
//{
//	glClear(GL_COLOR_BUFFER_BIT);		//clears the screen after display
//
//	glColor3f(1, 1, 1);
//	glBegin(GL_POLYGON);
//	glVertex2f(-10, -10);
//	glVertex2f(2000, -10);
//	glVertex2f(2000, 1000);
//	glVertex2f(-10, 1000);
//	glEnd();
//
//	Pounce.playGame();
//
//	glutSwapBuffers();		//brings the openGl window on the front
//	//printf("\n.");
//}