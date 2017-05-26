# This file contains the basic configuration for all plugins shipped with
# the application

!defined(PLUGIN_NAME, var): \
    error($$_FILE_: Tried to set up a plugin without defining PLUGIN_NAME first.)

isEmpty(PLUGIN_NAME): \
    error($$_FILE_: Tried to set up a plugin with an empty PLUGIN_NAME.)

!defined(PLUGIN_PATH, var): \
    error($$_FILE_: Tried to set up a plugin without defining PLUGIN_PATH first.)

isEmpty(PLUGIN_PATH): \
    error($$_FILE_: Tried to set up a plugin with an empty PLUGIN_PATH.)

!exists($$PLUGIN_PATH): \
    error($$_FILE_: Plugin path $$PLUGIN_PATH does not exist.)

# The PLUGIN_QML_DIR contains the path to the folder with all the qml files
# and related files
PLUGIN_QML_DIR = $$PLUGIN_PATH/qml

!defined(PLUGIN_QML_DIR, var): \
    error($$_FILE_: Tried to set up a plugin without defining PLUGIN_QML_DIR first.)

isEmpty(PLUGIN_QML_DIR): \
    error($$_FILE_: Tried to set up a plugin with an empty PLUGIN_QML_DIR.)

debug(Configuring plugin $$PLUGIN_NAME, 1)

TEMPLATE    = lib
QT          += qml quick
CONFIG      += qt plugin
TARGET      = $$PLUGIN_NAME

# Set up the deployment target
PLUGIN_DEPLOY_PATH = $$DEPLOY_PATH/plugins/$$PLUGIN_NAME

!exists(PLUGIN_DEPLOY_PATH):{
    createPluginDir.commands = $$createDirCommand($$PLUGIN_DEPLOY_PATH)
    QMAKE_EXTRA_TARGETS += createPluginDir
    PRE_TARGETDEPS += createPluginDir
}

win32:{
    DESTDIR    = $$DEPLOY_PATH/dev/lib/plugins/$$PLUGIN_NAME
    DLLDESTDIR = $$PLUGIN_DEPLOY_PATH
}else:DESTDIR = $$PLUGIN_DEPLOY_PATH

# --- Handling the QML deployment ---

!exists($$PLUGIN_QML_DIR){
    warning(Expected folder $$PLUGIN_QML_DIR)
    qmlcopy.commands =
} else {
    qmlcopy.commands = $$deployDirCommand($$PLUGIN_QML_DIR, $$PLUGIN_DEPLOY_PATH)
}

QMAKE_EXTRA_TARGETS += qmlcopy
POST_TARGETDEPS += qmlcopy
