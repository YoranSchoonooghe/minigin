#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "GameManager.h"
#include "Renderer.h"


#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	SDL_SetRenderDrawBlendMode(dae::Renderer::GetInstance().GetSDLRenderer(), SDL_BLENDMODE_BLEND);
	dae::GameManager::GetInstance().Init();
}

int main(int, char* []) {
#if __EMSCRIPTEN__
	fs::path data_location = "";
#else
	fs::path data_location = "./Data/";
	if (!fs::exists(data_location))
		data_location = "../Data/";
#endif
	dae::Minigin engine(data_location);
	engine.Run(load);
	return 0;
}
