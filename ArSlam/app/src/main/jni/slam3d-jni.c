//
//  slam3d-jni.c
//
//  Created by John Miller on 1/22/19.
//  Copyright © 2019 CMU. All rights reserved.
//

#include <jni.h>
#include <particleFilter.h>
#include <malloc.h>

JNIEXPORT jlong JNICALL Java_com_example_arslam_Slam3dJni_particleFilter_newPf(
        JNIEnv* env, jobject thiz) {
    particleFilter_t* pf = (particleFilter_t*)malloc(sizeof(particleFilter_t));
    particleFilter_init(pf);
    return (jlong)pf;
}

JNIEXPORT jlong JNICALL Java_com_example_arslam_Slam3dJni_particleFilter_newBcn(
        JNIEnv* env, jobject thiz) {
    bcn_t* bcn = (bcn_t*)malloc(sizeof(bcn_t));
    particleFilter_addBcn(bcn);
    return (jlong)bcn;
}

JNIEXPORT void JNICALL Java_com_example_arslam_Slam3dJni_particleFilter_freePf(
        JNIEnv* env, jobject thiz, jlong pf) {
    free((particleFilter_t*)pf);
}

JNIEXPORT void JNICALL Java_com_example_arslam_Slam3dJni_particleFilter_freeBcn(
        JNIEnv* env, jobject thiz, jlong bcn) {
    free((bcn_t*)bcn);
}

JNIEXPORT void JNICALL Java_com_example_arslam_Slam3dJni_particleFilter_depositVio(
        JNIEnv* env, jobject thiz, jlong pf, jdouble t, jfloat x, jfloat y, jfloat z, jfloat dist) {
    particleFilter_depositVio((particleFilter_t*)pf, (float)t, (float)x, (float)y, (float)z, (float)dist);
}

JNIEXPORT void JNICALL Java_com_example_arslam_Slam3dJni_particleFilter_depositUwb(
        JNIEnv* env, jobject thiz, jlong* pf, jlong* bcn, jfloat range, jfloat stdRange) {
    particleFilter_depositUwb(pf, bcn, range, stdRange);
}

JNIEXPORT void JNICALL Java_com_example_arslam_Slam3dJni_particleFilter_getTagLoc(
        JNIEnv* env, jobject thiz, const particleFilter_t* pf, double* t, float* x, float* y, float* z, float* theta) {
    particleFilter_getTagLoc(pf, t, x, y, z, theta);
}

JNIEXPORT void JNICALL Java_com_example_arslam_Slam3dJni_particleFilter_getBcnLoc(
        JNIEnv* env, jobject thiz, const particleFilter_t* pf, const bcn_t* bcn, double* t, float* x, float* y, float* z) {
    particleFilter_getBcnLoc(pf, bcn, t, x, y, z);
}
