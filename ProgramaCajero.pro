QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    impresion.cpp \
    main.cpp \
    mainwindow.cpp \
    ventanapagocheques.cpp \
    ventanapagotarjeta.cpp \
    ventanatipopago.cpp

HEADERS += \
    #JSON Library
    ../../vcpkg/JSON/include/nlohmann/adl_serializer.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/conversions/from_json.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/conversions/to_chars.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/conversions/to_json.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/exceptions.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/input/binary_reader.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/input/input_adapters.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/input/json_sax.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/input/lexer.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/input/parser.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/input/position_t.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/iterators/internal_iterator.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/iterators/iter_impl.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/iterators/iteration_proxy.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/iterators/iterator_traits.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/iterators/json_reverse_iterator.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/iterators/primitive_iterator.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/json_pointer.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/json_ref.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/macro_scope.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/macro_unscope.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/meta/cpp_future.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/meta/detected.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/meta/is_sax.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/meta/type_traits.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/meta/void_t.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/output/binary_writer.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/output/output_adapters.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/output/serializer.hpp \
    ../../vcpkg/JSON/include/nlohmann/detail/value_t.hpp \
    ../../vcpkg/JSON/include/nlohmann/json.hpp \
    ../../vcpkg/JSON/include/nlohmann/json_fwd.hpp \
    ../../vcpkg/JSON/include/nlohmann/thirdparty/hedley/hedley.hpp \
    ../../vcpkg/JSON/include/nlohmann/thirdparty/hedley/hedley_undef.hpp \
    #Project files
    impresion.h \
    mainwindow.h \
    ventanapagocheques.h \
    ventanapagotarjeta.h \
    ventanatipopago.h

FORMS += \
    mainwindow.ui \
    ventanapagocheques.ui \
    ventanapagotarjeta.ui \
    ventanatipopago.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    generadorCheques.py
