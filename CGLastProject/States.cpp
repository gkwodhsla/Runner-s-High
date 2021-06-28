#include"States.hpp"
#include"Robot.hpp"
#include"Polygons.hpp"
#include"Item.hpp"
#include "FrameWork.hpp"
#include "ground.hpp"
#include <memory>
#include <vector>
#include <random>
#include <string>



#include <fstream>
#include <iostream>

#define RANK_LIM 100

using namespace std;

random_device rd;
default_random_engine dre(rd());
bernoulli_distribution bdForPolygonGeneration(0.4f);//bd means bernoilli_distribution �̰Ŵ� �ش� ��ġ�� ������ �������� ������(40%)Ȯ����
bernoulli_distribution bdForPolygonType(0.5f);//�̰Ŵ� 50%Ȯ���� �Ƕ�̵常���� ť�� ������ ���ϰ�� �Ƕ�̵� �ƴϸ� ť��
bernoulli_distribution bdForItem(0.5f);// ������ ���� ���� ���� 


// ���� ����
int rank_arr[13] = { 0, };
int rank_arr_index = 0;
int rank_space_index = 0;
//�������� ���� ���� 
float score = 0;
int finalScore = 0;

float cameraXpos = 0.0f;
float cameraYpos = 4.0f;
float cameraZpos = 10.0f;

float lightXpos = 0.0f;
float lightYpos = 0.0f;
float lightZpos = 10.0f;

float generationTimer = 0.0;

float velocity = 6.0f;
float origin_velocity = 0.0f;
float gameTime = 0.0f;
float feverTime = 0.0f;

bool isFever = false;
bool isKeyDown = false;

float title_timer = 0.0f;

unique_ptr<Robot> myRobot;
vector<unique_ptr<PolygonAbstractClass>> myPolygons;
vector<unique_ptr<ItemAbstractClass>> myItem;

// �ٴ� �׸��� 
unique_ptr<Ground> myGround;
unique_ptr<Ground> myGround_page_two;
// Ÿ��Ʋ�� ���� ���� 
unique_ptr<Ground> myTitle;
bool isStart = false;

// �ִϸ��̼� ���ư��� ����



GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

void MainState::enter()
{
	myRobot = make_unique<Robot>();
	myGround = make_unique<Ground>();
	myGround->plane_type = 0;
	
	myGround_page_two = make_unique<Ground>();
	myGround_page_two->plane_type = 0;
	myGround_page_two->changeZpos(25.0f);

	myTitle = make_unique<Ground>();
	myTitle->plane_type = 1;

}

