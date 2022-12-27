#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include <SFML/Audio.hpp>

using namespace sf;

struct Player {
	RectangleShape sprite;
	int speed;
	int score;
	int life;

};
struct Enemy {
	RectangleShape sprite;
	int speed;
	int score;
	int life;
	SoundBuffer explosion_buffer;
	Sound explosion_sound;

};

int main(void) {
	
	// 윈도우 창 생성
	RenderWindow window(VideoMode(640, 480), "Let's win the Jesus!"); 
	window.setFramerateLimit(60);

	srand(time(0));

	long start_time = clock(); //게임 시작 시간
	long spent_time; //게임 진행 시간

	//폰트 
	Font font;
	font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf");

	//텍스트
	Text text;
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(Color(255, 255, 255));
	text.setPosition(0, 0);
	char info[40];
	text.setString("score");

	//배경
	Texture bg_texture;
	bg_texture.loadFromFile("./resources/background.jpg");
	Sprite bg_sprite;
	bg_sprite.setTexture(bg_texture);
	bg_sprite.setPosition(0, 0);

	//player
	struct Player player;
	player.sprite.setSize(Vector2f(40, 40));
	player.sprite.setPosition(100, 100);
	player.sprite.setFillColor(Color::Red);
	player.speed = 7;
	player.score = 0;
	player.life = 5;

	//enemy
	const int ENEMY_NUM = 10;

	struct Enemy enemy[ENEMY_NUM];

	//enemy 초기화
	for (int i = 0; i < ENEMY_NUM; i++)
	{
		//TODO : 굉장히 비효율적인 코드이므로 나중에 refactoring
		enemy[i].explosion_buffer.loadFromFile("./resources/rumble.flac");
		enemy[i].explosion_sound.setBuffer(enemy[i].explosion_buffer);
		enemy[i].score = 100;

		enemy[i].sprite.setSize(Vector2f(70, 70));
		enemy[i].sprite.setFillColor(Color::Yellow);
		enemy[i].sprite.setPosition(rand()%300+300, rand() % 480);
		enemy[i].life = 1;
		enemy[i].speed = -(rand() % 5 + 1);
	}

	// 윈도우가 열려 있을 때 까지 반복
	while (window.isOpen()) 
	{ 
		Event event;
		while (window.pollEvent(event)) 
		{
			switch (event.type)
			{
			case Event::Closed:// 종료(x) 버튼을 누르면
				window.close();// 윈도우를 닫는다
				break;
			//키보드를 눌렀을 때 (누른 순간만 감지)
			case Event::KeyPressed:
			{
				//space 누르면 모든  enemy 재출현
				if (event.key.code == Keyboard::Space)
				{
					for (int i = 0; i < ENEMY_NUM; i++)
					{
						enemy[i].sprite.setSize(Vector2f(70, 70));
						enemy[i].sprite.setFillColor(Color::Yellow);
						enemy[i].life = 1;
						enemy[i].sprite.setPosition(rand() % 300 + 300, rand() % 480);
					}
				}
				break;
			}

			}
			
		}

		spent_time = clock() - start_time;

		//player 방향키 start
		if (Keyboard::isKeyPressed(Keyboard::Left)) 
		{
			player.sprite.move(-player.speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			player.sprite.move(player.speed, 0);
		}
		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			player.sprite.move(0, -player.speed);
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			player.sprite.move(0, player.speed);
		} //방향키 end

		
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemy[i].life > 0)
			{
				//enemy와의 충돌
				if (player.sprite.getGlobalBounds().intersects(enemy[i].sprite.getGlobalBounds()))
				{
					printf("enemy[%d]와 충돌\n", i+1);
					enemy[i].life -= 1;
					player.score += enemy[i].score;

					// TODO : 코드 refactoring 필요
					if (enemy[i].life == 0)
					{
						enemy[i].explosion_sound.play();
					}
				}
				//enemy가 왼쪽에 진입하려는 순간
				else if (enemy[i].sprite.getPosition().x < 0)
				{
					player.life -= 1;
					enemy[i].life = 0;
				}
				enemy[i].sprite.move(enemy[i].speed, 0);
			}
		}

		//점수 적용
		sprintf(info, "Life : %d | Score : %d | Time : %dsec", player.life, player.score, spent_time/1000);
		text.setString(info);

		window.clear(Color::Black);
		window.draw(bg_sprite);

		//draw는 나중에 호출할수록 우선순위가 높아짐
		for (int i = 0; i < ENEMY_NUM; i++)
		{
			if (enemy[i].life > 0)
			{
				window.draw(enemy[i].sprite);
			}
		}
		
		window.draw(player.sprite);
		window.draw(text);
		window.display();
	}
	return 0;
}
