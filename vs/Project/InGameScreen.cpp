#include "InGameScreen.h"

Engine::InGameScreen::InGameScreen()
{

	delete texture;
	delete sprite;
	delete texture2;
	delete sprite2;

	delete dotTexture;
	delete dotSprite1;
	delete dotSprite2;
	delete dotSprite3;
	delete dotSprite4;
	delete music;
	delete text;
	delete text2;

	delete tx_obstacle;
	delete sp_obstacle;
	delete sp_obstacle2;

}

void Engine::InGameScreen::Init()
{
	//// Spawn setting
	//maxSpawnTime = 300;
	//numObjectPerSpawn = 1;
	//numObjectsInPool = 50;

	//// Load a texture
	//Texture* texture = new Texture("turtles.png");
	//for (int i = 0; i < numObjectsInPool; i++) {
	//	Turtle* o = new Turtle(CreateSprite(texture));
	//	objects.push_back(o);
	//}
	

#pragma region init background

	Texture* bgTexture = new Texture("senja.png");//
	backgroundSprite = (new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);//

#pragma endregion

#pragma region init inputManager

	game->GetInputManager()->AddInputMapping("mainmenu", SDLK_ESCAPE);

	game->GetInputManager()->AddInputMapping("Move Right", SDLK_RIGHT)
		->AddInputMapping("Move Left", SDLK_LEFT)
		->AddInputMapping("Move Up", SDLK_UP)
		->AddInputMapping("Move Down", SDLK_DOWN)
		->AddInputMapping("Jump", SDLK_SPACE)
		->AddInputMapping("Attack", SDLK_x)
		->AddInputMapping("Run Right", SDL_CONTROLLER_BUTTON_DPAD_RIGHT)
		->AddInputMapping("Run Left", SDL_CONTROLLER_BUTTON_DPAD_LEFT)
		->AddInputMapping("Jump", SDL_CONTROLLER_BUTTON_A)
		->AddInputMapping("Attack", SDL_CONTROLLER_BUTTON_X)
		->AddInputMapping("Quit", SDLK_ESCAPE)
		->AddInputMapping("Quit", SDL_CONTROLLER_BUTTON_Y)
		->AddInputMapping("Reset", SDLK_j);

	game->GetInputManager()/*->AddInputMapping("next", SDLK_s)*/
		->AddInputMapping("prev", SDLK_w)
		->AddInputMapping("prev", SDLK_UP)
		->AddInputMapping("next", SDLK_DOWN)
		->AddInputMapping("press", SDLK_RETURN);
	/*->AddInputMapping("press", SDLK_k);*/ //remove input mapping



#pragma endregion

#pragma region init parallaxBackground

	for (int i = 1; i <= 3; i++) {
		AddToLayer(backgrounds, "bg0" + to_string(i) + ".png");
	}
	for (int i = 4; i <= 5; i++) {
		AddToLayer(middlegrounds, "bg0" + to_string(i) + ".png");
	}
	for (int i = 6; i <= 6; i++) {
		AddToLayer(foregrounds, "bg0" + to_string(i) + ".png");
	}

	AddToLayer(front, "road.png");

	offset = 2;

#pragma endregion

#pragma region init spriteSheet

	texture = new Texture("duck.png");
	sprite = new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	sprite->SetNumXFrames(3)
		->SetNumYFrames(1)
		->AddAnimation("walk", 0, 2)
		->AddAnimation("float", 1, 1)
		->SetScale(5)
		->SetAnimationDuration(100)
		->SetPosition(50, 100)
		->SetBoundingBoxSize(150, 100);

#pragma endregion

#pragma region obstacle init


	Texture* platformTexture = new Texture("rock.png");
	Texture* platformTexture2 = new Texture("goku.png");
	vec2 start = vec2(2000, 0);
	for (int i = 0; i < 1; i++) {
		Sprite* platformSprite = new Sprite(platformTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
		platformSprite->SetSize(150, 200)->SetPosition(start.x + i * 1000, start.y);
		platformSprite->SetBoundingBoxSize(platformSprite->GetScaleWidth() - (3.5 * platformSprite->GetScale()), platformSprite->GetScaleHeight() - 10);
		platforms.push_back(platformSprite);
	}

	//debugging
	dotTexture = new Texture("dot.png");
	dotSprite1 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	dotSprite2 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	dotSprite3 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	dotSprite4 = new Sprite(dotTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());



#pragma endregion

#pragma region sprite angle based on mousecoords



#pragma endregion

#pragma region score feature

	score = 0;
	Uint32 lastTime = 0;  // Store the last time the score was updated

	//Debug
	std::string died = "You Died";

#pragma endregion

#pragma region sound init

	music = (new Music("Rosolanc.ogg"))->SetVolume(70);
	music2 = (new Music("2021-08-16_-_8_Bit_Adventure_-_www.FesliyanStudios.com.ogg"))->SetVolume(30);//

	//sound = (new Sound("jump.wav"))->SetVolume(100);
	sound = (new Sound("marioJump.wav"))->SetVolume(30);
	deathSound = (new Sound("oof.wav"))->SetVolume(30);

#pragma endregion

#pragma region text init

	text = new Text("lucon.ttf", 24, game->GetDefaultTextShader());
	text->SetScale(1.0f)->SetColor(255, 255, 255)->SetPosition(0, game->GetSettings()->screenHeight - (text->GetFontSize() * text->GetScale()));

	text2 = new Text("lucon.ttf", 24, game->GetDefaultTextShader());//
	text2->SetScale(2.0f)->SetColor(255, 255, 255)->SetPosition(0, game->GetSettings()->screenHeight - (text2->GetFontSize() * text2->GetScale()));//

#pragma endregion

	debug = false;

}

void Engine::InGameScreen::Update()
{

	//// Set background
	//game->SetBackgroundColor(235, 229, 52);

	//// Time to spawn objects
	//if (spawnDuration >= maxSpawnTime) {
	//	SpawnObjects();
	//	spawnDuration = 0;
	//}
	//// Update all objects
	//for (Turtle* o : objects) {
	//	o->Update((game->GetGameTime()));
	//}
	//// Count spawn duration
	//spawnDuration += (game->GetGameTime());

	// Back to main menu
	if (game->GetInputManager()->IsKeyReleased("mainmenu")) {
		ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
		music->Stop();
	}

	//State when game is running
	if (gstate == GameState::RUNNING) {

		if (music->IsPlaying() == false)
		{
			music->Play(true);
			music->IsPlaying() == true;

		}

		if (game->GetInputManager()->IsKeyReleased("mainmenu")) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
			music->Stop();
			music2->Play(true);
		}

		sprite->Update(game->GetGameTime());
		sprite->PlayAnim("walk");

#pragma region score

		Uint32 currentTime = SDL_GetTicks();

		//debugging
		//std::cout << "Current time: " << currentTime << std::endl;

		// If 1000 milliseconds (1 second) have passed, increment the score
		if (currentTime - lastTime >= 1000) {
			score += 1;
			lastTime = currentTime;
		}

		// Update the score text display
		text->SetText("Score: " + std::to_string(score))
			->SetPosition(1450, 850);

#pragma endregion

#pragma region Movement


		// Move monster sprite using keyboard
		vec2 oldMonsterPos = sprite->GetPosition();
		float x = oldMonsterPos.x, y = oldMonsterPos.y;
		if (game->GetInputManager()->IsKeyPressed("Move Right")) {
			x += 0.5f * game->GetGameTime();
			sprite->PlayAnim("walk")->SetFlipHorizontal(false)->SetRotation(0);
		}
		if (game->GetInputManager()->IsKeyPressed("Move Left")) {
			x -= 0.5f * game->GetGameTime();
			sprite->PlayAnim("walk")->SetFlipHorizontal(false)->SetRotation(0);
		}
		if (game->GetInputManager()->IsKeyPressed("Move Up")) {
			y += 0.5f * game->GetGameTime();
			sprite->PlayAnim("walk")->SetFlipHorizontal(false)->SetRotation(0);
		}
		if (game->GetInputManager()->IsKeyPressed("Move Down")) {
			y -= 0.5f * game->GetGameTime();
			sprite->PlayAnim("walk")->SetFlipHorizontal(false)->SetRotation(0);
		}

		/*if (game->GetInputManager()->IsKeyPressed("Quit")) {
			game->GetState() = State::EXIT;
			return;
		}*/

		sprite->SetPosition(x, y);

		//Jump mechanic
		if (game->GetInputManager()->IsKeyPressed("Jump") && !jump) {
			//Set gravity and yVelocity
			float ratio = (game->GetGameTime() / 16.7f);
			//gravity = 0.16f * ratio;
			gravity = 0.075f * ratio;
			yVelocity = 1.8f;
			jump = true;
			sound->Play(false);
			sprite->PlayAnim("float");
		}

		//logic limit y to make the sprite holds it y value when jump button is held

		if (y > 198) {
			yVelocity -= gravity;
		}
		else if (y < 198) {
			jump = false;
			yVelocity = 0;
			y = 198;
		}


		y += yVelocity * game->GetGameTime();
		sprite->SetPosition(x, y);

		//jika posisi sprite di pinggir layar maka sprite tidak bisa melewati batas kiri layar
		if (x <= 0)
		{
			x = 0;
			sprite->SetPosition(x, y);
		}

#pragma endregion

#pragma region mousepos

#pragma endregion

#pragma region obstacle handling

		// when sprite hit an obstacle the sate switch to game over
		for (Sprite* s : platforms) {
			if (s->GetBoundingBox()->CollideWith(sprite->GetBoundingBox())) {
				
				deathSound->Play(false);
				deathSound->IsPlaying() == false;
				gstate = GameState::GAME_OVER;
				return;
			}
		}

		for (Sprite* s : platforms)
		{

			float x_ = s->GetPosition().x;
			float y_ = 198;
			float velocity;

			//every 10 seconds obstacle speeds up by 0.1f
			float baseVelocity = 0.7f; //nilai awal kecepatan
			float increment = 0.1f; // nilai untuk increment kecepatan tiap kelipatan 10 pada score

			//nilai untuk menetukan tiap kelipatan berapa nilai velocity bertambah
			int range = score / 10; //nilai integer = 0 jika menghasilkan nilai float

			velocity = baseVelocity + (range * increment);               
			//kecepatan = nilai awal kecepatan + (nilai score tiap kelipatan 10 * nilai increment)

			// Apply velocity changes
			x_ -= velocity * game->GetGameTime();
			
			// makes parallax speed based on velocity
			MoveLayer(front, velocity);
			
			//Debug
			std::cout << "Speed : " << velocity << std::endl;

			//versi panjang
			/*if (score >= 0 && score <= 10)
			{
				velocity = 0.7f;
				x_ -= velocity * game->getgametime();
				movelayer(front, velocity);
				std::cout << "speed : " << velocity << std::endl;
				//return;

			}

			if (score > 10 && score <= 20)
			{
				velocity = 0.8f;
				x_ -= velocity * game->getgametime();
				movelayer(front, velocity);
				std::cout << "speed : " << velocity << std::endl;
			}

			if (score > 20 && score <= 30)
			{
				velocity = 0.9f;
				x_ -= velocity * game->getgametime();
				movelayer(front, velocity);
				std::cout << "speed : " << velocity << std::endl;
			}

			if (score > 30)
			{
				velocity = 1.0f;
				x_ -= velocity * game->getgametime();
				movelayer(front, velocity);
				std::cout << "speed : " << velocity << std::endl;
			}*/

			
			s->SetFlipHorizontal(true)
				->SetPosition(x_, y_)->Update(game->GetGameTime());

			//Debug
			std::cout << "The Value of x_ is : " << std::endl;
			std::cout << to_string(x) << std::endl;


			//Relocate obstacle position when its out of viewport
			if (x_ <= -200)
			{
				s->SetPosition(2000, 198);
			}

		}

		if (debug) {
			//Shape for debug
			BoundingBox* bb = sprite->GetBoundingBox();
			dotSprite1->SetPosition(bb->GetVertices()[0].x - (0.5f * dotSprite1->GetScaleWidth()),
				bb->GetVertices()[0].y - (0.5f * dotSprite1->GetScaleHeight()));
			dotSprite2->SetPosition(bb->GetVertices()[1].x - (0.5f * dotSprite2->GetScaleWidth()),
				bb->GetVertices()[1].y - (0.5f * dotSprite2->GetScaleHeight()));
			dotSprite3->SetPosition(bb->GetVertices()[2].x - (0.5f * dotSprite3->GetScaleWidth()),
				bb->GetVertices()[2].y - (0.5f * dotSprite3->GetScaleHeight()));
			dotSprite4->SetPosition(bb->GetVertices()[3].x - (0.5f * dotSprite4->GetScaleWidth()),
				bb->GetVertices()[3].y - (0.5f * dotSprite3->GetScaleHeight()));
		}


#pragma endregion

		MoveLayer(backgrounds, 0.005f);
		MoveLayer(middlegrounds, 0.03f);
		MoveLayer(foregrounds, 0.5f);
		//MoveLayer(front, 0.7f);

	}
	else if (gstate == GameState::GAME_OVER) // state if player hits the obstacle
	{		
		//Stops the bg music
		music->Stop();
		music->IsPlaying() == false;

		//sets input manager for handling
		if (game->GetInputManager()->IsKeyReleased("mainmenu")) {
			music2->Play(true);
			ScreenManager::GetInstance(game)->SetCurrentScreen("mainmenu");
		}//

		//output text to inform that the character is dead
		text2->SetText("YOU DIED - Press J to Restart")->SetPosition(400, 500);

		//sets the parallax background speed to 0
		MoveLayer(backgrounds, 0.0f);
		MoveLayer(middlegrounds, 0.0f);
		MoveLayer(foregrounds, 0.0f);
		MoveLayer(front, 0.0f);

		//input manager if user press "J"
		if (game->GetInputManager()->IsKeyPressed("Reset")) {
			gstate = GameState::RESET;
		}

	}
	else if (gstate == GameState::RESET)//if user pressed J and decided to continue the game
	{
		//make sure to stop the music 
		music->Stop();
		music->IsPlaying() == false;

		//resets all variables involved
		restartGame();

		//play the bg music 
		music->Play(true);
		music->IsPlaying() == true;

		//sets the game state to running
		gstate = GameState::RUNNING;
	}


}

