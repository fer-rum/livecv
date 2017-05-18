
# --- Shared subpaths ---
# These subpaths are equal relative to the root of the source tree,
# build tree and deployment tree
# Subpaths do NOT include a leading or trailing slash

initVar(SUBPATH_APPLICATION, application)

initVar(SUBPATH_EDITOR, editor)
initVar(SUBPATH_EDITOR_LCVEDITOR, $$SUBPATH_EDITOR/lcveditor)
initVar(SUBPATH_EDITOR_QMLJSPARSER, $$SUBPATH_EDITOR/qmljsparser)

initVar(SUBPATH_PLUGINS, plugins)
initVar(SUBPATH_PLUGINS_CORE, $$SUBPATH_PLUGINS/lcvcore)
initVar(SUBPATH_PLUGINS_FEATURES2D, $$SUBPATH_PLUGINS/lcvfeatures2d)
initVar(SUBPATH_PLUGINS_IMGPROC, $$SUBPATH_PLUGINS/lcvimgproc)
initVar(SUBPATH_PLUGINS_LIVE, $$SUBPATH_PLUGINS/live)
initVar(SUBPATH_PLUGINS_PHOTO, $$SUBPATH_PLUGINS/lcvphoto)
initVar(SUBPATH_PLUGINS_VIDEO, $$SUBPATH_PLUGINS/lcvvideo)


# --- Source tree paths ---
# NOTE: PROJECT_ROOT is defined in .qmake.conf to be globally viable
initVar(PATH_SOURCE_ROOT,               $$PROJECT_ROOT)
initVar(PATH_SOURCE_APPLICATION,        $$PATH_SOURCE_ROOT/$$SUBPATH_APPLICATION)
initVar(PATH_SOURCE_EDITOR,             $$PATH_SOURCE_ROOT/$$SUBPATH_EDITOR)
initVar(PATH_SOURCE_EDITOR_LCVEDITOR,   $$PATH_SOURCE_ROOT/$$SUBPATH_EDITOR_LCVEDITOR)
initVar(PATH_SOURCE_EDITOR_QMLJSPARSER, $$PATH_SOURCE_ROOT/$$SUBPATH_EDITOR_QMLJSPARSER)
initVar(PATH_SOURCE_PLUGINS,            $$PATH_SOURCE_ROOT/$$SUBPATH_PLUGINS)
initVar(PATH_SOURCE_PLUGINS_CORE,       $$PATH_SOURCE_ROOT/$$SUBPATH_PLUGINS_CORE)
initVar(PATH_SOURCE_PLUGINS_FEATURES2D, $$PATH_SOURCE_ROOT/$$SUBPATH_PLUGINS_FEATURES2D)
initVar(PATH_SOURCE_PLUGINS_IMGPROC,    $$PATH_SOURCE_ROOT/$$SUBPATH_PLUGINS_IMGPROC)
initVar(PATH_SOURCE_PLUGINS_LIVE,       $$PATH_SOURCE_ROOT/$$SUBPATH_PLUGINS_LIVE)
initVar(PATH_SOURCE_PLUGINS_PHOTO,      $$PATH_SOURCE_ROOT/$$SUBPATH_PLUGINS_PHOTO)
initVar(PATH_SOURCE_PLUGINS_VIDEO,      $$PATH_SOURCE_ROOT/$$SUBPATH_PLUGINS_VIDEO)

# --- Deploy tree paths ---
# NOTE: DEPLOY_PWD is defined in .qmake.conf to be globally viable

initVar(PATH_DEPLOY_APPLICATION,         $$DEPLOY_PWD)
initVar(PATH_DEPLOY_EDITOR,              $$DEPLOY_PWD/$$SUBPATH_EDITOR)
initVar(PATH_DEPLOY_EDITOR_LCVEDITOR,    $$DEPLOY_PWD/$$SUBPATH_EDITOR_LCVEDITOR)
initVar(PATH_DEPLOY_EDITOR_QMLJSPARSER,  $$DEPLOY_PWD/$$SUBPATH_EDITOR_QMLJSPARSER)
initVar(PATH_DEPLOY_PLUGINS,             $$DEPLOY_PWD/$$SUBPATH_PLUGINS)
initVar(PATH_DEPLOY_PLUGINS_CORE,        $$DEPLOY_PWD/$$SUBPATH_PLUGINS_CORE)
initVar(PATH_DEPLOY_PLUGINS_FEATURES2D,  $$DEPLOY_PWD/$$SUBPATH_PLUGINS_FEATURES2D)
initVar(PATH_DEPLOY_PLUGINS_IMGPROC,     $$DEPLOY_PWD/$$SUBPATH_PLUGINS_IMGPROC)
initVar(PATH_DEPLOY_PLUGINS_LIVE,        $$DEPLOY_PWD/$$SUBPATH_PLUGINS_LIVE)
initVar(PATH_DEPLOY_PLUGINS_PHOTO,       $$DEPLOY_PWD/$$SUBPATH_PLUGINS_PHOTO)
initVar(PATH_DEPLOY_PLUGINS_VIDEO,       $$DEPLOY_PWD/$$SUBPATH_PLUGINS_VIDEO)

# NOTE: It would be nice to have a plugin auto-discovery and setup mechanism...

