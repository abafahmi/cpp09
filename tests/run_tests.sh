#!/bin/bash

set -e

echo "================================"
echo "       CPP09 CI TESTS"
echo "================================"

# Go to project root
cd "$(dirname "$0")/.."

echo ""
echo "===== BUILDING ====="

echo "[1/3] Building ex00..."
make -C ex00

echo "[2/3] Building ex01..."
make -C ex01

echo "[3/3] Building ex02..."
make -C ex02

echo ""
echo "===== RUNNING PYTHON TESTS ====="

echo ""
echo "--- BitcoinExchange ---"
python3 tests/test_bitcoin.py

echo ""
echo "--- RPN ---"
python3 tests/test_rpn.py

echo ""
echo "--- PmergeMe ---"
python3 tests/test_pmerge.py

echo "[1/3] fclean ex00..."
make fclean -C ex00

echo "[2/3] fclean ex01..."
make fclean -C ex01

echo "[3/3] fclean ex02..."
make fclean -C ex02

echo ""
echo "================================"
echo "       ALL TESTS PASSED"
echo "================================"