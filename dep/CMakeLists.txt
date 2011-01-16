# Copyright (C) 2011 TrioraCore <http://www.trioracore.ru/>
# Copyright (C) 2008-2010 Trinity <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

if(CMAKE_COMPILER_IS_GNUCXX)
  add_definitions(--no-warnings)
elseif( MSVC )
  add_definitions(/W0)
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Linux")
  if(WITH_WORLDSERVER)
    add_subdirectory(jemalloc)
  endif()
endif()

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
  if(WITH_WORLDSERVER OR WITH_AUTHSERVER)
    add_subdirectory(acelite)
    if(USE_MYSQL_SOURCES)
      add_subdirectory(mysqllite)
    endif()
  endif()
  add_subdirectory(bzip2)
  add_subdirectory(zlib)
endif()

if(WITH_WORLDSERVER OR TOOLS)
  add_subdirectory(g3dlite)
endif()

if(WITH_WORLDSERVER)
  add_subdirectory(gsoap)
endif()

if(TOOLS)
  add_subdirectory(libmpq)
endif()
