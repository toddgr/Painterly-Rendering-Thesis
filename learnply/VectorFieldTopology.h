#pragma once
#include "Polyline.h"
#include "icMatrix.h"
#include "glError.h"
#include "polyhedron.h"

bool isZero(double x);

// Find minimum and maximum coordinate
void findMinMaxField(icVector3& min, icVector3& max);
icVector3 getVector(Quad* q, const icVector3& p);

// Inside quad
bool insideQuad(const Quad* q, const icVector3& p);
Quad* findQuad(const icVector3& y);

// Get streamline
void streamlineFB(POLYLINE& line, const icVector3& seed, const double& step, bool forward = true);
void streamline(POLYLINE& line, const icVector3& seed, const double& step);

// Find all singularities
struct Singularity {  // Verified
	int type = -1;
	icVector3 p;
	icVector3 rgb = icVector3(0.);
	icMatrix2x2 jacobi;
};

void display_singularities();
void extractSingularity();
void classifySingularity();
void extractSeparatrix();

bool sinp2Boundary(icVector3& currPos, const icVector3& min, const icVector3& max);

// Streamline tracing
void streamlineTrace(
	Quad*& nextQuad, icVector3& nextPos, icVector3& nextVec,
	Quad* currQuad, icVector3 currPos, icVector3 currVec, double t,
	const icVector3& min, const icVector3& max);

void streamlineTrace(
	Quad*& nextQuad, Quad* currQuad, icVector3 currPos, icVector3 currVec, double t,
	const icVector3& min, const icVector3& max);