void MainState::draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);


	auto viewMatrix = glm::mat4(1.0f);
	auto projectionMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::mat4(1.0f);
	auto modelTransformLocation = glGetUniformLocation(shaderProgramID, "transform");
	//��ǥ�� ��ȯ�� �κ�Ŭ������ draw���� ���� ����ȴ�.
	//ī�޶�� ������ �κ��� ������ ��ο��� ����ǹǷ� MainState���� �����Ѵ�.
	auto viewTransformLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	auto projectionTransformLocation = glGetUniformLocation(shaderProgramID, "projectionTransform");
	glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	//get location of uniform!

	auto eye = glm::vec3(cameraXpos, cameraYpos, cameraZpos);
	auto direction = glm::vec3(0.0f, 0.0f, -1.0f);

	auto viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
	glUniform3f(viewPosLocation, eye.x, eye.y, eye.z);
	auto lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos");
	glUniform3f(lightPosLocation, lightXpos, lightYpos, lightZpos);
	auto lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
	auto objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor");

	direction = glm::normalize(direction);
	viewMatrix = glm::lookAt(eye, eye + direction, glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	projectionMatrix = glm::perspective(glm::radians(120.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	//������� ī�޶�� ������ȯ ����.


	///////// ��ũ�Ѹ� �̱��� 
	if (isStart)
	{
		
		myRobot->draw(modelTransformLocation, objColorLocation);
		glUniform3f(objColorLocation, 0.0f, 1.0f, 1.0f);
		for (int i = 0; i < myPolygons.size(); ++i)
			myPolygons[i]->draw(modelTransformLocation);
		glUniform3f(objColorLocation, 1.0f, 1.0f, 0.0f);
		for (int i = 0; i < myItem.size(); i++)
			myItem[i]->draw(modelTransformLocation);
		//�̰��� ������ �׸��� �ڵ� ������ �ɰͰ����ϴ�.
	
		myGround->draw(modelTransformLocation, objColorLocation);
		myGround_page_two->draw(modelTransformLocation, objColorLocation);

		auto transMatrix = glm::mat4(1.0f);
		transMatrix = glm::translate(transMatrix, glm::vec3(-3.0f, 18.0f, 0.0f));
		transMatrix = glm::scale(transMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
		string s = "the score is:" + std::to_string(int(score));
		void * font = GLUT_BITMAP_9_BY_15;
		for (string::iterator i = s.begin(); i != s.end(); ++i)
		{
			char c = *i;
			glutBitmapCharacter(font, c);
		}
		glRasterPos2i(0, 0);
		//�ؽ�Ʈ �̹��� �׸���. �� �ڵ� �� ���ż� ��ŷ������Ʈ ǥ���Ͻø�ɰͰ����ϴ�.
		


		
	

	}
	else
	{
		glUniform3f(objColorLocation, 0.0f, 1.0f, 1.0f);
		myGround->draw(modelTransformLocation, objColorLocation);
		auto transMatrix = glm::mat4(1.0f);
		transMatrix = glm::translate(transMatrix, glm::vec3(-3.0f, 18.0f, 0.0f));
		transMatrix = glm::scale(transMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
		myTitle->draw(modelTransformLocation, objColorLocation);
	}
	glutSwapBuffers();
}

void MainState::handleEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		if (!isKeyDown)
			myRobot->changeXpos(-1.0f), isKeyDown = true;
		break;
	case 'd':
		if (!isKeyDown)
			myRobot->changeXpos(1.0f), isKeyDown = true;
		break;
	case 'A':
		if (!isKeyDown)
			myRobot->changeXpos(-1.0f), isKeyDown = true;
		break;
	case 'D':
		if (!isKeyDown)
			myRobot->changeXpos(1.0f), isKeyDown = true;
		break;
	case 's':
	case 'S':
		isStart = true;
		break;
	default:
		break;
	}
}
void MainState::keyUpEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		if (isKeyDown)
			myRobot->changeXpos(+1.0f), isKeyDown = false;
		break;
	case 'd':
		if (isKeyDown)
			myRobot->changeXpos(-1.0f), isKeyDown = false;
		break;
	case 'A':
		if (isKeyDown)
			myRobot->changeXpos(+1.0f), isKeyDown = false;
		break;
	case 'D':
		if (isKeyDown)
			myRobot->changeXpos(-1.0f), isKeyDown = false;
		break;
	case 's':
	case 'S':
		isStart = true;
		break;
	default:
		break;
	}
}
bool collide(float robot_z, float poloy_z, float robot_x, float poloy_x, float velocity)
{
	// x<0.5f  0.0
	velocity = velocity * 0.1f;
	if (((robot_z - velocity) < poloy_z) && (robot_x <= -3) && (poloy_x < -3)) //����
	{
		return true;
	}
	if (((robot_z - velocity) < poloy_z) && (-3 < robot_x) && (robot_x <= 1) &&
		(-1 < poloy_x) && (poloy_x < 2)) //�߾�
	{
		return true;
	}
	if (((robot_z - velocity) < poloy_z) && (1 < robot_x) && (2 < poloy_x))  // ������
	{
		return true;
	}


	return false;
}

