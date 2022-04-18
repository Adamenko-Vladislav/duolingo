cmake_minimum_required(VERSION 3.21)
project(duolingo)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED
        Multimedia)

include_directories(model)
include_directories(view)
include_directories(presenter)
include_directories(resources)
include_directories(tools)

add_executable(duolingo
        main.cpp
        model/model.cpp
        model/model.h
        view/view.cpp
        view/view.h
        presenter/presenter.cpp
        presenter/presenter.h
        resources/resources.qrc
        tools/file_loader.cpp
        tools/file_loader.h
        view/task_window.cpp
        view/task_window.h
        view/pick_an_option.cpp
        view/pick_an_option.h
        tools/pick_an_option_task.h
        tools/random.h
        view/win_scene.cpp
        view/win_scene.h
        tools/tools.cpp
        tools/tools.h
        view/input_answer.cpp
        view/input_answer.h
        view/audio_task.cpp
        view/audio_task.h
        view/mixed_task.cpp
        view/mixed_task.h)

target_link_libraries(duolingo
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::Multimedia
        )

