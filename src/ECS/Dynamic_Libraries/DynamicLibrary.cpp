/*
** EPITECH PROJECT, 2024
** DynamicLibrary
** File description:
** DynamicLibrary
*/

#include "DynamicLibrary.hpp"

#ifdef _WIN32 // Windows

LibraryHandle loadLibrary(const std::string& libraryPath) {
    HMODULE handle = LoadLibrary(libraryPath.c_str());
    if (!handle) {
        std::cerr << "Failed to load library: " << libraryPath << std::endl;
    }
    return handle;
}

void* getFunction(LibraryHandle library, const std::string& functionName) {
    void* func = (void*)GetProcAddress(library, functionName.c_str());
    if (!func) {
        std::cerr << "Failed to load function: " << functionName << std::endl;
    }
    return func;
}

void closeLibrary(LibraryHandle library) {
    if (library) {
        FreeLibrary(library);
    }
}

#else // Linux/macOS

LibraryHandle loadLibrary(const std::string& libraryPath) {
    void* handle = dlopen(libraryPath.c_str(), RTLD_LAZY);
    if (!handle) {
        std::cerr << "Failed to load library: " << dlerror() << std::endl;
    }
    return handle;
}

void* getFunction(LibraryHandle library, const std::string& functionName) {
    void* func = dlsym(library, functionName.c_str());
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Failed to load function: " << dlsym_error << std::endl;
    }
    return func;
}

void closeLibrary(LibraryHandle library) {
    if (library) {
        dlclose(library);
    }
}

#endif