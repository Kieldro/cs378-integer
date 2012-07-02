// --------------------------
// projects/integer/Integer.h
// Copyright (C) 2012
// Glenn P. Downing
// --------------------------

#ifndef Integer_h
#define Integer_h
#define DEBUG true

// --------
// includes
#include <cassert>   // assert
#include <iostream>  // ostream
#include <stdexcept> // invalid_argument
#include <string>		// string
#include <vector>		// vector
#include <algorithm>		// reverse()

//using namespace std;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
/*
// print contents of digits
template <typename II, typename OI>
void print(II b, IO e)// const
{
	int size = e-b;
	cerr << "shift_left_digits: " << size << endl;
	for(;b != e; ++b)
		cerr << " " << *b;
	cerr << endl;
}*/

// -----------------
// shift_left_digits
/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift left of the input sequence into the output sequence
 * (s << n) => x
 * complexity O(n)
 */
template <typename II, typename OI>
OI shift_left_digits (II b, II e, int n, OI x) {
	for(;b != e; ++b, ++x)
		*x = *b;

	for(int j = 0; j < n; ++j, ++x)
		*x = 0;

	return x;
}

// ------------------
// shift_right_digits
/**
 * @param b an iterator to the beginning of an input  sequence (inclusive)
 * @param e an iterator to the end       of an input  sequence (exclusive)
 * @param x an iterator to the beginning of an output sequence (inclusive)
 * @return  an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the shift right of the input sequence into the output sequence
 * (s >> n) => x
 * complexity O(2n)
 */
template <typename II, typename OI>
OI shift_right_digits (II b, II e, int n, OI x) {
	vector<int> temp;
	for(; b != e; ++b)
		temp.push_back(*b);
	
	for(int i = 0; i < int(temp.size()-n); ++i, ++x)
		*x = temp[i];

	return x;
}

// -----------
// plus_digits
/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the sum of the two input sequences into the output sequence
 * first number must be >= in length than second?
 * (s1 + s2) => x
 */
template <typename II1, typename II2, typename OI>
OI plus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
	// fills vectors with array of digits in reverse
	vector < int > number1;
	vector < int > number2;
	int length1 = 0;
	int length2 = 0;
	
	for(;b1 != e1; ++b1){
		number1.push_back(*b1);
		++length1;
	}
	reverse(number1.begin(), number1.end() );
	//can readjust to remove need for reverse
	for(;b2 != e2; ++b2){
		number2.push_back(*b2);
		++length2;
	}
	reverse(number2.begin(), number2.end() );
	
	// numbers are now reveresed in vectors
	int maxLen = std::max(length1, length2);
	
	vector < int > output(maxLen);
	int carry = 0;
	int temp = 0;
	
	for(int i = 0; i < maxLen; ++i){
		if(i >= length1 && i < length2){
			temp = number2[i] + carry;
			if(temp > 9){
				carry = 1;
				temp -= 10;
				output[i] = temp;
			}else{
				output[i] = temp;
				carry = 0;
			}
		}else if(i < length1 && i >= length2){
			temp = number1[i] + carry;
			if(temp > 9){
				carry = 1;
				temp -= 10;
				output[i] = temp;
			}else{
				output[i] = temp;
				carry = 0;
			}
		}else{
			temp = number1[i] + number2[i];
			temp += carry;
			if(temp > 9){
				carry = 1;
				temp -= 10;
				output[i] = temp;
			}else{
				output[i] = temp;
				carry = 0;
			}
		}

	}
	
	if(carry == 1){
		output.push_back(1);
		++maxLen;
	}

	for(int j = maxLen-1; j >= 0; --j, ++x)
		*x = output[j];
	
	return x;
}

// ------------
// minus_digits
/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the difference of the two input sequences into the output sequence
 * (s1 - s2) => x
 */
