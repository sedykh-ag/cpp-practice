import subprocess
import difflib
import sys
import os

failed = False

executable = sys.argv[1]

test_path = sys.argv[2]
ans_path = os.path.splitext(test_path)[0] + ".ans"
out_path = os.path.splitext(test_path)[0] + ".out"

with open(test_path, "r") as test, \
     open(ans_path, "r")  as ans,  \
     open(out_path, "w+") as out:

  subprocess.run([executable], stdin=test, stdout=out)
  out.seek(0)

  if (ans.read() != out.read()):
    ans.seek(0)
    out.seek(0)
    diff = difflib.unified_diff(
      ans.readlines(),
      out.readlines(),
      fromfile="output",
      tofile="expected",
      lineterm="",
    )
    print("\n".join(diff))
    failed = True

os.remove(out_path)
sys.exit(failed)
