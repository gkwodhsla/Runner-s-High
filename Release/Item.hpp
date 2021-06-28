#pragma once
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glew.h"
#include "GL/freeglut.h"
#include "GL/glm/glm.hpp"
#include "GL/glm/ext.hpp"
#include "GL/glm/gtc/matrix_transform.hpp"

enum class ITEM_DIRECTION
{
	LEFT,
	RIGHT,
	MIDDLE
};

//�������� �����Ǵ� ��ġ ���� 3���� �ִ� ����, ������, ��� 
class ItemAbstractClass
{
public:
	virtual void draw(GLint modelTransformLocation) = 0;
	virtual bool update(float) = 0;
	virtual float retItemZpos() = 0;
	virtual float retItemXpos() = 0;

	//update �Լ����� z���� ��� ���ҽ�Ű�ٰ� Ư�� z���� �����ϸ� return true(��ü�� �����.)
	//�߰������� rads�� ������Ŵ!!
};

class Item :public ItemAbstractClass
{
public:
	Item(ITEM_DIRECTION initDirection);
	virtual void draw(GLint modelTransformLocation) override;
	virtual bool update(float)override;
	virtual float retItemZpos() { return ItemZpos; };
	virtual float retItemXpos() { return ItemXpos; };
	~Item();
private:
	float ItemXpos;
	float ItemYpos;
	float ItemZpos;
	float rads;//rads������ŭ �������� y��������� ȸ���Ѵ�.
	unsigned int VAO, VBO, VBOC;
	glm::mat4 transMatrix;
	GLvoid initMatrix();
};

