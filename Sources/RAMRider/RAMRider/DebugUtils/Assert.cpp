#include "Assert.hpp"

#include <iostream>

enum class BuildType
{
	Production, Release, Debug
};

#if defined(__PROD__)
	static constexpr BuildType build = BuildType::Production;
#elif defined(__RELEASE__)
	static constexpr BuildType build = BuildType::Release;
#elif defined(__DEBUG__)
	static constexpr BuildType build = BuildType::Debug;
#else
	#error "Build type not defined"
#endif

namespace Assert
{
	constexpr bool DieOnAssert = build == BuildType::Release;

	void AssertionFailed(AssertType type, const std::string& expr, const std::string& func, const std::string& file, int line, std::optional<std::string> msg)
	{
		std::string assertFailed;
		std::string message = msg.has_value() ? *msg : "";

		switch (type)
		{
		case AssertType::Assert:
			assertFailed = "Assertion failed ";
			break;
		case AssertType::Precond:
			assertFailed = "Precondition failed ";
			break;
		case AssertType::Unreachable:
			assertFailed = "Unreachable code reached ";
		}

		std::string fullMessage = assertFailed + expr + ": " + message
								  +"\nFunction: " + func
								  + "\nFile: " + file
								  + "\nLine: " + std::to_string(line);

		// TODO: file logger, gui message box
		std::cerr << fullMessage << std::endl;

		DBBREAK();
		
		if constexpr (DieOnAssert)
			std::abort();
	}
}
