# RAMRider CLI executable

set(RAMRIDER_CLI_SOURCES
	"CLI/main.cpp"
)

add_executable(ramrider-cli ${RAMRIDER_CLI_SOURCES})

# Include directories for "CLI"
target_include_directories(ramrider-cli PUBLIC
        "${CMAKE_SOURCE_DIR}/Sources/CLI"
        "${CMAKE_SOURCE_DIR}/Sources/RAMRider"
)

# Link the RAMRider library
target_link_libraries(ramrider-cli PRIVATE ramrider)

# Set build-specific flags for different configurations
target_compile_definitions(ramrider-cli PRIVATE
        $<$<CONFIG:Debug>:__DEBUG__>
        $<$<CONFIG:Production>:__PROD__>
)