template <typename II1, typename II2, typename OI>
OI minus_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {vector < int > number1;
	vector < int > number2;
	int length1 = 0;
	int length2 = 0;
	
	for(;b1 != e1; ++b1){
		number1.push_back(*b1);
		++length1;
	}
	for(;b2 != e2; ++b2){
		number2.push_back(*b2);
		++length2;
	}
	
	int maxLen = length1;
	int diff = -1;
	int count = 0;
        vector < int > zeroes;
	if(length1 > length2){
		diff = length1 - length2;
		while(count < diff){
			zeroes.push_back(0);
			++count;
		}
                number2.insert( number2.begin(), zeroes.begin(), zeroes.end() );
	}

	vector < int > output(maxLen);
	int lastLocation = -1;
	int val = 0;
	int num1 = 0;
	int num2 = 0;
	int temp = 0;

	for(int i = 0; i < maxLen; ++i){
		if(i == 0){
			num1 = number1[i];
			num2 = number2[i];
			val = num1-num2;
			output[i] = val;
			lastLocation = i;
			continue;
		}
		else{
			num1 = number1[i];
			num2 = number2[i];
			if(num1 > num2){
				val = num1 - num2;
				output[i] = val;
				if(val != 0)
					lastLocation = i;
			}
			else{
				temp = output[lastLocation];
				temp -= 1;
				output[lastLocation] = temp;
				++lastLocation;
				if(lastLocation == i){
					num1 += 10;
					val = num1-num2;
					output[i] = val;
					lastLocation = i;
				}else{
					while(lastLocation < i){
						output[lastLocation] = 9;
						++lastLocation;
					}
					num1+= 10;
					val = num1-num2;
					output[i] = val;
					lastLocation = i;
				}
			}
		}
	}
	
	for(int j = 0; j < maxLen; ++j){
		*x = output[j];
		++x;
	}
	
	return x;
}


// -----------------
// vector_add
vector < int > vector_add(vector < int > number1, vector < int > number2){
	int length1 = (int) number1.size();
        int length2 = (int) number2.size();
        int maxLen = -1;
        if(length1 > length2)
            maxLen = length1;
        else
            maxLen = length2;
	vector < int > output(maxLen);
	int carry = 0;
	int temp = 0;
	for(int i = 0; i < maxLen; ++i){
		if(i >= length1 && i < length2){
			temp = number2[i] + carry;
			if(temp > 9){
				carry = 1;
				temp -= 10;
				output[i] = temp;
			}else{
				output[i] = temp;
				carry = 0;
			}
		}else if(i < length1 && i >= length2){
			temp = number1[i] + carry;
			if(temp > 9){
				carry = 1;
				temp -= 10;
				output[i] = temp;
			}else{
				output[i] = temp;
				carry = 0;
			}
		}else{
			temp = number1[i] + number2[i];
			temp += carry;
			if(temp > 9){
				carry = 1;
				temp -= 10;
				output[i] = temp;
			}
                        else{
				output[i] = temp;
				carry = 0;
			}
		}
               /* cout<<"number1 is:"<<number1[i]<<endl;
                cout<<"number2 is:"<<number2[i]<<endl;
                cout<<"temp is: "<<temp<<endl;
                cout<<"carry is: "<<carry<<endl;*/

	}
	if(carry == 1){
		output.push_back(1);
	}
        return output;
}


// -----------------
// generateTable
// -----------------
vector < vector < int > > generateTable(vector < int > number){
    vector < vector < int > > output(10);
    vector < int > empty(1); 
    empty[0] = 0;
    output[0] = empty;
    output[1] = number;
    vector < int > copy;
    int size = number.size();
    for(int i = 0; i < size; ++i){
        copy.push_back(number[i]);
    }
    for(int j = 2; j <= 9; ++j){
        copy = vector_add(copy, number);
        output[j] = copy;
    }
    return output;
}

// -----------------
// multiplies_digits
/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the product of the two input sequences into the output sequence
 * (s1 * s2) => x
 */