void MainState::update()
{
	//�̰� ������Ʈ���� ������� ���ΰ��� �浹üũ�� �����Ͻø� �ɰͰ����ϴ�.
	if(isStart)
	{
	myRobot->update(velocity);

	//���������� �ٴڱ׸��� 
	gameTime += 0.05;
	score += velocity * 0.05;
	if (gameTime >= 2.0f && isFever == false)//����Ÿ���� 5.0�ʸ��� �ӵ��� 1.0�� �����Ѵ�.
	{
		velocity += 1.0f;
		gameTime = 0.0f;
		//���� origin_velocity = velocity; // ������ �ӵ� �� ���� �ִ� �ڸ�.
	}
	for (int i = 0; i < myPolygons.size(); ++i)
	{
		//update�Լ� ȣ���ϸ鼭 ���� ���� ��ȯ�ϴ��� �˻��ϰ� true��ȯ�� ��ü�� ���ΰ����� �ڿ�
		//�ִٴ� ���̱⿡ ��ü�� �迭(����)���� �����Ѵ�.
		if (collide(myRobot->retRobotZpos(), myPolygons[i]->retPolygonZpos(),
			myRobot->retRobotXpos(), myPolygons[i]->retPolygonXpos(), velocity) && isFever == false)// �浹 üũ 
		{
			change = true;
		}
		// ���� ���� or ���� �ʱ� ȭ�� ��ȯ
		if (myPolygons[i]->update(velocity))
		{
			myPolygons.erase(myPolygons.begin() + i);
			//break;
		}

	}
	for (int i = 0; i < myItem.size(); ++i)
	{
		//update�Լ� ȣ���ϸ鼭 ���� ���� ��ȯ�ϴ��� �˻��ϰ� true��ȯ�� ��ü�� ���ΰ����� �ڿ�
		//�ִٴ� ���̱⿡ ��ü�� �迭(����)���� �����Ѵ�.
		if (!isFever && collide(myRobot->retRobotZpos(), myItem[i]->retItemZpos(), myRobot->retRobotXpos(), myItem[i]->retItemXpos(), velocity))// �浹 üũ 
		{
			myItem.erase(myItem.begin() + i);
			isFever = true; // �ǹ� Ÿ�� ��
			origin_velocity = velocity; // ������ �ӵ� �� ����
			velocity *= 2.0f; // �ӵ��� 2�辿 ������Ų��.
			break;
		}
		else if (myItem[i]->update(velocity))
		{
			myItem.erase(myItem.begin() + i);
			break;
		}

	}
	if (isFever == true) // �ǹ� Ÿ���̶��
	{
		feverTime += 0.03f;
		for (int i = 0; i < myPolygons.size(); ++i) // �ǹ� �浹�� 
		{
			//update�Լ� ȣ���ϸ鼭 ���� ���� ��ȯ�ϴ��� �˻��ϰ� true��ȯ�� ��ü�� ���ΰ����� �ڿ�
			//�ִٴ� ���̱⿡ ��ü�� �迭(����)���� �����Ѵ�.
			if (collide(myRobot->retRobotZpos()-3.0f, myPolygons[i]->retPolygonZpos(),
				myRobot->retRobotXpos(), myPolygons[i]->retPolygonXpos(), velocity) )// �浹 üũ 
			{
				
				myPolygons[i]->ChangePolygonRotateType();
			
			}
			// ���� ���� or ���� �ʱ� ȭ�� ��ȯ
			if (myPolygons[i]->update(velocity))
			{
				myPolygons.erase(myPolygons.begin() + i);
				//break;
			}
		}
		for (int i = 0; i < myItem.size(); ++i)
		{
			if (myItem[i]->update(velocity))
				myItem.erase(myItem.begin() + i);
		}
	}
	if (feverTime >= 2.0f) //5.0�ʰ� ������ �ǹ� ����
	{
		velocity = origin_velocity;
		isFever = false;
		feverTime = 0.0f;
	}
	generationTimer += 0.05;
	if (generationTimer >= 1.5f)
	{
		generationTimer = 0.0f;
		int generationCount = 0;//�� ī��Ʈ�� 2�� �Ѿ�� ������ ����X �� ��� 1���⿣ ���� �ִ�.
		for (int i = 0; i < 3; ++i)
		{
			if (bdForPolygonGeneration(dre) && generationCount < 2)
			{
				++generationCount;
				if (bdForPolygonType(dre))
				{
					if (i == 0) myPolygons.emplace_back(make_unique<Pyramid>(POLYGON_DIRECTION::LEFT));
					else if (i == 1)myPolygons.emplace_back(make_unique<Pyramid>(POLYGON_DIRECTION::MIDDLE));
					else myPolygons.emplace_back(make_unique<Pyramid>(POLYGON_DIRECTION::RIGHT));

				}
				else
				{
					if (i == 0) myPolygons.emplace_back(make_unique<Cube>(POLYGON_DIRECTION::LEFT));
					else if (i == 1)myPolygons.emplace_back(make_unique<Cube>(POLYGON_DIRECTION::MIDDLE));
					else myPolygons.emplace_back(make_unique<Cube>(POLYGON_DIRECTION::RIGHT));
				}
			}
			else
			{

				if (bdForItem(dre))
				{

					if (i == 0)
					{
						myItem.emplace_back(make_unique<Item>(ITEM_DIRECTION::LEFT));
					
							
					}

					else if (i == 1)
					{
						myItem.emplace_back(make_unique<Item>(ITEM_DIRECTION::MIDDLE));
						
					}
					else 
					{
						myItem.emplace_back(make_unique<Item>(ITEM_DIRECTION::RIGHT));
						
					}
				}

				//�̰��� ������ �����ϴ� �ڵ� �����ø� �ɰͰ����ϴ�.
			}
		}
	}
	myGround_page_two->update(velocity);
	myGround->update(velocity);
	}
	else {
		myTitle->update(velocity);
	
	}

}

