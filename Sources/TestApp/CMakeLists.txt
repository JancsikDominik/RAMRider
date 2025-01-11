# TestApp executable

set(RAMRIDER_TESTAPP_SOURCES
	"App/TestApp.cpp"
	"App/TestApp.hpp"
)

add_executable(test-app ${RAMRIDER_TESTAPP_SOURCES})

# Include directories for "CLI"
target_include_directories(test-app PUBLIC
	"${CMAKE_SOURCE_DIR}/Sources/App"
)