template <typename II1, typename II2, typename OI>
OI multiplies_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
    vector < int > number1;
    vector < int > number2;
    int length1 = 0;
    int length2 = 0;
    for(;b1 != e1; ++b1){
	number1.push_back(*b1);
        ++length1;
    }
    reverse(number1.begin(), number1.end());
    for(;b2 != e2; ++b2){
        number2.push_back(*b2);
        ++length2;
    }
    reverse(number2.begin(), number2.end());
    
    //print();
    vector < vector < int > > table(10);
    table = generateTable(number1);
    int counter = 0;
    vector < int > temp;
    int val = -1;
    vector < int > output(1);
    output[0] = 0;
    int count = 0;
    vector < int > zeroes;
    vector < int > empty(1);
    empty[0] = 0;
    vector < int > copy;
    while (counter < length2){
        val = number2[counter];
        if(val != 0)
            temp = table[val];
        else
            temp = empty;
        if(counter != 0){
       		while(count < counter){
                        zeroes.push_back(0);
                        ++count;
       		 }
	         temp.insert( temp.begin(), zeroes.begin(), zeroes.end() );
	}
        if(counter == (length2-1)){
            if((int)output.size() < 3){
                 if((int)output.size() == 1){
                     if(output[0] == 0){
                         output = temp;
                         break;}
                 }
                 else{
                     if(output[0] == 0 && output[1] == 0){
                        output = temp;
                        break;
                     }
                 }
            }
        }
        if(counter == 0){
            output = temp;
        }
        else{
            output = vector_add(output, temp);
        }
        ++counter;
        temp = empty;
    }
    
    int outputLen = (int) output.size();
    for(int j = outputLen-1; j >= 0; --j){
	*x = output[j];
	++x;
    }	
    return x;
}

// --------------
// isLessThanOrEqual
// this method returns true if number1 is smaller than number2 else it returns false
bool isLessThanOrEqual (vector < int > number1, vector < int > number2){
	int length1 = (int)number1.size();
	int length2 = (int)number2.size();
	if(length1 > length2)
		return false;
	else{
		if(length2 > length1)
			return true;
		else{
			for(int i = 0; i < length1; ++i){
				if(number1[i] == number2[i])
					continue;
				if(number1[i] > number2[i])
					return false;
				else
					return true;
			}
		}
	}
	return true;
}



// --------------
// reverse_and_fix
vector < int > reverse_and_fix(vector < int > number){
    vector < int > output(number.size()-1);
    int count = 0;
    for(int j = (number.size()-2); j >=0; --j){
        output[count] = number[j];
        ++count;
    }
    return output;
}



// --------------
// findVal
int findVal(vector < vector < int > > table, vector < int > number){
    int out = 0;
    bool lessThan = isLessThanOrEqual(table[0], number);
  /*  for(int j = 0; j < (int) table[0].size(); ++j){
        cout<<table[1][j];
    }*/
    for(int i = 0; i < 10; ++i){
        if(lessThan == false){
            out = i-2;
            break;
        }
        lessThan = isLessThanOrEqual(table[i], number);
        if(i == 9 && lessThan == true){
            out = 9;
        }
    }
    return out;
}


// ---------------
// trimLeadingZeroes
vector < int > trimLeadingZeroes(vector < int > number){
    vector < int > output;
    bool foundFirst = false;
    for(int i = 0; i < (int)number.size(); ++i){
        if(foundFirst == false){
            if(number[i] != 0){
                foundFirst = true;
                output.push_back(number[i]);
            }
        }
        else{
            output.push_back(number[i]);
        }
    }
    return output;
}

// --------------
// vector_subtract
vector < int > vector_subtract(vector < int > number1, vector < int > number2){
	int length1 = (int)number1.size();
	int length2 = (int)number2.size();
	int maxLen = length1;
	int diff = -1;
	int count = 0;
        number1 = trimLeadingZeroes(number1);
        number2 = trimLeadingZeroes(number2);
        vector < int > zeroes;
	if(length1 > length2){
		diff = length1 - length2;
		while(count < diff){
			zeroes.push_back(0);
			++count;
		}
        number2.insert( number2.begin(), zeroes.begin(), zeroes.end() );
	}
	vector < int > output(maxLen);
	int lastLocation = -1;
	int val = 0;
	int num1 = 0;
	int num2 = 0;
	int temp = 0;

	for(int i = 0; i < maxLen; ++i){
		if(i == 0){
			num1 = number1[i];
			num2 = number2[i];
			val = num1-num2;
			output[i] = val;
			lastLocation = i;
			continue;
		}
		else{
			num1 = number1[i];
			num2 = number2[i];
			if(num1 > num2){
				val = num1 - num2;
				output[i] = val;
				if(val != 0)
					lastLocation = i;
			}
			else{
				temp = output[lastLocation];
				temp -= 1;
				output[lastLocation] = temp;
				++lastLocation;
				if(lastLocation == i){
					num1 += 10;
					val = num1-num2;
					output[i] = val;
					lastLocation = i;
				}else{
					while(lastLocation < i){
						output[lastLocation] = 9;
						++lastLocation;
					}
					num1+= 10;
					val = num1-num2;
					output[i] = val;
					lastLocation = i;
				}
			}
		}
	}	
	return output;
}


