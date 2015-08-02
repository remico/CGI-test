import qbs

CppApplication {
    name: "cgi_app"
    type: "application" // To suppress bundle generation on Mac
    consoleApplication: true

    Properties {
        // on Windows we generally use MSVC
        condition: !qbs.hostOS.contains("windows")
        cpp.cxxFlags: ["-std=c++11"]
    }

    Depends { name: "Qt"; submodules: ["core"] }

    cpp.includePaths: ["src", "src/service", "src/view"]

    files: [
        "src/view/directoryview.h",
        "src/view/archiveview.h",
        "src/view/fileview.h",
        "src/view/plainarchiveview.cpp",
        "src/view/plainarchiveview.h",
        "src/view/plaindirectoryview.cpp",
        "src/view/plaindirectoryview.h",
        "src/view/plaintxtfileview.cpp",
        "src/view/plaintxtfileview.h",
        "src/service/packer.cpp",
        "src/service/packer.h",
        "src/archivereader.h",
        "src/constants.h",
        "src/directory.cpp",
        "src/directory.h",
        "src/fileitem.h",
        "src/main.cpp",
        "src/noncompressedarchivereader.cpp",
        "src/noncompressedarchivereader.h",
        "src/pagemaker.cpp",
        "src/pagemaker.h",
        "src/simplefactory.cpp",
        "src/simplefactory.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: product.type
        qbs.install: true
        qbs.installDir: "cgi-bin"
    }
}

