SET(APPS heap)
foreach(app ${APPS})
    add_executable(${app}.app ${app}.c)    
endforeach(app ${APPS})
