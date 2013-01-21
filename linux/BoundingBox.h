#pragma once

class BoundingBox
{
public:
	BoundingBox(void);
	~BoundingBox(void);
};


// --------------------------
//
// Oriented Bounding Box Class
//
// --------------------------

//
// Check if a point is in this bounding box
//
bool CBBox::IsPointInBox(const CVec3 &InP)
{
	// Rotate the point into the box's coordinates
	CVec3 P = m_M.InvertSimple() * InP;
	
	// Now just use an axis-aligned check
	if ( fabs(P.x) < m_Extent.x && fabs(P.y) < m_Extent.y && fabs(P.z) < m_Extent.z ) 
		return true;
		
	return false;
}

//
// Check if a sphere overlaps any part of this bounding box
//
bool CBBox::IsSphereInBox( const CVec3 &InP, float fRadius)
{
	float fDist;
	float fDistSq = 0;
	CVec3 P = m_M.InvertSimple() * InP;
	
	// Add distance squared from sphere centerpoint to box for each axis
	for ( int i = 0; i < 3; i++ )
	{
		if ( fabs(P[i]) > m_Extent[i] )
		{
			fDist = fabs(P[i]) - m_Extent[i];
			fDistSq += fDist*fDist;
		}
	}
	return ( fDistSq <= fRadius*fRadius );
}

//
// Check if the bounding box is completely behind a plane( defined by a normal and a point )
//
bool CBBox::BoxOutsidePlane( const CVec3 &InNorm, const CVec3 &InP )
{
	// Plane Normal in Box Space
	CVec3 Norm = InNorm.RotByMatrix( m_M.InvertSimple().mf ); // RotByMatrix only uses rotation portion of matrix
	Norm = CVec3( fabs( Norm.x ), fabs( Norm.y ), fabs( Norm.z ) );
	
	float Extent = Norm.Dot( m_Extent ); // Box Extent along the plane normal
	float Distance = InNorm.Dot( GetCenterPoint() - InP ); // Distance from Box Center to the Plane

	// If Box Centerpoint is behind the plane further than its extent, the Box is outside the plane
	if ( Distance < -Extent ) return true;
	return false;
}

//
// Does the Line (L1, L2) intersect the Box?
//
bool CBBox::IsLineInBox( const CVec3& L1, const CVec3& L2 )
{	
	// Put line in box space
	CMatrix MInv = m_M.InvertSimple();
	CVec3 LB1 = MInv * L1;
	CVec3 LB2 = MInv * L2;

	// Get line midpoint and extent
	CVec3 LMid = (LB1 + LB2) * 0.5f; 
	CVec3 L = (LB1 - LMid);
	CVec3 LExt = CVec3( fabs(L.x), fabs(L.y), fabs(L.z) );

	// Use Separating Axis Test
	// Separation vector from box center to line center is LMid, since the line is in box space
	if ( fabs( LMid.x ) > m_Extent.x + LExt.x ) return false;
	if ( fabs( LMid.y ) > m_Extent.y + LExt.y ) return false;
	if ( fabs( LMid.z ) > m_Extent.z + LExt.z ) return false;
	// Crossproducts of line and each axis
	if ( fabs( LMid.y * L.z - LMid.z * L.y)  >  (m_Extent.y * LExt.z + m_Extent.z * LExt.y) ) return false;
	if ( fabs( LMid.x * L.z - LMid.z * L.x)  >  (m_Extent.x * LExt.z + m_Extent.z * LExt.x) ) return false;
	if ( fabs( LMid.x * L.y - LMid.y * L.x)  >  (m_Extent.x * LExt.y + m_Extent.y * LExt.x) ) return false;
	// No separating axis, the line intersects
	return true;
}

//
// Returns a 3x3 rotation matrix as vectors
//
inline void CBBox::GetInvRot( CVec3 *pvRot )
{
	pvRot[0] = CVec3( m_M.mf[0], m_M.mf[1], m_M.mf[2] );
	pvRot[1] = CVec3( m_M.mf[4], m_M.mf[5], m_M.mf[6] );
	pvRot[2] = CVec3( m_M.mf[8], m_M.mf[9], m_M.mf[10] );
}

//
// Check if any part of a box is inside any part of another box
// Uses the separating axis test.
//
bool CBBox::IsBoxInBox( CBBox &BBox )
{
	CVec3 SizeA = m_Extent;
	CVec3 SizeB = BBox.m_Extent;
	CVec3 RotA[3], RotB[3];	
	GetInvRot( RotA );
	BBox.GetInvRot( RotB );

    float R[3][3];  // Rotation from B to A
    float AR[3][3]; // absolute values of R matrix, to use with box extents
    float ExtentA, ExtentB, Separation;
    int i, k;

    // Calculate B to A rotation matrix
    for( i = 0; i < 3; i++ )
        for( k = 0; k < 3; k++ )
			{
            R[i][k] = RotA[i].Dot(RotB[k]); 
            AR[i][k] = fabs(R[i][k]);
            }
            
    // Vector separating the centers of Box B and of Box A	
    CVec3 vSepWS = BBox.GetCenterPoint() - GetCenterPoint();
    // Rotated into Box A's coordinates
    CVec3 vSepA( vSepWS.Dot(RotA[0]), vSepWS.Dot(RotA[1]), vSepWS.Dot(RotA[2]) );            

     // Test if any of A's basis vectors separate the box
	for( i = 0; i < 3; i++ )
	{
		ExtentA = SizeA[i];
		ExtentB = SizeB.Dot( CVec3( AR[i][0], AR[i][1], AR[i][2] ) );
		Separation = fabs( vSepA[i] );

		if( Separation > ExtentA + ExtentB ) return false;
	}

	// Test if any of B's basis vectors separate the box
	for( k = 0; k < 3; k++ )
	{
		ExtentA = SizeA.Dot( CVec3( AR[0][k], AR[1][k], AR[2][k] ) );
		ExtentB = SizeB[k];
		Separation = fabs( vSepA.Dot( CVec3(R[0][k],R[1][k],R[2][k]) ) );

		if( Separation > ExtentA + ExtentB ) return false;
	}

	// Now test Cross Products of each basis vector combination ( A[i], B[k] )
	for( i=0 ; i<3 ; i++ )
		for( k=0 ; k<3 ; k++ )
		{
		int i1 = (i+1)%3, i2 = (i+2)%3;
		int k1 = (k+1)%3, k2 = (k+2)%3;
		ExtentA = SizeA[i1] * AR[i2][k]  +  SizeA[i2] * AR[i1][k];
		ExtentB = SizeB[k1] * AR[i][k2]  +  SizeB[k2] * AR[i][k1];
		Separation = fabs( vSepA[i2] * R[i1][k]  -  vSepA[i1] * R[i2][k] );
		if( Separation > ExtentA + ExtentB ) return false;
		}

	// No separating axis found, the boxes overlap	
	return true;
	}