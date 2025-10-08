#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
using namespace sf;

class Player
{
public:
	Texture texture;
	Sprite sprite;
	float speed = 1.f;
	Vector2f direction = { 0.f, 0.f };
	Vector2f gravity = { 0.f, 0.5f };

	// -- Анімація
	Vector2i frameSize = { 32, 64 };
	std::map<std::string, std::vector<IntRect>> animations = {
		// IDLE anim
		{ 
			"idle", {
				IntRect({ 0 * 32, 0 * 64 }, frameSize)
			}
		},
		// WALK anim
		{
			"walk", {
				IntRect({ 1 * 32, 0 * 64 }, frameSize),
				IntRect({ 2 * 32, 0 * 64 }, frameSize),
				IntRect({ 3 * 32, 0 * 64 }, frameSize),
				IntRect({ 4 * 32, 0 * 64 }, frameSize),
				IntRect({ 5 * 32, 0 * 64 }, frameSize),
				IntRect({ 6 * 32, 0 * 64 }, frameSize),
			}
		},
	};
	std::string currentAnimation = "idle";
	float frameDuration = 0.8f;
	int currentFrame = -1;
	float elapsedTime = frameDuration;


public:
	Player();
	Player(const char[]);
	~Player();

	void updateDirection();
	// -- Оновлення анімації
	void updateAnimation(float);
	void update(float);
	void draw(RenderWindow&);
	Vector2f getScale();
	void setScale(Vector2f);
	void setCurrentAnimation(const char[]);
};