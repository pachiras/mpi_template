cmake_minimum_required(VERSION 3.9.1)
project(mpi_template)

set(CMAKE_CXX_STANDARD 14)

# -fopenmp flag (enables OpenMP)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -pedantic -lm -O3 -funroll-loops -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

add_executable(mpi_template main.cpp)

# MPI
find_package(MPI REQUIRED)
target_link_libraries(mpi_template PUBLIC MPI::MPI_CXX)

# Enable the testing features.
enable_testing()

# Add the test which is simply run the application.
add_test(NAME run_exe COMMAND ${PROJECT_NAME})
add_test(
    NAME run_mpi
    COMMAND mpirun -hostfile ./hostfile -n 300 ./build/mpi_template > test.log
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
)