// --------------
// divides_digits
/**
 * @param b  an iterator to the beginning of an input  sequence (inclusive)
 * @param e  an iterator to the end       of an input  sequence (exclusive)
 * @param b2 an iterator to the beginning of an input  sequence (inclusive)
 * @param e2 an iterator to the end       of an input  sequence (exclusive)
 * @param x  an iterator to the beginning of an output sequence (inclusive)
 * @return   an iterator to the end       of an output sequence (exclusive)
 * the sequences are of decimal digits
 * output the division of the two input sequences into the output sequence
 * (s1 / s2) => x
 */
template <typename II1, typename II2, typename OI>
OI divides_digits (II1 b1, II1 e1, II2 b2, II2 e2, OI x) {
	// <your code>
	vector < int > number1;
	vector < int > number2(2);
	int length1 = 0;
	int length2 = 0;
	for(;b1 != e1; ++b1){
	number1.push_back(*b1);
		++length1;
	}
	reverse(number1.begin(), number1.end());
	for(;b2 != e2; ++b2){
		number2.push_back(*b2);
		++length2;
	}
	reverse(number2.begin(), number2.end());
	if(length1 < length2){
        *x = 0;
        return x;
    }
    vector < vector < int > > table(10);
    table = generateTable(number2);
    vector < int > temp;
    for(int i = 0; i <=9; ++i){
        temp = reverse_and_fix(table[i]);
        table[i] = temp;
    }
    reverse(number1.begin(), number1.end());
    reverse(number2.begin(), number2.end());
    number2 = trimLeadingZeroes(number2);
    int count = 0;
    int remainder = 0;
    int counter = 0;
    bool smaller = false;
    vector < int > output;
    vector < int > remainderVector;
    while(count < length1){
        vector < int > temp(1);
        if(count == 0){
            remainder = number1[0];
            temp[0] = remainder;
        }
        else{
            temp[0] = remainderVector[0];
            for(int z = 1; z < (int)remainderVector.size(); ++z){
                temp.push_back(remainderVector[z]);
            }
            temp.push_back(number1[count]);
        }
        smaller = isLessThanOrEqual(number2, temp);
        counter = count+1;
        while(smaller == false && counter < length1){
            temp.push_back(number1[counter]);
            smaller = isLessThanOrEqual(number2, temp);
            ++counter;
        }
        int val = findVal(table, temp);
        output.push_back(val);
        count = counter;
        remainderVector = vector_subtract(temp, table[val]);
        remainderVector = trimLeadingZeroes(remainderVector);
    }
    int outputLen = (int) output.size();
    for(int j = 0; j < outputLen; ++j){
	*x = output[j];
	++x;
    }	
    return x;
}

// -------
// Integer
template < typename T, typename C = vector<T> >
class Integer {
	// -----------
	// operator ==
	/**
	 * friend functions are allowed to look at private class variables/methods.
	 * 
	 */
	friend bool operator == (const Integer& lhs, const Integer& rhs) {
		if(lhs.digits.front() == 0 and rhs.digits.front() == 0){
			assert(lhs.digits.size() == 1);		// no leading zeroes allowed
			return true;
		}
		//if(DEBUG) cerr << "BOOYAKASHA!" << endl;
		
		if(lhs.negative xor rhs.negative)
			return false;
		
		typename C::const_iterator b0 = lhs.digits.begin();
		typename C::const_iterator b1 = rhs.digits.begin();
		typename C::const_iterator e0 = lhs.digits.end();
		typename C::const_iterator e1 = rhs.digits.end();
		
		for(; b0 != e0 and b1 != e1; ++b0, ++b1)
			if(*b0 != *b1)
				return false;
		
		if(b0 == e0 and b1 == e1)
			return true;
		else		// not equal length
			return false;
	}

