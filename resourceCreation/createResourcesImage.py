#!/usr/bin/env python3
#
# create multiple images*.qrc files
# representing the files in images/
#
from typing import List
import glob

numFiles: int = 2
filesHandles = []

for i in range(numFiles):
    filesHandles.append(open("images" + str(i) + ".qrc", "w"))
    print('<!DOCTYPE RCC><RCC version="1.0">', file=filesHandles[i])
    print("<qresource>", file=filesHandles[i])


files: List[str] = glob.glob("images/*")
for i, f in enumerate(sorted(files)):
    if i < 100:
        print("    <file>" + f + "</file>", file=filesHandles[0])
    else:
        print("    <file>" + f + "</file>", file=filesHandles[1])

for i in range(numFiles):
    print("</qresource>", file=filesHandles[i])
    print("</RCC>", file=filesHandles[i])
    filesHandles[i].close()
