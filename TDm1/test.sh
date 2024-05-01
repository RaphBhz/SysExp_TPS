#!/bin/bash

test1() {
	res1="$(head -c 10 fichierTest.txt)";
	if [ $(cat test1c) == $(res1) ]; then
		echo "test1: ✅ Test passed"
	else
		echo "test1: ❌ Test failed"
	fi
}
