#ifndef __MODEDEFINITION_H__
#define __MODEDEFINITION_H__


#define __PARALLELMODE__ // parallel mode
#define __TCLMODE__ // tcl mode
#define __RESEARCHMODE__ // research mode, one layer
//#define __TCLAMBDAMODE__ // tcl( \lambda ) mode
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
#define __WRITELOGMODE__ // write log mode
#define __READWEIGHTTABLEMODE__ // read weight table mode
#define __WRITEWEIGHTTABLEMODE__ // write weight table mode
//#define __TESTMOVESPPED__ // test the speed of move table and framework

//#define __MULTISTAGE_MAXTILEMODE__
//#define __MULTISTAGE_TILENUMMODE__

#define STAGENUM 2
#define NOMOVEPENALTY -1000000

#define LEARNING_RATE 0.1
#define iUpperbound 22
#define iLowerBound 15
#define iRange 7
#define PlayRound 1000
#ifdef __RESEARCHMODE__
#define LogPeriod 100
#else
#define LogPeriod 1000
#endif
#define LAMBDA 0.000001
const int upsidedown_table[16] = {3, 2, 1, 0, 7, 6, 5, 4, 11, 10, 9, 8, 15, 14, 13, 12};
const int rotate_table[16] = {3, 7, 11, 15, 2, 6, 10, 14, 1, 5, 9, 13, 0, 4, 8, 12};
#ifdef __MULTISTAGE_MAXTILEMODE__
#if STAGENUM == 1
const int stage_threshold[1] = {iUpperbound};
const int stage_upperbound[1] = { iUpperbound };
#elif STAGENUM == 2
const int stage_threshold[2] = { 10, iUpperbound};
const int stage_upperbound[2] = { 10, iUpperbound };
#elif STAGENUM == 3
const int stage_threshold[3] = { 10, 15, iUpperbound };
const int stage_upperbound[3] = { 10, 15, iUpperbound };
#else 
const int stage_threshold[4] = { 5, 10, 15, iUpperbound };
const int stage_upperbound[4] = { 5, 10, 15, iUpperbound };
#endif
#else 
#if STAGENUM == 1
const int stage_threshold[1] = { 16 };
const int stage_upperbound[1] = { iUpperbound };
#elif STAGENUM == 2
const int stage_threshold[2] = { 8, 16 };
const int stage_upperbound[2] = { iUpperbound, iUpperbound };
#elif STAGENUM == 3
const int stage_threshold[3] = { 6, 11, 16 };
const int stage_upperbound[3] = { iUpperbound, iUpperbound, iUpperbound };
#else 
const int stage_threshold[4] = { 4, 8, 12, 16 };
const int stage_upperbound[4] = { iUpperbound, iUpperbound, iUpperbound, iUpperbound };
#endif
#endif

#endif