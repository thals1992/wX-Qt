#!/usr/bin/env python3
#
# developer script to make backup
#
import shutil
import os
import subprocess
from datetime import datetime
from typing import Optional


def runMe(cmd: str):
    p = subprocess.Popen(cmd, stdout=subprocess.PIPE, stderr=subprocess.PIPE, shell=True)
    (output, err) = p.communicate()
    p.wait()
    return output.decode("utf-8"), err.decode("utf-8"), p.returncode


baseDir: Optional[str] = os.environ.get("HOME")
assert baseDir is not None
dropBoxDir: str = baseDir + os.sep + "Dropbox"
tmpPath: str = baseDir + os.sep + "tmp"
#
# change this to app name
#
appName: str = "wxqt"

currentTime = datetime.now()
dateStringForFile: str = currentTime.strftime("%Y_%m_%d_%H_%M")
dateStringForBox: str = currentTime.strftime("%Y_%m_%d_%a").lower()

try:
    os.mkdir(dropBoxDir + os.sep + dateStringForBox)
except Exception:
    pass

baseFile: str = appName + "_" + dateStringForFile + ".zip"
fileName: str = tmpPath + os.sep + baseFile
command: str = "git archive -o " + fileName + " HEAD"

out, err, retCode = runMe(command)
if retCode != 0:
    print(retCode)
    print(out)
    print(err)

shutil.copyfile(fileName, dropBoxDir + os.sep + dateStringForBox + os.sep + baseFile)
