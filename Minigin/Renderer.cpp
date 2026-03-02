#include <stdexcept>
#include <cstring>
#include <iostream>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include <imgui.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <chrono>
#include <implot.h>

int dae::Renderer::m_samplesExercise1 = 10;
int dae::Renderer::m_samplesExercise2 = 100;
std::vector<float> dae::Renderer::m_plotDataExercise1{};

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;

	SDL_SetHint(SDL_HINT_RENDER_VSYNC, "1");

#if defined(__EMSCRIPTEN__)
	m_renderer = SDL_CreateRenderer(window, nullptr);
#else
	m_renderer = SDL_CreateRenderer(window, nullptr);
#endif

	if (m_renderer == nullptr)
	{
		std::cout << "Failed to create the renderer: " << SDL_GetError() << "\n";
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImPlot::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
#if __EMSCRIPTEN__
	// For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
	// You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
	io.IniFilename = NULL;
#endif

	ImGui_ImplSDL3_InitForSDLRenderer(window, m_renderer);
	ImGui_ImplSDLRenderer3_Init(m_renderer);
}

void dae::Renderer::Render() const
{
	ImGui_ImplSDLRenderer3_NewFrame();
	ImGui_ImplSDL3_NewFrame();
	ImGui::NewFrame();

	//ImGui::ShowDemoWindow(); // For demonstration purposes, do not keep this in your engine

	// Exercise 1
	ImGui::Begin("Exercise 1");

	ImGui::InputInt("##samples1", &m_samplesExercise1);
	ImGui::SameLine();
	ImGui::Text("# samples");

	if (ImGui::Button("Thrash the cache"))
	{
		m_plotDataExercise1 = ThrashCache();
	}

	if (!m_plotDataExercise1.empty())
	{
		float maxValue = *std::max_element(m_plotDataExercise1.begin(), m_plotDataExercise1.end()) * 1.1f;

		if (ImPlot::BeginPlot("Exercise 1", ImVec2(300, 150), ImPlotFlags_NoLegend | ImPlotFlags_NoMouseText))
		{
			const char* stepLabels[] = { "1", "4", "16", "64", "256", "1024" };
			double stepIndices[] = { 0, 2, 4, 6, 8, 10 };
			const char* stepLabelsFull[] = { "1", "2", "4", "8", "16", "32", "64", "128", "256", "512", "1024" };
			double stepIndicesFull[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

			ImPlot::SetupAxisTicks(ImAxis_X1, stepIndices, 6, stepLabels);

			ImPlot::SetupAxisLimits(ImAxis_Y1, 0, maxValue, ImPlotCond_Always);

			ImPlot::SetNextLineStyle(IMPLOT_AUTO_COL, 2.0f);

			ImPlot::PlotLine("##ThrashData", m_plotDataExercise1.data(), (int)m_plotDataExercise1.size());

			if (ImPlot::IsPlotHovered())
			{
				ImPlotPoint mouse = ImPlot::GetPlotMousePos();

				int idx = (int)round(mouse.x);

				if (idx >= 0 && idx < (int)m_plotDataExercise1.size())
				{
					float xVal = (float)stepIndicesFull[idx];
					float yVal = m_plotDataExercise1[idx];

					ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4.0f, ImColor(255, 100, 100), -1.0f, ImColor(255, 100, 100));
					ImPlot::PlotScatter("##hover_dot", &xVal, &yVal, 1);

					ImGui::BeginTooltip();
					ImGui::Text("x=%s, y=%.2f", stepLabelsFull[idx], yVal);
					ImGui::EndTooltip();
				}
			}

			ImPlot::EndPlot();
		}
	}

	ImGui::End();

	// Exercise 2
	ImGui::Begin("Exercise 2");

	ImGui::InputInt("##samples1", &m_samplesExercise1);
	ImGui::SameLine();
	ImGui::Text("# samples");

	ImGui::Button("Thrash the cache with GameObject3D");

	ImGui::Button("Thrash the cache with GameObject3DAlt");


	ImGui::End();

	ImGui::Render();
	
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), m_renderer);
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
	ImPlot::DestroyContext();

	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_FRect dst{};
	dst.x = x;
	dst.y = y;
	SDL_GetTextureSize(texture.GetSDLTexture(), &dst.w, &dst.h);
	SDL_RenderTexture(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_FRect dst{};
	dst.x = x;
	dst.y = y;
	dst.w = width;
	dst.h = height;
	SDL_RenderTexture(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }

std::vector<float> dae::Renderer::ThrashCache()
{
	std::vector<float> results{};
	results.reserve(11);

	const int bufferSize = 100'000'000;
	std::vector<int> buffer{};
	buffer.resize(bufferSize);

	int stepsize = 1;
	for (stepsize = 1; stepsize <= 1024; stepsize *= 2)
	{
		const auto start = std::chrono::high_resolution_clock::now();

		for (int index = 0; index < buffer.size(); index += stepsize)
		{
			buffer[index] *= 2;
		}

		const auto end = std::chrono::high_resolution_clock::now();
		const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

		results.emplace_back((float)elapsedTime);
	}

	return results;
}
