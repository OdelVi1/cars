target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)

file (GLOB_RECURSE MY_SOURCE_FILES CONFIGURE_DEPENDS LIST_DIRECTORIES false RELATIVE ${CMAKE_CURRENT_LIST_DIR} 
*.cpp
gifts/*.cpp
cars/*.cpp
directions/*.cpp
game_status/*.cpp
)
target_sources (${CMAKE_PROJECT_NAME} PRIVATE ${MY_SOURCE_FILES})
