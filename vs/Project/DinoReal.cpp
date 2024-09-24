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

	//auto currentScreen = Engine::ScreenManager::GetInstance(this)->GetCurrentScreen();

	//0B4A77D0 mainmenu
	//0B108098 ingame

	//auto currentScreen = Engine::ScreenManager::GetInstance(this)->GetCurrentScreen();
	/*if (currentScreen && currentScreen->GetName() == "mainmenu") {
		music->Stop();
	}*/

	//if (currentScreen && "mainmenu")
	//{
	//	//introMusic->Play(true);
	//	music->Stop();
	//}	
	//if (currentScreen && "ingame")
	//{
	//	//introMusic->Stop();
	//	music->Play(true);
	//}

	//if (Engine::ScreenManager::GetInstance(this)->SetCurrentScreen("ingame"))
	//{
	//	//introMusic->Stop();
	//	music->Play(true);
	//}

}



void Engine::DinoReal::Render()
{
	Engine::ScreenManager::GetInstance(this)->Draw();


}
