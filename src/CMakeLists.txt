file(GLOB HEADER_LIST
  CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/include/**/**.h")

file(GLOB SOURCE_LIST
  "${PROJECT_SOURCE_DIR}/src/*.c"
  "${PROJECT_SOURCE_DIR}/src/**/*.c")

add_library(embarcas ${SOURCE_LIST} ${HEADER_LIST})
target_include_directories(embarcas PUBLIC ../include)

