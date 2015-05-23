**************************************
*
* Name: Luv Somani
* ID: 14024639
* Date: 2/26/10
* Lab2
*
* Program description: The program finds the quotient and remainder when 
* performing division of two unsigned numbers.
* 
* Pseudo Code:
*int divisor = 6;
*int dividend = 101;
*int quotient;
*int remainder;
*int varA;
*int varB;
*int result;
*
*
*if(divisor == 0){
*	quotient = -1;
*	remainder = -1;
* 	exit;
*}
*varB = 0;
*varA = dividend;
*do{
*		varA = varA - divisor;
*		if(varA - divisor < 0){
*			break;
*		}
*		varB++;
*}
*quotient = varB;
*if (quotient == 0){
*	varB = dividend
*	remainder = varB;
*}
*varA = 0;
*while(varB != 0){
*	varA = varA + divisor;
*	varB--;
*}
*result = varA;
*varA = dividend;
*remainder = varA - result;
*
**************************************

* start of data section

		ORG $B000
DIVIDEND	FCB     101		    The dividend
DIVISOR	FCB       6     	    The divisor.

		ORG $B010
QUOTIENT	RMB       1         The quotient.
REMAINDER	RMB       1         The remainder.
RESULT	RMB	    1		  Reserved for remainder calculation
* define any other variables that you might need here using RMB (not FCB or FDB)


		ORG $C000
		LDAB		DIVISOR 	
		BEQ		ZERO		Branch to ZERO section if divisor is 0
		BRA		ENDZE		Skip ZERO section for other cases
ZERO		LDAA		#$FF		
		STAA		QUOTIENT	Store FF into results
		STAA		REMAINDER
		BRA		DONE		
ENDZE		CLRB
		LDAA		DIVIDEND	Load dividend	
DOUNTL	SUBA		DIVISOR	Subtract divisor from current value
		BLO		ENDDO		Branch if overflow in subtraction
		INCB				Increment quotient counter
		BRA 		DOUNTL	Keep executing do-until loop
ENDDO		STAB		QUOTIENT	Store quotient in memory
IF		BNE		ENDIF		Case when divisor > dividend
		LDAB		DIVIDEND	Store dividend as remainder when quotient is 0.
		STAB		REMAINDER
		BRA		DONE		
ENDIF		CLRA
		LDAB		QUOTIENT
WHILE		BEQ		ENDW		Loop to find quotient * divisor		
		ADDA		DIVISOR
		DECB		
		BRA		WHILE
ENDW		STAA		RESULT	Store quotient * divisor in RESULT
		LDAA		DIVIDEND	
		SUBA		RESULT	Subtract quotient * divisor from dividend
		STAA		REMAINDER	Store the result in remainder
DONE		BRA		DONE		Infinite loop
		END
		