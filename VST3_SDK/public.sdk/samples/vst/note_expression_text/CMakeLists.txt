
set(noteexpressiontext_sources
	source/plug.cpp
	source/plug.h
	source/plugcids.h
	source/plugcontroller.cpp
	source/plugcontroller.h
	source/plugentry.cpp
	source/plugparamids.h
	source/version.h
	resource/plug.uidesc
)

set(target noteexpressiontext)
smtg_add_vst3plugin(${target} ${SDK_ROOT} ${noteexpressiontext_sources})
target_include_directories(${target} PRIVATE ${VSTGUI_ROOT}/vstgui4)
target_link_libraries(${target} PRIVATE base sdk vstgui_support)

smtg_add_vst3_resource(${target} "resource/plug.uidesc")

if(MAC)
	smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS)
elseif(WIN)
	target_sources(${target} PRIVATE resource/plug.rc)
endif()