void MainState::exit()
{
	myRobot.release();
	myGround.release();
	myTitle.release();
	//��� ��ü �ı�
	//�ϴ� ����ũ ������ ���� �־ ���� �Ҵ����� �� �ʿ䰡X
	//�ڵ����� �Ҵ�������.
}



void RankingState::enter()
{
	 title_timer = 0.0f;
	 rank_arr[13] = { 0, };
	 rank_arr_index = 0;
	 rank_space_index = 0;
	 finalScore = score;

}

void RankingState::draw()
{

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);

	void * font = GLUT_BITMAP_9_BY_15; // ������ ��Ʈ�� ��Ʈ 

	std::ifstream in("Ranking.txt"); // ��ŷ ������ ����

	if (!in.is_open()) {
		std::cout << "������ ã�� �� �����ϴ�!" << std::endl;
		return;
	}
	std::string rank;
	
	while (in) // ��ŷ ���Ͽ��� ������ �о�´�
	{
		getline(in, rank); // 1�پ� �޾ƿ�
		rank_arr[rank_arr_index++] = atoi(rank.c_str()); // ���� ���� 10��
	}
	in.close(); // ������ �ݴ´�
	rank_arr[rank_arr_index++] = score;// �������� ���ھ� �� ����Ѵ� rank_arr�� 13��¥�� �迭
	for (int i = 11; i >0; i--)// ��������
	{
		for (int j = 0; j < i; j++)
		{
			if (rank_arr[j] < rank_arr[j + 1])
			{
				int tmp = rank_arr[j];
				rank_arr[j] = rank_arr[j + 1];
				rank_arr[j + 1] = tmp;
			}

		}
	} 

	std::ofstream  out("Ranking.txt"); // ���������� �����ϴ�. 
	for (int i = 0; i < 10; i++)
	{
		 out << rank_arr[i] << std::endl; 
	}// ���� ���� 10���� �����Ѵ�
	out.close();// �ݾ��ش� 

	auto modelTransformLocation = glGetUniformLocation(shaderProgramID, "transform");
	auto transMatrix = glm::mat4(1.0f);
	transMatrix = glm::translate(transMatrix, glm::vec3(-3.0f, 18.0f, 0.0f));
	transMatrix = glm::scale(transMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glRasterPos2i(0, 0);
	// ����  ���� ��� �ϱ� (0,0)��ġ�� 
	string s = "Final Score : " + std::to_string(finalScore);
	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	// ����  ��ŷ ����ϱ�  (0,-1)~ (0,-9)���� ���ĵ� arr���� ���!
	for (int i = 0; i < 10; i++)
	{
		glRasterPos2i(0, (-i-1));
		string c = std::to_string(int(i+1))+"_rank :" +  std::to_string(int(rank_arr[i]));
		for (string::iterator i = c.begin(); i != c.end(); ++i)
		{
			char c = *i;
			glutBitmapCharacter(font, c);
		}

	}



	// ����


	glutSwapBuffers();
}

void RankingState::handleEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		break;
	default:
		break;
	}
}
void RankingState::keyUpEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		break;
	default:
		break;
	}
}

void RankingState::update()
{
	title_timer += 0.05f;
	if (title_timer > 2.0f)
	{
		//change = true;
		glutLeaveMainLoop();
	}

	//������Ʈ

}

void RankingState::exit()
{
	//��� ��ü �ı�
	//�ϴ� ����ũ ������ ���� �־ ���� �Ҵ����� �� �ʿ䰡X
	//�ڵ����� �Ҵ�������.
}

