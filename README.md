# Dungeon
## Modify CMake list to build project
project(<your_project_name>)  

set(<your_source_list_name>  
    ${PROJECT_SOURCE_DIR}/<folder_name>/main.cpp  
    ${PROJECT_SOURCE_DIR}/<folder_name>/main.h  
    ....and all the files in the project folder  
)  

add_executable(<folder_name> ${<your_source_list_name>})
