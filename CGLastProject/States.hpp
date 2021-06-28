#pragma once

//enter에서 스테이트의 초기화 수행
//draw 에서 그리기
//handleEvent에서 키보드 이벤트 처리
//update에서 게임로직 업데이트
//exit에서 현재 그려지고있는 모든 객체 파괴
//상태는 한번 만들고 계속 쓰다가 게임이 완전히 종료되면 없애버린다.
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