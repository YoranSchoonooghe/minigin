#pragma once

namespace dae
{
	class Properties final
	{
	public:
		explicit Properties();
		~Properties() = default;
		Properties(const Properties& other) = delete;
		Properties(Properties&& other) = delete;
		Properties& operator=(const Properties& other) = delete;
		Properties& operator=(Properties&& other) = delete;

		void RenderUI();

	private:
		void RenderTransformProperties();
	};
}