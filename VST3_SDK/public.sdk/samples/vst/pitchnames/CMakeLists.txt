
set(pitchnames_sources
	source/factory.cpp
	source/pitchnames.cpp
	source/pitchnames.h
	source/pitchnamesdatabrowsersource.cpp
	source/pitchnamesdatabrowsersource.h
	source/version.h
)

set(target pitchnames)
smtg_add_vst3plugin(${target} ${SDK_ROOT} ${pitchnames_sources})
target_include_directories(${target} PRIVATE ${VSTGUI_ROOT}/vstgui4)
target_link_libraries(${target} PRIVATE base sdk vstgui_support)

smtg_add_vst3_resource(${target} "resource/pitchnames.uidesc")

if(MAC)
	smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/mac/Info.plist" PREPROCESS)
elseif(WIN)
	target_sources(${target} PRIVATE resource/pitchnames.rc)
endif()
