/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/
#ifndef itkBlobSpatialObject_h
#define itkBlobSpatialObject_h

#include <list>

#include "itkPointBasedSpatialObject.h"

namespace itk
{
/**
 * \class BlobSpatialObject
 * \brief Spatial object representing a potentially amorphous object.
 *
 * The BlobSpatialObject is a discretized representation of a "blob",
 * which can be taken to be an arbitrary, possibly amorphous shape.
 * The representation is a list of the points (voxel centers) contained
 * in the object.  This can be thought of as an alternate way to
 * represent a binary image.
 *
 * \sa SpatialObjectPoint
 * \ingroup ITKSpatialObjects
 *
 * \wiki
 * \wikiexample{SpatialObjects/BlobSpatialObject,Blob}
 * \endwiki
 */

template< unsigned int TDimension = 3 >
class ITK_TEMPLATE_EXPORT BlobSpatialObject:
  public PointBasedSpatialObject<  TDimension >
{
public:
  ITK_DISALLOW_COPY_AND_ASSIGN(BlobSpatialObject);

  using Self = BlobSpatialObject;
  using Superclass = PointBasedSpatialObject< TDimension >;
  using Pointer = SmartPointer< Self >;
  using ConstPointer = SmartPointer< const Self >;
  using ScalarType = double;
  using BlobPointType = SpatialObjectPoint< TDimension >;
  using PointListType = std::vector< BlobPointType >;
  using PointType = typename Superclass::PointType;
  using SpatialObjectPointType = typename Superclass::SpatialObjectPointType;
  using TransformType = typename Superclass::TransformType;
  using BoundingBoxType = typename Superclass::BoundingBoxType;
  using PointContainerType = VectorContainer< IdentifierType, PointType >;
  using PointContainerPointer = SmartPointer< PointContainerType >;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Method for creation through the object factory. */
  itkTypeMacro(BlobSpatialObject, SpatialObject);

  /** Returns a reference to the list of the Blob points. */
  PointListType & GetPoints();

  /** Returns a reference to the list of the Blob points. */
  const PointListType & GetPoints() const;

  /** Set the list of Blob points. */
  void SetPoints(PointListType & newPoints);

  /** Return a point in the list given the index */
  const SpatialObjectPointType * GetPoint(IdentifierType id) const override
  { return &( m_Points[id] ); }

  /** Return a point in the list given the index */
  SpatialObjectPointType * GetPoint(IdentifierType id) override
  { return &( m_Points[id] ); }

  /** Return the number of points in the list */
  SizeValueType GetNumberOfPoints() const override
  { return static_cast<SizeValueType>( m_Points.size() ); }

  /** Method returns the Point closest to the given point */
  IdentifierType ClosestPoint(const PointType & curPoint) const;

  /** Returns true if the point is inside the Blob, false otherwise. */
  bool IsInside(const PointType & point, unsigned int depth,
    const std::string & name) const override;

  /** Compute the boundaries of the Blob. */
  bool ComputeObjectBoundingBox() const override;

protected:
  PointListType m_Points;


  BlobSpatialObject();
  ~BlobSpatialObject() override = default;

  /** Method to print the object. */
  void PrintSelf(std::ostream & os, Indent indent) const override;
};
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkBlobSpatialObject.hxx"
#endif

#endif // itkBlobSpatialObject_h
