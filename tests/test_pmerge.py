#!/usr/bin/env python3
import os
import random
import subprocess
import sys

BASE = os.path.dirname(os.path.abspath(__file__))
BIN  = os.path.abspath(os.path.join(BASE, "..", "ex02", "PmergeMe"))

GREEN = "\033[92m"
RED   = "\033[91m"
CYA   = "\033[96m"
DIM   = "\033[2m"
BOLD  = "\033[1m"
RST   = "\033[0m"


def run(args):
    try:
        r = subprocess.run(
            [BIN] + args,
            text=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            timeout=30,
        )
        return r.stdout
    except FileNotFoundError:
        return f"<binary not found: {BIN}>"
    except subprocess.TimeoutExpired:
        return "<timeout>"


def banner(ok):
    return f"{GREEN}✅ PASS{RST}" if ok else f"{RED}❌ FAIL{RST}"


def show_case_small():
    args = ["3", "5", "9", "7", "4"]
    got = run(args)
    lines = [l for l in got.splitlines() if l.strip()]

    expected_before = "Before: 3 5 9 7 4"
    expected_after  = "After: 3 4 5 7 9"

    ok = (
        len(lines) >= 4
        and lines[0].strip() == expected_before
        and lines[1].strip() == expected_after
    )
    print(f"  {BOLD}./PmergeMe 3 5 9 7 4 (Before/After + timings){RST}  {banner(ok)}")
    if ok:
        for l in lines:
            print(f"      {DIM}{l}{RST}")
    else:
        print(f"    {CYA}expected:{RST}")
        print(f"      {GREEN}{expected_before}{RST}")
        print(f"      {GREEN}{expected_after}{RST}")
        print(f"      {GREEN}<two timing lines>{RST}")
        print(f"    {CYA}got:{RST}")
        for l in lines or ["<empty>"]:
            print(f"      {RED}{l}{RST}")
    print()
    return ok


def show_case_3000():
    random.seed(42)
    nums = [str(random.randint(1, 100000)) for _ in range(3000)]
    got = run(nums)
    lines = [l for l in got.splitlines() if l.strip()]

    ok = False
    before = after = []
    if len(lines) >= 2:
        try:
            before = list(map(int, lines[0].split(":", 1)[1].split()))
            after  = list(map(int, lines[1].split(":", 1)[1].split()))
            ok = before == list(map(int, nums)) and after == sorted(before)
        except Exception:
            ok = False

    print(f"  {BOLD}./PmergeMe <3000 random ints> sorted correctly{RST}  {banner(ok)}")
    if ok:
        print(f"      {DIM}Before[:10] = {before[:10]} …{RST}")
        print(f"      {DIM}After [:10] = {after[:10]} …{RST}")
    else:
        print(f"    {CYA}expected:{RST} {GREEN}After == sorted(Before){RST}")
        print(f"    {CYA}got:{RST}     {RED}sequence not sorted or output malformed{RST}")
    print()
    return ok


def show_case_error():
    got = run(["-1", "2"])
    expected = "Error"
    ok = got.strip() == expected
    print(f"  {BOLD}./PmergeMe -1 2{RST}  {banner(ok)}")
    if ok:
        print(f"      {DIM}{got.strip()}{RST}")
    else:
        print(f"    {CYA}expected:{RST}")
        print(f"      {GREEN}{expected}{RST}")
        print(f"    {CYA}got:{RST}")
        for l in got.strip().splitlines() or ["<empty>"]:
            print(f"      {RED}{l}{RST}")
    print()
    return ok


def main():
    print(f"\n{BOLD}{CYA}ex02 / PmergeMe — Ford-Johnson{RST}\n")
    if not os.path.exists(BIN):
        print(f"  {RED}missing binary: {BIN}{RST}\n")
        sys.exit(1)

    total = 0
    passed = 0
    for f in (show_case_small, show_case_3000, show_case_error):
        total += 1
        passed += f()

    color = GREEN if passed == total else RED
    print(f"{BOLD}TOTAL PmergeMe: {color}{passed}/{total}{RST}")
    sys.exit(0 if passed == total else 1)


if __name__ == "__main__":
    main()