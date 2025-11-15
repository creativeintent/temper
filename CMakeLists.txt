cmake_minimum_required(VERSION 3.22)

project(temper VERSION 1.0.4)
#find_package(JUCE CONFIG REQUIRED)  

# --- Fetch JUCE ---
include(FetchContent)
FetchContent_Declare(
    juce
    GIT_REPOSITORY https://github.com/juce-framework/JUCE.git
    GIT_TAG        7.0.12 # Change to desired tag or branch
)
FetchContent_MakeAvailable(juce)
#juce_set_vst2_sdk_path(...)


file(GLOB_RECURSE TEMPER_SRCS
  ${PROJECT_SOURCE_DIR}/Source/*.cpp
  ${PROJECT_SOURCE_DIR}/Source/*.h
)
file(GLOB_RECURSE TEMPER_ASSETS
     ${PROJECT_SOURCE_DIR}/Assets/*)

juce_add_plugin(temper 
   
    COMPANY_NAME "creativeintent"
    COMPANY_WEBSITE "https://github.com/creativeintent/temper/tree/master"
    PLUGIN_CODE T3mp 
    PLUGIN_MANUFACTURER_CODE Crin 
    FORMATS Standalone VST3 LV2 AU
    PRODUCT_NAME "temper"
    DESCRIPTION "temper the temperated distortion plugin"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    VST3_CATEGORIES "Distortion"
    AU_MAIN_TYPE "kAudioUnitType_MusicEffect"
    )

juce_generate_juce_header(temper)

target_sources(temper
    PRIVATE
        ${TEMPER_SRCS})

target_compile_definitions(temper
    PRIVATE
        # JUCE_WEB_BROWSER and JUCE_USE_CURL would be on by default, but you might not need them.
        JUCE_WEB_BROWSER=0  # If you remove this, add `NEEDS_WEB_BROWSER TRUE` to the `juce_add_gui_app` call
        JUCE_USE_CURL=0     # If you remove this, add `NEEDS_CURL TRUE` to the `juce_add_gui_app` call
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:temper,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:temper,JUCE_VERSION>"
        JUCE_VST3_CAN_REPLACE_VST2=0)
target_include_directories(temper PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Include)

juce_add_binary_data(temperData SOURCES ${TEMPER_ASSETS})

target_link_libraries(temper
    PRIVATE
        #FLAC
        #vorbis
        #vorbisenc
        #vorbisfile
        #ogg
        temperData
        juce::juce_core
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_utils
        juce::juce_data_structures
        juce::juce_dsp
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce::juce_opengl
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
#        juce::juce_recommended_warning_flags
        )