#include "DinoReal.h"

Engine::DinoReal::DinoReal(Setting* setting) :Engine::Game(setting)
{
	setting->windowTitle = "DinoReal-Game";
}

Engine::DinoReal::~DinoReal()
{

}

void Engine::DinoReal::Init()
{

	//music = (new Music("Rosolanc.ogg"))->SetVolume(70)->Play(true);

	inputManager/*->AddInputMapping("next", SDLK_s)
		->AddInputMapping("prev", SDLK_w)*/
		->AddInputMapping("prev", SDLK_UP)
		->AddInputMapping("next", SDLK_DOWN)
		->AddInputMapping("press", SDLK_RETURN);
	/*->AddInputMapping("press", SDLK_k);*/ //remove input mapping

	Engine::ScreenManager::GetInstance(this)->AddScreen("ingame", new InGameScreen())
		->AddScreen("mainmenu", new MainMenuScreen())
		->SetCurrentScreen("mainmenu");

}

void Engine::DinoReal::Update()
{
	Engine::ScreenManager::GetInstance(this)->Update();

}



void Engine::DinoReal::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();


}
