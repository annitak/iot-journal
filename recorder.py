''' recorder.py records audio at 44,100 Hz and saves input to recording.raw '''

import subprocess

raw_input("Press Enter to begin recording")
arecord_task = subprocess.Popen(["arecord", "-q", "-f", "S16_LE", "-r44100", "recording.raw"])
raw_input("Press Enter to end recording")
arecord_task.terminate()
arecord_task.wait()