
set(noteexpressionsynth_sources
	source/brownnoise.h
	source/factory.cpp
	source/filter.h
	source/note_expression_synth_controller.cpp
	source/note_expression_synth_controller.h
	source/note_expression_synth_processor.cpp
	source/note_expression_synth_processor.h
	source/note_expression_synth_ui.cpp
	source/note_expression_synth_ui.h
	source/note_expression_synth_voice.cpp
	source/note_expression_synth_voice.h
	source/note_touch_controller.cpp
	source/note_touch_controller.h
	source/version.h
 )

set(target noteexpressionsynth)
smtg_add_vst3plugin(${target} ${SDK_ROOT} ${noteexpressionsynth_sources})
target_include_directories(${target} PUBLIC ${VSTGUI_ROOT}/vstgui4)
target_link_libraries(${target} PRIVATE base sdk vstgui_support)

smtg_add_vst3_resource(${target} "resource/note_expression_synth.uidesc")
smtg_add_vst3_resource(${target} "resource/about.png")
smtg_add_vst3_resource(${target} "resource/background.png")
smtg_add_vst3_resource(${target} "resource/groupframe.png")
smtg_add_vst3_resource(${target} "resource/knob.png")
smtg_add_vst3_resource(${target} "resource/knob2.png")
smtg_add_vst3_resource(${target} "resource/knob big.png")
smtg_add_vst3_resource(${target} "resource/vst3_logo_small.png")

if(MAC)
	smtg_set_bundle(${target} INFOPLIST "${CMAKE_CURRENT_LIST_DIR}/resource/Info.plist" PREPROCESS)
elseif(WIN)
	target_sources(${target} PRIVATE resource/note_expression_synth.rc)
endif()
