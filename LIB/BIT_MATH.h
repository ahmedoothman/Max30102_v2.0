#ifndef _BIT_MATH_H
#define _BIT_MATH_H

/*
 * WRT_BIT is to assign 1 or 0 to  a specific bit in a register
 * while maintaining all the bits' value as it is.
 * Steps:
 * 		1- Clear the specific bit you want to write on
 * 		2- Insert the new value you want to write
 */
/*#define WRT_BIT(REG, BIT, VAL) ( (REG) = ( ( (REG) & (~(1<<(BIT))) ) | ( (VAL) << (BIT)  ) ) )*/
#define WRT_BIT(REG, BIT, VAL)  REG = ( (REG) &  (~(1<<BIT)) ) | (VAL<<BIT)
/*
 * SET_BIT is used to assign 1 to a specific bit in a register
 * while maintaining all other bits' value as it is.
 */
#define SET_BIT(REG, BIT)  ( (REG) |=  (1<<(BIT)) )

/*
 * CLR_BIT is used to assign 0 to a specific bit in a register
 * while maintaining all other bits' value as it is.
 */
#define CLR_BIT(REG, BIT)  ( (REG) &= (~(1<<(BIT))) )

/*
 * TOG_BIT is used to flip a specific bit in a register from 0 to 1 or from 1 to 0
 * while maintaining all other bits' value as it is.
 */
#define TOG_BIT(REG, BIT)  ( (REG) ^=  (1<<(BIT)) )

/*
 * GET_BIT is used to read the value of a specific bit in a register
 * while maintaining all the bits' value as it is.
 */
#define GET_BIT(REG, BIT)  ( ( (REG) >> (BIT) ) & 1 )


#endif /* _BIT_MATH_H */
