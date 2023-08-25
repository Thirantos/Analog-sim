# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-src"
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-build"
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix"
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/tmp"
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src/daw_header_libraries-populate-stamp"
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src"
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src/daw_header_libraries-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src/daw_header_libraries-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_header_libraries-subbuild/daw_header_libraries-populate-prefix/src/daw_header_libraries-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
