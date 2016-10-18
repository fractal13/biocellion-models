/*

Copyright © 2013 Battelle Memorial Institute. All Rights Reserved.

NOTICE:  These data were produced by Battelle Memorial Institute (BATTELLE) under Contract No. DE-AC05-76RL01830 with the U.S. Department of Energy (DOE).  For a five year period from May 28, 2013, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, and perform publicly and display publicly, by or on behalf of the Government.  There is provision for the possible extension of the term of this license.  Subsequent to that period or any extension granted, the Government is granted for itself and others acting on its behalf a nonexclusive, paid-up, irrevocable worldwide license in this data to reproduce, prepare derivative works, distribute copies to the public, perform publicly and display publicly, and to permit others to do so.  The specific term of the license can be identified by inquiry made to BATTELLE or DOE.  NEITHER THE UNITED STATES NOR THE UNITED STATES DEPARTMENT OF ENERGY, NOR BATTELLE, NOR ANY OF THEIR EMPLOYEES, MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR USEFULNESS OF ANY DATA, APPARATUS, PRODUCT, OR PROCESS DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY OWNED RIGHTS.

*/

/* DO NOT USE FUNCTIONS THAT ARE NOT THREAD SAFE (e.g. rand(), use Util::getModelRand() instead) */

#include "biocellion.h"

#include "model_routine.h"

/* MODEL START */

#include "model_define.h"

/* MODEL END */

using namespace std;

void ModelRoutine::updateGlobalData( Vector<U8>& v_globalData ) {
	/* MODEL START */

	/* nothing to do */

	/* MODEL END */

	return;
}

void ModelRoutine::updateIfGridSpacing( REAL& ifGridSpacing ) {
	/* MODEL START */

	ifGridSpacing = IF_GRID_SPACING;

	/* MODEL END */

	return;
}

void ModelRoutine::updateOptModelRoutineCallInfo( OptModelRoutineCallInfo& callInfo ) {
	/* MODEL START */

	callInfo.numUpdateIfGridVarPreStateAndGridStepRounds = 0;
	callInfo.numUpdateIfGridVarPostStateAndGridStepRounds = 0;

	/* MODEL END */

	return;
}

void ModelRoutine::updateDomainBdryType( domain_bdry_type_e a_domainBdryType[DIMENSION] ) {
	/* MODEL START */

	CHECK( DIMENSION == 3 );

	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		a_domainBdryType[dim] = DOMAIN_BDRY_TYPE_NONPERIODIC_HARD_WALL;
	}

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEBufferBdryType( pde_buffer_bdry_type_e& pdeBufferBdryType ) {
	/* MODEL START */

	pdeBufferBdryType = PDE_BUFFER_BDRY_TYPE_HARD_WALL;

	/* MODEL END */

	return;
}

void ModelRoutine::updateTimeStepInfo( TimeStepInfo& timeStepInfo ) {
	/* MODEL START */

	timeStepInfo.durationBaselineTimeStep = BASELINE_TIME_STEP;
	timeStepInfo.numStateAndGridTimeStepsPerBaseline = STEPS_PER_BASELINE;

	/* MODEL END */

	return;
}

void ModelRoutine::updateSyncMethod( sync_method_e& extraMechIntrctSyncMethod, sync_method_e& updateIfGridVarSyncMethod/* dummy if both callUpdateIfGridVarPreStateAndGridStep and callUpdateIfGridVarPostStateAndGridStep are set to false in ModelRoutine::updateOptModelRoutineCallInfo */ ) {
	/* MODEL START */

	extraMechIntrctSyncMethod = SYNC_METHOD_OVERWRITE;
	updateIfGridVarSyncMethod = SYNC_METHOD_OVERWRITE;

	/* MODEL END */

	return;
}

#if HAS_SPAGENT
void ModelRoutine::updateSpAgentInfo( Vector<SpAgentInfo>& v_spAgentInfo ) {
	/* MODEL START */

  /* AVT:
   * reserve space in the cell type for mass, etc.
   */
	v_spAgentInfo.resize( NUM_CELL_TYPES );
  S32 i = 0;
	SpAgentInfo info;
  
  info.dMax = CELL_D_MAX[i];
  info.hasBool = false;
  info.numBoolVars = 0;
  info.numStateModelReals = NUM_PROLIFERATING_CELL_REALS;
  info.numStateModelInts = 0;
  info.numExtraMechIntrctModelReals = 0;
  info.numExtraMechIntrctModelInts = 0;
  info.v_odeNetInfo.clear();
  v_spAgentInfo[i] = info;
  

	/* MODEL END */

	return;
}
#endif

void ModelRoutine::updateJunctionEndInfo( Vector<JunctionEndInfo>& v_junctionEndInfo ) {
	/* MODEL START */

	v_junctionEndInfo.clear();

	/* MODEL END */

	return;
}

void ModelRoutine::updatePDEInfo( Vector<PDEInfo>& v_pdeInfo ) {
	/* MODEL START */

	v_pdeInfo.clear();

	/* MODEL END */

	return;
}

void ModelRoutine::updateIfGridModelVarInfo( Vector<IfGridModelVarInfo>& v_ifGridModelRealInfo, Vector<IfGridModelVarInfo>& v_ifGridModelIntInfo ) {
	/* MODEL START */

	v_ifGridModelRealInfo.clear();
	v_ifGridModelIntInfo.clear();

	/* MODEL END */

	return;
}

void ModelRoutine::updateRNGInfo( Vector<RNGInfo>& v_rngInfo ) {
	/* MODEL START */

	v_rngInfo.resize( NUM_MODEL_RNGS );
  
	RNGInfo& rngInfoUniform = v_rngInfo[MODEL_RNG_UNIFORM];

	rngInfoUniform.type = RNG_TYPE_UNIFORM;
	rngInfoUniform.param0 = 0.0;
	rngInfoUniform.param1 = 1.0;
	rngInfoUniform.param2 = 0.0;/* dummy */

	RNGInfo& rngInfoGaussian = v_rngInfo[MODEL_RNG_GAUSSIAN];

	rngInfoGaussian.type = RNG_TYPE_GAUSSIAN;
	rngInfoGaussian.param0 = 0.0;
	rngInfoGaussian.param1 = 1.0;
	rngInfoGaussian.param2 = 0.0;/* dummy */

	/* MODEL END */

	return;
}

void ModelRoutine::updateFileOutputInfo( FileOutputInfo& fileOutputInfo ) {
	/* MODEL START */

	fileOutputInfo.particleOutput = true;
	fileOutputInfo.particleNumExtraOutputVars = 0;
	fileOutputInfo.v_gridPhiOutput.clear();
	fileOutputInfo.v_gridPhiOutputDivideByKappa.clear();

	/* MODEL END */

	return;
}

void ModelRoutine::updateSummaryOutputInfo( SummaryOutputInfo& summaryOutputInfo ) {
	/* MODEL START */

	/* nothing to do */

	/* MODEL END */

	return;
}

void ModelRoutine::init( void ) {
	/* MODEL START */

	/* nothing to do */

	/* MODEL END */

	return;
}

void ModelRoutine::term( void ) {
	/* MODEL START */

	/* nothing to do */

	/* MODEL END */

	return;
}

void ModelRoutine::setPDEBuffer( const VIdx& startVIdx, const VIdx& regionSize, BOOL& isPDEBuffer ) {
	/* MODEL START */

	isPDEBuffer = false;

	/* MODEL END */

	return;
}

void ModelRoutine::setHabitable( const VIdx& vIdx, BOOL& isHabitable ) {
	/* MODEL START */

	isHabitable = true;

	/* MODEL END */

	return;
}

