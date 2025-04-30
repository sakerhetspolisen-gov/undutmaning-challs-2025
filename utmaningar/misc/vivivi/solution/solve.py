from pwn import *

def win_level(r: remote, keys: str) -> None:
    r.recvuntil(b'666>')
    r.sendline(keys.encode("utf-8"))


def main():
    r = remote("undutmaning-vivivi.chals.io", 443, ssl=True, sni="undutmaning-vivivi.chals.io")

    win_level(r, 'gU$')
    info("Win upper")

    win_level(r, 'g?G')
    info("Win lucky-13")

    win_level(r, 'qa~Wq5@a')
    info("Win micro-macro")

    win_level(r, 'j6>j')
    info("Win boring")

    # First winnable level.
    win_level(r, 'dd<esc>100i0<cr><esc>dd<c-v>ggg<c-a>')
    info("Win counting")

    win_level(r, ':%s#Vim#666#ig<cr>')
    info("Win replace")

    win_level(r, 'qqI{"ip":"<esc>f:i", "port"<esc>A}<esc>j@qq@q')
    info("Win json")

    win_level(r, 'ddGdd:%s#,#<cr>:%norm <<<cr>:sort n<cr>')
    info('Win boring-numbers-juggling')

    win_level(r, ':set paste<cr>i<c-r>=execute("smile")<cr><esc>dd')
    info('Win give-me-a-smile')

    # This trick works on most levels ;)
    #
    # Kudos if you came all the way here, but if you cheated I'm proud of you
    # as well!
    #
    # +1 if you used a reverse shell.
    win_level(r, 'dG:r /c*/l*/i*/w*<cr>kdd')
    info('Win i-am-so-random')

    r.interactive()

if __name__ == "__main__":
    main()
