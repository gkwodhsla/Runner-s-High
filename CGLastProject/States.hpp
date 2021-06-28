#pragma once

//enter���� ������Ʈ�� �ʱ�ȭ ����
//draw ���� �׸���
//handleEvent���� Ű���� �̺�Ʈ ó��
//update���� ���ӷ��� ������Ʈ
//exit���� ���� �׷������ִ� ��� ��ü �ı�
//���´� �ѹ� ����� ��� ���ٰ� ������ ������ ����Ǹ� ���ֹ�����.
class State
{
public:
	virtual void enter() = 0;
	virtual void draw() =0;
	virtual void handleEvent(unsigned char key, int x, int y) = 0;
	virtual void keyUpEvent(unsigned char key, int x, int y) = 0;
	virtual void update() = 0;
	virtual void exit() = 0;
	bool change = false;
};

class MainState :public State
{
public:
	virtual void enter() override;
	virtual void draw() override;
	virtual void handleEvent(unsigned char key, int x, int y) override;
	virtual void keyUpEvent(unsigned char key, int x, int y) override;
	virtual void update() override;
	virtual void exit() override;
};

class RankingState :public State
{
public:
	virtual void enter() override;
	virtual void draw() override;
	virtual void handleEvent(unsigned char key, int x, int y) override;
	virtual void keyUpEvent(unsigned char key, int x, int y) override;
	virtual void update() override;
	virtual void exit() override;
};

class TitleState :public State
{
public:
	virtual void enter() override;
	virtual void draw() override;
	virtual void handleEvent(unsigned char key, int x, int y) override;
	virtual void keyUpEvent(unsigned char key, int x, int y) override;
	virtual void update() override;
	virtual void exit() override;
};