# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

# Name of the solution
project ("GPR4400-PhysicsEngine")

# Include sub-projects.
set(EXECUTABLE_CUSTOM_NAME "Vectors")
add_subdirectory ("Vectors")
