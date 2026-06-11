#include "Time.hpp"

f64 RiseEngine::Time::s_deltaTime_ = 0.0;
f64 RiseEngine::Time::s_totalTime_ = 0.0;
uint64 RiseEngine::Time::s_frameCount_ = 0;
std::chrono::steady_clock::time_point RiseEngine::Time::s_lastFrame_ = std::chrono::steady_clock::now();
std::chrono::steady_clock::time_point RiseEngine::Time::s_startTime_ = std::chrono::steady_clock::now();

void RiseEngine::Time::Update()
{
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<f64> elapsed = now - s_lastFrame_;
	s_lastFrame_ = now;
	s_deltaTime_ = elapsed.count();
	s_totalTime_ += s_deltaTime_;
	s_frameCount_++;
}

f64 RiseEngine::Time::GetTimeSinceStart()
{
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<f64> elapsed = now - s_startTime_;
	return elapsed.count();
}
