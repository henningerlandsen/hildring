import os
import ycm_core


fallback_flags = [ '-x', 'c++', '-Wall', '-Wextra', '-Werror' ]


current_path = os.path.dirname(os.path.realpath(__file__))
database = ycm_core.CompilationDatabase(current_path + '/bin')

def MatchingSourceFile(filename):
    filename = filename.replace('/include/', '/source/')
    return filename[:-1] + 'cpp'

def IsHeaderFile( filename ):
    extension = os.path.splitext( filename )[ 1 ]
    return extension in [ '.h', '.hxx', '.hpp', '.hh' ]

def FlagsForFile( filename, **kwargs ):
    if IsHeaderFile(filename):
        print(filename + " is a header")
        filename = MatchingSourceFile(filename)
        print("Matching source file: " + filename)
    filename = os.path.abspath(filename)
    compilation_info = database.GetCompilationInfoForFile( filename )
    if not compilation_info:
        print("File not found in compilation database: " + filename)
        compilation_info = database.GetCompilationInfoForFile("demo/main.cpp")
    flags = list(compilation_info.compiler_flags_)
    if flags == []:
        print("Using fallback flags")
        flags = fallback_flags
    return {
            'flags': flags,        
            'include_paths_relative_to_dir': compilation_info.compiler_working_dir_
    }

def main():
    print(FlagsForFile("hildring/engine/include/util/LifetimeTokenStack.h"))


if __name__ == '__main__':
    main();
