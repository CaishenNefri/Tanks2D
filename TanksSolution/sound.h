#pragma once

#include <map>
#include <string>
#include <SFML\Audio.hpp>
#include "tank.h"

typedef std::map < std::string, sf::Sound > soundsMap;

class Sound{
private:
	std::map<int, sf::SoundBuffer> buffer;
public:
	//Lista dŸwiêków:
	//jazda, spoczynek, gameOver, strza³, strza³Blok
	soundsMap Sounds;

	Sound(){
		int i{ 0 };

		buffer[i].loadFromFile("data/dŸwiêki/jazdaV2.wav");
		Sounds["jazda"].setBuffer(buffer[i]);
		Sounds["jazda"].setLoop(true);
		Sounds["jazda"].setVolume(50);
		i++;

		buffer[i].loadFromFile("data/dŸwiêki/spoczynekV2.wav");
		Sounds["spoczynek"].setBuffer(buffer[i]);
		Sounds["spoczynek"].setLoop(true);
		Sounds["spoczynek"].setVolume(50);
		i++;

		buffer[i].loadFromFile("data/dŸwiêki/gameOver.wav");
		Sounds["gameOver"].setBuffer(buffer[i]);
		Sounds["gameOver"].setVolume(75);
		i++;

		buffer[i].loadFromFile("data/dŸwiêki/strza³.wav");
		Sounds["strza³"].setBuffer(buffer[i]);
		Sounds["strza³"].setVolume(25);
		i++;

		buffer[i].loadFromFile("data/dŸwiêki/strza³BlokV3.wav");
		Sounds["strza³Blok"].setBuffer(buffer[i]);
		Sounds["strza³Blok"].setVolume(75);
		i++;

		buffer[i].loadFromFile("data/dŸwiêki/wybuch.wav");
		Sounds["wybuch"].setBuffer(buffer[i]);
		Sounds["wybuch"].setVolume(100);
	}

	void updateSound(std::list<TankPtr> & tanks){
		bool jedziemy{ false };
		for (auto & tank : tanks){
			if (tank->move != Tank::Move::none){
				jedziemy = { true };
				break;
			}
		}
		if (jedziemy){
			if (Sounds["jazda"].getStatus() != sf::Sound::Status::Playing){
				Sounds["spoczynek"].stop();
				Sounds["jazda"].play();
			}
		}
		else{
			if (Sounds["spoczynek"].getStatus() != sf::Sound::Status::Playing){
				Sounds["jazda"].stop();
				Sounds["spoczynek"].play();
			}
		}
	}
	void stopAll(){
		Sounds["jazda"].stop();
		Sounds["spoczynek"].stop();
		Sounds["gameOver"].stop();
		Sounds["strza³"].stop();
		Sounds["strza³Blok"].stop();
	}
};