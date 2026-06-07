# Obtener los archivos fuente, si existen
file(GLOB SRCS "*.cpp")

if(SRCS)
    add_executable(cpp09_ex00 ${SRCS})

    target_compile_options(cpp09_ex00 PRIVATE -Wall -Wextra -Werror -O2 -fsanitize=address)
    target_link_options(cpp09_ex00 PRIVATE -fsanitize=address)

    target_compile_definitions(cpp09_ex00 PRIVATE
            RESETT="\\033[0m"
            RED="\\033[31m"
            GREEN="\\033[32m"
            YELLOW="\\033[33m"
            BLUE="\\033[34m"
            MAGENTA="\\033[35m"
            CYAN="\\033[36m"
            WHITE="\\033[37m"
    )
endif()