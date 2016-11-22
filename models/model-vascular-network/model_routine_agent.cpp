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

#if HAS_SPAGENT
void ModelRoutine::addSpAgents( const BOOL init, const VIdx& startVIdx, const VIdx& regionSize, const IfGridBoxData<BOOL>& ifGridHabitableBoxData, Vector<VIdx>& v_spAgentVIdx, Vector<SpAgentState>& v_spAgentState, Vector<VReal>& v_spAgentOffset ) {
	/* MODEL START */

	if( init == true ) {
		const S64 numUBs = regionSize[0] * regionSize[1] * regionSize[2];

		for( S32 i = 0 ; i < NUM_CELL_TYPES ; i++ ) {
			S64 numCells = ( S64 )( ( REAL )numUBs * A_CELL_DENSITY_PER_UB[i] );

			for( S64 j = 0 ; j < numCells ; j++ ) {
				VIdx vIdx;
				SpAgentState state;
				VReal vOffset;

				for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
					vIdx[dim] = startVIdx[dim] + ( idx_t )( ( REAL )regionSize[dim] * Util::getModelRand( MODEL_RNG_UNIFORM ) );
					if( vIdx[dim] < startVIdx[dim] ) {
						vIdx[dim] = startVIdx[dim];
					}
					else if( vIdx[dim] >= startVIdx[dim] + regionSize[dim] ) {
						vIdx[dim] = startVIdx[dim] + regionSize[dim] - 1;
					}

					vOffset[dim] = IF_GRID_SPACING * -0.5 + IF_GRID_SPACING * Util::getModelRand( MODEL_RNG_UNIFORM );
					if( vOffset[dim] < IF_GRID_SPACING * -0.5 ) {
						vOffset[dim] = -0.5;
					}
					else if( vOffset[dim] > IF_GRID_SPACING * 0.5 ) {
						vOffset[dim] = 0.5;
					}
				}

				state.setType( i );
				state.setRadius( A_CELL_RADIUS[i] );

				v_spAgentVIdx.push_back( vIdx );
				v_spAgentState.push_back( state );
				v_spAgentOffset.push_back( vOffset );
			}
		}
	}

	/* MODEL END */

	return;
}

void ModelRoutine::spAgentCRNODERHS( const S32 odeNetIdx, const VIdx& vIdx, const SpAgent& spAgent, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox, const Vector<double>& v_y, Vector<double>& v_f ) {
	/* MODEL START */

	ERROR( "unimplemented." );

	/* MODEL END */

	return;
}

void ModelRoutine::updateSpAgentState( const VIdx& vIdx, const AgentJunctionInfo& junctionInfo, const VReal& vOffset, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* [elemIdx] */, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* [elemIdx] */, SpAgentState& state/* INOUT */ ) {
	/* MODEL START */

	/* nothing to do */

	/* MODEL END */

	return;
}

void ModelRoutine::spAgentSecretionBySpAgent( const VIdx& vIdx, const AgentJunctionInfo& junctionInfo, const VReal& vOffset, const AgentMechIntrctData& mechIntrctData, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* [elemIdx] */, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* [elemIdx] */, SpAgentState& state/* INOUT */, Vector<SpAgentState>& v_spAgentState, Vector<VReal>& v_spAgentDisp ) {
	/* MODEL START */

	/* nothing to do */

	/* MODEL END */

	return;
}

void ModelRoutine::updateSpAgentBirthDeath( const VIdx& vIdx, const SpAgent& spAgent, const AgentMechIntrctData& mechIntrctData, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* [elemIdx] */, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* [elemIdx] */, BOOL& divide, BOOL& disappear ) {
	/* MODEL START */

        divide = false;
        disappear = false;

	/* MODEL END */

	return;
}

S32 findNearestInterface(const VReal& vOffset, const VReal& vDir) {
	S32 interface = -1;
	REAL tNearest = 1.5; // at least one t value should be less than sqrt(2)
	for (S32 dim = 0; dim < DIMENSION; dim++) {
		S32 t = ((vDir[dim] > 0 ? 0.5 : -0.5) - vOffset[dim] / IF_GRID_SPACING) / vDir[dim];
		if (t < tNearest) {
			interface = dim;
		}
	}
	return interface;
}

