#!/usr/bin/env python3
import os
import shutil
import subprocess
import sys
import tempfile

BASE = os.path.dirname(os.path.abspath(__file__))
ROOT = os.path.abspath(os.path.join(BASE, ".."))
BIN  = os.path.join(ROOT, "ex00", "btc")
DB   = os.path.join(ROOT, "ex00", "data.csv")

GREEN = "\033[92m"
RED   = "\033[91m"
CYA   = "\033[96m"
DIM   = "\033[2m"
BOLD  = "\033[1m"
RST   = "\033[0m"


def run(args, cwd):
    try:
        r = subprocess.run(
            [BIN] + args,
            cwd=cwd,
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
    print(f"\n{BOLD}{CYA}ex00 / btc — Bitcoin Exchange{RST}\n")
    if not os.path.exists(BIN):
        print(f"  {RED}missing binary: {BIN}{RST}\n")
        sys.exit(1)

    passed = total = 0

    with tempfile.TemporaryDirectory() as d:
        if os.path.exists(DB):
            shutil.copy(DB, os.path.join(d, "data.csv"))

        inp = os.path.join(d, "input.txt")

        # ---- example from the subject ----
        with open(inp, "w") as f:
            f.write(
                "date | value\n"
                "2011-01-03 | 3\n"
                "2011-01-03 | 2\n"
                "2011-01-03 | 1\n"
                "2011-01-03 | 1.2\n"
                "2011-01-09 | 1\n"
                "2012-01-11 | -1\n"
                "2001-42-42\n"
                "2012-01-11 | 1\n"
                "2012-01-11 | 2147483648\n"
            )

        expected = (
            "2011-01-03  => 3 = 0.9\n"
            "2011-01-03  => 2 = 0.6\n"
            "2011-01-03  => 1 = 0.3\n"
            "2011-01-03  => 1.2 = 0.36\n"
            "2011-01-09  => 1 = 0.32\n"
            "Error: not a positive number.\n"
            "Error: bad input => 2001-42-42\n"
            "2012-01-11  => 1 = 7.1\n"
            "Error: too large a number."
        )
        got = run([inp], cwd=d)
        total += 1
        passed += show("example input.txt", got, expected)

    # ---- missing file ----
    expected = "Error: could not open file."
    got = run(["/tmp/definitely_missing_xyz.txt"], cwd=ROOT)
    total += 1
    passed += show("missing input file", got, expected)

    color = GREEN if passed == total else RED
    print(f"{BOLD}TOTAL btc: {color}{passed}/{total}{RST}")
    sys.exit(0 if passed == total else 1)


if __name__ == "__main__":
    main()