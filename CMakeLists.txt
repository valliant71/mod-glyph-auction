AC_ADD_SCRIPT("${CMAKE_CURRENT_LIST_DIR}/src/GlyphAuctionHouse.cpp")
AC_ADD_SCRIPT_LOADER("GlyphAuction" "${CMAKE_CURRENT_LIST_DIR}/src/loader.h")

AC_ADD_CONFIG_FILE("${CMAKE_CURRENT_LIST_DIR}/conf/GlyphAuction.conf.dist")