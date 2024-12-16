cmake_minimum_required(VERSION 3.14)
project(hull_graph_shortest_way)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(hull_graph_shortest_way
    graph.h
    graph.cpp
    random_vertex_generator.h
    vertex.h
    graph_exception.h
    random_vertex_generator.cpp
    graph_serializer.h
    graph_serializer.cpp
    hull_graph.h
    hull_graph.cpp 
	shortest_way_finder.h 
	shortest_way_finder.cpp)

add_executable(shortest_way main.cpp)

target_link_libraries(shortest_way PRIVATE gigagraph)
