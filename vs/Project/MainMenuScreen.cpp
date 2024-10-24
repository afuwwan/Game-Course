#include "MainMenuScreen.h"

Engine::MainMenuScreen::MainMenuScreen()
{
	text = NULL;
}

void Engine::MainMenuScreen::Init()
{
	
	Texture* bgTexture = new Texture("senja.png");//
	backgroundSprite = (new Sprite(bgTexture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))->SetSize((float)game->GetSettings()->screenWidth, (float)game->GetSettings()->screenHeight);//

	
	// Create a Texture
	Texture* texture = new Texture("buttons.png");

	// Create Sprites
	Sprite* playSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(6)
		->SetNumYFrames(1)
		->AddAnimation("normal", 5, 5)
		->AddAnimation("hover", 3, 4)
		->AddAnimation("press", 3, 4)
		->SetAnimationDuration(400);

	Sprite* exitSprite = (new Sprite(texture, game->GetDefaultSpriteShader(), game->GetDefaultQuad()))
		->SetNumXFrames(6)
		->SetNumYFrames(1)
		->AddAnimation("normal", 2, 2)
		->AddAnimation("hover", 0, 1)
		->AddAnimation("press", 0, 1)
		->SetAnimationDuration(400);

	//Create Buttons
	Button* playButton = new Button(playSprite, "play");
	playButton->SetPosition((game->GetSettings()->screenWidth / 2) - (playSprite->GetScaleWidth() / 2),
		400);
	buttons.push_back(playButton);

	Button* exitButton = new Button(exitSprite, "exit");
	exitButton->SetPosition((game->GetSettings()->screenWidth / 2) - (exitSprite->GetScaleWidth() / 2),
		250);
	buttons.push_back(exitButton);

	// Set play button into active button
	currentButtonIndex = 0;
	buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);

	// Create Text
	text = (new Text("8-bit Arcade In.ttf", 100, game->GetDefaultTextShader()))
		->SetText("DUCK ON A CART")->SetPosition(game->GetSettings()->screenWidth * 0.5f - 300, game->GetSettings()->screenHeight - 100.0f)->SetColor(255, 255, 255);

	// Add input mappings
	game->GetInputManager()->AddInputMapping("next", SDLK_DOWN)
		->AddInputMapping("prev", SDLK_UP)
		->AddInputMapping("press", SDLK_RETURN);

	//SDL_CONTROLLER

	//music = (new Music("Rosolanc.ogg"))->SetVolume(70)->Stop();
	music2 = (new Music("2021-08-16_-_8_Bit_Adventure_-_www.FesliyanStudios.com.ogg"))->SetVolume(30)->Play(true);


}


void Engine::MainMenuScreen::Update()
{
	
	//music->Stop();
	//music2->Play(true);

	//if (music2->IsPlaying() == false)
	//{
	//	music2->Play(true);
	//	//music2->IsPlaying() == true;

	//}

	// Set background
	game->SetBackgroundColor(52, 155, 235);

	//Debug
	if (music2->IsPlaying() == true)
	{
		std::cout << "music 2 is playing" << std::endl;
	}
	else if (music2->IsPlaying() == false)
	{
		std::cout << "music 2 is not playing" << std::endl;
	}

	//Button States
	if (game->GetInputManager()->IsKeyReleased("next")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Next Button
		currentButtonIndex = (currentButtonIndex < (int)buttons.size() - 1) ? currentButtonIndex + 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->GetInputManager()->IsKeyReleased("prev")) {
		// Set previous button to normal state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::NORMAL);
		// Prev Button
		currentButtonIndex = currentButtonIndex > 0 ? currentButtonIndex - 1 : currentButtonIndex;
		// Set current button to hover state
		buttons[currentButtonIndex]->SetButtonState(Engine::ButtonState::HOVER);
	}

	if (game->GetInputManager()->IsKeyReleased("press")) {
		// Set current button to press state
		Button* b = buttons[currentButtonIndex];
		b->SetButtonState(Engine::ButtonState::PRESS);
		// If play button then go to InGame, exit button then exit
		if ("play" == b->GetButtonName()) {
			ScreenManager::GetInstance(game)->SetCurrentScreen("ingame");
			music2->Stop();
		}
		else if ("exit" == b->GetButtonName()) {
			game->SetState(Engine::State::EXIT);
		}
	}

	// Update All buttons
	for (Button* b : buttons) {
		b->Update(game->GetGameTime());
	}

}

void Engine::MainMenuScreen::Draw()
{
	
	backgroundSprite->Draw();
	
	// Render all buttons
	for (Button* b : buttons) {
		b->Draw();
	}
	// Render title 
	text->Draw();
}
