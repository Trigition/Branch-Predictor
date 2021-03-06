#ifndef PREDICTOR21264_H
#define PREDICTOR21264_H
#include <stdio.h>
/*
  Define all your tables and their sizes here.
  All tables must be statically-sized.
  Please don't call malloc () or any of its relatives within your
  program.  The predictor will have a budget, namely (64K + 256) bits
  (not bytes).  That encompasses all storage (all tables, plus GHR, if
  necessary -- but not PC) used for the predictor.  That may not be
  the amount of storage your predictor uses, however -- for example,
  you may implement 2-bit predictors with a table of ints, in which
  case the simulator will use more memory -- that's okay, we're only
  concerned about the memory used by the simulated branch predictor.
*/

//Define Sizes for entries

//Create 10 bit local history size
struct localHistoryEntry {
	unsigned entry : 10;
};

//Create 3 bit saturation for local prediction
struct localPredictEntry {
	unsigned entry : 3;
};

//Create Table for local History
struct localHistoryEntry localHist[1024];


//Create Table for Local Prediction
struct localPredictEntry localPredict[1024];


//Define tables

//12 bit history integer
struct gHistory {
	unsigned history : 12;
} globalHistory;

//Create Global Prediction Table
typedef struct globalTable {
	char table[4096];
} gPredictionTable;

//Create Chooser Prediction table
typedef struct chooserPredictionTable {
	char table[4096];
} chooserTable;


/*
  Initialize the predictor.
*/
void init_predictor ();

/*
  Make a prediction for conditional branch instruction at PC 'pc'.
  Returning true indicates a prediction of taken; returning false
  indicates a prediction of not taken.
*/
bool make_prediction (unsigned int pc);

/*
  Train the predictor the last executed branch at PC 'pc' and with
  outcome 'outcome' (true indicates that the branch was taken, false
  indicates that the branch was not taken).
*/
void train_predictor (unsigned int pc, bool outcome);
void update_chooser(unsigned short index, bool outcome);

bool local_prediction (unsigned short index);
void update_local_predictor (unsigned short index, bool outcome);

bool global_prediction ();
void update_global_predictor (bool outcome);


#endif
