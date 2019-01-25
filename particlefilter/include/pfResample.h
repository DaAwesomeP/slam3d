//
//  pfResample.h
//
//  Created by John Miller on 1/11/19.
//  Copyright © 2019 CMU. All rights reserved.
//

#ifndef _PFRESAMPLE_H
#define _PFRESAMPLE_H

#include "particleFilter.h"

#ifdef __cplusplus
extern "C" {
#endif
    
    void pfResample_resample(tag_t* tag, bcn_t* bcn, float range, float stdRange, bcn_t** allBcns, int numBcns);
    
#ifdef __cplusplus
} // extern "C"
#endif
    
#endif
