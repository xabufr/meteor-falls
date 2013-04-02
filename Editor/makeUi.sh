#!/bin/bash

for fic in UI/*.ui
do
	base=$(basename $fic)
	fileBase=${base%.*}
	echo "processing $fic to UI/${fileBase}.py"
	pyside-uic $fic -o UI/${fileBase}.py
done
