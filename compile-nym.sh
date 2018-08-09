g++ -std=c++17 nym.cpp -o nym 2> debug-message.txt
if [ -s debug-message.txt ]; then
	less debug-message.txt
	echo "errors found"
fi
