#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "RenderComponent.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	auto pBackground = std::make_unique<dae::GameObject>();
	pBackground->AddComponent<dae::RenderComponent>("background.png");
	scene.Add(std::move(pBackground));

	auto pLogo = std::make_unique<dae::GameObject>();
	pLogo->AddComponent<dae::RenderComponent>("logo.png");
	pLogo->SetPosition(358, 180);
	scene.Add(std::move(pLogo));

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto pTitle = std::make_unique<dae::GameObject>();
	pTitle->AddComponent<dae::TextComponent>("Programming 4 Assignment", font);
	pTitle->SetPosition(292, 20);
	scene.Add(std::move(pTitle));

	auto pFPSCounter = std::make_unique<dae::GameObject>();
	pFPSCounter->AddComponent<dae::TextComponent>("60.0 FPS", font);
	pFPSCounter->AddComponent<dae::FPSComponent>();
	pFPSCounter->SetPosition(10, 10);
	scene.Add(std::move(pFPSCounter));
}

int main(int, char*[]) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if(!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
    return 0;
}
