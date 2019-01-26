import RPi.GPIO as GPIO
import sys
if len(sys.argv)<2:
  print("Usage: python %s [true|false]"%sys.argv[0])
  exit()
vidport = 27
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.setup(vidport, GPIO.OUT)
GPIO.output(vidport, sys.argv[1][0]!='f')
