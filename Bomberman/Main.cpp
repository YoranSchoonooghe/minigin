#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#if _DEBUG && __has_include(<vld.h>)
#include <vld.h>
#endif

#include "Minigin.h"
#include "States/GameStateMachine.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "TextComponent.h"
#include "Components/FPSComponent.h"
#include "Components/RenderComponent.h"
#include "Components/AnimatedSpriteComponent.h"
#include "Commands/MoveCommand.h"
#include "Components/CharacterControllerComponent.h"
#include "Components/HealthComponent.h"
#include "Components/HealthDisplayComponent.h"
#include "Commands/DamageCommand.h"
#include "Components/ScoreComponent.h"
#include "Components/ScoreDisplayComponent.h"
#include "Commands/ScoreCommand.h"
#include "Renderer.h"
#include "Components/TimerComponent.h"
#include "Components/TimerDisplayComponent.h"
#include "Components/BoxColliderComponent.h"
#include "Commands/DropBombCommand.h"
#include "Components/AnimationControllerComponent.h"
#include "Components/CameraComponent.h"
#include "Components/PowerUpComponent.h"
#include "Components/BombermanComponent.h"
#include "Components/EnemyBehaviourComponent.h"
#include "Audio/ServiceLocator.h"
#include "Audio/SDLSoundSystem.h"

#include <filesystem>
namespace fs = std::filesystem;

static void load()
{
	dae::GameStateMachine::GetInstance().Init();
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
