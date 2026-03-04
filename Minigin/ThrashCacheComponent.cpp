#include "ThrashCacheComponent.h"
#include <chrono>
#include <imgui.h>
#include <implot.h>

dae::ThrashCacheComponent::ThrashCacheComponent(GameObject* pOwner)
	: Component(pOwner)
{
}

void dae::ThrashCacheComponent::RenderUI()
{
	RenderExercise1();
	RenderExercise2();
}

#pragma region RenderExercises
void dae::ThrashCacheComponent::RenderExercise1()
{
	ImGui::Begin("Exercise 1");

	ImGui::InputInt("##samples1", &m_samplesExercise1);
	ImGui::SameLine();
	ImGui::Text("# samples");

	if (ImGui::Button("Thrash the cache"))
	{
		m_plotDataExercise1 = ThrashCache(m_samplesExercise1);
	}

	if (!m_plotDataExercise1.empty())
	{
		float maxValue = *std::max_element(m_plotDataExercise1.begin(), m_plotDataExercise1.end()) * 1.1f;

		if (ImPlot::BeginPlot("Exercise 1", ImVec2(300, 150), ImPlotFlags_NoLegend | ImPlotFlags_NoMouseText))
		{
			ImPlot::SetupAxisTicks(ImAxis_X1, STEP_INDICES_HALF, 6, STEP_LABELS_HALF);
			ImPlot::SetupAxisLimits(ImAxis_Y1, 0, maxValue, ImPlotCond_Always);

			ImPlot::SetNextLineStyle(ImColor(213, 99, 14), 2.0f);
			ImPlot::PlotLine("##ThrashData", m_plotDataExercise1.data(), (int)m_plotDataExercise1.size());

			double verticalLine = 4;
			ImPlot::SetNextLineStyle(ImVec4(1, 0, 0, 1), 1.0f);
			ImPlot::PlotInfLines("Vertical Line", &verticalLine, 1);

			if (ImPlot::IsPlotHovered())
			{
				ImPlotPoint mouse = ImPlot::GetPlotMousePos();

				int idx = (int)round(mouse.x);

				if (idx >= 0 && idx < (int)m_plotDataExercise1.size())
				{
					float xVal = (float)STEP_INDICES[idx];
					float yVal = m_plotDataExercise1[idx];

					ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4.0f, ImColor(255, 100, 100), -1.0f, ImColor(255, 100, 100));
					ImPlot::PlotScatter("##hover_dot", &xVal, &yVal, 1);

					ImGui::BeginTooltip();
					ImGui::Text("x=%s, y=%.2f", STEP_LABELS[idx], yVal);
					ImGui::EndTooltip();
				}
			}

			ImPlot::EndPlot();
		}
	}

	ImGui::End();
}

