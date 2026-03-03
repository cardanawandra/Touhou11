set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86)

# Set compilers to LLVM
set(CMAKE_C_COMPILER clang-cl)
set(CMAKE_CXX_COMPILER clang-cl)
set(CMAKE_LINKER lld-link)
set(CMAKE_AR llvm-lib)
set(CMAKE_ASM_MASM_COMPILER llvm-ml)
set(CMAKE_RC_COMPILER llvm-rc)
set(CMAKE_MT llvm-mt)

set(MSVC_ROOT "/workspace/msvc_env/MSVC")
set(WINSDK_ROOT "/workspace/msvc_env/WinSDK")

# Only apply VFS and Clang-specific flags to C and C++, not ASM
add_compile_options(
    "$<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/clang:-ivfsoverlay>"
    "$<$<OR:$<COMPILE_LANGUAGE:C>,$<COMPILE_LANGUAGE:CXX>>:/clang:/workspace/vfs-overlay.json>"
)

set(CLANG_FLAGS "-m32 -imsvc ${MSVC_ROOT}/include -imsvc ${WINSDK_ROOT}/Include/ucrt -imsvc ${WINSDK_ROOT}/Include/um -imsvc ${WINSDK_ROOT}/Include/shared")

# Use _INIT to prevent infinite flag accumulation
set(CMAKE_C_FLAGS_INIT "${CLANG_FLAGS}")
set(CMAKE_CXX_FLAGS_INIT "${CLANG_FLAGS} /EHsc")

set(LINKER_FLAGS "/machine:X86 /libpath:${MSVC_ROOT}/lib/x86 /libpath:${WINSDK_ROOT}/Lib/ucrt/x86 /libpath:${WINSDK_ROOT}/Lib/um/x86")

set(CMAKE_EXE_LINKER_FLAGS_INIT "${LINKER_FLAGS}")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "${LINKER_FLAGS}")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "${LINKER_FLAGS}")

# Don't try to look for Linux native libraries
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)