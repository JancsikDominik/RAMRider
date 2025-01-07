#ifndef __CUSTOM_ASSERT_HPP__
#define __CUSTOM_ASSERT_HPP__

#include "Compiler.hpp"

#include <string>
#include <optional>

#if !defined(__PRETTY_FUNCTION__) && !defined(__GNUC__)
#define __PRETTY_FUNCTION__ __FUNCSIG__
#endif
#define STR(x) #x
#define EXPRESSION_TO_STRING(x) std::string("(") + #x + std::string(")")


namespace Assert
{
	enum class AssertType
	{
		Precond, Assert, Unreachable
	};

	void AssertionFailed(AssertType type,  const std::string& expr, const std::string& func, const std::string& file, int line, std::optional<std::string> msg = std::nullopt);
}

// Stripping the asserts from production
#ifdef __PROD__
	#define ASSERT(x, ...) ;
	#define UNREACHABLE(...) ;
	#define PRECOND(expr, ...) ;
	#define ASSERT_FAILED(...) ;
	#define DBBREAK() ;

#else

#ifdef ASSERT
	#undef ASSERT
#endif
	#define ASSERT(expr, ...)																																		\
		do {																																						\
			if (!(expr))	{																																		\
				Assert::AssertionFailed(Assert::AssertType::Assert, EXPRESSION_TO_STRING(expr), __PRETTY_FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__);			\
			}																																						\
		} while (0)

	#define UNREACHABLE(...) { Assert::AssertionFailed(Assert::AssertType::Unreachable, "", __PRETTY_FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__); }

	#define PRECOND(expr, ...) 																																		\
		do {																																						\
			if (!(expr)) { 																																			\
				 Assert::AssertionFailed(Assert::AssertType::Precond, EXPRESSION_TO_STRING(expr), __PRETTY_FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__);			\
			} 																																						\
		} while (0)

	#define ASSERT_FAILED(...) { Assert::AssertionFailed(Assert::AssertType::Assert, "", __PRETTY_FUNCTION__, __FILE__, __LINE__, ##__VA_ARGS__); }

	#define DBBREAK() COMPILER_DEBUG_BREAK()

#endif // __PROD__

#endif // __CUSTOM_ASSERT_HPP__
