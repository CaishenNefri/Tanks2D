#include "game.h"

void Game::menu(){
	const int ILE{ 3 };
	sf::Text tekst[ILE];
	sf::String str[]{"1 player", "2 players", "Exit"};
	sf::Sprite menuStone = spr.stoneBig;

	for (int i = 0; i < ILE; i++){
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(okno.getSize().y / 12);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(float(okno.getSize().y / 3),
			float(okno.getSize().y / 2.5 + i * okno.getSize().y / 6.4));
	}

	spr.tankIco.setScale(map.pr.scale * 1.5, map.pr.scale * 1.5);

	icon = GameState::SinglePlayerGame;

	while (state == GameState::Menu){
		eventsMenu();

		for (int i = 0; i < ILE; i++){
			if (i == int(icon) - 1){
				tekst[i].setColor(sf::Color::Red);
				spr.tankIco.setPosition(tekst[i].getPosition());
				spr.tankIco.move(float(okno.getSize().x) / float(-20.0), 0);
			}
			else tekst[i].setColor(sf::Color::White);
		}
		okno.clear();
		for (int y = 0; y < 15; y++){
			for (int x = 0; x < map.pr.widthInBlocks / 2; x++){
				if (x == 0 || y == 0 || x == map.pr.widthInBlocks / 2 - 1 || y == 14){
					menuStone.setScale(map.pr.scale, map.pr.scale); 
					menuStone.setPosition(map.pr.sides + x * (map.pr.blockSize * 2), map.pr.topBot + y * (map.pr.blockSize * 2));
					okno.draw(menuStone);
				}
			}
		}
		spr.backGround.setPosition(std::round(map.pr.widthInBlocks / 8) * map.pr.blockSize + map.pr.sides, 4 * map.pr.blockSize + map.pr.topBot);
		spr.backGround.setScale(2 * map.pr.scale, 2 * map.pr.scale);
		okno.draw(spr.backGround);
		okno.draw(spr.tankIco);
		for (int i = 0; i < ILE; i++){
			okno.draw(tekst[i]);
		}
		FPSclock.draw(okno);
		okno.display();
	}
}
void Game::eventsMenu(){
	sf::Event event;
	while (okno.pollEvent(event)){
		//Wciœniêcie ESC lub przycisk X w oknie
		if (event.type == sf::Event::Closed || event.type == sf::Event::KeyPressed &&
			event.key.code == sf::Keyboard::Escape)
			state = GameState::EXIT;
		//1 player mode (czo³g w odpowiedniej pozycji + enter)
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return &&
			icon == GameState::SinglePlayerGame){
			state = GameState::SinglePlayerGame;
		}
		//2 players mode (czo³g w odpowiedniej pozycji + enter)
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return &&
			icon == GameState::TwoPlayerGame){
			state = GameState::TwoPlayerGame;
		}
		//EXIT mode (czo³g w odpowiedniej pozycji + enter)
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Return &&
			icon == GameState::EXIT){
			state = GameState::EXIT;
		}
		//poruszanie ikonk¹ czo³gu - strza³ka do góry
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Up && int(icon) > 1){
			switch (icon){
			case GameState::TwoPlayerGame: icon = GameState::SinglePlayerGame;
				break;
			case GameState::EXIT: icon = GameState::TwoPlayerGame;
				break;
			}
		}
		//poruszanie ikonk¹ czo³gu - strza³ka w dó³
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::Down && int(icon) < 3){
			switch (icon){
			case GameState::SinglePlayerGame: icon = GameState::TwoPlayerGame;
				break;
			case GameState::TwoPlayerGame: icon = GameState::EXIT;
				break;
			}
		}
		else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T){
			FPSclock.switchClock();
		}
	}
}