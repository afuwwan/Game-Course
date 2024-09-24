#ifndef INGAMESCREEN_H
#define INGAMESCREEN_H

#include "Screen.h"
#include "Turtle.h"
#include "ScreenManager.h"
#include "Game.h"
#include "Setting.h"
#include "Texture.h"
#include "Sprite.h"
#include "Music.h"
#include "Sound.h"
#include "Text.h"
#include "Input.h"
#include <vector>
#include <chrono>
#include <iostream>
#include "DinoReal.h"
#include "Lesson07_GUI.h"
#include <SDL/SDL.h>

namespace Engine {
	class InGameScreen :
		public Engine::Screen
	{
	public:
		enum class GameState
		{
			RUNNING,
			RESET,
			GAME_OVER
		};
		GameState gstate;

		InGameScreen();
		void Init();
		void Update();
		void Draw();
		virtual void restartGame();
	private:
		Engine::Sprite* CreateSprite(Texture* texture);
		void SpawnObjects();
		vector<Turtle*> objects;
		float spawnDuration = 0, maxSpawnTime = 0, numObjectsInPool = 0, numObjectPerSpawn = 0;

		int score;
		int lastTime;
		int lastSpriteTime;

		Texture* dotTexture = NULL;
		vector<Sprite*> platforms;

		Sprite* dotSprite1 = NULL;
		Sprite* dotSprite2 = NULL;
		Sprite* dotSprite3 = NULL;
		Sprite* dotSprite4 = NULL;

		Text* text = NULL;
		Text* text2 = NULL;
		std::string died;

		Engine::Sprite* backgroundSprite = NULL;
		Engine::Texture* Ptexture = NULL;
		Engine::Texture* texture = NULL;
		Engine::Sprite* sprite = NULL;
		Engine::Texture* texture2 = NULL;
		Engine::Sprite* sprite2 = NULL;

		Engine::Texture* tx_obstacle = NULL;
		Engine::Sprite* sp_obstacle = NULL;
		Engine::Sprite* sp_obstacle2 = NULL;
		//std::vector<Sprite*> platforms;
		//vector<Sprite*> platforms;


		float yVelocity = 0, gravity = 0;
		bool jump = false, debug = false;

		Music* music = NULL;
		Sound* sound = NULL;
		Sound* deathSound = NULL;

		vector<Sprite*> backgrounds, middlegrounds, foregrounds, front;

		void MoveLayer(vector<Sprite*>& bg, float speed);
		void DrawLayer(vector<Sprite*>& bg);
		void AddToLayer(vector<Sprite*>& bg, string name);
		float offset = 4;

		//Input* mousepos = NULL;

		bool gameOver = false;//
	};
}

#endif



//
//		DinoReal(Setting* setting);
//		~DinoReal();
//		virtual void Init();
//		virtual void Update();
//		virtual void Render();
//		virtual void restartGame();
//		// void GenerateNewSprite();
//	private:
//		int score;
//		int lastTime;
//		int lastSpriteTime;
//
//		Texture* dotTexture = NULL;
//		vector<Sprite*> platforms;
//
//		Sprite* dotSprite1 = NULL;
//		Sprite* dotSprite2 = NULL;
//		Sprite* dotSprite3 = NULL;
//		Sprite* dotSprite4 = NULL;
//
//		Text* text = NULL;
//		Text* text2 = NULL;
//		std::string died;
//
//		Engine::Sprite* backgroundSprite = NULL;
//		Engine::Texture* Ptexture = NULL;
//		Engine::Texture* texture = NULL;
//		Engine::Sprite* sprite = NULL;
//		Engine::Texture* texture2 = NULL;
//		Engine::Sprite* sprite2 = NULL;
//
//		Engine::Texture* tx_obstacle = NULL;
//		Engine::Sprite* sp_obstacle = NULL;
//		Engine::Sprite* sp_obstacle2 = NULL;
//		//std::vector<Sprite*> platforms;
//		//vector<Sprite*> platforms;
//
//
//		float yVelocity = 0, gravity = 0;
//		bool jump = false, debug = false;
//
//		Music* music = NULL;
//		Sound* sound = NULL;
//		Sound* deathSound = NULL;
//
//		vector<Sprite*> backgrounds, middlegrounds, foregrounds, front;
//
//		void MoveLayer(vector<Sprite*>& bg, float speed);
//		void DrawLayer(vector<Sprite*>& bg);
//		void AddToLayer(vector<Sprite*>& bg, string name);
//		float offset = 4;
//
//		//Input* mousepos = NULL;
//
//		bool gameOver = false;//
//
//
//	};
//}