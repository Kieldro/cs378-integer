# file variables
source="RunInteger.c++"
unitFile="TestInteger.c++"
outFile="RunInteger.out"
unit=true

clear
if $unit; then
echo COMPILING UNIT TESTS...
g++ -ansi -pedantic -ldl -Wall $unitFile -lcppunit -o $unitFile.app
if ([ $? == 0 ]); then
echo RUNNING UNIT TESTS...
./$unitFile.app #>& TestInteger.out
#valgrind $unitFile.app >& TestInteger.out
fi fi
		
if ([ $? == 0 ]); then
echo COMPILING PROGRAM...
g++ -ansi -pedantic -Wall $source -o $source.app
if ([ $? == 0 ]); then		# if no errors
echo RUNNING PROGRAM...
./$source.app #>& $outFile
#valgrind ./$source.app < $inFile >& $outFile

#echo CHECKING OUTPUT...; diff -lc RunInteger.out RunInteger.in
<<MULTICOMMENT

echo GENERATING COMMIT LOG...
git log > Integer.log

echo RUNNING DOXYGEN...; doxygen Doxyfile

zip Integer README.txt html/* RunInteger.c++ RunInteger.h RunInteger.in \
RunInteger.out Integer.h Integer.log TestInteger.c++ TestInteger.out

turnin --submit reza cs378pj3 Integer.zip
MULTICOMMENT
fi fi
