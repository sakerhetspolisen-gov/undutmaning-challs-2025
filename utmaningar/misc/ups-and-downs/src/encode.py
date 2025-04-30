#!/usr/bin/env python
# vim: set sw=2 ts=2 et:
#
# Encode a message in Baudot code (ITA2/US TTY) and
# then 2-AFSK and write it as a .wav to disk.
# Then encode it as ATSC A/52 (AC-3) using ffmpeg.
# Can be played back with mpv or other players.
# 
# Depends on SciPy and ffmpeg. For Ubuntu:
#   apt-get install python3-scipy ffmpeg

from scipy.signal import butter, lfilter
import argparse
import math # should've used numpy to begin with. It is what it is.
import os
import scipy.io.wavfile as wavfile
import struct
import subprocess

# Index into 'LUT' for each symbol table
LTRS = 0
FIGS = 1

#ITA2, US TTY. There is a swedish ITA2 subset with ÅÄÖ but lets keep it simple.
LUT = [
  [
    "\0", "E", "\n", "A", " ", "S", "I", "U",
    "\r", "D", "R", "J", "N", "F", "C", "K",
    "T", "Z", "L", "W", "H", "Y", "P", "Q",
    "O", "B", "G", "", "M", "X", "V", ""
  ],
  [
    "\0",  "3",  "\n",  "-",  " ",  "\a",  "8",  "7",
    "\r",  "$",  "4",  "\"",  ",",  "!",  ":",  "(",
    "5",  "'",  ")",  "2",  "#",  "6",  "0",  "1",
    "9",  "?",  "&",  "",  ".",  "/",  ";",  ""
  ]
]

# Actual ITA2 code of LTRS, FIGS
LTRS_sym = 0b11111
FIGS_sym = 0b11011

def _symbol_lookup(sym, tbl):
  """ do a linear search for a symbol into the LUT"""
  for i, j in enumerate(LUT[tbl]):
    if sym == j:
      return i

def format_message(msg):
  """Returns a (str, arr)-tuple with 'syms' represented as a Unicode string
  of printable characters from the ITA2 alphabet and an array of the
  ITA2 symbols as integers. Symbols not representable as ITA2 will
  be encoded as empty spaces."""
  curr_tbl = LTRS
  osyms = []
  ochrs = []
  msg = msg.upper()
  for sym in msg:
    # Do a lookup in the current symbol table.
    # If the symbol is found, append it to the result.
    val = _symbol_lookup(sym, curr_tbl)
    if val is None:
      # The symbol was not found in the current symbol table, check the
      # next one. Switch symbol tables if found and emit a LTRS/FIGS
      # symbol.
      next_tbl = (curr_tbl + 1) % 2
      val = _symbol_lookup(sym, next_tbl)
      if val is not None:
        curr_tbl = next_tbl
        osyms.append(LTRS_sym if curr_tbl == LTRS else FIGS_sym)
      else:
        # The symbol was found in neither of LTRS, FIGS tables. Emit a space.
        sym = " "
        val = _symbol_lookup(sym, curr_tbl)

    osyms.append(val)
    ochrs.append(sym) 

    # unshift on space
    if sym == " " and curr_tbl != LTRS:
      osyms.append(LTRS_sym)
      curr_tbl = LTRS
  return "".join(ochrs), osyms

def _sample(start, n, f, sample_rate):
  res = []
  i = 0
  for i in range(start, round(start + n)):
    val = math.sin((2*math.pi*f*i)/sample_rate)
    res.append(val)
  return res, i

# NB: At RF, MARK is the higher frequency (usually). However, assuming AFSK and
#     J3E/SSB-SC lower sideband and not a direct FSK approach or upper
#     sideband, the baseband gets mirrored on the lower side of the carrier.
#     So we generate a mirrored baseband signal here. The use of LSB for AFSK
#     RTTY TX appears to be mainly an amateur radio thing.
def to_pcm(syms, baud_rate=45.45, mark_hz=2125, space_hz=2295,
    sample_rate=44100):
  # from idle/mark/1 state:
  # one start/space/0 bit, 5 data bits, 2 stop/mark/1 bits, no parity bit
  # 45.45 baud rate, unit interval 1/45.45=0.022 seconds

  res = [] # samples, keep everything in memory
  curr = 0 # current sample index
  samples_per_unit_interval = round(1/baud_rate * sample_rate)

  # Initial idle (MARK)
  vals, curr =  _sample(curr, 1*sample_rate, mark_hz, sample_rate)
  res += vals
  for sym in syms:
    # start bit (SPACE)
    vals, curr = _sample(curr, samples_per_unit_interval, space_hz, sample_rate)
    res += vals
    # data bits
    for b in bin(sym)[2:].zfill(5)[::-1]:
      freq = space_hz if b == '0' else mark_hz
      vals, curr = _sample(curr, samples_per_unit_interval, freq, sample_rate)
      res += vals
    # stop bits (MARK)
    vals, curr = _sample(curr, samples_per_unit_interval*2, mark_hz, sample_rate)
    res += vals
  # Trailing idle (MARK)
  vals, curr =  _sample(curr, 1*sample_rate, mark_hz, sample_rate)
  res += vals
  return res

def lowpass_filter(samples, critical_freq=3000, sample_rate=44100):
  b, a = butter(7, critical_freq, fs=sample_rate)
  return lfilter(b, a, samples)

def die(msg):
  print(msg, file=sys.stderr)
  exit(1)

if __name__ == "__main__":
  parser = argparse.ArgumentParser(prog="encode.py", description="Encode text to AFSK RTTY")
  parser.add_argument("--sample_rate", type=int, default=44100, help="PCM sample rate")
  parser.add_argument("--baud_rate", type=float, default=45.45, help="RTTY baud rate")
  parser.add_argument("--mark_hz", type=int, default=2125, help="MARK frequency (hz)")
  parser.add_argument("--space_hz", type=int, default=2295, help="SPACE frequency (hz)")
  parser.add_argument("--cutoff", type=int, default=3000, help="Low-pass -3dB frequency (hz)")
  parser.add_argument("--out", type=str, default="challenge.bin", help="output path prefix")
  parser.add_argument('message')
  args = parser.parse_args()

  if len(args.message) == 0:
    die("Message may not be empty")
  if args.message[0] != '\n':
    args.message = '\n' + args.message # By convention

  msg, syms = format_message(args.message)
  samples = to_pcm(syms, args.baud_rate, args.mark_hz, args.space_hz, args.sample_rate)
  samples = lowpass_filter(samples, args.cutoff, args.sample_rate)
  samples *= 2**16/3 # scale values to s16le
  wavfile.write(args.out + ".wav", args.sample_rate, samples.astype("<h"))
  subprocess.run(["ffmpeg", "-y",
      "-i", args.out + ".wav",
      "-f", "ac3",
      args.out])
  os.unlink(args.out + ".wav")
  print("\nRYRYRYRYRYRYRYRYRYRYRYRYRYRY")
  print("RYRYRYRYRYRYRYRYRYRYRYRYRYRY")
  print("RYRYRYRYRYRYRYRYRYRYRYRYRYRY")
  print("RYRYRYRYRYRYRYRYRYRYRYRYRYRY\n")
  print(f"message encoded with ITA2 alphabet, US TTY variant: {msg}")
  print(f"written to {args.out}")