void ModelRoutine::adjustSpAgent( const VIdx& vIdx, const AgentJunctionInfo& junctionInfo, const VReal& vOffset, const AgentMechIntrctData& mechIntrctData, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* [elemIdx] */, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* [elemIdx] */, SpAgentState& state/* INOUT */, VReal& disp ) {
	/* MODEL START */

	VReal fwdDir; // forward direction vector
	VReal bckDir; // backward direction vector
	REAL mag = 0.0;
	for (S32 dim = 0; dim < DIMENSION; dim++) {
		fwdDir[dim] = -0.5 + Util::getModelRand(MODEL_RNG_UNIFORM);
		mag += fwdDir[dim] * fwdDir[dim];
	}
#if REAL_IS_FLOAT
	mag = sqrtf(mag);
#else
	mag = sqrt(mag);
#endif
	for (S32 dim = 0; dim < DIMENSION; dim++) {
		fwdDir[dim] /= mag; // normalize
		bckDir[dim] = -fwdDir[dim];
	}

	S32 fwdInt = findNearestInterface(vOffset, fwdDir); // nearest forward interface
	S32 bckInt = findNearestInterface(vOffset, bckDir); // nearest backward interface

	VIdx fwdOffset; // forward neighbor offset
	VIdx bckOffset; // backward neighbor offset
	for (S32 dim = 0; dim < DIMENSION; dim++) {
		fwdOffset[dim] = dim == fwdInt ? (fwdDir[fwdInt] > 0 ? 1 : -1) : 0;
		bckOffset[dim] = dim == bckInt ? (bckDir[bckInt] > 0 ? 1 : -1) : 0;
	}

	NbrBox<REAL> nbr = v_gridPhiNbrBox[DIFFUSIBLE_ELEM_CHEMOATTRACTANT];

	REAL fwdVal = 0.0;
	REAL bckVal = 0.0;
	if (nbr.getValidFlag(fwdOffset)) {
		fwdVal = nbr.getVal(fwdOffset);
	}
	if (nbr.getValidFlag(bckOffset)) {
		bckVal = nbr.getVal(bckOffset);
	}

	disp = mechIntrctData.force;

	S32 agentType = state.getType();
	REAL chemForce = A_CELL_CHEMOTAXIS_FORCE_STRENGTH[agentType] * (fwdVal - bckVal);
	if (chemForce > 0) {
		for (S32 dim = 0; dim < DIMENSION; dim++) {
			disp[dim] += fwdDir[dim] * chemForce;
		}
	}

	// random motion
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
    disp[dim] += A_CELL_RADIUS[state.getType()] * ( Util::getModelRand( MODEL_RNG_GAUSSIAN ) ) * A_CELL_TEMP[state.getType()];
	}

	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {/* limit the maximum displacement within a single time step */
		if( disp[dim] > IF_GRID_SPACING ) {
			disp[dim] = IF_GRID_SPACING;
		}
		else if( disp[dim] < ( IF_GRID_SPACING * -1.0 ) ) {
			disp[dim] = IF_GRID_SPACING * -1.0;
		}
	}

	/* MODEL END */

	return;
}

void ModelRoutine::divideSpAgent( const VIdx& vIdx, const AgentJunctionInfo& junctionInfo, const VReal& vOffset, const AgentMechIntrctData& mechIntrctData, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* [elemIdx] */, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* [elemIdx] */, SpAgentState& motherState/* INOUT */, VReal& motherDisp, SpAgentState& daughterState, VReal& daughterDisp, Vector<BOOL>& v_junctionDivide, BOOL& motherDaughterLinked, JunctionEnd& motherEnd, JunctionEnd& daughterEnd ) {
	/* MODEL START */

	ERROR( "unimplemented." );
  
	/* MODEL END */

	return;
}
#endif

