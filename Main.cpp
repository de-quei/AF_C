#include <stdio.h>
#include <SFML/Graphics.hpp>
using namespace sf;

int main(void) {
	
	RenderWindow window(VideoMode(640, 480), "AfterSchool"); // 윈도우 창 생성
	window.setFramerateLimit(60);

	RectangleShape player;
	player.setSize(Vector2f(40, 40));
	player.setPosition(100, 100);
	player.setFillColor(Color::Red);
	int player_speed = 5;

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

		if (Keyboard::isKeyPressed(Keyboard::Left)) 
		{
			player.move(-player_speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.move(player_speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.move(0, -player_speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player.move(0, player_speed);
		}

		window.clear(Color::Black);
		window.draw(player);
		window.display();
	}
	return 0;
}
