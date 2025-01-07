#include "Assert.hpp"

#include <iostream>

namespace Assert
{
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

		std::abort();
	}
}
