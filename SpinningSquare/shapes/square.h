#include "generalMacros.h"
struct Square{
	float points_point[4][2];
	float changeIn[4][2];
	float points_center[2];
	float motion_dist[4];
	float motion_angle[4];

	void (*controls_wasd)(void);
	void (*controls_jl)(void);

	int controlMode;
}square;

void calcDist(void){
	float changeInX, changeInY;
	float changeInX_pow, changeInY_pow;
	float changeIn_total;
	
	for(int i=0; i<4; i++){
		changeInX = square.points_point[i][GEN_X] - square.points_center[GEN_X];
		if(changeInX < 0)
			changeInX = changeInX * (-1);
		square.changeIn[i][GEN_X] = changeInX;
		changeInY = square.points_point[i][GEN_Y] - square.points_center[GEN_Y];
		if(changeInY < 0)
			changeInY = changeInY * (-1);
		square.changeIn[i][GEN_Y] = changeInY;

		changeInX_pow = pow(changeInX, 2);
		changeInY_pow = pow(changeInY, 2);
		changeIn_total = changeInX_pow + changeInY_pow;

		if(changeIn_total < 0){
			changeIn_total = changeIn_total * (-1);
		}
		
		square.motion_dist[i] = sqrt(changeIn_total);
	}
}

void calcAngle(void){
	float changeInX_pow, changeInY_pow;
	float changeIn_total;
	float imaginaryPoint[2];
	float imaginaryDist;
	float radConv = M_PI/180;
	
	for(int i=0; i<4; i++){
		if((square.points_point[i][GEN_X] >= square.points_center[GEN_X]) &&
		   (square.points_point[i][GEN_Y] >= square.points_center[GEN_Y])){
		/*quad I*/
			printf("quad I\n");
			imaginaryPoint[GEN_X] = (square.points_center[GEN_X]-square.points_center[GEN_X]) + (square.changeIn[i][GEN_X]);
			imaginaryPoint[GEN_Y] = (square.points_point[i][GEN_Y]-square.points_center[GEN_Y]) - (square.changeIn[i][GEN_Y]);
			
			changeInX_pow = pow(imaginaryPoint[GEN_X]-(square.points_center[GEN_X]-square.points_center[GEN_X]),2);
			changeInY_pow = pow(imaginaryPoint[GEN_Y]-(square.points_center[GEN_Y]-square.points_center[GEN_Y]),2);
			changeIn_total = changeInX_pow + changeInY_pow;
			if(changeIn_total < 0)
				changeIn_total = changeIn_total * (-1);

			imaginaryDist = sqrt(changeIn_total);
			square.motion_angle[i] = acos(imaginaryDist/square.motion_dist[i]);
		}else if((square.points_point[i][GEN_X] < square.points_center[GEN_X]) &&
			 (square.points_point[i][GEN_Y] >= square.points_center[GEN_Y])){
		/*quad II*/
		        printf("quad II\n");
			imaginaryPoint[GEN_X] = (square.points_center[GEN_X]-square.points_center[GEN_X]) - (square.changeIn[i][GEN_X]);
			imaginaryPoint[GEN_Y] = (square.points_point[i][GEN_Y]-square.points_center[GEN_Y]) - (square.changeIn[i][GEN_Y]);
			
			changeInX_pow = pow(imaginaryPoint[GEN_X]-(square.points_center[GEN_X]-square.points_center[GEN_X]),2);
			changeInY_pow = pow(imaginaryPoint[GEN_Y]-(square.points_center[GEN_Y]-square.points_center[GEN_Y]),2);
			changeIn_total = changeInX_pow + changeInY_pow;
			if(changeIn_total < 0)
				changeIn_total = changeIn_total * (-1);
			
			imaginaryDist = sqrt(changeIn_total);
			square.motion_angle[i] = 180*radConv - acos(imaginaryDist/square.motion_dist[i]);
		}else if((square.points_point[i][GEN_X] <= square.points_center[GEN_X]) &&
			 (square.points_point[i][GEN_Y] < square.points_center[GEN_Y])){
		/*quad III*/
		        printf("quad III\n");
			imaginaryPoint[GEN_X] = (square.points_point[i][GEN_X]-square.points_center[GEN_X]) + (square.changeIn[i][GEN_X]);
			imaginaryPoint[GEN_Y] = (square.points_center[GEN_Y]-square.points_center[GEN_Y]) - (square.changeIn[i][GEN_Y]);
			
			changeInX_pow = pow(imaginaryPoint[GEN_X]-(square.points_center[GEN_X]-square.points_center[GEN_X]),2);
			changeInY_pow = pow(imaginaryPoint[GEN_Y]-(square.points_center[GEN_Y]-square.points_center[GEN_Y]),2);
			changeIn_total = changeInX_pow + changeInY_pow;
			if(changeIn_total < 0)
				changeIn_total = changeIn_total * (-1);

			imaginaryDist = sqrt(changeIn_total);
			square.motion_angle[i] = 270*radConv - acos(imaginaryDist/square.motion_dist[i]);
		}else if((square.points_point[i][GEN_X] > square.points_center[GEN_X]) &&
			 (square.points_point[i][GEN_Y] < square.points_center[GEN_Y])){
		/*quad IV*/
		        printf("quad IV\n");
			imaginaryPoint[GEN_X] = (square.points_point[i][GEN_X]-square.points_center[GEN_X])-(square.changeIn[i][GEN_X]);
			imaginaryPoint[GEN_Y] = (square.points_center[GEN_Y]-square.points_center[GEN_Y]) - (square.changeIn[i][GEN_Y]);
		
			changeInX_pow = pow(imaginaryPoint[GEN_X]-(square.points_center[GEN_X]-square.points_center[GEN_X]),2);
			changeInY_pow = pow(imaginaryPoint[GEN_Y]-(square.points_center[GEN_Y]-square.points_center[GEN_Y]),2);
			changeIn_total = changeInX_pow + changeInY_pow;
			if(changeIn_total < 0)
				changeIn_total = changeIn_total * (-1);
			
			imaginaryDist = sqrt(changeIn_total);
			square.motion_angle[i] = 360*radConv - acos(imaginaryDist/square.motion_dist[i]);
		}
	}
}


