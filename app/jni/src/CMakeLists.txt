cmake_minimum_required(VERSION 3.6)
project(Arx)

# Encontre as bibliotecas SDL2, SDL2_mixer, SDL2_image e SDL2_ttf
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Adicione os diretórios de inclusão das bibliotecas encontradas
include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_MIXER_INCLUDE_DIRS}
        ${SDL2_IMAGE_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
)

# Obtenha a lista de arquivos de origem
file(GLOB SOURCES src/*.c src/*.h src/*/*.c src/*/*.h)

# Defina o diretório de saída do executável
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs/${ANDROID_ABI})

# Crie o executável do projeto
add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCES})

# Vincule as bibliotecas necessárias
target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        ${SDL2_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        main
)