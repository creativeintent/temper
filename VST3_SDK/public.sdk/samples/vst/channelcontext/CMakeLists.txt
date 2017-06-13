
set(channelcontext_sources
	source/plug.cpp
	source/plug.h
	source/plugcids.h
	source/plugcontroller.cpp
	source/plugcontroller.h
	source/plugentry.cpp
	source/plugparamids.h
	source/version.h
)

set(target channelcontext)
smtg_add_vst3plugin(${target} ${SDK_ROOT} ${channelcontext_sources})
target_link_libraries(${target} PRIVATE base sdk)
if(MAC)
	smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/mac/Info.plist" PREPROCESS)
elseif(WIN)
	target_sources(${target} PRIVATE resource/plug.rc)
endif()
