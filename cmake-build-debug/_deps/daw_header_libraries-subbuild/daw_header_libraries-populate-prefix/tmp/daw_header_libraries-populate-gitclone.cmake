# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src/daw_header_libraries-populate-stamp/daw_header_libraries-populate-gitclone-lastrun.txt" AND EXISTS "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src/daw_header_libraries-populate-stamp/daw_header_libraries-populate-gitinfo.txt" AND
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src/daw_header_libraries-populate-stamp/daw_header_libraries-populate-gitclone-lastrun.txt" IS_NEWER_THAN "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src/daw_header_libraries-populate-stamp/daw_header_libraries-populate-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src/daw_header_libraries-populate-stamp/daw_header_libraries-populate-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-src'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            clone --no-checkout --config "advice.detachedHead=false" "https://github.com/beached/header_libraries.git" "daw_header_libraries-src"
    WORKING_DIRECTORY "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://github.com/beached/header_libraries.git'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe" 
          checkout "v2.93.1" --
  WORKING_DIRECTORY "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-src"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: 'v2.93.1'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-src"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-src'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src/daw_header_libraries-populate-stamp/daw_header_libraries-populate-gitinfo.txt" "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src/daw_header_libraries-populate-stamp/daw_header_libraries-populate-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src/daw_header_libraries-populate-stamp/daw_header_libraries-populate-gitclone-lastrun.txt'")
endif()
