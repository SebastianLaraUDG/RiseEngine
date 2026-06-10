#pragma once

namespace RiseEngine
{
	/*
	* Global time management.
	* Static.
	*/
	class Time
	{
	public:
		static void Update();

		static f32 GetDeltaTime() { return static_cast<f32>(s_deltaTime_); }
		static f64 GetExactDeltaTime() { return s_deltaTime_; }
		static uint64 GetFrameCount() { return s_frameCount_; }
		static f64 GetTimeSinceStart();

	private:
		Time() = delete; // Singleton.
		
		static f64 s_deltaTime_;
		static f64 s_totalTime_;
		static uint64 s_frameCount_;
		static std::chrono::steady_clock::time_point s_lastFrame_;
		static std::chrono::steady_clock::time_point s_startTime_;// = std::chrono::steady_clock::now();
	};
}