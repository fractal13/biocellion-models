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
    { /* AVT: 1 particle in the middle of the partition */
      /* only if we are the middle partition */
      for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
        idx_t mid = Info::getDomainSize(dim) / 2;
        if(!(mid >= startVIdx[dim] && mid < startVIdx[dim] + regionSize[dim])) {
          // we are not the middle region
          return;
        }
      }
      
      VIdx vIdx;
      SpAgentState state;
      VReal vOffset;
      
      for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
        vIdx[dim] = startVIdx[dim] + regionSize[dim]/2;
        vOffset[dim] = 0.0;
      }
      
      state.setType( CELL_TYPE_PROLIFERATING );
      state.setRadius( CELL_RADIUS[CELL_TYPE_PROLIFERATING] );
      state.setModelReal( PROLIFERATING_CELL_REAL_MASS, CELL_MINIMUM_MASS[CELL_TYPE_PROLIFERATING] );
      
      v_spAgentVIdx.push_back( vIdx );
      v_spAgentState.push_back( state );
      v_spAgentOffset.push_back( vOffset );
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

  /* AVT:
   * growing mass at a regular rate right now.
   * TODO: grow based on nurtients, and deplete the nutrient */
  REAL mass = state.getModelReal( PROLIFERATING_CELL_REAL_MASS );
  mass *= CELL_GROWTH_RATE[state.getType()];
  state.setModelReal( PROLIFERATING_CELL_REAL_MASS, mass );
  
  /* mass = volume * density
   * volume = mass/density;
   * Volume = 4/3 PI * r^3
   * r = cbrt((3 Volume) / (4 PI))
   * r = cbrt((3 mass/density) / (4 PI))
   */
  REAL radius = cbrt(3.0 * mass / CELL_DENSITY[state.getType()] / 4.0 / MY_PI);
  state.setRadius(radius);

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

  /* AVT:
   * If the cell has reached twice the minimum mass, then flag it for division. */
  const SpAgentState &state = spAgent.state;
  REAL mass = state.getModelReal( PROLIFERATING_CELL_REAL_MASS );
  if( mass >= 2.0 * CELL_MINIMUM_MASS[CELL_TYPE_PROLIFERATING] ) {
    divide = true;
  }
  else {
    divide = false;
  }
	disappear = false;

	/* MODEL END */

	return;
}

void ModelRoutine::adjustSpAgent( const VIdx& vIdx, const AgentJunctionInfo& junctionInfo, const VReal& vOffset, const AgentMechIntrctData& mechIntrctData, const Vector<NbrBox<REAL> >& v_gridPhiNbrBox/* [elemIdx] */, const Vector<NbrBox<REAL> >& v_gridModelRealNbrBox/* [elemIdx] */, const Vector<NbrBox<S32> >& v_gridModelIntNbrBox/* [elemIdx] */, SpAgentState& state/* INOUT */, VReal& disp ) {
	/* MODEL START */

  /* AVT:
   * Give cell some random motiion
   */
	disp = mechIntrctData.force;
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
    disp[dim] += CELL_RANDOM_MOTION[state.getType()] * state.getRadius() * Util::getModelRand( MODEL_RNG_GAUSSIAN );
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

  /* AVT:
   * Divide a cell into a mother and daughter cell.
   * This is really creating the new daughter cell, and giving it half of the resources of the mother cell.
   * The cells need to be moved away from each other as they split.  The direction is randomly chosen.
   * NOTE: The essence of this code was borrowed from the yeast example.
   */
	daughterDisp = motherDisp = mechIntrctData.force;
	daughterState.setType( motherState.getType() );

  REAL mass = motherState.getModelReal( PROLIFERATING_CELL_REAL_MASS );
  mass /= 2.0;
  REAL radius = cbrt(3.0 * mass / CELL_DENSITY[motherState.getType()] / 4.0 / MY_PI);
	motherState.setRadius( radius );
	daughterState.setRadius( radius );
  motherState.setModelReal( PROLIFERATING_CELL_REAL_MASS, mass );
  daughterState.setModelReal( PROLIFERATING_CELL_REAL_MASS, mass );

  /* divide direction */
  REAL scale = 0.0;
  VReal dir;

  /* generate random unit vector */
  for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
    dir[dim] = Util::getModelRand( MODEL_RNG_UNIFORM ) - 0.5;
    scale += dir[dim] * dir[dim];
  }
  scale = sqrt( scale );
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {
		dir[dim] /= scale;
	}

  /* push each cell 1 radius in divide direction */
	motherDisp += dir * radius;
	daughterDisp -= dir * radius;

  /* limit movement */
	for( S32 dim = 0 ; dim < DIMENSION ; dim++ ) {/* limit the maximum displacement within a single time step */
		if( motherDisp[dim] > IF_GRID_SPACING ) {
			motherDisp[dim] = IF_GRID_SPACING;
		}
		else if( motherDisp[dim] < ( IF_GRID_SPACING * -1.0 ) ) {
			motherDisp[dim] = IF_GRID_SPACING * -1.0;
		}
		if( daughterDisp[dim] > IF_GRID_SPACING ) {
			daughterDisp[dim] = IF_GRID_SPACING;
		}
		else if( daughterDisp[dim] < ( IF_GRID_SPACING * -1.0 ) ) {
			daughterDisp[dim] = IF_GRID_SPACING * -1.0;
		}
	}

  /* no junctions between the two cells */
	v_junctionDivide.clear();
	motherDaughterLinked = false;
  
	/* MODEL END */

	return;
}
#endif

