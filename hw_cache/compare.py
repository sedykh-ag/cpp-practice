"""
This script compares LFU cache with ideal cache,
using LFU tests.
"""

import glob
import os
import subprocess
import sys


ideal_exe = sys.argv[1]
lfu_exe = sys.argv[2]
tests_path = "../lfu/tests/"

def run_exe_on_file(exe, path):
  with open(path, "r") as file:
    result = subprocess.run([exe], stdin=file, capture_output=True, text=True, check=True)
    return result.stdout.strip()

with open("../compare_results.txt", "w") as f:
  for test in glob.glob(os.path.join(tests_path, "*.dat")):
    lfu_out = run_exe_on_file(lfu_exe, test)
    ideal_out = run_exe_on_file(ideal_exe, test)
    f.write(f"test: {test}\t lfu hits: {lfu_out}\t ideal hits: {ideal_out}\t hits diff: {int(ideal_out) - int(lfu_out)}\n")
