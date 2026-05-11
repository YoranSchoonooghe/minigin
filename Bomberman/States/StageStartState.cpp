#include "StageStartState.h"
#include "PlayState.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "Components/RenderComponent.h"
#include "ResourceManager.h"
#include <string>
#include "Components//TimerComponent.h"
#include "GameManager.h"
#include "Audio/ServiceLocator.h"

dae::StageStartState::StageStartState(int stageNumber)
	: m_stageNumber{ stageNumber }
{
}

dae::StageStartState::~StageStartState()
{
	if (m_pTimerComponentSubject)
	{
		m_pTimerComponentSubject->RemoveObserver(this);
	}
}

void dae::StageStartState::Enter()
{
	LoadScene();
}

void dae::StageStartState::Exit()
{
}

void dae::StageStartState::Notify(const Event& event, GameObject*)
{
	switch (event.id)
	{
	case make_sdbm_hash("OnTimerFinished"):
		GameManager::GetInstance().Play();
		break;
	case make_sdbm_hash("OnSubjectDestroyed"):
		m_pTimerComponentSubject = nullptr;
		break;
	}
}

void dae::StageStartState::LoadScene()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene();

	dae::Renderer::GetInstance().SetBackgroundColor({ 0, 0, 0, 255 });

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);

	auto pStageLabel = std::make_unique<dae::GameObject>("StageLabel");
	pStageLabel->AddComponent<dae::RenderComponent>("", true);
	pStageLabel->AddComponent<dae::TextComponent>("STAGE " + std::to_string(m_stageNumber), font);
	pStageLabel->SetLocalPosition(200, 500);
	scene.Add(std::move(pStageLabel));

	auto pTimer = std::make_unique<dae::GameObject>("Timer");
	auto pTimerComponent = pTimer->AddComponent<dae::TimerComponent>(m_timeToStart);
	m_pTimerComponentSubject = pTimerComponent->GetTimerSubject();
	m_pTimerComponentSubject->AddObserver(this);
	pTimerComponent->Start();
	scene.Add(std::move(pTimer));

	dae::ServiceLocator::GetSoundSystem().AddAudioSource(dae::AudioSource(0, "Audio/StageStart.wav"));
	dae::ServiceLocator::GetSoundSystem().Play(0);
}
