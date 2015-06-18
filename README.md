# Flow IO OpenCV

This is a fork and [OpenCV](http://opencv.org/) wrapper of the optical flow input/output code provided as part of the [Sintel dataset](http://sintel.is.tue.mpg.de/) [1]. The code is based on `imageLib`, a small C++ library for multi-channel images based on the [StereoMatcher](http://research.microsoft.com/en-us/downloads/9bc7fd74-5953-4064-9732-76405573aaef/) [2] code by Daniel Scharstein and Richard Szeliski. We refer to:

* [lib_flow_io/README-FlowIO](lib_flow_io/README-FlowIO.md): the original README shipped with the Sintel dataset.
* [lib_flow_io/imageLib/README](lib_flow_io/imageLibe/README.md): the original README of `imageLib` shipped with the Sintel dataset.
* [lib_flow_io/imageLib/README-StereoMatcher](lib_flow_io/imageLib/README.StereoMatcher.md): the original README of the StereoMatcher.

    [1] D. J. Butler, J. Wulff, G. B. Stanley, M. J. Black.
        A naturalistic open source movie for optical flow evaluation.
        In European Conference on Computer Vision, pages 611 - 625, 2012.
    [2] D. Scharstein, R. Szeliski.
        A taxonomy and evaluation of dense two-frame stereo correspondence algorithms.
        Technical Report MSR-TR-2001-81, Microsoft Research, 2001.

## Compile

The OpenCV wrapper is based on [CMake](http://www.cmake.org/) and (surprise!) OpenCV (for example, follow [Installing OpenCV on Linux](http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html#linux-installation) to install OpenCV). The code has been tested on Ubuntu 14.04 and 14.10.

    $ sudo apt-get install cmake build-essential
    $ mkdir build
    $cd build
    $ cmake ..
    $ ./cli/cli --help
    Allowed options:
      --help                produce help message
      --input-dir arg       input directory
      --output-dir arg      output directory
      --vis-dir arg         visualize results in a separate directory

The provided command line tool can be used to convert `.flo` files to `.txt` files using the `cv::FileStorage` format. Additionally, the tool provides visualization capabilities. For example:

    $ ./cli/cli ../alley_1_flow ../alley_1_cflow --vis-dir ../alley_1_flow_vis

The result is shown below:

![Example: visualized flow of the alley_1 sequence.](screenshot.png?raw=true "Example: visualized flow of the alley_1 sequence.")

## Usage

A usage example is provided in `cli/main.cpp`:

    // Define input file and output (visualization) path (or directly output file).
    boost::filesystem::path in_file(...);
    boost::filesystem::path out_dir(...);
    boost::filesystem::path vis_dir(...);
    
    cv::Mat flow = FlowIOOpenCVWrapper::read(in_file.string());
    
    boost::filesystem::path txt_path = out_dir / in_file.filename();
    IO::writeMat(txt_path.string() + ".txt", flow);
    
    if (visualize) {
        cv::Mat image = FlowIOOpenCVWrapper::flowToColor(flow);

        boost::filesystem::path image_path = vis_dir / in_file.filename();
        cv::imwrite(image_path.string() + ".png", image);
    }

## License

