#!/bin/sh

ret=0


echo Tests were unsuccessful.

for name in $(find ./tests -type f | grep ".in")
do
	rm comp.tmp
	./prog $name >>comp.tmp
	diff -q ".$(cut -d "." -f2 <<<$name).out" "./comp.tmp"
        if [ $? -eq 1 ];
        then
	ret=1
	echo --------------------------------$name---------------------------------
	cat comp.tmp
	echo --OCEKAVANY VYSTUP-------------------------------VYSTUP PROGRAMU--------
        diff -y ".$(cut -d "." -f2 <<<$name).out" "./comp.tmp"
	echo
	echo -------------------------------------------------------------------------
        fi

done
if [ $ret -ne 0 ]
then
    echo Tests were unsuccessful.
else
    echo Tests were successful.
fi
exit $ret