	// -----------
	// operator !=
	/**
	 * returns true is both Integers are not equal, false otherwise.
	 */
	friend bool operator != (const Integer& lhs, const Integer& rhs) {
		return !(lhs == rhs);}

	// ----------
	// operator <
	/**
	 * returns true if lhs is less than rhs.
	 */
	friend bool operator < (const Integer& lhs, const Integer& rhs) {
		if (lhs.negative and !rhs.negative)
			return true;
		if(!lhs.negative and rhs.negative)
			return false;
		
		if(lhs.digits.size() < rhs.digits.size() )
			return lhs.negative ? !true : true;
		if(lhs.digits.size() > rhs.digits.size() )
			return lhs.negative ? !false : false;
		
		assert(lhs.digits.size() == rhs.digits.size() );
		assert(lhs.negative == rhs.negative);
		
		typename C::const_iterator b0 = lhs.digits.begin();
		typename C::const_iterator b1 = rhs.digits.begin();
		typename C::const_iterator e0 = lhs.digits.end();
		typename C::const_iterator e1 = rhs.digits.end();
		
		for(; b0 != e0 and b1 != e1; ++b0, ++b1)
			if(*b0 < *b1)
				return lhs.negative ? !true : true;
			else if(*b0 > *b1)
				return lhs.negative ? !false : false;
		
		// equal
		return false;
	}

	// -----------
	// operator <=
	/**
	 * returns true if lhs is less than or equal to rhs.
	 */
	friend bool operator <= (const Integer& lhs, const Integer& rhs) {
		return !(rhs < lhs);}

    // ----------
    // operator >
    // ----------

    /**
     * returns true if lhs is greater than rhs.
     */
    friend bool operator > (const Integer& lhs, const Integer& rhs) {
        return (rhs < lhs);}

    // -----------
    // operator >=
    /**
     * returns true if lhs is greater than or equal to rhs.
     */
    friend bool operator >= (const Integer& lhs, const Integer& rhs) {
        return !(lhs < rhs);}

    // ----------
    // operator +
    /**
     * returns an Integer equal to lhs + rhs.
     */
    friend Integer operator + (Integer lhs, const Integer& rhs) {
        return lhs += rhs;}

    // ----------
    // operator -
    /**
     * returns an Integer equal to lhs - rhs.
     */
    friend Integer operator - (Integer lhs, const Integer& rhs) {
        return lhs -= rhs;}

    // ----------
    // operator *
    /**
     * returns an Integer equal to lhs * rhs.
     */
    friend Integer operator * (Integer lhs, const Integer& rhs) {
        return lhs *= rhs;}

    // ----------
    // operator /
    /**
     * returns an Integer equal to lhs / rhs.
     * @throws invalid_argument if (rhs == 0)
     */
    friend Integer operator / (Integer lhs, const Integer& rhs) {
        return lhs /= rhs;}

    // ----------
    // operator %
    /**
     * returns an Integer equal to lhs % rhs.
     * @throws invalid_argument if (rhs <= 0)
     */
    friend Integer operator % (Integer lhs, const Integer& rhs) {
        return lhs %= rhs;}

    // -----------
    // operator <<
    /**
     * returns an Integer equal to lhs digit-shifted right by rhs.
     */
    friend Integer operator << (Integer lhs, int rhs) {
        return lhs <<= rhs;}

	// -----------
	// operator >>
	/**
	 * returns an Integer equal to lhs digit-shifted left by rhs.
	 */
	friend Integer operator >> (Integer lhs, int rhs) {
		return lhs >>= rhs;}

	// -----------
	// operator <<
	/**
	 * Outputs the value of rhs to the ostream object.
	 */
	friend std::ostream& operator << (std::ostream& lhs, const Integer& rhs) {
		typename C::const_iterator b = rhs.digits.begin();
		typename C::const_iterator e = rhs.digits.end();
		
		if(rhs.negative)
			lhs << '-';
		for(; b != e; ++b)
			lhs << *b;

		return lhs;
	}

