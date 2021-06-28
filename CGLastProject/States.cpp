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
bernoulli_distribution bdForPolygonGeneration(0.4f);//bd means bernoilli_distribution 이거는 해당 위치에 폴리곤 생성할지 안할지(40%)확률로
bernoulli_distribution bdForPolygonType(0.5f);//이거는 50%확률로 피라미드만들지 큐브 만들지 참일경우 피라미드 아니면 큐브
bernoulli_distribution bdForItem(0.5f);// 아이템 생성 할지 말지 


// 글자 변수
int rank_arr[13] = { 0, };
int rank_arr_index = 0;
int rank_space_index = 0;
//위에까지 글자 변수 
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

// 바닥 그리기 
unique_ptr<Ground> myGround;
unique_ptr<Ground> myGround_page_two;
// 타이틀을 위한 변수 
unique_ptr<Ground> myTitle;
bool isStart = false;

// 애니메이션 날아가기 변수



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
	//좌표계 변환은 로봇클래스의 draw에서 직접 적용된다.
	//카메라와 투영은 로봇과 폴리곤 모두에게 적용되므로 MainState에서 진행한다.
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
	//여기까지 카메라랑 투영변환 수행.


	///////// 스크롤링 미구현 
	if (isStart)
	{
		
		myRobot->draw(modelTransformLocation, objColorLocation);
		glUniform3f(objColorLocation, 0.0f, 1.0f, 1.0f);
		for (int i = 0; i < myPolygons.size(); ++i)
			myPolygons[i]->draw(modelTransformLocation);
		glUniform3f(objColorLocation, 1.0f, 1.0f, 0.0f);
		for (int i = 0; i < myItem.size(); i++)
			myItem[i]->draw(modelTransformLocation);
		//이곳에 아이템 그리는 코드 넣으면 될것같습니다.
	
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
		//텍스트 이미지 그리기. 이 코드 잘 쓰셔서 랭킹스테이트 표시하시면될것같습니다.
		


		
	

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
	if (((robot_z - velocity) < poloy_z) && (robot_x <= -3) && (poloy_x < -3)) //왼쪽
	{
		return true;
	}
	if (((robot_z - velocity) < poloy_z) && (-3 < robot_x) && (robot_x <= 1) &&
		(-1 < poloy_x) && (poloy_x < 2)) //중앙
	{
		return true;
	}
	if (((robot_z - velocity) < poloy_z) && (1 < robot_x) && (2 < poloy_x))  // 오른쪽
	{
		return true;
	}


	return false;
}

