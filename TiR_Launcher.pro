QT += quick

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        config_storage.cpp \
        config_storage_adapter.cpp \
        main.cpp \
        main_window_vm.cpp \
        registered_enums.cpp \
        screen_ratio/screen_ratio_manager.cpp \
        screen_ratio_manager_vm.cpp \
        tir/tir_launcher.cpp

RESOURCES += qml.qrc

TRANSLATIONS += \
    TiR_Launcher_en_GB.ts \
    TiR_Launcher_ru_RU.ts

CONFIG += lrelease
CONFIG += embed_translations

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    config_storage.h \
    config_storage_adapter.h \
    main_window_vm.h \
    registered_enums.h \
    screen_ratio/screen_ratio_manager.h \
    screen_ratio_manager_vm.h \
    screen_ratio/screen_ratio_preset_type.h \
    tir/tir_launcher.h \
    json.hpp

RC_ICONS = tir.ico
