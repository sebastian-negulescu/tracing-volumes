workspace 'tracing-volumes'
    configurations { 'Debug', 'Release' }

project 'tracing-volumes'
    kind 'ConsoleApp' -- could change to WindowedApp in the future
    language 'C++'
    targetdir 'bin/%{ cfg.buildcfg }'

    files { '*.h', '*.cc' }
    flags { 'C++11' }

    filter 'configurations:Debug'
        defines { 'DEBUG' }
        symbols 'On'

    filter 'configurations:Release'
        defines { 'NDEBUG' }
        optimize 'On'
