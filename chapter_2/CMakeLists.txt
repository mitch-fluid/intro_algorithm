SET(SORT_SRC misc.c sort.c)
SET(APP_LIST selection_sort insertion_sort bubble_sort merge_sort)

foreach(APP ${APP_LIST})
    add_executable(${APP}.app ${APP}.c ${SORT_SRC})
endforeach(APP ${APP_LIST})
