#include "ground.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


bool isShake = false;

float ground_data[] = {

	// 위치 // 컬러 // 텍스처 좌표
	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, //+ +
	-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,//- +
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,//- -

	0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,//++
	-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,//- - 
	0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f//+ -
};
float ground_data2[] = {

	// 위치 // 컬러 // 텍스처 좌표
	0.5f, 0.5f, 2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, //+ +
	-0.5f, 0.5f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,//- +
	-0.5f,- 0.5f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,//- -

	0.5f, 0.5f, 2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,//++
	-0.5f, -0.5f, 2.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,//- - 
	0.5f, -0.5f, 2.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f//+ -
};

Ground::Ground()
{
	int widthImage = 500;
	int heightImage = 500;
	int numberOfChannel = 1;
	groundXpos = 0.0f;
	groundYpos = -4.0f;
	groundZpos = -5.0f;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	//--- 첫 번째 버텍스 데이터
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(ground_data), ground_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0); //--- 위치 속성
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float))); //--- 색상 속성
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float))); // 텍스처 좌표 속성
	glEnableVertexAttribArray(2);

	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data1 = stbi_load("track.png", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);

	numberOfChannel = 2;
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	unsigned char* data2 = stbi_load("Title.png", &widthImage, &heightImage, &numberOfChannel, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImage, heightImage, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);



}
void Ground::draw(GLint modelTransformLocation, GLint objColorLocation)
{
	initMatrix();
	if (plane_type == 0)
	{
		transMatrix = glm::translate(transMatrix, glm::vec3(groundXpos, groundYpos, groundZpos));
		transMatrix = glm::scale(transMatrix, glm::vec3(25.0f, 1.0f, 40.0f));

		glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[0]); //--- texture1을 사용하여 폴리곤을 그린다.*/
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	if (plane_type == 1)
	{
		transMatrix = glm::translate(transMatrix, glm::vec3(groundXpos, groundYpos+9.0f, groundZpos));
		transMatrix = glm::scale(transMatrix, glm::vec3(40.0f, 25.0f, 10.0f));
		transMatrix = glm::rotate(transMatrix, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
		glBindVertexArray(VAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture[1]); //--- texture1을 사용하여 폴리곤을 그린다.*/
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	
}
void Ground::update(float velocity)
{
	if (plane_type == 0)
	{
		if (groundZpos + 0.05f*velocity >= 25.0f+velocity*0.001f)
		{
			groundZpos = -35.0f;
		}
		else groundZpos += 0.05f*velocity;
	}
	if (plane_type == 1)
	{
		if (isShake == true)
		{
			groundYpos += 0.05f;
			if (groundYpos >= -3.0f)
			{
				isShake = false;
			}

		}
		else
		{
			groundYpos -= 0.05f;
			if (groundYpos < -5.0f)
			{
			
				isShake = true;
			}
		}

	}

}
Ground::~Ground()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Ground::initMatrix()
{
	glLoadIdentity();
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			transMatrix[i][j] = 0.0f;
		}
	}
	transMatrix[0][0] = 1.0f;
	transMatrix[1][1] = 1.0f;
	transMatrix[2][2] = 1.0f;
	transMatrix[2][2] = 1.0f;
	transMatrix[3][3] = 1.0f;

}
