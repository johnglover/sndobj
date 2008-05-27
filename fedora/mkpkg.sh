tsocks cvs -z3 -d:pserver:anonymous@sndobj.cvs.sourceforge.net:/cvsroot/sndobj co -P sndobj
rm -r sndobj/msvc6.0
rm -r sndobj/src/asio
rm -r sndobj/src/examples
rm -r sndobj/src/templates
rm -r sndobj/trane
rm -r sndobj/cffi
rm -r sndobj/CVS
rm -r sndobj/java
rm -r sndobj/CVS
rm -r sndobj/python/CVS
rm -r sndobj/python/lib
rm -r sndobj/include/CVS
rm -r sndobj/include/rfftw/CVS
rm sndobj/include/*.h
rm -r sndobj/lib
mv sndobj SndObj-$1
tar cf ~/rpm-build/SOURCES/SndObj-$1.tar SndObj-$1
gzip ~/rpm-build/SOURCES/SndObj-$1.tar
rm -r SndObj-$1

