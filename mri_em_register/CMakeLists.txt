project(mri_em_register)

include_directories(${FS_INCLUDE_DIRS})

set(SOURCES
  mri_em_register.c
  findtranslation.cpp
  emregisterutils.cpp
)

add_test_script(NAME mri_em_register_test SCRIPT test_mri_em_register DEPENDS mri_em_register)

add_executable(mri_em_register ${SOURCES})
add_help(mri_em_register mri_em_register.help.xml)
target_link_libraries(mri_em_register utils)
install(TARGETS mri_em_register DESTINATION bin)
