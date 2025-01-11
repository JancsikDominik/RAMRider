#include "TestApp.hpp"

#include <chrono>
#include <thread>
#include <iostream>

[[maybe_unused]] static uint8_t gs_staticVariable = 1;

TestApp::TestApp()
	: m_uint8Data{ 8u }
	, m_uint16Data{ 16u }
	, m_uint32Data{ 32u }
	, m_uint64Data{ 64u }
	, m_int8Data{ -8 }
	, m_int16Data{ -16 }
	, m_int32Data{ -32 }
	, m_int64Data{ -64 }
	, m_floatData{ 3.14f }
	, m_doubleData{ 2.71828 }
	, m_stringData{ "Find the std::string" }
	, m_charPtrData{ "Find the char*" }
{}

void TestApp::Run() const
{
	PrintAll();
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void TestApp::RunFor(const std::chrono::seconds& seconds) const
{
	PrintAll();
	const auto start = std::chrono::steady_clock::now();

	while (std::chrono::steady_clock::now() - start < seconds) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}

void TestApp::PrintAll() const
{
	std::cout   << "Data:\n"
			    << "    uint8: " << static_cast<uint16_t>(m_uint8Data) << "\n"
	            << "    uint16: " << m_uint16Data << "\n"
			    << "    uint32: " << m_uint32Data << "\n"
				<< "    uint64: " << m_uint64Data << "\n"
				<< "    int8: " << static_cast<int16_t>(m_int8Data) << "\n"
				<< "    int16: " << m_int16Data << "\n"
				<< "    int32: " << m_int32Data << "\n"
				<< "    int64: " << m_int64Data << "\n"
				<< "    float: " << m_floatData << "\n"
				<< "    double: " << m_doubleData << "\n"
				<< "    string: " << m_stringData << "\n"
				<< "    char*: " << m_charPtrData << std::endl;
}

int main()
{
	const TestApp app;
	app.Run();

	return 0;
}