void square_render(void){
	glLoadIdentity();
        glBegin(GL_QUADS);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2f(square.points_point[P_0][P_0_X], square.points_point[P_0][P_0_Y]);
		glColor3f(0.0, 1.0, 0.0);
		glVertex2f(square.points_point[P_1][P_1_X], square.points_point[P_1][P_1_Y]);
		glColor3f(0.0, 0.0, 1.0);
		glVertex2f(square.points_point[P_2][P_2_X], square.points_point[P_2][P_2_Y]);
		glColor3f(1.0, 0.0, 1.0);
		glVertex2f(square.points_point[P_3][P_3_X], square.points_point[P_3][P_3_Y]);
        glEnd();
}

void square_default_init(void){
	square.points_point[P_0][P_0_X] = -0.25;
	square.points_point[P_0][P_0_Y] = 0.25;	

	square.points_point[P_1][P_1_X] = 0.25;
	square.points_point[P_1][P_1_Y] = 0.25;

	square.points_point[P_2][P_2_X] = 0.25;
	square.points_point[P_2][P_2_Y] = -0.25;

	square.points_point[P_3][P_3_X] = -0.25;
	square.points_point[P_3][P_3_Y] = -0.25;

	square.points_center[GEN_X] = 0;
	square.points_center[GEN_Y] = 0;

	calcDist();
	calcAngle();
}

void square_spin(float degree, char direction){
	float radianConverter = M_PI/180;
	float newDegree[4];
	
	if(direction == '+' && degree < 0){
                direction = '-';
                degree = degree * (-1);
        }else if(direction == '-' && degree < 0){
                direction = '+';
                degree = degree * (-1);
        }

	if(direction != '+' && direction != '-'){
                printf("invalid direction definition\n");

        }else if(direction == '+'){
		degree = degree * radianConverter;
		for(int i=0; i<4; i++){
			newDegree[i] = square.motion_angle[i] + degree;
			if(newDegree[i] > 360*radianConverter){
				while(newDegree[i] > 360*radianConverter){
					newDegree[i] -= 360*radianConverter;
				}
			}
			if(newDegree[i] == 360*radianConverter){
				newDegree[i] = 0;
			}
			square.motion_angle[i] = newDegree[i];

			square.points_point[i][GEN_X] = cos(newDegree[i]) * square.motion_dist[i] + square.points_center[GEN_X];
			square.points_point[i][GEN_Y] = sin(newDegree[i]) * square.motion_dist[i] + square.points_center[GEN_Y];
		}
	}else if(direction == '-'){
		degree = degree * radianConverter;
		for(int i=0; i<4; i++){
			newDegree[i] = square.motion_angle[i] - degree;
			if(newDegree[i] < 0){
				while(newDegree[i] < 0){
					newDegree[i] += 360*radianConverter;
				}
			}
			
			square.motion_angle[i] = newDegree[i];
			
			square.points_point[i][GEN_X] = cos(newDegree[i]) * square.motion_dist[i] + square.points_center[GEN_X];
			square.points_point[i][GEN_Y] = sin(newDegree[i]) * square.motion_dist[i] + square.points_center[GEN_Y];
		}
	}
}

