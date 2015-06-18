/**
 * OpenCV wrapper for optical flow input/output and visualization capabilities
 * provided by the Sintel dataset [1] based on imageLib, originally developed
 * as part of StereoMatcher [2].
 * 
 *  [1] D. J. Butler, J. Wulff, G. B. Stanley, M. J. Black.
 *      A naturalistic open source movie for optical flow evaluation.
 *      In European Conference on Computer Vision, pages 611 - 625, 2012.
 *  [2] D. Scharstein, R. Szeliski.
 *      A taxonomy and evaluation of dense two-frame stereo correspondence algorithms.
 *      Technical Report MSR-TR-2001-81, Microsoft Research, 2001.
 * 
 * Copyright (c) 2015, David Stutz
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 * - Neither the name of David Stutz nor the names of its contributors may be
 * used to endorse or promote products derived from this software without specific
 * prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef FLOWIOOPENCVWRAPPER_H
#define	FLOWIOOPENCVWRAPPER_H

#include <opencv2/opencv.hpp>
#include <string>

/**
 * OpenCV wrapper to read and write .flo files as well as visualize flow.
 */
class FlowIOOpenCVWrapper {
public:
    /**
     * Read a .flo file into a cv::Mat with 2 channels of type CV_32F.
     * 
     * @param path
     * @return 
     */
    static cv::Mat read(std::string path);
    /**
     * Write a cv::Mat file with2 channels of type CV_32F to a .flo file.
     * @param path
     * @param flow
     */
    static void write(std::string path, const cv::Mat & flow);
    /**
     * Color the flow and return a 3-channel BGR image.
     * 
     * @param flow
     * @return 
     */
    static cv::Mat flowToColor(const cv::Mat & flow, float max = -1);
    
};

#endif	/* FLOWIOOPENCVWRAPPER_H */

