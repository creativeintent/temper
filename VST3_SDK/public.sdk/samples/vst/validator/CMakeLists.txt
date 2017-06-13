
set(validator_sources
	source/main.cpp
	source/usediids.cpp
	source/validator.cpp
	source/validator.h
	${SDK_ROOT}/public.sdk/source/vst/vstinitiids.cpp
	${SDK_ROOT}/public.sdk/source/vst/testsuite/vsttestsuite.cpp
	${SDK_ROOT}/public.sdk/source/vst/testsuite/vsttestsuite.h
	${SDK_ROOT}/public.sdk/source/vst/hosting/processdata.cpp
	${SDK_ROOT}/public.sdk/source/vst/hosting/processdata.h
	${SDK_ROOT}/public.sdk/source/vst/hosting/plugprovider.cpp
	${SDK_ROOT}/public.sdk/source/vst/hosting/plugprovider.h
	${SDK_ROOT}/public.sdk/source/vst/hosting/hostclasses.cpp
	${SDK_ROOT}/public.sdk/source/vst/hosting/hostclasses.h
	${SDK_ROOT}/public.sdk/source/vst/hosting/module.cpp
	${SDK_ROOT}/public.sdk/source/vst/hosting/module.h
	${SDK_ROOT}/public.sdk/source/vst/hosting/optional.h
	${SDK_ROOT}/public.sdk/source/vst/hosting/stringconvert.cpp
	${SDK_ROOT}/public.sdk/source/vst/hosting/stringconvert.h
	${SDK_ROOT}/public.sdk/source/vst/hosting/uid.h
)

if(APPLE)
	set(validator_sources
		${validator_sources}
		${SDK_ROOT}/public.sdk/source/vst/hosting/module_mac.mm
	)
elseif(LINUX)
	set(validator_sources
		${validator_sources}
		${SDK_ROOT}/public.sdk/source/vst/hosting/module_linux.cpp
	)
elseif(WIN)
	set(validator_sources
		${validator_sources}
		${SDK_ROOT}/public.sdk/source/vst/hosting/module_win32.cpp
	)
endif()

set(target validator)
add_executable(${target} ${validator_sources})
target_link_libraries(${target} PRIVATE base sdk)
if(APPLE AND NOT XCODE)
	find_library(COCOA_FRAMEWORK Cocoa)
	target_link_libraries(${target} PRIVATE ${COCOA_FRAMEWORK})
endif()