void Engine::InGameScreen::restartGame()
{
	sprite->SetPosition(50, 100);

	// Reset platform positions to their original state
	vec2 start = vec2(2000, 195);  // Starting position for platforms
	for (int i = 0; i < platforms.size(); i++) {
		platforms[i]->SetPosition(start.x + i * 1000, start.y + i);
	}

	//reset other game variables 
	score = 0;
	text2->SetText(" ")->SetPosition(400, 450);


	MoveLayer(backgrounds, 0.005f);
	MoveLayer(middlegrounds, 0.03f);
	MoveLayer(foregrounds, 0.5f);
	MoveLayer(front, 0.7f);
}

void Engine::InGameScreen::Draw()
{



	// Render all objects
	//for (Turtle* o : objects) {
	//	o->Draw();
	//}

	backgroundSprite->Draw();

	//DrawLayer(backgrounds);
	DrawLayer(middlegrounds);


	//DrawLayer(foregrounds);

	for (Sprite* s : platforms) {
		s->Draw();
	}

	sprite->Draw();


	if (debug) {
		dotSprite1->Draw();
		dotSprite2->Draw();
		dotSprite3->Draw();
		dotSprite4->Draw();
	}

	DrawLayer(front);

	text->Draw();
	text2->Draw();

}


#pragma region Parallax Functions

