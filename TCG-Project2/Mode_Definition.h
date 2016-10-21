#ifndef __MODEDEFINITION_H__
#define __MODEDEFINITION_H__

#define PlayRound 5000000
#define __TCLMODE__ // tcl mode
//#define __BOXATANGLEMODE__ // box at angle mode
//#define __BOXATSIDEMODE__ // box at side mode
//#define __BOXATMIDDLEMODE__ // box at middle mode
#define __OUTSIDEAXEMODE__ // out side axe mode
#define __INSIDEAXEMODE__  // in side axe mode
//#define __OUTSIDELINEMODE__ // out side line mode
#define __INSIDELINEMODE__ // in side line mode
#define __OUTSIDERECMODE__ // out side rectangle mode
//#define __INSIDERECMODE__ // in side rectangle mode
//#define __TRIANGLEMODE__ // triangle mode
#define __TRAININGMODE__ // training mode
#define __COUNTTILENUMBERMODE__ // count tile number mode
//#define __MERGETILEMODE__ // merge tile mode
#define __MERGECOUNTMODE__ // total number of mergeable count mode
//#define __TRAININGSTAGE2MODE__ // training stage 2 mode
//#define __WRITELOGMODE__ // write log mode
//#define __READWEIGHTTABLEMODE__ // read weight table mode
//#define __WRITEWEIGHTTABLEMODE__ // write weight table mode
#define NOMOVEPENALTY -1000000

#define LEARNING_RATE 0.1
#define iUpperbound 22
#define iLowerBound 15
#define iRange 7
const int upsidedown_table[16] = {3, 2, 1, 0, 7, 6, 5, 4, 11, 10, 9, 8, 15, 14, 13, 12};
const int rotate_table[16] = {3, 7, 11, 15, 2, 6, 10, 14, 1, 5, 9, 13, 0, 4, 8, 12};


#endif