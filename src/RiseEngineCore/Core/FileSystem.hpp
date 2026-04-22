#pragma once
#include <filesystem>
#include <string>

class FileSystem
{
public:
	// Helper: std::filesystem::path(__FILE__).parent_path().parent_path()
	inline static void SetEngineRoot(const std::filesystem::path& path)
	{
		engineRoot_ = path;
	}

	// Helper: std::filesystem::current_path().
	inline static void SetGameRoot(const std::filesystem::path& path)
	{
		gameRoot_ = path;
	}

	// @param path - Remember to start with "engine://" or "game://" .
	// @return The absolute location of the given asset depending on engine or game folders.
	// If the path does not contain one of these prefix, returns path.
	static std::filesystem::path Resolve(std::string_view path)
	{
		// What this basically does is generate a string starting with the engine
		// location then appends the supplied path removing the engine/game prefix.

		if (path.starts_with(ENGINE_PREFIX))
		{
			return engineRoot_ / path.substr(ENGINE_PREFIX.length());
		}
		if (path.starts_with(GAME_PREFIX))
		{
			return gameRoot_ / path.substr(GAME_PREFIX.length());
		}
		return path; // Fallback.
	}

private:
	static constexpr std::string_view ENGINE_PREFIX = "engine://";
	static constexpr std::string_view GAME_PREFIX = "game://";
	
private:
	static inline std::filesystem::path engineRoot_;
	static inline std::filesystem::path gameRoot_;
};

