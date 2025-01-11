#ifndef TESTAPP_HPP
#define TESTAPP_HPP

#include <chrono>
#include <string>
#include <cstdint>

class TestApp
{
public:
	TestApp();
	[[noreturn]] void Run() const;
	void RunFor(const std::chrono::seconds& seconds) const;

private:
	void PrintAll() const;

	uint8_t m_uint8Data;
	uint16_t m_uint16Data;
	uint32_t m_uint32Data;
	uint64_t m_uint64Data;
	int8_t m_int8Data;
	int16_t m_int16Data;
	int32_t m_int32Data;
	int64_t m_int64Data;
	float m_floatData;
	double m_doubleData;
	std::string m_stringData;
	const char* m_charPtrData;
};



#endif //TESTAPP_HPP
