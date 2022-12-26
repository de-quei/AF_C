#include <stdio.h>
#include <SFML/Graphics.hpp>
using namespace sf;

int main(void) {
	
	RenderWindow window(VideoMode(640, 480), "AfterSchool"); // 윈도우 창 생성

	RectangleShape player;
	player.setSize(Vector2f(40, 40));
	player.setPosition(100, 100);

	while (window.isOpen()) // 윈도우가 열려 있을 때 까지 반복
	{ 
		Event event;
		while (window.pollEvent(event)) 
		{
			switch (event.type)
			{
			case Event::Closed:// 종료(x) 버튼을 누르면
				window.close();// 윈도우를 닫는다
			}
			
		}
		window.draw(player);
		window.display();
	}
	return 0;
}
