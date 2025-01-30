/*
** EPITECH PROJECT, 2024
** DeleteDL
** File description:
** DeleteDL
*/

#ifndef DELETEDL
#define DELETEDL

template <typename T>
struct LibraryDeleter {
    LibraryHandle libraryHandle;

    LibraryDeleter(LibraryHandle handle) : libraryHandle(handle) {}

    void operator()(T* object) {
        if (object) {
            object->shutdown();
            delete object;
        }
        if (libraryHandle) {
            closeLibrary(libraryHandle);
        }
    }
};

#endif /* !DELETEDL */
