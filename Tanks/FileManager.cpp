#include "FileManager.h"
#include <iostream>

std::string FileManager::GetExecutablePath()
{
    char buffer[MAX_PATH];
    DWORD size = GetModuleFileNameA(NULL, buffer, MAX_PATH);
    if (size != 0) {
        // Ensure null-termination of the string
        buffer[size] = '\0';
        return std::string(buffer);
    }
    else {
        // Handle the error or return an empty string
        return "";
    }
}

std::string FileManager::GetImagePath(const std::string& imageName)
{
    std::string executablePath = GetExecutablePath();
    if (!executablePath.empty()) {
        // Find the last occurrence of the directory separator ("\") or ("/")
        size_t found = executablePath.find_last_of("\\/");
        if (found != std::string::npos) {
            // Remove the executable file name and the last directory (two levels up)
            found = executablePath.find_last_of("\\/", found - 1);

            if (found != std::string::npos) {

                found = executablePath.find_last_of("\\/", found - 1);
                return executablePath.substr(0, found + 1) + "textures\\" + imageName;
            }
        }
    }

    return "";
}


