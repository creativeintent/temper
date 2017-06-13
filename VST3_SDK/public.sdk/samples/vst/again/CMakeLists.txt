
if (SMTG_CREATE_VST2_VERSION)
	set(again_vst2_sources
		${SDK_ROOT}/public.sdk/source/common/memorystream.cpp
		${SDK_ROOT}/public.sdk/source/vst/hosting/eventlist.cpp
		${SDK_ROOT}/public.sdk/source/vst/hosting/hostclasses.cpp
		${SDK_ROOT}/public.sdk/source/vst/hosting/parameterchanges.cpp
		${SDK_ROOT}/public.sdk/source/vst/hosting/processdata.cpp
		${SDK_ROOT}/public.sdk/source/vst/vst2wrapper/vst2wrapper.cpp
		${SDK_ROOT}/public.sdk/source/vst/vst2wrapper/vst2wrapper.h
		${SDK_ROOT}/public.sdk/source/vst2.x/audioeffect.cpp
		${SDK_ROOT}/public.sdk/source/vst2.x/audioeffectx.cpp
		source/againentry_vst2.cpp
	)
endif()

set(again_sources
	source/again.cpp
	source/again.h
	source/againcids.h
	source/againcontroller.cpp
	source/againcontroller.h
	source/againentry.cpp
	source/againparamids.h
	source/againprocess.h
	source/againsidechain.cpp
	source/againsidechain.h
	source/againuimessagecontroller.h
	source/version.h
)

set(again_simple_sources
	${SDK_ROOT}/public.sdk/source/vst/vstsinglecomponenteffect.cpp
	${SDK_ROOT}/public.sdk/source/vst/vstsinglecomponenteffect.h
	source/againparamids.h
	source/againsimple.cpp
	source/againsimple.h
	source/version.h
)

# VST2 is only defined for macOS and Windows
if(MAC OR WIN)
	set(again_sources ${again_sources} ${again_vst2_sources})
endif()

set(target again)
smtg_add_vst3plugin(${target} ${SDK_ROOT} ${again_sources})
target_include_directories(${target} PUBLIC ${VSTGUI_ROOT}/vstgui4)
target_link_libraries(${target} PRIVATE base sdk vstgui_support)

smtg_add_vst3_resource(${target} "resource/again.uidesc")
smtg_add_vst3_resource(${target} "resource/background.png")
smtg_add_vst3_resource(${target} "resource/slider_background.png")
smtg_add_vst3_resource(${target} "resource/slider_handle.png")
smtg_add_vst3_resource(${target} "resource/slider_handle#2x.png")
smtg_add_vst3_resource(${target} "resource/vu_on.png")
smtg_add_vst3_resource(${target} "resource/vu_off.png")

if(MAC)
	smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/mac/Info.plist" PREPROCESS)
elseif(WIN)
	target_sources(${target} PRIVATE resource/again.rc)
endif()


set(targetsimple againsimple)
smtg_add_vst3plugin(${targetsimple} ${SDK_ROOT} ${again_simple_sources})
target_include_directories(${targetsimple} PUBLIC ${VSTGUI_ROOT}/vstgui4)
target_link_libraries(${targetsimple} PRIVATE base sdk vstgui_support)

smtg_add_vst3_resource(${targetsimple} "resource/again.uidesc")
smtg_add_vst3_resource(${targetsimple} "resource/background.png")
smtg_add_vst3_resource(${targetsimple} "resource/slider_background.png")
smtg_add_vst3_resource(${targetsimple} "resource/slider_handle.png")
smtg_add_vst3_resource(${targetsimple} "resource/slider_handle#2x.png")
smtg_add_vst3_resource(${targetsimple} "resource/vu_on.png")
smtg_add_vst3_resource(${targetsimple} "resource/vu_off.png")

if(MAC)
	smtg_set_bundle(${targetsimple} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/mac/Info.plist" PREPROCESS)
elseif(WIN)
	target_sources(${targetsimple} PRIVATE resource/again.rc)
endif()
