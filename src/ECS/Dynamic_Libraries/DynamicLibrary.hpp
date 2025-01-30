/*
** EPITECH PROJECT, 2024
** DynamicLibrary
** File description:
** DynamicLibrary
*/

#ifndef DYNAMICLIBRARY
#define DYNAMICLIBRARY

#include <string>
#include <iostream>

// Cross-platform handle for dynamic libraries
#ifdef _WIN32
    #include <windows.h>
    typedef HMODULE LibraryHandle;
#else
    #include <dlfcn.h>
    typedef void* LibraryHandle;
#endif

// Load a dynamic library (DLL on Windows, .so on Linux)
LibraryHandle loadLibrary(const std::string& libraryPath);

// Get a function from the library
void* getFunction(LibraryHandle library, const std::string& functionName);

// Close the loaded dynamic library
void closeLibrary(LibraryHandle library);

#endif /* !DYNAMICLIBRARY */
