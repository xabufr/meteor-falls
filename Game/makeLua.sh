#!/bin/sh

files="LuaInterface.pkg"
outdir="src/Lua/"
cppExt=".cpp"
hExt=".h"
luapp="tolua++"
tmpdir=`pwd`

cd $outdir

for oneFile in $files
do
	fileName=$(basename $oneFile)
	fileBaseName=${fileName%.*}
	 $luapp -o $fileBaseName$cppExt $oneFile
done

cd $tmpdir
