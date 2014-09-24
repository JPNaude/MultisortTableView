QT += core gui sql
greaterThan(QT_MAJOR_VERSION, 4) {
QT += widgets
}

TARGET = MultisortTableView
TEMPLATE = app

SOURCES += \
    main.cpp \
    MultisortTableView.cpp \
    MultisortTreeView.cpp

HEADERS += \
    AlphanumComparer.h \
    MultisortTableView.h \
    MultisortTreeView.h \
    AlphanumSortProxyModel.h \
    ColumnsSorter.h

RESOURCES += \
    resources.qrc
