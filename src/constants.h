#ifndef CONSTANTS
#define CONSTANTS

#if defined (Q_OS_WIN)
#define DEFAULT_ENCODING "Windows-1251"
#define APP_EXT          ".exe"
#else
#define DEFAULT_ENCODING "UTF-8"
#define APP_EXT          ""
#endif

#define ARC_DIR       "archives"

#define PARAM_ARC       "arc="
#define PARAM_FILE_VW   "file_vw="
#define PARAM_FILE_DL   "file_dl="

// -- types for SimpleFactory class (really simple way to parameterize the factory)
#define ARC_READER_TYPE     ArchiveType_NonCompressed
#define ARC_VIEW_TYPE       ArchiveViewType_Plain
#define FILE_VIEW_TYPE      FileViewType_PlainTxt
#define DIR_VIEW_TYPE       DirectoryViewType_Plain

#endif // CONSTANTS
