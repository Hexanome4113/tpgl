project(transformation_d-arbre)

add_executable(transformation_d-arbre main.cpp ../Code/src/XMLNode.cpp)

install(TARGETS transformation_d-arbre RUNTIME DESTINATION bin)