	// ---
	// pow
	/**
	 * power
	 * does NOT modify the argument
	 * returns an Integer equal to x raised to the power e.
	 * @throws invalid_argument if (x == 0) && (e == 0)
	 * @throws invalid_argument if (e < 0)
	 */
	friend Integer pow (Integer x, int e) {
		return x.pow(e);}

	private:
		// ----
		// data
		C digits;
		bool negative;
	private:
		// -----
		// valid
		// invariant of the constructed object
		// returns true if digits is valid.
		bool valid () const {
			if(digits.size() < 1) return false;

			if(digits.size() > 1 and digits[0] == 0)
				return false;

			if(digits.size() == 1 and digits[0] == 0 and negative)
				return false;

			for(int i = 0; (unsigned)i < digits.size(); ++i)
				if(digits[i] > 9 or digits[i] < 0)
					return false;
			
			return true;
		}

	public:
		// ------------
		// constructors
		/**
		 * 
		 * int value will be <= 2147483647 
		 */
		Integer (int value) {
			negative = false;
			if(value < 0){
				negative = true;
				value *= -1;
			}

			if(value == 0)
				digits.push_back(0);
			else
				for(int i = value%10; value != 0; value/=10, i=value%10)
					digits.push_back(i);
			
			assert(digits.size() <= 10);
			std::reverse(digits.begin(), digits.end() );
			assert(valid() );
		}

		/**
		 * Constuctor taking a string arguement.
		 * @throws invalid_argument if value is not a valid representation of an Integer
		 */
		explicit Integer (const std::string& value) {
			int i = 0;
			negative = false;
			if(value[0] == '-'){
				negative = true;
				++i;
			}
			
			
			for(; unsigned(i) < value.length(); ++i)
				digits.push_back(value[i] - '0');
			//if(DEBUG) cerr << "BOOYAKASHA!" << endl;
			
			if (!valid())
				throw std::invalid_argument("Integer::Integer()");
		}

		// Default copy, destructor, and copy assignment.
		// Integer (const Integer&);
		// ~Integer ();
		// Integer& operator = (const Integer&);
		
		// ----------
		// operator -
		/**
		 * negation does no modify the arguement
		 */
		Integer operator - () const {
			Integer x = *this;
			if(x != 0)
				x.negative = !x.negative;
			
			return x;
		}

		// -----------
		// operator ++
		/**
		* preincrement the operand
		*/
		Integer& operator ++ () {
			*this += 1;
			return *this;
		}

		/**
		* postincrement the operand
		*/
		Integer operator ++ (int) {
			Integer x = *this;
			++(*this);
			return x;
		}

		// -----------
		// operator --
		/**
		* predecrement the operand
		*/
		Integer& operator -- () {
			*this -= 1;
			return *this;
		}

		/**
		* postdecrement the operand
		*/
		Integer operator -- (int) {
			Integer x = *this;
			--(*this);
			return x;
		}

		// -----------
		// operator +=
		/**
		* both numbers must be positive
		*/
		Integer& operator += (const Integer& rhs) {
			typename C::iterator b0 = this->digits.begin();
			typename C::iterator e0 = this->digits.end();
			typename C::const_iterator b1 = rhs.digits.begin();
			typename C::const_iterator e1 = rhs.digits.end();
			typename C::iterator x = this->digits.begin();
			
			//if(this->negative == rhs.negative)
			typename C::iterator p = plus_digits(b0, e0, b1, e1, x);
			this->digits = C(x, p);
			/*else if (rhs.negative)
				*this -= rhs;
			*/
			return *this;
		}

		// -----------
		// operator -=
		/**
		* Assig
		*/
		Integer& operator -= (const Integer& rhs) {
			typename C::iterator b0 = this->digits.begin();
			typename C::iterator e0 = this->digits.end();
			typename C::const_iterator b1 = rhs.digits.begin();
			typename C::const_iterator e1 = rhs.digits.end();
			typename C::iterator x = this->digits.begin();
			
			typename C::iterator p = minus_digits(b0, e0, b1, e1, x);
			this->digits = C(x, p);
			
			return *this;
		}

