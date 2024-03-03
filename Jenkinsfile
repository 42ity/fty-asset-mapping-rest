#!/usr/bin/env groovy

@Library('etn-ipm2-jenkins') _

// run with default parameters
//etn_ipm2_build_and_tests_pipeline_cmake()

// disable test & memcheck (libcxxtools10, libtntnet13)
import params.CmakePipelineParams
CmakePipelineParams parameters = new CmakePipelineParams()
parameters.debugBuildRunTests = false
parameters.debugBuildRunMemcheck = false
etn_ipm2_build_and_tests_pipeline_cmake(parameters)
