//
//  particleFilter.c
//
//  Created by John Miller on 11/1/18.
//  Copyright © 2018 CMU. All rights reserved.
//

#define _USE_MATH_DEFINES
#include <math.h>
#undef _USE_MATH_DEFINES
#include <stdlib.h>
#include <time.h>

#include "particleFilter.h"

static void _randomNormal2(float* x, float* y);

void particleFilter_init(particleFilter_t* pf)
{
	int i;
	tagParticle_t* p;

	for (i = 0; i < PF_N_TAG; ++i)
	{
		p = &pf[i];
		p->w = 1.0f;
		p->x = 0.0f;
		p->y = 0.0f;
		p->z = 0.0f;
		p->theta = 0.0f;
	}

	srand(time(NULL));
}

void particleFilter_applyVio(particleFilter_t* pf, float dt, float dx, float dy, float dz, float std_xyz, float std_theta)
{
	int i;
	tagParticle_t* p;
	float c, s, p_dx, p_dy;
	float rx, ry, rz, rtheta;

	for (i = 0; i < PF_N_TAG; ++i)
	{
		p = &pf[i];
		c = cosf(p->theta);
		s = sinf(p->theta);
		p_dx = dx * c - dy * s;
		p_dy = dx * s + dy * c;

		_randomNormal2(&rx, &ry);
		_randomNormal2(&rz, &rtheta);

		p->x += p_dx + std_xyz * rx;
		p->y += p_dy + std_xyz * ry;
		p->z += dz + std_xyz *rz;
		p->theta = fmodf(p->theta + std_theta * rtheta), 2 * M_PI);
	}
}

void particleFilter_addBeacon(particleFilter_t* pf, beacon_t* b)
{
	int i, j;
	tagParticle_t* tp;
	beaconParticle_t* bp;
	float f1, f2, g1, g2;

	for (i = 0; i < PF_N_TAG; ++i)
	{
		tp = &pf[i];
		for (j = 0; j < PF_N_BEACON; ++j)
		{
			bp = &b[i][j];
		}
	}
}

static void _randomNormal2(float* x, float* y)
{
	float f = sqrt(-2 * log((float)rand() / RAND_MAX));
	float g = (float)rand() / RAND_MAX * 2 * M_PI;
	*x = f * cosf(g);
	*y = f * sinf(g);
}

