# file variables
source="RunSMP.c++"
unitFile="TestSMP.c++"
inFile="RunSMP.in"
outFile="RunSMP.out"
unit=false

if $unit; then
echo COMPILING UNIT TESTS...
g++ -ansi -pedantic -lcppunit -ldl -Wall $unitFile -o $unitFile.app
if ([ $? == 0 ]); then
echo RUNNING UNIT TESTS...
./$unitFile.app >& TestSMP.out
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
echo CHECKING OUTPUT...; diff -lc RunSMP.out RunSMP.in

echo GENERATING COMMIT LOG...
git log > SMP.log
#echo RUNNING DOXYGEN...; doxygen Doxyfile

#echo UPDATING SPHERE FILE...; cp $source Sphere$source

zip SMP README.txt html/* RunSMP.c++ RunSMP.h RunSMP.in RunSMP.out \
SMP.h SMP.log SphereSMP.c++ TestSMP.c++ TestSMP.out

turnin --submit inbleric cs378pj2 SMP.zip
MULTICOMMENT
fi fi