void Engine::InGameScreen::MoveLayer(vector<Sprite*>& bg, float speed)
{
	for (Sprite* s5 : bg) {
		if (s5->GetPosition().x < -game->GetSettings()->screenWidth + offset) {
			s5->SetPosition(game->GetSettings()->screenWidth + offset - 1, 0);
		}
		s5->SetPosition(s5->GetPosition().x - speed * game->GetGameTime(), s5->GetPosition().y);
		s5->Update(game->GetGameTime());
	}
}

void Engine::InGameScreen::DrawLayer(vector<Sprite*>& bg)
{
	for (Sprite* s5 : bg) {
		s5->Draw();
	}
}

void Engine::InGameScreen::AddToLayer(vector<Sprite*>& bg, string name)
{
	Texture* Ptexture = new Texture(name);

	Sprite* s5 = new Sprite(Ptexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	s5->SetSize(game->GetSettings()->screenWidth + offset, game->GetSettings()->screenHeight);
	bg.push_back(s5);

	Sprite* s2 = new Sprite(Ptexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad());
	s2->SetSize(game->GetSettings()->screenWidth + offset, game->GetSettings()->screenHeight)->SetPosition(game->GetSettings()->screenWidth + offset - 1, 0);
	bg.push_back(s2);
}

#pragma endregion



//not currently in use

//Engine::Sprite* Engine::InGameScreen::CreateSprite(Texture* texture)
//{
//#pragma region dont touch
//
//	return (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
//		->SetNumXFrames(14)
//		->SetNumYFrames(4)
//		->AddAnimation("hit", 2, 4)
//		->AddAnimation("spikes", 5, 12)
//		->AddAnimation("idle-1", 14, 27)
//		->AddAnimation("idle-2", 28, 41)
//		->AddAnimation("spikes-out", 42, 49)
//		->PlayAnim("spikes")
//		->SetScale(1.5)
//		->SetAnimationDuration(100);
//
//#pragma endregion 
//	//return 0;
//
//}

//not currently in use
void Engine::InGameScreen::SpawnObjects()
{
	//Find Die object to reuse for spawning
	//int spawnCount = 0;
	//for (Turtle* o : objects) {
	//	if (spawnCount == numObjectPerSpawn) {
	//		break;
	//	}
	//	if (o->IsDie()) {
	//		// Set state to spawn
	//		
	//		// Random spawn position
	//		int min = 0;
	//		int max = (int) (game->GetSettings()->screenWidth - o->GetWidth());
	//		float x = (float) (rand() % (max - min + 1) + min);
	//		float y = game->GetSettings()->screenHeight + o->GetHeight();
	//		o->SetSpawn()->SetPosition(x, y);
	//		spawnCount++;
	//	}
	//}
}

