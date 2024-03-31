cmake_minimum_required(VERSION 3.16)

Project(Linux_test)

enable_language(C CXX)
 
set(SOURCES Linux_main.c 
            Linux_task.c
            Linux_timer.c
            Linux_log.c
            Linux_storage.c)
        

add_executable(Linux_test 
	       ../Platform_Adaptor/Platform_Adaptor.c
               ${SOURCES}) 
              

