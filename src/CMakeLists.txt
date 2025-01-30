# src/CMakeLists.txt

# Create a library for your game engine
add_library(GameLib
    ECS/Components/ComponentFactory.cpp
    ECS/Components/ComponentFactory.hpp
    ECS/Components/ComponentRegistry.hpp
    ECS/Components/Components.hpp
    ECS/Components/ComponentStorage.hpp
    ECS/Components/ComponentTypeID.hpp
    ECS/Components/ComponentTypeID.cpp

    ECS/Core/Core.cpp
    ECS/Core/Core.hpp

    ECS/Dynamic_Libraries/DeleteDL.hpp
    ECS/Dynamic_Libraries/DynamicLibrary.cpp
    ECS/Dynamic_Libraries/DynamicLibrary.hpp

    ECS/Entities/Entity.hpp
    ECS/Entities/EntityManager.cpp
    ECS/Entities/EntityManager.hpp

    ECS/Graphical/Graphical.hpp
    ECS/Graphical/IGraphical.hpp
    ECS/Graphical/SFMLGraphical.cpp
    ECS/Graphical/SFMLGraphical.hpp
    ECS/Graphical/SFMLInput.cpp
    ECS/Graphical/SFMLRenderer.cpp

    ECS/JSONParser/JSONComponentParser.cpp
    ECS/JSONParser/JSONComponentParser.hpp
    ECS/JSONParser/JSONStorage.hpp

    # Scene manager ?

    ECS/SpawnerParser/SpawnerParser.cpp
    ECS/SpawnerParser/SpawnerParser.hpp

    ECS/System_Handling/System.hpp
    ECS/System_Handling/SystemManager.hpp

    ECS/Systems/ClickSystem.hpp
    ECS/Systems/CollisionsSystem.hpp
    ECS/Systems/InputSystem.hpp
    ECS/Systems/MovementSystem.hpp
    ECS/Systems/RenderSystem.hpp
    ECS/Systems/SpawnerSystem.hpp

    ECS/Timer/Timer.hpp


    Game/CardStack/CardStack.cpp
    Game/CardStack/CardStack.hpp
)

# Specify include directories for the library
target_include_directories(GameLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    # Add other include directories if necessary
)