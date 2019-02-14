/**
 * Copyright (c) 2019, University Osnabrück
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

#ifndef LAS_VEGAS_IOMESHINTERFACE_TCC
#define LAS_VEGAS_IOMESHINTERFACE_TCC

namespace lvr2{

const std::string attribute_type<EdgeHandle>::attr_group            = "edge_attributes";
const std::string attribute_type<OptionalEdgeHandle>::attr_group    = "edge_attributes";
const std::string attribute_type<VertexHandle>::attr_group          = "vertex_attributes";
const std::string attribute_type<OptionalVertexHandle>::attr_group  = "vertex_attributes";
const std::string attribute_type<FaceHandle>::attr_group            = "face_attributes";
const std::string attribute_type<OptionalFaceHandle>::attr_group    = "face_attributes";
const std::string attribute_type<ClusterHandle>::attr_group         = "cluster_attributes";
const std::string attribute_type<OptionalClusterHandle>::attr_group = "cluster_attributes";

template<typename MapT>
bool IOMeshInterface::addDenseAttributeMap(const MapT& map, const std::string& group, const std::string& name)
{
  typename AttributeChannel<typename channel_type<typename MapT::ValueType>::type>::Ptr values_channel_ptr(
      new AttributeChannel<typename channel_type<typename MapT::ValueType>::type>(
          map.numValues(), channel_type<typename MapT::ValueType>::w));

  auto& values = *values_channel_ptr;
  Index i = 0;
  for(auto handle: map)
  {
    values[i++] = map[handle]; //TODO handle deleted map values.
  }
  return addChannel(group, name, values_channel_ptr);
}

template <typename MapT>
boost::optional<MapT> IOMeshInterface::getDenseAttributeMap(const std::string& group, const std::string& name)
{
  typename AttributeChannel<typename channel_type<typename MapT::ValueType>::type>::Ptr channel_ptr;
  if(getChannel(group, name, channel_ptr) && channel_ptr
      && channel_ptr->width() == channel_type<typename MapT::ValueType>::w)
  {
    auto& channel = *channel_ptr;
    MapT map;
    map.reserve(channel.numAttributes());
    for(size_t i=0; i<channel_ptr->numAttributes(); i++)
    {
      typename MapT::HandleType handle(i);
      map.insert(handle, channel[i]);
    }
    return map;
  }
  return boost::none;
}

template<typename MapT>
bool IOMeshInterface::addAttributeMap(const MapT& map, const std::string& group, const std::string& name)
{
  typename AttributeChannel<typename channel_type<typename MapT::ValueType>::type>::Ptr values_channel_ptr(
      new AttributeChannel<typename channel_type<typename MapT::ValueType>::type>(
          map.numValues(), channel_type<typename MapT::ValueType>::w));
  IndexChannel::Ptr index_channel_ptr(new IndexChannel(map.numValues(), 1));

  auto& values = *values_channel_ptr;
  auto& indices = *index_channel_ptr;

  Index i = 0;
  for(auto handle: map)
  {
    values[i] = map[handle];
    indices[i++] = handle.idx();
  }

  return addChannel(group, name, values_channel_ptr) && addChannel(group, name + "_idx", index_channel_ptr);
}

template<typename MapT>
boost::optional<MapT> IOMeshInterface::getAttributeMap(const std::string& group, const std::string& name)
{
  typename AttributeChannel<typename channel_type<typename MapT::ValueType>::type>::Ptr values_channel_ptr;
  typename IndexChannel::Ptr index_channel_ptr;
  if(getChannel(group, name+"_idx", index_channel_ptr) && getChannel(group, name, values_channel_ptr)
      && index_channel_ptr && values_channel_ptr && index_channel_ptr->width() == 1
      && values_channel_ptr->width() == channel_type<typename MapT::ValueType>::w
      && index_channel_ptr->numAttributes() == values_channel_ptr->numAttributes())
  {
    auto& indices = *index_channel_ptr;
    auto& values = *values_channel_ptr;
    MapT map;

    map.reserve(indices.numAttributes());
    for(size_t i=0; i<index_channel_ptr->numAttributes(); i++)
    {
      map.insert(typename MapT::HandleType(indices[i]), values[i]);
    }
    return map;
  }
  return boost::none;
}

} /* namespace lvr2 */

#endif //LAS_VEGAS_IOMESHINTERFACE_TCC
