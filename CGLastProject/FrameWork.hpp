#pragma once
#include "States.hpp"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glm/glm.hpp"
#include "GL/glm/ext.hpp"
#include "GL/glm/gtc/matrix_transform.hpp"
//draw함수가 메인에서 그리기 함수로 등록이되고 현재 스테이트의 드로우를 호출한다.
//핸들이벤트가 메인에서 키보드 이벤트 함수로 등록(키보드 이벤트만 존재하여서.)되고
//현재 스테이트의 핸들 이벤트를 호출한다.
//업데이트 함수가 타이머 메인에서 타이머 함수로 등록되고 이곳에서 현재 스테이트의 업데이트 함수를 호출.
//체인지 스테이트를 통해서 스테이트를 변경한다.
extern GLuint shaderProgramID;
class FrameWork
{
public:
	FrameWork(State* _initState):curState(_initState)
	{
		curState->enter();
	}
	void draw()
	{
		curState->draw();
	}
	void update()
	{
		curState->update();
	}
	void handleEvent(unsigned char key, int x, int y)
	{
		curState->handleEvent(key, x, y);
	}
	void keyUpEvent(unsigned char key, int x, int y)
	{
		curState->keyUpEvent(key, x, y);
	}
	void changeState(State* _state) //현재 상태의exit함수를 호출하고 다음 스테이트의 enter 함수를 호출한다.
	{
		curState->exit();
		curState = nullptr;
		curState = _state;
		curState->enter();
	}
	GLint retShaderProgramID()
	{
		return shaderProgramID;
	}
private:
	State* curState = nullptr;
	int running = true;
	
	//현재 무슨 스테이트인지 담고있는 변수.
};