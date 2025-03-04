#include <shlobj.h>
#include <string>

std::string GetAppDataPath() {
    char path[MAX_PATH];
    if (SHGetFolderPathA(NULL, CSIDL_LOCAL_APPDATA, NULL, 0, path) == S_OK) {
        return std::string(path) + "\\Parqueadero AVL\\data\\";
    }
    return ""; // Manejar error
}