/* walk up and down left and right */
void square_wasd_controls(void){
	if(vk.w == true){
		square.points_point[P_0][P_0_Y] = square.points_point[P_0][P_0_Y] + 0.01;
		square.points_point[P_1][P_1_Y] = square.points_point[P_1][P_1_Y] + 0.01;
		square.points_point[P_2][P_2_Y] = square.points_point[P_2][P_2_Y] + 0.01;
		square.points_point[P_3][P_3_Y] = square.points_point[P_3][P_3_Y] + 0.01;
	        square.points_center[GEN_Y] = square.points_center[GEN_Y] + 0.01;
	}
	if(vk.a == true){
		square.points_point[P_0][P_0_X] = square.points_point[P_0][P_0_X] - 0.01;
                square.points_point[P_1][P_1_X] = square.points_point[P_1][P_1_X] - 0.01;
                square.points_point[P_2][P_2_X] = square.points_point[P_2][P_2_X] - 0.01;
                square.points_point[P_3][P_3_X] = square.points_point[P_3][P_3_X] - 0.01;
                square.points_center[GEN_X] = square.points_center[GEN_X] - 0.01;
	}
	
	if(vk.s == true){
		square.points_point[P_0][P_0_Y] = square.points_point[P_0][P_0_Y] - 0.01;
                square.points_point[P_1][P_1_Y] = square.points_point[P_1][P_1_Y] - 0.01;
                square.points_point[P_2][P_2_Y] = square.points_point[P_2][P_2_Y] - 0.01;
                square.points_point[P_3][P_3_Y] = square.points_point[P_3][P_3_Y] - 0.01;
                square.points_center[GEN_Y] = square.points_center[GEN_Y] - 0.01;
	}
	
	if(vk.d == true){
		square.points_point[P_0][P_0_X] = square.points_point[P_0][P_0_X] + 0.01;
                square.points_point[P_1][P_1_X] = square.points_point[P_1][P_1_X] + 0.01;
                square.points_point[P_2][P_2_X] = square.points_point[P_2][P_2_X] + 0.01;
                square.points_point[P_3][P_3_X] = square.points_point[P_3][P_3_X] + 0.01;
		square.points_center[GEN_X] = square.points_center[GEN_X] + 0.01;
	}
}

void square_jl_controls(void){
	if(vk.j == true){
		printf("rotate clockwise\n");
		square_spin(1, '+');
		printf("\n");
	}
		
	if(vk.l == true){
		printf("rotate counter-clockwise\n");
		square_spin(1, '-');
	}

	if(vk.i == true){
		printf("Enumerated square struct\n");
		for(int i=0; i<2; i++)
			for(int j=0; j<2; j++)
				printf("\tpoints[%d][%d]: %f\n",i, j, square.points_point[i][j]);
		printf("\n");
        	for(int i=0; i<2; i++)
			for(int j=0; j<2; j++)
				printf("\tchangeIn[%d][%d]: %f\n", i, j, square.changeIn[i][j]);
			
        	printf("\n\tcenter(%f, %f)\n", square.points_center[0], square.points_center[1]);
		printf("\n");
		for(int i=0; i<2; i++)
	        	printf("\tmotion dist[%d]: %f\n",i, square.motion_dist[i]);
		printf("\n");
        	for(int i=0; i<2; i++)
			printf("\tangle[%d] %f\n", i, square.motion_angle[i]*(180/M_PI));
	}
}
