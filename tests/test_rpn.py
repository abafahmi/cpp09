#!/usr/bin/env python3
import os
import subprocess
import sys

BASE = os.path.dirname(os.path.abspath(__file__))
BIN  = os.path.abspath(os.path.join(BASE, "..", "ex01", "RPN"))

GREEN = "\033[92m"
RED   = "\033[91m"
CYA   = "\033[96m"
DIM   = "\033[2m"
BOLD  = "\033[1m"
RST   = "\033[0m"


def run(expr):
    try:
        r = subprocess.run(
            [BIN, expr],
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=10,
        )
        return r.stdout
    except FileNotFoundError:
        return f"<binary not found: {BIN}>"
    except subprocess.TimeoutExpired:
        return "<timeout>"


def show(label, got, expected):
    ok = got.strip() == expected.strip()
    tag = f"{GREEN}✅ PASS{RST}" if ok else f"{RED}❌ FAIL{RST}"
    print(f"  {BOLD}{label}{RST}  {tag}")
    if ok:
        for line in got.strip().splitlines() or ["<empty>"]:
            print(f"      {DIM}{line}{RST}")
    else:
        print(f"    {CYA}expected:{RST}")
        for line in expected.strip().splitlines():
            print(f"      {GREEN}{line}{RST}")
        print(f"    {CYA}got:{RST}")
        for line in got.strip().splitlines() or ["<empty>"]:
            print(f"      {RED}{line}{RST}")
    print()
    return ok


def main():
    print(f"\n{BOLD}{CYA}ex01 / RPN — Reverse Polish Notation{RST}\n")
    if not os.path.exists(BIN):
        print(f"  {RED}missing binary: {BIN}{RST}\n")
        sys.exit(1)

    cases = [
        ("8 9 * 9 - 9 - 9 - 4 - 1 +", "42"),
        ("7 7 * 7 -",                 "42"),
        ("1 2 * 2 / 2 * 2 4 - +",     "0"),
        ("(1 + 1)",                   "Error"),
        ("1 +",                       "Error"),
        ("1 0 /",                     "Error"),
    ]

    passed = total = 0
    for expr, expected in cases:
        got = run(expr)
        total += 1
        passed += show(f'./RPN "{expr}"', got, expected)

    color = GREEN if passed == total else RED
    print(f"{BOLD}TOTAL RPN: {color}{passed}/{total}{RST}")
    sys.exit(0 if passed == total else 1)


if __name__ == "__main__":
    main()