cmake_minimum_required(VERSION 3.20) #设置cmake最低版本

# 设置项目名称 版本 语言
project(yuri VERSION 0.1 LANGUAGES CXX)
# pacman -S mingw-w64-x86_64-libmariadbclient
# pacman -S mingw-w64-x86_64-qt6
# pacman -S mingw-w64-x86_64-cmake

#set(CMAKE_PREFIX_PATH "C:\\msys64\\mingw64\\lib\\cmake") # qt库目录

set(CMAKE_AUTOUIC ON) # 自动编译ui文件
set(CMAKE_AUTOMOC ON) # 自动编译moc文件
set(CMAKE_AUTORCC ON) # 自动编译资源文件
set(CMAKE_CXX_STANDARD 17) # 设置c++ 最低版本
set(CMAKE_CXX_STANDARD_REQUIRED ON) # 要求使用指定版本号
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # 开启生成 compile_commands.json

# 寻找qt依赖库
find_package(QT NAMES Qt6 REQUIRED COMPONENTS  Widgets LinguistTools )
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS  Widgets LinguistTools)
find_package(Qt6 COMPONENTS Network REQUIRED)
find_package(Qt6 COMPONENTS StateMachine REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Sql)

# 设置翻译文件
set(TS_FILES yuri_zh_CN.ts)
INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
)

file(GLOB HEAD_FILE ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB SRC_FILE ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB UI_FILE ${PROJECT_SOURCE_DIR}/ui/*.ui)
file(GLOB QRC_FILE ${PROJECT_SOURCE_DIR}/qrc/*.qrc)
file(GLOB HPP_FILE ${PROJECT_SOURCE_DIR}/hpp/*.hpp)


set(LIB_FILES ${TS_FILES} ${SRC_FILE} ${HEAD_FILE} ${UI_FILE} ${QRC_FILE} ${HPP_FILE})

# 添加项目文件
set(PROJECT_SOURCES
    main.cpp
    ${TS_FILES}
    ${LIB_FILES}
)

# 如果qt 版本大于等于6
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    # 构建可执行问价
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
    # 链接文件
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Sql)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Network)
    target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::StateMachine)
    
    # 设置项目属性
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        #    WIN32_EXECUTABLE TRUE
    )

else()
    message("QT version is less 6")
endif()