		// -----------
		// operator *=
		/**
		* <your documentation>
		*/
		Integer& operator *= (const Integer& rhs) {
			typename C::iterator b0 = this->digits.begin();
			typename C::iterator e0 = this->digits.end();
			typename C::const_iterator b1 = rhs.digits.begin();
			typename C::const_iterator e1 = rhs.digits.end();
			//typename C::iterator x = this->digits.begin();
			
			/*
			
			for(int i = 0; unsigned(i) < digits.size(); ++i)
				L.push_back(digits[i] );
			
			cerr << "multdig L: " << L.size() << endl;
			for(vector<int>::iterator it = L.begin(); it != L.end(); ++it)
				cerr << *it;
			cerr << endl;
			*/
			
			//if(DEBUG){cerr << "*this : " << *this << endl;}
			//if(DEBUG) cerr << "rhs   : " << rhs << endl;
			
			C temp(digits.size() + rhs.digits.size() + 1, 0);		// allocated more size than needed
			typename C::iterator x = temp.begin();
			typename C::iterator p = multiplies_digits(b0, e0, b1, e1, x);
			
			digits.assign(x, p);
			
			if (rhs.negative xor this->negative)
				negative = true;
			
			//if(DEBUG) cerr << "result: "<< *this << endl << endl;
			return *this;
		}

		// -----------
		// operator /=
		/**
		* <your documentation>
		* @throws invalid_argument if (rhs == 0)
		*/
		Integer& operator /= (const Integer& rhs) {
			typename C::iterator b0 = this->digits.begin();
			typename C::iterator e0 = this->digits.end();
			typename C::const_iterator b1 = rhs.digits.begin();
			typename C::const_iterator e1 = rhs.digits.end();
			typename C::iterator x = this->digits.begin();
			
			divides_digits(b0, e0, b1, e1, x);
			
			if (rhs.negative xor this->negative)
				negative = true;
			
			//if(DEBUG) cerr << "BOOYAKASHA! " << *this << endl;
			return *this;
		}

		// -----------
		// operator %=
		/**
		* <your documentation>
		* @throws invalid_argument if (rhs <= 0)
		*/
		Integer& operator %= (const Integer& rhs) {
			
			
			
			return *this;
		}

		// ------------
		// operator <<=
		/**
		* <your documentation>
		*/
		Integer& operator <<= (int n) {
			// <your code>
			return *this;}

		// ------------
		// operator >>=
		/**
		* <your documentation>
		*/
		Integer& operator >>= (int n) {
			// <your code>
			return *this;}

		// ---
		// abs
		/**
		* absolute value
		* <your documentation>
		*/
		Integer& abs () {
			negative = false;
			
			return *this;
		}
		
		// ---
		// pow
		/**
		* power
		* <your documentation>
		* @throws invalid_argument if (this == 0) && (e == 0)
		* @throws invalid_argument if (e < 0)
		*/
		Integer& pow (int e) {
			Integer n = *this;
			if(this == 0 && (e == 0) )
				throw std::invalid_argument("Integer::pow(int)");
			
			if(e < 0)
				throw std::invalid_argument("Integer::pow(int)");
			
			Integer result = 1;
//			for (int i = 0; i < e; ++i)
//				result *= *this;
			//cerr << "e is: "<< e << endl;
			//if(DEBUG) cerr << "pow this: " << *this << endl;
			
			//if(11 & 1) cerr << "BOOYAKASHA: "<< endl;
			if(e > 1)
				result = n.pow(e/2); 
			
			if(!(e & 1) )		// even
				result *= result;
			else{		// odd
				result *= result;
				result *= *this;
			}
			
			*this = result;
			return *this;
		}
	};

// ---
// abs
/**
 * absolute value
 * does NOT modify the argument
 * <your documentation>
 */
template <typename T, typename C>
Integer<T, C> abs (Integer<T, C> x) {
	
	
	return x.abs();
}
#endif // Integer_h
