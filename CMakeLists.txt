cmake_minimum_required(VERSION 3.21)

# ---- Project ----

project(
    LibFire
    VERSION 1.0.8.2
    HOMEPAGE_URL https://github.com/fireundubh/LibFire
    LANGUAGES CXX
)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.rc
    @ONLY
)

set(headers
    src/PCH.h
    src/Papyrus/Registration.h
    src/Papyrus/ActorValueHelper.h
    src/Papyrus/PapyrusActor.h
    src/Papyrus/PapyrusArray.h
    src/Papyrus/PapyrusFaction.h
    src/Papyrus/PapyrusFormList.h
    src/Papyrus/PapyrusObjectREFR.h
    src/Papyrus/PapyrusPlayerCharacter.h
    src/Papyrus/PapyrusRace.h
    src/Papyrus/PapyrusSpell.h
    src/Papyrus/PapyrusString.h
    src/Papyrus/PapyrusTime.h
)

set(sources
    src/main.cpp
    src/PCH.cpp
    src/Papyrus/Registration.cpp
    src/Papyrus/ActorValueHelper.cpp
    src/Papyrus/PapyrusActor.cpp
    src/Papyrus/PapyrusArray.cpp
    src/Papyrus/PapyrusFaction.cpp
    src/Papyrus/PapyrusFormList.cpp
    src/Papyrus/PapyrusObjectREFR.cpp
    src/Papyrus/PapyrusPlayerCharacter.cpp
    src/Papyrus/PapyrusRace.cpp
    src/Papyrus/PapyrusSpell.cpp
    src/Papyrus/PapyrusString.cpp
    src/Papyrus/PapyrusTime.cpp
)

source_group(
    TREE
    ${CMAKE_CURRENT_SOURCE_DIR}
    FILES
    ${headers}
    ${sources}
)

# ---- Add CMake features ----

include(CheckIPOSupported)
include(GNUInstallDirs)
include(GoogleTest)

# ---- Dependencies ----

find_package(CommonLibSSE CONFIG REQUIRED)
find_package(binary_io REQUIRED)
find_package(spdlog REQUIRED)
find_package(fmt REQUIRED)

# ---- Configuration for all targets ----

if (MSVC)
    add_compile_definitions(
        UNICODE
        _UNICODE
        NOMINMAX
        _AMD64_
        WIN32_LEAN_AND_MEAN
        _CRT_USE_BUILTIN_OFFSETOF # Fixes MSVC being non-compliant with offsetof behavior by default.
    )

    if ($ENV{CLION_IDE})
        add_compile_definitions(
            __cpp_lib_char8_t         # Workaround for CLion bug.
            __cpp_consteval           # Workaround for CLion bug.
        )
    endif ()

    add_compile_options(
        /bigobj # support large object file format
        /utf-8  # assume UTF-8 sources even without a BOM

        # warnings -> errors
        /we4715	# 'function' : not all control paths return a value

        # disable warnings
        /wd4005 # macro redefinition
        /wd4061 # enumerator 'identifier' in switch of enum 'enumeration' is not explicitly handled by a case label
        /wd4117 # definition of reserved macro, needed for workarounds for CLion
        /wd4200 # nonstandard extension used : zero-sized array in struct/union
        /wd4201 # nonstandard extension used : nameless struct/union
        /wd4265 # 'type': class has virtual functions, but its non-trivial destructor is not virtual; instances of this class may not be destructed correctly
        /wd4266 # 'function' : no override available for virtual member function from base 'type'; function is hidden
        /wd4371 # 'classname': layout of class may have changed from a previous version of the compiler due to better packing of member 'member'
        /wd4459 # declaration of 'identifier' hides global declaration
        /wd4514 # 'function' : unreferenced inline function has been removed
        /wd4582 # 'type': constructor is not implicitly called
        /wd4583 # 'type': destructor is not implicitly called
        /wd4623 # 'derived class' : default constructor was implicitly defined as deleted because a base class default constructor is inaccessible or deleted
        /wd4625 # 'derived class' : copy constructor was implicitly defined as deleted because a base class copy constructor is inaccessible or deleted
        /wd4626 # 'derived class' : assignment operator was implicitly defined as deleted because a base class assignment operator is inaccessible or deleted
        /wd4710 # 'function' : function not inlined
        /wd4711 # function 'function' selected for inline expansion
        /wd4820 # 'bytes' bytes padding added after construct 'member_name'
        /wd5026 # 'type': move constructor was implicitly defined as deleted
        /wd5027 # 'type': move assignment operator was implicitly defined as deleted
        /wd5045 # Compiler will insert Spectre mitigation for memory load if /Qspectre switch specified
        /wd5053 # support for 'explicit(<expr>)' in C++17 and earlier is a vendor extension
        /wd5204 # 'type-name': class has virtual functions, but its trivial destructor is not virtual; instances of objects derived from this class may not be destructed correctly
        /wd5220 # 'member': a non-static data member with a volatile qualified type no longer implies that compiler generated copy / move constructors and copy / move assignment operators are not trivial
    )
endif ()

check_ipo_supported(RESULT USE_IPO OUTPUT IPO_OUTPUT)
if(USE_IPO)
    set(CMAKE_INTERPROCEDURAL_OPTIMIZATION "$<$<CONFIG:RELEASE>:ON>")
endif()

# ---- Configure target DLL ----

add_commonlibsse_plugin(
    ${PROJECT_NAME}
    AUTHOR
        fireundubh
    SOURCES
        ${headers}
        ${sources}
        ${CMAKE_CURRENT_BINARY_DIR}/version.rc
        .clang-format
)

target_compile_features(
    ${PROJECT_NAME}
    PUBLIC
        cxx_std_23
)

target_compile_definitions(
    ${PROJECT_NAME}
    PUBLIC
        WINVER=0x0601	# windows 7, minimum supported version by skyrim special edition
        _WIN32_WINNT=0x0601
        "$<$<BOOL:${SKSE_SUPPORT_XBYAK}>:SKSE_SUPPORT_XBYAK=1>"
        "$<$<BOOL:${ENABLE_SKYRIM_SE}>:ENABLE_SKYRIM_SE=1>"
        "$<$<BOOL:${ENABLE_SKYRIM_AE}>:ENABLE_SKYRIM_AE=1>"
        "$<$<BOOL:${ENABLE_SKYRIM_VR}>:ENABLE_SKYRIM_VR=1>"
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:src>
)

target_link_options(
    ${PROJECT_NAME}
    PUBLIC
        ${LINK_OPTIONS_${CONFIG}}
)

target_precompile_headers(
    ${PROJECT_NAME}
    PRIVATE
        src/PCH.h
)

set(OUTPUT_ROOT "$ENV{SkyrimAE_Mods}/${PROJECT_NAME}" CACHE STRING "")

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:${PROJECT_NAME}>" "${OUTPUT_ROOT}/SKSE/Plugins/"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${CMAKE_SOURCE_DIR}/Scripts/Source/${PROJECT_NAME}.psc" "${OUTPUT_ROOT}/Scripts/Source/${PROJECT_NAME}.psc"
)
