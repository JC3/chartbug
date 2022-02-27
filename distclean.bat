rmdir /S /Q example1\debug example1\release
rmdir /S /Q example2\debug example2\release
del Makefile.* example1\Makefile.* example2\Makefile.*
del .qmake.stash
