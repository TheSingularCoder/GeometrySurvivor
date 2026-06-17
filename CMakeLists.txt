cmake_minimum_required(VERSION 3.23)
project(GeometrySurvivor)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(APP_SRC
        src/main.cpp
)

set(LIB_HEADERS
        include/Game.h
        include/SDL_wrapper.h
        include/Vector2D.h
        include/State.h
        include/PlayingState.h
        include/Entity.h
        include/EntityManager.h
        include/ColliderManager.h
        include/Timer.h
        include/infoAI.h
        include/Factory.h
        include/MenuState.h
        include/Spells.h
        include/RandomUtils.h
        include/CollisionLayers.h
        #==========COMPONENTS=================
        include/Components/Component.h
        include/Components/TransformComponent.h
        include/Components/ComponentsList.h
        include/Components/SimpleSpriteComponent.h
        include/Components/ControllerComponent.h
        include/Components/SimpleAIComponent.h
        include/Components/ColliderComponent.h
        include/Components/HealthComponent.h
        include/Components/PlayerComponent.h
        include/Components/SpellComponent.h
        include/Components/LifeTimeComponent.h
        include/Components/SpellComponent.h
        include/Components/Colliders.h
        include/Components/ArcherAIComponent.h
        include/Components/SquareAIComponent.h
        include/Components/ScaleComponent.h
        include/Components/MageAIComponent.h
        include/Components/SummonerAIComponent.h
        include/GameData.h
        include/ShopState.h
        include/SpellStats.h
        include/SpellRegistry.h

)

set(LIB_SRC
        src/Game.cpp
        src/PlayingState.cpp
        src/EntityManager.cpp
        src/ColliderManager.cpp
        src/Timer.cpp
        src/MenuState.cpp
        src/Factory/Factory.cpp
        src/Factory/EnemyFactory.cpp
        src/Factory/SpellFactory.cpp
        #=====COMPONENTS============
        src/Components/TransformComponent.cpp
        src/Components/SimpleSpriteComponent.cpp
        src/Components/ControllerComponent.cpp
        src/Components/SimpleAIComponent.cpp
        src/Components/ColliderComponent.cpp
        src/Components/HealthComponent.cpp
        src/Components/PlayerComponent.cpp
        src/Components/SpellComponent.cpp
        src/Components/LifeTimeComponent.cpp
        src/Components/SpellComponent.cpp
        src/Components/Colliders.cpp
        src/Components/ArcherAIComponent.cpp
        src/Components/SquareAIComponent.cpp
        src/Components/ScaleComponent.cpp
        src/Components/MageAIComponent.cpp
        src/Components/SummonerAIComponent.cpp
        src/ShopState.cpp
)

include(FetchContent)
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.0
)
FetchContent_MakeAvailable(SDL2)

add_library(Library)


target_sources(Library
    PRIVATE ${LIB_SRC}
    PUBLIC
    FILE_SET HEADERS
    BASE_DIRS include
    FILES ${LIB_HEADERS}
)


target_link_libraries(Library
    PUBLIC
    SDL2::SDL2
)

add_executable(GeometrySurvivorApp)
target_sources(GeometrySurvivorApp
    PRIVATE ${APP_SRC}
)
target_link_libraries(GeometrySurvivorApp
    PRIVATE
    Library
)
target_compile_options(GeometrySurvivorApp PRIVATE
    -Wall
    -Wextra
    -Wconversion
    -Wshadow
)