void dae::ThrashCacheComponent::RenderExercise2()
{
	ImGui::Begin("Exercise 2");

	ImGui::InputInt("##samples2", &m_samplesExercise2);
	ImGui::SameLine();
	ImGui::Text("# samples");

	RenderExercise2Base();
	RenderExercise2Alt();
	RenderExercise2Combined();

	ImGui::End();
}
void dae::ThrashCacheComponent::RenderExercise2Base()
{
	if (ImGui::Button("Thrash the cache with GameObject3D"))
	{
		m_plotDataExercise2 = ThrashCacheGameObject<GameObjectBase>(m_samplesExercise2);
	}

	if (!m_plotDataExercise2.empty())
	{
		float maxValue = *std::max_element(m_plotDataExercise2.begin(), m_plotDataExercise2.end()) * 1.1f;

		if (ImPlot::BeginPlot("Exercise 2", ImVec2(300, 150), ImPlotFlags_NoLegend | ImPlotFlags_NoMouseText))
		{
			ImPlot::SetupAxisTicks(ImAxis_X1, STEP_INDICES_HALF, 6, STEP_LABELS_HALF);
			ImPlot::SetupAxisLimits(ImAxis_Y1, 0, maxValue, ImPlotCond_Always);

			ImPlot::SetNextLineStyle(ImColor(51, 179, 87), 2.0f);
			ImPlot::PlotLine("##ThrashData", m_plotDataExercise2.data(), (int)m_plotDataExercise2.size());

			if (ImPlot::IsPlotHovered())
			{
				ImPlotPoint mouse = ImPlot::GetPlotMousePos();

				int idx = (int)round(mouse.x);

				if (idx >= 0 && idx < (int)m_plotDataExercise2.size())
				{
					float xVal = (float)STEP_INDICES[idx];
					float yVal = m_plotDataExercise2[idx];

					ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4.0f, ImColor(255, 100, 100), -1.0f, ImColor(255, 100, 100));
					ImPlot::PlotScatter("##hover_dot", &xVal, &yVal, 1);

					ImGui::BeginTooltip();
					ImGui::Text("x=%s, y=%.2f", STEP_LABELS[idx], yVal);
					ImGui::EndTooltip();
				}
			}

			ImPlot::EndPlot();
		}
	}
}
void dae::ThrashCacheComponent::RenderExercise2Alt()
{
	if (ImGui::Button("Thrash the cache with GameObject3DAlt"))
	{
		m_plotDataExercise2Alt = ThrashCacheGameObject<GameObjectAlt>(m_samplesExercise2);
	}

	if (!m_plotDataExercise2Alt.empty())
	{
		float maxValue = *std::max_element(m_plotDataExercise2Alt.begin(), m_plotDataExercise2Alt.end()) * 1.1f;

		if (ImPlot::BeginPlot("Exercise 2 Alt", ImVec2(300, 150), ImPlotFlags_NoLegend | ImPlotFlags_NoMouseText))
		{
			ImPlot::SetupAxisTicks(ImAxis_X1, STEP_INDICES_HALF, 6, STEP_LABELS_HALF);
			ImPlot::SetupAxisLimits(ImAxis_Y1, 0, maxValue, ImPlotCond_Always);

			ImPlot::SetNextLineStyle(ImColor(66, 150, 250), 2.0f);
			ImPlot::PlotLine("##ThrashData", m_plotDataExercise2Alt.data(), (int)m_plotDataExercise2Alt.size());

			if (ImPlot::IsPlotHovered())
			{
				ImPlotPoint mouse = ImPlot::GetPlotMousePos();

				int idx = (int)round(mouse.x);

				if (idx >= 0 && idx < (int)m_plotDataExercise2Alt.size())
				{
					float xVal = (float)STEP_INDICES[idx];
					float yVal = m_plotDataExercise2Alt[idx];

					ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4.0f, ImColor(255, 100, 100), -1.0f, ImColor(255, 100, 100));
					ImPlot::PlotScatter("##hover_dot", &xVal, &yVal, 1);

					ImGui::BeginTooltip();
					ImGui::Text("x=%s, y=%.2f", STEP_LABELS[idx], yVal);
					ImGui::EndTooltip();
				}
			}

			ImPlot::EndPlot();
		}
	}
}
void dae::ThrashCacheComponent::RenderExercise2Combined()
{
	if (!m_plotDataExercise2.empty() && !m_plotDataExercise2Alt.empty())
	{
		ImGui::Text("Combined:");

		float maxValue = *std::max_element(m_plotDataExercise2.begin(), m_plotDataExercise2.end()) * 1.1f;

		if (ImPlot::BeginPlot("Exercise 2 Combined", ImVec2(300, 150), ImPlotFlags_NoLegend | ImPlotFlags_NoMouseText))
		{
			ImPlot::SetupAxisTicks(ImAxis_X1, STEP_INDICES_HALF, 6, STEP_LABELS_HALF);
			ImPlot::SetupAxisLimits(ImAxis_Y1, 0, maxValue, ImPlotCond_Always);

			ImPlot::SetNextLineStyle(ImColor(51, 179, 87), 2.0f);
			ImPlot::PlotLine("##ThrashData", m_plotDataExercise2.data(), (int)m_plotDataExercise2.size());

			ImPlot::SetNextLineStyle(ImColor(66, 150, 250), 2.0f);
			ImPlot::PlotLine("##ThrashData", m_plotDataExercise2Alt.data(), (int)m_plotDataExercise2Alt.size());

			if (ImPlot::IsPlotHovered())
			{
				ImPlotPoint mouse = ImPlot::GetPlotMousePos();

				int idx = (int)round(mouse.x);

				if (idx >= 0 && idx < (int)m_plotDataExercise2Alt.size())
				{
					float xVal = (float)STEP_INDICES[idx];
					float yVal = m_plotDataExercise2Alt[idx];

					ImPlot::SetNextMarkerStyle(ImPlotMarker_Circle, 4.0f, ImColor(255, 100, 100), -1.0f, ImColor(255, 100, 100));
					ImPlot::PlotScatter("##hover_dot", &xVal, &yVal, 1);

					ImGui::BeginTooltip();
					ImGui::Text("x=%s, y=%.2f", STEP_LABELS[idx], yVal);
					ImGui::EndTooltip();
				}
			}

			ImPlot::EndPlot();
		}
	}
}
#pragma endregion

#pragma region ThrashCache
std::vector<float> dae::ThrashCacheComponent::ThrashCache(int samples) const
{
	const int numSteps = 11;
	std::vector<float> averagedResults(numSteps, 0.0f);

	const int bufferSize = 30'000'000;
	std::vector<int> buffer(bufferSize, 1);

	for (int s = 0; s < samples; ++s)
	{
		int stepIdx = 0;
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			const auto start = std::chrono::high_resolution_clock::now();

			for (int index = 0; index < bufferSize; index += stepsize)
			{
				buffer[index] *= 2;
			}

			const auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			averagedResults[stepIdx] += static_cast<float>(elapsedTime);
			++stepIdx;
		}
	}

	for (float& result : averagedResults)
	{
		result /= static_cast<float>(samples);
	}

	return averagedResults;
}

template<typename T>
std::vector<float> dae::ThrashCacheComponent::ThrashCacheGameObject(int samples) const
{
	const int numSteps = 11;
	std::vector<float> averagedResults(numSteps, 0.0f);

	const int bufferSize = 30'000'000;
	std::vector<T> buffer(bufferSize);

	for (int s = 0; s < samples; ++s)
	{
		int stepIdx = 0;
		for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
		{
			const auto start = std::chrono::high_resolution_clock::now();

			for (int index = 0; index < bufferSize; index += stepsize)
			{
				buffer[index].id *= 2;
			}

			const auto end = std::chrono::high_resolution_clock::now();
			const auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

			averagedResults[stepIdx] += static_cast<float>(elapsedTime);
			++stepIdx;
		}
	}

	for (float& result : averagedResults)
	{
		result /= static_cast<float>(samples);
	}

	return averagedResults;
}
#pragma endregion