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
#include "flowIOOpenCVWrapper.h"
#include "imageLib.h" // Important to include this before flowIO.h
#include "flowIO.h"
#include "colorcode.h"
#include "motiontocolor.h"

cv::Mat FlowIOOpenCVWrapper::read(std::string path) {
    
    CFloatImage flow;
    ReadFlowFile(flow, path.c_str());
    
    int rows = flow.Shape().height;
    int cols = flow.Shape().width;
    
    assert(rows > 0);
    assert(cols > 0);
    assert(flow.Shape().nBands == 2);
    
    cv::Mat matFlow(rows, cols, CV_32FC2, cv::Scalar(0, 0));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matFlow.at<cv::Vec2f>(i, j)[0] = flow.Pixel(j, i, 0);
            matFlow.at<cv::Vec2f>(i, j)[1] = flow.Pixel(j, i, 1);
        }
    }
    
    return matFlow;
}

void FlowIOOpenCVWrapper::write(std::string path, const cv::Mat & flow) {
    assert(flow.channels() == 2);
    assert(flow.type() == CV_32FC2);
    
    int rows = flow.rows;
    int cols = flow.cols;
    
    CFloatImage cFlow(cols, rows, 2);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cFlow.Pixel(j, i, 0) = flow.at<cv::Vec2f>(i, j)[0];
            cFlow.Pixel(j, i, 1) = flow.at<cv::Vec2f>(i, j)[1];
        }
    }
    
    WriteFlowFile(cFlow, path.c_str());
}

cv::Mat FlowIOOpenCVWrapper::flowToColor(const cv::Mat & flow, float max) {
    assert(flow.channels() == 2);
    // assert(flow.type() == CV_32F);
    
    int rows = flow.rows;
    int cols = flow.cols;
    
    CFloatImage cFlow(cols, rows, 2);
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cFlow.Pixel(j, i, 0) = flow.at<cv::Vec2f>(i, j)[0];
            cFlow.Pixel(j, i, 1) = flow.at<cv::Vec2f>(i, j)[1];
        }
    }
    
    CByteImage cImage;
    MotionToColor(cFlow, cImage, max);
    
    assert(cImage.Shape().height == rows);
    assert(cImage.Shape().width == cols);
    assert(cImage.Shape().nBands == 3);
    
    cv::Mat image(rows, cols, CV_8UC3, cv::Scalar(0, 0, 0));
    
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            image.at<cv::Vec3b>(i, j)[0] = cImage.Pixel(j, i, 0);
            image.at<cv::Vec3b>(i, j)[1] = cImage.Pixel(j, i, 1);
            image.at<cv::Vec3b>(i, j)[2] = cImage.Pixel(j, i, 2);
        }
    }
    
    // cv::cvtColor(image, image, CV_HSV2BGR);
    
    return image;
}
