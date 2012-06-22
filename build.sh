# file variables
source="RunInteger.c++"
unitFile="TestInteger.c++"
inFile="RunInteger.in"
outFile="RunInteger.out"
unit=false

if $unit; then
echo COMPILING UNIT TESTS...
g++ -ansi -pedantic -lcppunit -ldl -Wall $unitFile -o $unitFile.app
if ([ $? == 0 ]); then
echo RUNNING UNIT TESTS...
./$unitFile.app #>& TestInteger.out
#valgrind $unitFile.app >& TestSMP.out
fi fi
		
if ([ $? == 0 ]); then
echo COMPILING PROGRAM...
g++ -ansi -pedantic -Wall $source -o $source.app
if ([ $? == 0 ]); then		# if no errors
echo RUNNING PROGRAM...
./$source.app < $inFile #>& $outFile
#valgrind ./$source.app < $inFile >& $outFile
<<MULTICOMMENT
echo CHECKING OUTPUT...; diff -lc RunInteger.out RunInteger.in

echo GENERATING COMMIT LOG...
git log > Integer.log
#echo RUNNING DOXYGEN...; doxygen Doxyfile

#echo UPDATING SPHERE FILE...; cp $source Sphere$source

zip Integer README.txt html/* RunInteger.c++ RunInteger.h RunInteger.in \
RunInteger.out Integer.h Integer.log \
SphereInteger.c++ TestInteger.c++ TestInteger.out

turnin --submit reza cs378pj3 Integer.zip
MULTICOMMENT
fi fi