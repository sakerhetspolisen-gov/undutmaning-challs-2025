#!/usr/bin/env python3
from pathlib import Path
import difflib
import os
import sys

import pynvim

INTERFACE = "0.0.0.0"
PORT = 4711

ROOT = Path("/ctf")

GREEN = "\033[32;1m"
GRAY = "\033[37;2m"
WHITE = "\033[37;1m"
RED = "\033[31;1m"
BLUE = "\033[34;1m"
RESET = "\033[0m"


def gray(s: str, **kwargs):
    print(f"{GRAY}{s}{RESET}", **kwargs)


def white(s: str, **kwargs):
    print(f"{WHITE}{s}{RESET}", **kwargs)


def color_diff(diff):
    for line in diff:
        if line.startswith("+"):
            yield GREEN + line + RESET
        elif line.startswith("-"):
            yield RED + line + RESET
        else:
            yield line


def run_stage(path: Path):
    with open(ROOT / path / "start") as fp:
        start = [l.rstrip('\n') for l in fp.readlines()]

    with open(ROOT / path / "limit") as fp:
        pro, limit = [int(n) for n in fp.read().strip().split(" ")]

    with open(ROOT / path / "want") as fp:
        want = fp.readlines()

    with pynvim.attach("child", argv=["/usr/bin/env", f"nvim", "-n", "--clean", "--embed", "--headless"]) as nvim:
        nvim.current.buffer[:] = start

        gray("start:")
        print("\n".join(start))
        print("")

        gray("want:")
        print("\n".join([l.rstrip('\n') for l in want]))
        print("")

        gray(f"limit: ", end="")
        print(limit)
        if pro != limit:
            gray(f"pro: ", end="")
            print(pro)
        print("")

        print(f"{RED}666>{RESET} ", end="")

        try:
            user_keys = input().rstrip("\n")
        except UnicodeDecodeError as ude:
            print("malformed input :(")
            return False

        # Enforce character limit. But remove the trailing newline.
        if len(user_keys) > limit:
            print("too long :(")
            return False

        keys = nvim.replace_termcodes(user_keys)

        # NOTE: from `:help feedkeys()`
        #  		't'	Handle keys as if typed; otherwise they are handled as
        # if coming from a mapping.  This matters for undo,
        # opening folds, etc.
        nvim.feedkeys(keys, "t", escape_csi=False)

        got = [l + "\n" for l in nvim.current.buffer[:]]

        diff = difflib.unified_diff(
            got,
            want,
            fromfile="start",
            tofile="want",
        )
        print("".join(color_diff(diff)))

    result = got == want
    if result:
        # Enforce character limit. But remove the trailing newline.
        if pro != limit and len(user_keys) <= pro:
            white("Holy shit. You are divine.")

    return result


def get_flag():
    print("undut{qaithe_number_of_the_beast<esc>q666@a:wq}")


def validate(levels):
    for l in levels:
        if not os.path.isdir(f"{ROOT}/levels/{l}"):
            raise ValueError(f"level does not exist: {l}")
        if not os.path.exists(f"{ROOT}/levels/{l}/start"):
            raise ValueError(f"level missing start: {l}")
        if not os.path.exists(f"{ROOT}/levels/{l}/want"):
            raise ValueError(f"level missing want: {l}")
        if not os.path.exists(f"{ROOT}/levels/{l}/limit"):
            raise ValueError(f"level missing limit: {l}")


def start_game():
    levels = [
        "upper",
        "lucky-13",
        "micro-macro",
        "boring",
        "counting",
        "666",
        "json",
        "boring-numbers-juggling",
        "give-me-a-smile",
        "i-am-so-random",
    ]

    # NOTE: helper function to check that all game files are in place.
    # validate(levels)

    print("""\
                        .
    ##############..... ##############
    ##############......##############
      ##########..........##########
      ##########........##########
      ##########.......##########
      ##########.....##########..
      ##########....##########.....
    ..##########..##########.........
  ....##########.#########.............
    ..################JJJ............
      ################.............
      ##############.JJJ.JJJJJJJJJJ
      ############...JJ...JJ..JJ  JJ
      ##########....JJ...JJ..JJ  JJ
      ########......JJJ..JJJ JJJ JJJ
      ######    .........
                  .....
                    .
          """)


    print(f"""
    {RED}Welcome, to the cult of the beast!
    VI VI VI{RESET}

    Insert the keys that correspond to the correct vim motions that would
    transform the start text into the wanted text.

    To help you in your quest here are a few pointers.
    - :helpgrep is king
    - NVIM v0.10.0
    - We utilize `feedkeys` which encodes chars like this: <esc> <cr>
    """)

    print("""
             //                 /*
          ,(/(//,               *###
        ((((((////.             /####%*
     ,/(((((((/////*            /########
    /*///((((((//////.          *#########/
    //////((((((((((((/         *#########/.
    ////////((((((((((((*       *#########/.
    /////////(/(((((((((((      *#########(.
    //////////.,((((((((((/(    *#########(.
    //////////.  /(((((((((((,  *#########(.
    (////////(.    (((((((((((( *#########(.
    (////////(.     ,#((((((((((##########(.
    ((//////((.       /#((((((((##%%######(.
    ((((((((((.         #(((((((####%%##%#(.
    ((((((((((.          ,((((((#####%%%%%(.
     .#(((((((.            (((((#######%%
        /(((((.             .(((#%##%%/*
          ,(((.               /(#%%#
            ./.                 #*



    """)

    for n, level in enumerate(levels):
        # TODO: consider adding hint support
        gray(f"level: ", end="")
        print(f"{level} ({n}/{len(levels)-1})")
        print("")
        if not run_stage(Path("levels") / Path(level)):
            print("Wrong. Begone heathen!")
            return

        print("")
        gray("")
        print("")

    get_flag()


def main():
    start_game()


if __name__ == "__main__":
    main()
