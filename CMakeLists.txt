cmake_minimum_required(VERSION 3.16)
project(ERPSystem VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ERP_SOURCES
    src/main.cpp
    src/Employee.cpp
    src/Department.cpp
    src/Product.cpp
    src/Account.cpp
    src/Customer.cpp
    src/SalesOrder.cpp
    src/PayrollRecord.cpp
    src/HRManager.cpp
    src/InventoryManager.cpp
    src/AccountsManager.cpp
    src/PayrollManager.cpp
    src/SalesManager.cpp
    src/ERPSystem.cpp
)

add_executable(erp ${ERP_SOURCES})

target_include_directories(erp PRIVATE include)

if(MSVC)
    target_compile_options(erp PRIVATE /W4 /permissive-)
else()
    target_compile_options(erp PRIVATE -Wall -Wextra -Wpedantic)
endif()
