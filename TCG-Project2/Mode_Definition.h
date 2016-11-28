#ifndef __MODEDEFINITION_H__
#define __MODEDEFINITION_H__

// Use Feature
#define __OUTSIDEAXEMODE__ // out side axe mode
#define __INSIDEAXEMODE__  // in side axe mode
#define __INSIDELINEMODE__ // in side line mode
#define __OUTSIDERECMODE__ // out side rectangle mode
#define __COUNTTILENUMBERMODE__ // count tile number mode
#define __MERGECOUNTMODE__ // total number of mergeable count mode

// read/write log and table
#define __WRITELOGMODE__ // write log mode
#define __READWEIGHTTABLEMODE__ // read weight table mode
#define __WRITEWEIGHTTABLEMODE__ // write weight table mode

// train mode:
//#define __SEARCHMODE__ // Alpha Beta Search
#define __PARALLELMODE__ // parallel mode
#define __TRAIN1113MODE__ // train the table for the rule 1 1 1 3 ( three 1 and one 3)
#ifdef __TRAIN1113MODE__
#define __ADDRANDOMTILE1113MODE__
#define __1113SEARCHMODE__
#define __1113CONDITIONALSEARCHMODE__
#endif
#define __TRAININGMODE__ // training mode
#ifdef __TRAININGMODE__
#define __TCLMODE__ // tcl mode
#endif

// unuse mode:
//#define __BOXATANGLEMODE__ // box at angle mode
//#define __BOXATSIDEMODE__ // box at side mode
//#define __BOXATMIDDLEMODE__ // box at middle mode
//#define __UCTMODE__ // UCT mode 
//#define __TCLAMBDAMODE__ // tcl( \lambda ) mode
//#define __TRAININGSTAGE2MODE__ // training stage 2 mode
//#define __TESTMOVESPPED__ // test the speed of move table and framework
//#define __TRIANGLEMODE__ // triangle mode
//#define __MERGETILEMODE__ // merge tile mode
//#define __OUTSIDELINEMODE__ // out side line mode
//#define __INSIDERECMODE__ // in side rectangle mode



//#define __MULTISTAGE_MAXTILEMODE__
#define __MULTISTAGE_TILENUMMODE__
#define STAGENUM 2

#define NOMOVEPENALTY -1000000
#define LEARNING_RATE 0.1
#define iUpperbound 24
#define iLowerBound 15
#define iRange 7
#define PlayRound 1000
#ifdef __SEARCHMODE__
#define LogPeriod 50
#elif defined __UCTMODE__
#define LogPeriod 50
#else
#define LogPeriod 1000
#endif
#define LAMBDA 0.1
#define SIMULATIONDEEP 0
#define UCTBRANCHNUM 0
#define CUT_OFF_DEPTH 0
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
#endif
#ifdef __MULTISTAGE_TILENUMMODE__
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