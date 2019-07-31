/**
 * Copyright (c) 2018, University Osnabrück
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the University Osnabrück nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL University Osnabrück BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * SlamOptions.hpp
 *
 *  @date May 28, 2019
 *  @author Malte Hillmann
 */
#ifndef SLAMOPTIONS_HPP_
#define SLAMOPTIONS_HPP_

namespace lvr2
{

/**
 * @brief A struct to configure SlamAlign
 */
struct SlamOptions
{
    // ==================== General Options ======================================================

    /// Use the unmodified Pose of new Scans. If false, apply the relative refinement of
    /// previous Scans
    bool    trustPose = false;

    /// Match scans to the combined Pointcloud of all previous Scans instead of just the last Scan
    bool    metascan = false;

    /// Show more detailed output
    bool    verbose = false;

    // ==================== Reduction Options ====================================================

    /// The Voxel size for Voxel based reduction
    float   reduction = -1;

    /// Ignore all Points closer than <value> to the origin of a scan
    float   minDistance = -1;

    /// Ignore all Points farther away than <value> from the origin of a scan
    float   maxDistance = -1;

    // ==================== ICP Options ==========================================================

    /// Number of iterations for ICP
    int     icpIterations = 50;

    /// The maximum distance between two points during ICP
    float   icpMaxDistance = 25;

    /// The maximum number of Points in a Leaf of a KDTree
    int     maxLeafSize = 20;

    /// The epsilon difference between ICP-errors for the stop criterion of ICP
    double  epsilon = 0.00001;

    // ==================== SLAM Options =========================================================

    /// Use simple Loop Closing
    bool    doLoopClosing = false;

    /// Use complex Loop Closing with GraphSLAM
    bool    doGraphSlam = false;

    /// The maximum distance between two poses to consider a closed loop or Edge.
    /// Mutually exclusive to closeLoopPairs
    float   closeLoopDistance = 500;

    /// The minimum pair overlap between two poses to consider a closed loop or Edge.
    /// Mutually exclusive to closeLoopDistance
    int     closeLoopPairs = -1;

    /// The minimum number of Scans to be considered a Loop. Also used for GraphSLAM when
    /// considering Edges
    int     loopSize = 20;

    /// Number of ICP iterations during Loopclosing and number of
    /// GraphSLAM iterations
    int     slamIterations = 50;

    /// The maximum distance between two points during SLAM
    float   slamMaxDistance = 25;

    /// The epsilon difference of SLAM corrections for the stop criterion of SLAM
    double  slamEpsilon = 0.5;
};

} /* namespace lvr2 */

#endif /* SLAMOPTIONS_HPP_ */
