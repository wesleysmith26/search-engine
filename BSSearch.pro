TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    documentparser.cpp

HEADERS += \
    indexing/common_lang_constants.h \
    indexing/string_util.h \
    stemming/english_stem.h \
    stemming/stemming.h \
    utilities/debug_logic.h \
    utilities/safe_math.h \
    utilities/utilities.h \
    rapidxml/rapidxml.hpp \
    rapidxml/rapidxml_utils.hpp \
    documentparser.h \