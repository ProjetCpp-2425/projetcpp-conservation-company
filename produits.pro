QT += core gui widgets sql

CONFIG += c++11
RESOURCES +=
QT += core gui widgets


# Vous pouvez faire échouer la compilation si vous utilisez des APIs obsolètes.
# Pour ce faire, décommentez la ligne suivante.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # désactive toutes les APIs obsolètes avant Qt 6.0.0
TEMPLATE = app
TARGET = mon_application
INCLUDEPATH += .

SOURCES += \
    connection.cpp \
    historymanager.cpp \
    main.cpp \
    mainwindow.cpp \
    produit.cpp \
    statestiques.cpp

HEADERS += \
    connection.h \
    historymanager.h \
    mainwindow.h \
    produit.h \
    statestiques.h


FORMS += \
    mainwindow.ui

TRANSLATIONS += translations/app_fr.ts \
                translations/app_en.ts



# Règles par défaut pour le déploiement.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