//
//- (void)initFromUwb:(UwbMeasurement*)uwb beacon:(Beacon*)beacon
//{
//	double angle = (double)arc4random() / UINT32_MAX * 2 * M_PI;
//	double dist = ((double)arc4random() / UINT32_MAX * 2 - 1) * 3 * uwb.s + uwb.r;
//	
//	double f1 = sqrt(-2 * log((double)arc4random() / UINT32_MAX));
//	double f2 = (double)arc4random() / UINT32_MAX * 2 * M_PI;
//	
//	self.w = 1.0;
//	self.x = beacon.x + dist * cos(angle);
//	self.y = beacon.y + dist * sin(angle);
//	self.theta = (double)arc4random() / UINT32_MAX * 2 * M_PI;
//	self.scale = f1 * cos(f2) * SCALE_STD + 1;
//}
//
//- (void)initFromOther:(Particle*)other withXYBandwidth:(double)hXY withThetaBandwidth:(double)hTheta withScaleBandwidth:(double)hScale
//{
//	double f1 = sqrt(-2 * log((double)arc4random() / UINT32_MAX));
//	double g1 = sqrt(-2 * log((double)arc4random() / UINT32_MAX));
//	double f2 = (double)arc4random() / UINT32_MAX * 2 * M_PI;
//	double g2 = (double)arc4random() / UINT32_MAX * 2 * M_PI;
//	
//	self.w = 1.0;
//	self.x = other.x + f1 * cos(f2) * hXY;
//	self.y = other.y + f1 * sin(f2) * hXY;
//	self.theta = other.theta + g1 * cos(g2) * hTheta;
//	self.scale = other.scale + g1 * sin(g2) * hScale;
//	
//	self.theta = fmod(self.theta, 2 * M_PI);
//}
//
//
//#define NUM_PARTICLES   (10000)
//#define VIO_XY_STD      (1e-3)
//#define VIO_STD_THETA   (1e-6)
//#define VIO_STD_SCALE   (1e-3)
//#define RESAMPLE_THRESH (0.5)
//
//- (id)initWithBcn:(NSArray*)bcn
//{
//	self = [super init];
//	if (self)
//	{
//		self.isInit = NO;
//		self.bcn = bcn;
//		self.loc = [[OutputLocation alloc] initWithT:0 x:0 y:0 z:0 theta:0 s:0];
//		self.lastVio = [[VioMeasurement alloc] initWithT:0 x:0 y:0 z:0];
//		self.particles = [NSMutableArray arrayWithCapacity:NUM_PARTICLES];
//		self.spareParticles = [NSMutableArray arrayWithCapacity:NUM_PARTICLES];
//		self.randArray = [NSMutableArray arrayWithCapacity:NUM_PARTICLES];
//		for (int i = 0; i < NUM_PARTICLES; ++i)
//		{
//			[self.particles addObject:[[Particle alloc] init]];
//			[self.spareParticles addObject:[[Particle alloc] init]];
//			[self.randArray addObject:[NSNumber numberWithDouble:0]];
//		}
//	}
//	return self;
//}
//
//- (void)depositVio:(VioMeasurement*)vio
//{
//	[self applyVio:vio];
//	[self computeLocationWithT:vio.t];
//}
//
//- (void)depositUwb:(UwbMeasurement*)uwb
//{
//	if (!self.isInit)
//		[self initializeParticlesFromUwb:uwb];
//	else
//		[self applyUwb:uwb];
//	
//	[self resampleParticles];
//	[self computeLocationWithT:uwb.t];
//}
//
//- (void)applyUwb:(UwbMeasurement*)uwb
//{
//	Beacon* b = self.bcn[uwb.i];
//	for (Particle* p in self.particles)
//		if (fabs(hypot(p.x - b.x, p.y - b.y) - uwb.r) > 3 * uwb.s)
//			p.w *= 0.5;
//}
//
//- (void)initializeParticlesFromUwb:(UwbMeasurement*)uwb
//{
//	for (Particle* p in self.particles)
//		[p initFromUwb:uwb beacon:self.bcn[uwb.i]];
//	
//	self.isInit = YES;
//}
//
//- (void)computeLocationWithT:(double)t
//{
//	if (!self.isInit)
//		return;
//	
//	double wsum = 0;
//	double xsum = 0;
//	double ysum = 0;
//	double csum = 0;
//	double ssum = 0;
//	for (Particle* p in self.particles)
//	{
//		double w = p.w;
//		wsum += w;
//		xsum += w * p.x;
//		ysum += w * p.y;
//		csum += w * cos(p.theta);
//		ssum += w * sin(p.theta);
//	}
//	self.loc.t = t;
//	self.loc.x = xsum / wsum;
//	self.loc.y = ysum / wsum;
//	self.loc.z = self.lastVio.z;
//	self.loc.theta = atan2(ssum, csum);
//	
//	double dsum = 0;
//	for (Particle* p in self.particles)
//	{
//		double dx = p.x - self.loc.x;
//		double dy = p.y - self.loc.y;
//		dsum += p.w * (dx * dx + dy * dy);
//	}
//	self.loc.s = sqrt(dsum / wsum);
//}
//
//- (void)resampleParticles
//{
//	double s = 0;
//	double ss = 0;
//	double csum = 0;
//	double ssum = 0;
//	double scaleSum = 0;
//	double weightCdf[NUM_PARTICLES];
//	for (int i = 0; i < NUM_PARTICLES; ++i)
//	{
//		Particle* p = self.particles[i];
//		double w = p.w;
//		s += w;
//		ss += w * w;
//		csum += w * cos(p.theta);
//		ssum += w * sin(p.theta);
//		scaleSum += w * p.scale;
//		weightCdf[i] = s;
//	}
//	double ess = s * s / ss;
//	
//	if (ess / NUM_PARTICLES < RESAMPLE_THRESH)
//	{
//		csum /= s;
//		ssum /= s;
//		scaleSum /= s;
//		
//		double scaleDev = 0;
//		for (int i = 0; i < NUM_PARTICLES; ++i)
//		{
//			Particle* p = self.particles[i];
//			self.randArray[i] = [NSNumber numberWithDouble:(double)arc4random() / UINT32_MAX * s];
//			scaleDev += p.w * (p.scale - scaleSum) * (p.scale - scaleSum);
//		}
//		NSArray* randCdf = [self.randArray sortedArrayUsingSelector:@selector(compare:)];
//		scaleDev /= s;
//		
//		double hXY = 0.1;
//		double hTheta = sqrt(-log(csum * csum + ssum * ssum) / ess);
//		double hScale = sqrt(scaleDev / sqrt(ess));
//		
//		int i = 0;
//		int j = 0;
//		int k = 0;
//		while (k < NUM_PARTICLES)
//		{
//			while (k < NUM_PARTICLES && [randCdf[i] doubleValue] < weightCdf[j])
//			{
//				[self.spareParticles[k++] initFromOther:self.particles[j]
//										withXYBandwidth:hXY
//									 withThetaBandwidth:hTheta
//									 withScaleBandwidth:hScale];
//				++i;
//			}
//			++j;
//		}
//		
//		NSMutableArray* tmp = self.particles;
//		self.particles = self.spareParticles;
//		self.spareParticles = tmp;
//	}
//	else
//	{
//		double m = s / NUM_PARTICLES;
//		for (Particle* p in self.particles)
//			p.w /= m;
//	}
//}