void read_file(string s)
{
	std::ifstream in("Ranking.txt");
	

	if (in.is_open()) {
		// ��ġ �����ڸ� ���� ������ �ű��.
		in.seekg(0, std::ios::end);

		// �׸��� �� ��ġ�� �д´�. (������ ũ��)
		int size = in.tellg();

		// �� ũ���� ���ڿ��� �Ҵ��Ѵ�.
		s.resize(size);

		// ��ġ �����ڸ� �ٽ� ���� �� ������ �ű��.
		in.seekg(0, std::ios::beg);

		// ���� ��ü ������ �о ���ڿ��� �����Ѵ�.
		in.read(&s[0], size);
		std::cout << s << std::endl;
	}
	else {
		std::cout << "������ ã�� �� �����ϴ�!" << std::endl;
	}



}


void TitleState::enter()
{
	myTitle = make_unique<Ground>();
	myTitle->plane_type = 1;
}

void TitleState::draw()
{
	glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);


	auto viewMatrix = glm::mat4(1.0f);
	auto projectionMatrix = glm::mat4(1.0f);
	viewMatrix = glm::mat4(1.0f);
	projectionMatrix = glm::mat4(1.0f);
	auto modelTransformLocation = glGetUniformLocation(shaderProgramID, "transform");
	//��ǥ�� ��ȯ�� �κ�Ŭ������ draw���� ���� ����ȴ�.
	//ī�޶�� ������ �κ��� ������ ��ο��� ����ǹǷ� MainState���� �����Ѵ�.
	auto viewTransformLocation = glGetUniformLocation(shaderProgramID, "viewTransform");
	glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	auto projectionTransformLocation = glGetUniformLocation(shaderProgramID, "projectionTransform");
	glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	//get location of uniform!

	auto eye = glm::vec3(cameraXpos, cameraYpos, cameraZpos);
	auto direction = glm::vec3(0.0f, 0.0f, -1.0f);

	auto viewPosLocation = glGetUniformLocation(shaderProgramID, "viewPos");
	glUniform3f(viewPosLocation, eye.x, eye.y, eye.z);
	auto lightPosLocation = glGetUniformLocation(shaderProgramID, "lightPos");
	glUniform3f(lightPosLocation, lightXpos, lightYpos, lightZpos);
	auto lightColorLocation = glGetUniformLocation(shaderProgramID, "lightColor");
	glUniform3f(lightColorLocation, 1.0f, 1.0f, 1.0f);
	auto objColorLocation = glGetUniformLocation(shaderProgramID, "objectColor");

	direction = glm::normalize(direction);
	viewMatrix = glm::lookAt(eye, eye + direction, glm::vec3(0.0f, 1.0f, 0.0f));

	glUniformMatrix4fv(viewTransformLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	projectionMatrix = glm::perspective(glm::radians(120.0f), 4.0f / 3.0f, 0.1f, 1000.0f);
	glUniformMatrix4fv(projectionTransformLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	//������� ī�޶�� ������ȯ ����.


	///////// ��ũ�Ѹ� �̱��� 

	myTitle->draw(modelTransformLocation, objColorLocation);


	auto transMatrix = glm::mat4(1.0f);
	transMatrix = glm::translate(transMatrix, glm::vec3(-3.0f, 18.0f, 0.0f));
	transMatrix = glm::scale(transMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	string s = "the score is:" + std::to_string(int(score));
	void * font = GLUT_BITMAP_9_BY_15;
	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	glRasterPos2i(0, 0);
	//�ؽ�Ʈ �̹��� �׸���. �� �ڵ� �� ���ż� ��ŷ������Ʈ ǥ���Ͻø�ɰͰ����ϴ�.
	glutSwapBuffers();
}

void TitleState::handleEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 's':
		change = true;
		break;
	default:
		break;
	}
}
void TitleState::keyUpEvent(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'a':
		break;
	default:
		break;
	}
}

void TitleState::update()
{

	//������Ʈ

}

void TitleState::exit()
{
	myTitle.release();
	//��� ��ü �ı�
	//�ϴ� ����ũ ������ ���� �־ ���� �Ҵ����� �� �ʿ䰡X
	//�ڵ����� �Ҵ�������.
}