void MainState::update()
{
	//이곳 업데이트에서 폴리곤과 주인공의 충돌체크를 구현하시면 될것같습니다.
	if(isStart)
	{
	myRobot->update(velocity);

	//위에까지가 바닥그리기 
	gameTime += 0.05;
	score += velocity * 0.05;
	if (gameTime >= 2.0f && isFever == false)//게임타임이 5.0초마다 속도가 1.0씩 증가한다.
	{
		velocity += 1.0f;
		gameTime = 0.0f;
		//원래 origin_velocity = velocity; // 기존의 속도 값 저장 있던 자리.
	}
	for (int i = 0; i < myPolygons.size(); ++i)
	{
		//update함수 호출하면서 무슨 값을 반환하는지 검사하고 true반환시 객체가 주인공보다 뒤에
		//있다는 말이기에 객체를 배열(벡터)에서 제거한다.
		if (collide(myRobot->retRobotZpos(), myPolygons[i]->retPolygonZpos(),
			myRobot->retRobotXpos(), myPolygons[i]->retPolygonXpos(), velocity) && isFever == false)// 충돌 체크 
		{
			change = true;
		}
		// 게임 종료 or 게임 초기 화면 전환
		if (myPolygons[i]->update(velocity))
		{
			myPolygons.erase(myPolygons.begin() + i);
			//break;
		}

	}
	for (int i = 0; i < myItem.size(); ++i)
	{
		//update함수 호출하면서 무슨 값을 반환하는지 검사하고 true반환시 객체가 주인공보다 뒤에
		//있다는 말이기에 객체를 배열(벡터)에서 제거한다.
		if (!isFever && collide(myRobot->retRobotZpos(), myItem[i]->retItemZpos(), myRobot->retRobotXpos(), myItem[i]->retItemXpos(), velocity))// 충돌 체크 
		{
			myItem.erase(myItem.begin() + i);
			isFever = true; // 피버 타임 온
			origin_velocity = velocity; // 기존의 속도 값 저장
			velocity *= 2.0f; // 속도를 2배씩 증가시킨다.
			break;
		}
		else if (myItem[i]->update(velocity))
		{
			myItem.erase(myItem.begin() + i);
			break;
		}

	}
	if (isFever == true) // 피버 타임이라면
	{
		feverTime += 0.03f;
		for (int i = 0; i < myPolygons.size(); ++i) // 피버 충돌시 
		{
			//update함수 호출하면서 무슨 값을 반환하는지 검사하고 true반환시 객체가 주인공보다 뒤에
			//있다는 말이기에 객체를 배열(벡터)에서 제거한다.
			if (collide(myRobot->retRobotZpos()-3.0f, myPolygons[i]->retPolygonZpos(),
				myRobot->retRobotXpos(), myPolygons[i]->retPolygonXpos(), velocity) )// 충돌 체크 
			{
				
				myPolygons[i]->ChangePolygonRotateType();
			
			}
			// 게임 종료 or 게임 초기 화면 전환
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
	if (feverTime >= 2.0f) //5.0초가 지나면 피버 종료
	{
		velocity = origin_velocity;
		isFever = false;
		feverTime = 0.0f;
	}
	generationTimer += 0.05;
	if (generationTimer >= 1.5f)
	{
		generationTimer = 0.0f;
		int generationCount = 0;//이 카운트가 2가 넘어가면 폴리곤 생성X 즉 적어도 1방향엔 길이 있다.
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

				//이곳에 아이템 생성하는 코드 넣으시면 될것같습니다.
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
	//모든 객체 파괴
	//일단 유니크 포인터 쓰고 있어서 따로 할당해제 할 필요가X
	//자동으로 할당해제됨.
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

	void * font = GLUT_BITMAP_9_BY_15; // 내가쓸 비트맵 폰트 

	std::ifstream in("Ranking.txt"); // 랭킹 파일을 열고

	if (!in.is_open()) {
		std::cout << "파일을 찾을 수 없습니다!" << std::endl;
		return;
	}
	std::string rank;
	
	while (in) // 랭킹 파일에서 점수를 읽어온다
	{
		getline(in, rank); // 1줄씩 받아옴
		rank_arr[rank_arr_index++] = atoi(rank.c_str()); // 점수 저장 10개
	}
	in.close(); // 파일을 닫는다
	rank_arr[rank_arr_index++] = score;// 마지막에 스코어 를 출력한다 rank_arr은 13개짜리 배열
	for (int i = 11; i >0; i--)// 버블정렬
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

	std::ofstream  out("Ranking.txt"); // 정렬했으니 저장하다. 
	for (int i = 0; i < 10; i++)
	{
		 out << rank_arr[i] << std::endl; 
	}// 상위 점수 10개를 저장한다
	out.close();// 닫아준다 

	auto modelTransformLocation = glGetUniformLocation(shaderProgramID, "transform");
	auto transMatrix = glm::mat4(1.0f);
	transMatrix = glm::translate(transMatrix, glm::vec3(-3.0f, 18.0f, 0.0f));
	transMatrix = glm::scale(transMatrix, glm::vec3(2.0f, 2.0f, 2.0f));
	glUniformMatrix4fv(modelTransformLocation, 1, GL_FALSE, glm::value_ptr(transMatrix));
	glRasterPos2i(0, 0);
	// 최종  점수 출력 하기 (0,0)위치에 
	string s = "Final Score : " + std::to_string(finalScore);
	for (string::iterator i = s.begin(); i != s.end(); ++i)
	{
		char c = *i;
		glutBitmapCharacter(font, c);
	}
	// 최종  랭킹 출력하기  (0,-1)~ (0,-9)까지 정렬된 arr에서 출력!
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



	// 글자


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

	//업데이트

}

void RankingState::exit()
{
	//모든 객체 파괴
	//일단 유니크 포인터 쓰고 있어서 따로 할당해제 할 필요가X
	//자동으로 할당해제됨.
}

void read_file(string s)
{
	std::ifstream in("Ranking.txt");
	

	if (in.is_open()) {
		// 위치 지정자를 파일 끝으로 옮긴다.
		in.seekg(0, std::ios::end);

		// 그리고 그 위치를 읽는다. (파일의 크기)
		int size = in.tellg();

		// 그 크기의 문자열을 할당한다.
		s.resize(size);

		// 위치 지정자를 다시 파일 맨 앞으로 옮긴다.
		in.seekg(0, std::ios::beg);

		// 파일 전체 내용을 읽어서 문자열에 저장한다.
		in.read(&s[0], size);
		std::cout << s << std::endl;
	}
	else {
		std::cout << "파일을 찾을 수 없습니다!" << std::endl;
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
	//좌표계 변환은 로봇클래스의 draw에서 직접 적용된다.
	//카메라와 투영은 로봇과 폴리곤 모두에게 적용되므로 MainState에서 진행한다.
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
	//여기까지 카메라랑 투영변환 수행.


	///////// 스크롤링 미구현 

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
	//텍스트 이미지 그리기. 이 코드 잘 쓰셔서 랭킹스테이트 표시하시면될것같습니다.
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

	//업데이트

}

void TitleState::exit()
{
	myTitle.release();
	//모든 객체 파괴
	//일단 유니크 포인터 쓰고 있어서 따로 할당해제 할 필요가X
	//자동으로 할당해제됨.
}