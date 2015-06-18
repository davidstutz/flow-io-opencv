# StereoMatcher

This directory contains the source code to the two-frame dense stereo
matching code developed by Daniel Scharstein and Richard Szeliski.
Please see the associated `Licence.txt` and Copyright.h files for terms and
conditions of use.

The algorithms implemented in this code are described in our Technical
Report:

    D. Scharstein and R. Szeliski. A taxonomy and evaluation of dense
    two-frame stereo correspondence algorithms. Technical Report
    MSR-TR-2001-81, Microsoft Research, November 2001.

which can be found at
[http://www.research.microsoft.com/scripts/pubs/view.asp?TR_ID=MSR-TR-2001-81](http://www.research.microsoft.com/scripts/pubs/view.asp?TR_ID=MSR-TR-2001-81)
and which will also appear in a special issue of IJCV on stereo matching.

To compile the code, please use the Workspace or makefile.  
If you wish to run the graph cut algorithm, you will need to follow the
instructions given in `maxflow/README-maxflow.txt`.

The program is driven by command line arguments and scripts. To run a
particular scriptfile, just use
StereoMatch script `scriptfile.txt`
Some sample scripts that you can use to evaluate the output of your stereo
algorithm or to run one of the matching algorithms are given on the 
Middlebury Stereo Web site,
[http://www.middlebury.edu/stereo/code.html](http://www.middlebury.edu/stereo/code.html)
You can also find some sample data sets at the same location.

There is no documentation provided beyond the comments embedded in the
source code.  The main parameters controlling the algorithm are in
StereoParameters.h, and a subset of these is documented in more detail in
the Techical Report cited above.  If you don't understand what a parameter
is doing, just leave it at its default value (it may control experimental
code we are still working on).

You can obtain the latest version of this software by following the
download link from the Middlebury Stereo Web page URL given above.

Daniel Scharstein and Richard Szeliski, December 6, 2001.