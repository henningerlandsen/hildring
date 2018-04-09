import os
import ycm_core

database = ycm_core.CompilationDatabase("")

def MatchingSourceFile(filename):
    filename = filename.replace('/include/', '/source/')
    return filename[:-1] + 'cpp'

def IsHeaderFile( filename ):
    extension = os.path.splitext( filename )[ 1 ]
    return extension in [ '.h', '.hxx', '.hpp', '.hh' ]

def FlagsForFile( filename, **kwargs ):
    if IsHeaderFile(filename):
        filename = MatchingSourceFile(filename)
    compilation_info = database.GetCompilationInfoForFile( filename )
    if not compilation_info:
        return None
    return {
            'flags': list(compilation_info.compiler_flags_),
        'include_paths_relative_to_dir': compilation_info.compiler_working_dir_
    }
