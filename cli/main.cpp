/**
 * Example for flow reading and visualization. The command line tool converts all
 * .flo files in the given directory to .txt files (stored using cv::FileStorage)
 * and creates visualizations as .png images.
 * 
 * Usage:
 * $ ./cli/cli --help
 * Allowed options:
 *   --help                produce help message
 *   --input-dir arg       input directory
 *   --output-dir arg      output directory
 *   --vis-dir arg         visualize results in a separate directory
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
#include <cstdlib>
#include <vector>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include "flowIOOpenCVWrapper.h"

std::multimap<std::string, boost::filesystem::path> readDirectory(boost::filesystem::path directory, 
        std::vector<std::string> extensions) {
    
    assert(boost::filesystem::is_directory(directory));
    assert(!extensions.empty());
    
    std::multimap<std::string, boost::filesystem::path> files;
    boost::filesystem::directory_iterator end;
    
    for (boost::filesystem::directory_iterator it(directory); it != end; ++it) {
        
        // Check extensions.
        bool correct = false;
        for (std::vector<std::string>::iterator ex = extensions.begin(); 
                ex != extensions.end(); ++ex) {
            
            if (*ex == it->path().extension().string()) {
                correct = true;
            }
        }
        
        if (correct) {
            files.insert(std::multimap<std::string, boost::filesystem::path>::value_type(it->path().string(), it->path()));
        }
    }
    
    return files;
}

int writeMat(boost::filesystem::path file, const cv::Mat& mat) {
    assert(mat.rows > 0 && mat.cols > 0);
    
    cv::FileStorage fs(file.string(), cv::FileStorage::WRITE);
    fs << "mat" << mat;
    
    fs.release();
    return mat.rows;
}

int main(int argc, char** argv) {

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("help", "produce help message")
        ("input-dir",  boost::program_options::value<std::string>(), "input directory")
        ("output-dir", boost::program_options::value<std::string>(), "output directory")
        ("vis-dir", boost::program_options::value<std::string>()->default_value(""), "visualize results in a separate directory");

    boost::program_options::positional_options_description positionals;
    positionals.add("input-dir", 1);
    positionals.add("output-dir", 1);
    
    boost::program_options::variables_map parameters;
    boost::program_options::store(boost::program_options::command_line_parser(argc, argv).options(desc).positional(positionals).run(), parameters);
    boost::program_options::notify(parameters);

    if (parameters.find("help") != parameters.end()) {
        std::cout << desc << std::endl;
        return 1;
    }
    
    boost::filesystem::path in_dir(parameters["input-dir"].as<std::string>());
    if (!boost::filesystem::is_directory(in_dir)) {
        std::cout << "Input directory does not exist." << std::endl;
        return 1;
    }
    
    boost::filesystem::path out_dir(parameters["output-dir"].as<std::string>());
    if (!boost::filesystem::is_directory(out_dir)) {
        boost::filesystem::create_directories(out_dir);
    }
    
    bool visualize = false;
    boost::filesystem::path vis_dir(parameters["vis-dir"].as<std::string>());
    
    if (!vis_dir.empty()) {
        if (!boost::filesystem::is_directory(vis_dir)) {
            boost::filesystem::create_directories(vis_dir);
        }
        
        visualize = true;
    }
    
    std::vector<std::string> extension;
    extension.push_back(".flo");
    
    std::multimap<std::string, boost::filesystem::path> frames = readDirectory(in_dir, extension);
    assert(frames.size() > 0);
    
    for (std::multimap<std::string, boost::filesystem::path>::iterator it = frames.begin(); 
            it != frames.end(); it++) {
        // std::cout << "Converting flow " << it->second.string() << "." << std::endl;
        
        // Read .flo file.
        cv::Mat flow = FlowIOOpenCVWrapper::read(it->second.string());
        
        boost::filesystem::path txt_path = out_dir / it->second.filename();
        writeMat(txt_path.string() + ".txt", flow);
        
        if (visualize) {
            cv::Mat image = FlowIOOpenCVWrapper::flowToColor(flow);
            
            boost::filesystem::path image_path = vis_dir / it->second.filename();
            cv::imwrite(image_path.string() + ".png", image);
            
            // std::cout << "Visualized flow " << image_path.string() << "." << std::endl;
        }
    }
    
    return 0;
}
