#
# Headers
#
# argos3/plugins/simulator/visualizations/qt-opengl/models
set(ARGOS3_HEADERS_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL_MODELS
  models/qtopengl_box.h
  models/qtopengl_cylinder.h
  models/qtopengl_light.h)
# argos3/plugins/simulator/visualizations/qt-opengl/dialogs/layouts
set(ARGOS3_HEADERS_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL_DIALOGS_LAYOUTS
  dialogs/layouts/qtopengl_entity_dialog_layout.h
  dialogs/layouts/qtopengl_embodied_entity_dialog_layout.h
  dialogs/layouts/qtopengl_box_entity_dialog_layout.h
  dialogs/layouts/qtopengl_cylinder_entity_dialog_layout.h
  dialogs/layouts/qtopengl_light_entity_dialog_layout.h
  dialogs/layouts/qtopengl_bot_entity_dialog_layout.h
  dialogs/layouts/qtopengl_epuck_entity_dialog_layout.h
  dialogs/layouts/qtopengl_eyebot_entity_dialog_layout.h
  dialogs/layouts/qtopengl_footbot_entity_dialog_layout.h
  dialogs/layouts/qtopengl_spiri_entity_dialog_layout.h)
# argos3/plugins/simulator/visualizations/qt-opengl/dialogs
set(ARGOS3_HEADERS_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL_DIALOGS
  dialogs/qtopengl_add_entity_dialog.h)
# argos3/plugins/simulator/visualizations/qt-opengl
set(ARGOS3_HEADERS_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL
  dialogs/layouts/qtopengl_entity_dialog_layout.h
  dialogs/layouts/qtopengl_embodied_entity_dialog_layout.h
  dialogs/layouts/qtopengl_box_entity_dialog_layout.h
  dialogs/layouts/qtopengl_cylinder_entity_dialog_layout.h
  dialogs/layouts/qtopengl_light_entity_dialog_layout.h
  dialogs/layouts/qtopengl_bot_entity_dialog_layout.h
  dialogs/layouts/qtopengl_epuck_entity_dialog_layout.h
  dialogs/layouts/qtopengl_eyebot_entity_dialog_layout.h
  dialogs/layouts/qtopengl_footbot_entity_dialog_layout.h
  dialogs/layouts/qtopengl_spiri_entity_dialog_layout.h
  dialogs/qtopengl_add_entity_dialog.h
  qtopengl_application.h
  qtopengl_camera.h
  qtopengl_log_stream.h
  qtopengl_main_window.h
  qtopengl_render.h
  qtopengl_user_functions.h
  qtopengl_widget.h)
if(ARGOS_WITH_LUA)
  set(ARGOS3_HEADERS_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL
    ${ARGOS3_HEADERS_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL}
    qtopengl_lua_editor.h
    qtopengl_lua_find_dialog.h
    qtopengl_lua_main_window.h
    qtopengl_lua_syntax_highlighter.h
    qtopengl_lua_statetree_item.h
    qtopengl_lua_statetree_model.h)
endif(ARGOS_WITH_LUA)

#
# Source files
#
# Common for all builds
set(ARGOS3_SOURCES_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL
  ${ARGOS3_HEADERS_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL}
  ${ARGOS3_HEADERS_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL_MODELS}
  models/qtopengl_box.cpp
  models/qtopengl_cylinder.cpp
  models/qtopengl_light.cpp
  dialogs/layouts/qtopengl_entity_dialog_layout.cpp
  dialogs/layouts/qtopengl_embodied_entity_dialog_layout.cpp
  dialogs/layouts/qtopengl_box_entity_dialog_layout.cpp
  dialogs/layouts/qtopengl_cylinder_entity_dialog_layout.cpp
  dialogs/layouts/qtopengl_light_entity_dialog_layout.cpp
  dialogs/layouts/qtopengl_bot_entity_dialog_layout.cpp
  dialogs/layouts/qtopengl_epuck_entity_dialog_layout.cpp
  dialogs/layouts/qtopengl_eyebot_entity_dialog_layout.cpp
  dialogs/layouts/qtopengl_footbot_entity_dialog_layout.cpp
  dialogs/layouts/qtopengl_spiri_entity_dialog_layout.cpp
  dialogs/qtopengl_add_entity_dialog.cpp
  qtopengl_application.cpp
  qtopengl_camera.cpp
  qtopengl_main_window.cpp
  qtopengl_render.cpp
  qtopengl_user_functions.cpp
  qtopengl_widget.cpp)
if(ARGOS_WITH_LUA)
  set(ARGOS3_SOURCES_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL
    ${ARGOS3_SOURCES_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL}
    qtopengl_lua_editor.cpp
    qtopengl_lua_find_dialog.cpp
    qtopengl_lua_main_window.cpp
    qtopengl_lua_syntax_highlighter.cpp
    qtopengl_lua_statetree_item.cpp
    qtopengl_lua_statetree_model.cpp)
endif(ARGOS_WITH_LUA)

#
# Create Qt-OpenGL visualization
#
add_library(argos3plugin_${ARGOS_BUILD_FOR}_qtopengl SHARED
  ${ARGOS3_SOURCES_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL})
target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_qtopengl argos3plugin_${ARGOS_BUILD_FOR}_entities ${ARGOS_QTOPENGL_LIBRARIES})
# Link SDL if necessary
# if(SDL_FOUND)
#  target_link_libraries(argos3plugin_${ARGOS_BUILD_FOR}_qtopengl ${SDL_LIBRARY})
# endif(SDL_FOUND)

install(DIRECTORY icons textures DESTINATION include/argos3/plugins/simulator/visualizations/qt-opengl)
install(FILES ${ARGOS3_HEADERS_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL_MODELS} DESTINATION include/argos3/plugins/simulator/visualizations/qt-opengl/models)
install(FILES ${ARGOS3_HEADERS_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL_DIALOGS_LAYOUTS} DESTINATION include/argos3/plugins/simulator/visualizations/qt-opengl/dialogs/layouts)
install(FILES ${ARGOS3_HEADERS_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL_DIALOGS} DESTINATION include/argos3/plugins/simulator/visualizations/qt-opengl/dialogs)
install(FILES ${ARGOS3_HEADERS_PLUGINS_SIMULATOR_VISUALIZATIONS_QTOPENGL}        DESTINATION include/argos3/plugins/simulator/visualizations/qt-opengl)
install(TARGETS argos3plugin_${ARGOS_BUILD_FOR}_qtopengl
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib/argos3
  ARCHIVE DESTINATION lib/argos3
)
