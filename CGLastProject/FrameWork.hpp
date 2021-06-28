#pragma once
#include "States.hpp"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glm/glm.hpp"
#include "GL/glm/ext.hpp"
#include "GL/glm/gtc/matrix_transform.hpp"
//draw�Լ��� ���ο��� �׸��� �Լ��� ����̵ǰ� ���� ������Ʈ�� ��ο츦 ȣ���Ѵ�.
//�ڵ��̺�Ʈ�� ���ο��� Ű���� �̺�Ʈ �Լ��� ���(Ű���� �̺�Ʈ�� �����Ͽ���.)�ǰ�
//���� ������Ʈ�� �ڵ� �̺�Ʈ�� ȣ���Ѵ�.
//������Ʈ �Լ��� Ÿ�̸� ���ο��� Ÿ�̸� �Լ��� ��ϵǰ� �̰����� ���� ������Ʈ�� ������Ʈ �Լ��� ȣ��.
//ü���� ������Ʈ�� ���ؼ� ������Ʈ�� �����Ѵ�.
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
	void changeState(State* _state) //���� ������exit�Լ��� ȣ���ϰ� ���� ������Ʈ�� enter �Լ��� ȣ���Ѵ�.
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
	
	//���� ���� ������Ʈ���� ����ִ� ����.
};