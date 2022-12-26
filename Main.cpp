#include <stdio.h>
#include <SFML/Graphics.hpp>
using namespace sf;

int main(void) {
	
	RenderWindow window(VideoMode(640, 480), "AfterSchool"); //윈도우 창 생성
	while (window.isOpen()) {
		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) {
				window.close();
			}
		}
	}
	return 0;
}