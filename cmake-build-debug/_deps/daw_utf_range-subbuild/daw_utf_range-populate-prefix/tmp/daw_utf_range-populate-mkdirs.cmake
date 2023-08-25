# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_utf_range-src"
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_utf_range-build"
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_utf_range-subbuild/daw_utf_range-populate-prefix"
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_utf_range-subbuild/daw_utf_range-populate-prefix/tmp"
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_utf_range-subbuild/daw_utf_range-populate-prefix/src/daw_utf_range-populate-stamp"
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_utf_range-subbuild/daw_utf_range-populate-prefix/src"
  "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_utf_range-subbuild/daw_utf_range-populate-prefix/src/daw_utf_range-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_utf_range-subbuild/daw_utf_range-populate-prefix/src/daw_utf_range-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "C:/Users/thijm/git/Analog-sim/cmake-build-debug/_deps/daw_utf_range-subbuild/daw_utf_range-populate-prefix/src/daw_utf_range-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
