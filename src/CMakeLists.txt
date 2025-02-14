file(GLOB HEADER_LIST
  CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/**/**.hpp")

file(GLOB SOURCE_LIST
  "${PROJECT_SOURCE_DIR}/src/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/**/*.cpp")

add_library(embarcas ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(embarcas PUBLIC ../include)

