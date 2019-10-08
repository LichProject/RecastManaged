#pragma once
#include "../Unmanaged/Detour/DetourNavMeshBuilder.h"
#include "../Tools/Math/Vector3.h"

namespace RecastManaged
{
	namespace Detour
	{
		public ref class NavMeshCreateParams
		{
			dtNavMeshCreateParams* _params;
			bool _destructWithMe;
			bool _disposed;

		public:
			NavMeshCreateParams(dtNavMeshCreateParams* navMeshCreateParams, bool* destructWithMe);

			NavMeshCreateParams(bool* destructWithMe);

			NavMeshCreateParams();

			~NavMeshCreateParams()
			{
				this->!NavMeshCreateParams();
			}

			!NavMeshCreateParams()
			{
				if (!this->_disposed && this->_destructWithMe)
				{
					delete _params;
					_params = nullptr;
					
					this->_disposed = true;
				}
			}

			dtNavMeshCreateParams* GetPointer()
			{
				return this->_params;
			}

			property const unsigned short* Verts
			{
				const unsigned short* get()
				{
					return _params->verts;
				}

				void set(const unsigned short* value)
				{
					_params->verts = value;
				}
			}

			virtual property int VertCount
			{
				int get()
				{
					return _params->vertCount;
				}

				void set(int value)
				{
					_params->vertCount = value;
				}
			}

			property const unsigned short* Polys
			{
				const unsigned short* get()
				{
					return _params->polys;
				}

				void set(const unsigned short* value)
				{
					_params->polys = value;
				}
			}

			property const unsigned short* PolyFlags
			{
				const unsigned short* get()
				{
					return _params->polyFlags;
				}

				void set(const unsigned short* value)
				{
					_params->polyFlags = value;
				}
			}

			property const unsigned char* PolyAreas
			{
				const unsigned char* get()
				{
					return _params->polyAreas;
				}

				void set(const unsigned char* value)
				{
					_params->polyAreas = value;
				}
			}

			virtual property int PolyCount
			{
				int get()
				{
					return _params->polyCount;
				}

				void set(int value)
				{
					_params->polyCount = value;
				}
			}

			virtual property int NVP
			{
				int get()
				{
					return _params->nvp;
				}

				void set(int value)
				{
					_params->nvp = value;
				}
			}

			property const unsigned* DetailMeshes
			{
				const unsigned* get()
				{
					return _params->detailMeshes;
				}

				void set(const unsigned* value)
				{
					_params->detailMeshes = value;
				}
			}

			property const float* DetailVerts
			{
				const float* get()
				{
					return _params->detailVerts;
				}

				void set(const float* value)
				{
					_params->detailVerts = value;
				}
			}

			virtual property int DetailVertsCount
			{
				int get()
				{
					return _params->detailVertsCount;
				}

				void set(int value)
				{
					_params->detailVertsCount = value;
				}
			}

			property const unsigned char* DetailTris
			{
				const unsigned char* get()
				{
					return _params->detailTris;
				}

				void set(const unsigned char* value)
				{
					_params->detailTris = value;
				}
			}

			virtual property int DetailTriCount
			{
				int get()
				{
					return _params->detailTriCount;
				}

				void set(int value)
				{
					_params->detailTriCount = value;
				}
			}

			property const float* OffMeshConVerts
			{
				const float* get()
				{
					return _params->offMeshConVerts;
				}

				void set(const float* value)
				{
					_params->offMeshConVerts = value;
				}
			}

			property const float* OffMeshConRad
			{
				const float* get()
				{
					return _params->offMeshConRad;
				}

				void set(const float* value)
				{
					_params->offMeshConRad = value;
				}
			}

			property const unsigned short* OffMeshConFlags
			{
				const unsigned short* get()
				{
					return _params->offMeshConFlags;
				}

				void set(const unsigned short* value)
				{
					_params->offMeshConFlags = value;
				}
			};

			property const unsigned char* OffMeshConAreas
			{
				const unsigned char* get()
				{
					return _params->offMeshConAreas;
				}

				void set(const unsigned char* value)
				{
					_params->offMeshConAreas = value;
				}
			}

			property const unsigned char* OffMeshConDir
			{
				const unsigned char* get()
				{
					return _params->offMeshConDir;
				}

				void set(const unsigned char* value)
				{
					_params->offMeshConDir = value;
				}
			}

			virtual property int OffMeshConCount
			{
				int get()
				{
					return _params->offMeshConCount;
				}

				void set(int value)
				{
					_params->offMeshConCount = value;
				}
			}

			virtual property unsigned UserID
			{
				unsigned get()
				{
					return _params->userId;
				}

				void set(unsigned value)
				{
					_params->userId = value;
				}
			}

			virtual property int TileX
			{
				int get()
				{
					return _params->tileX;
				}

				void set(int value)
				{
					_params->tileX = value;
				}
			}

			virtual property int TileY
			{
				int get()
				{
					return _params->tileY;
				}

				void set(int value)
				{
					_params->tileY = value;
				}
			}

			virtual property Tools::Math::Vector3^ BMin
			{
				Tools::Math::Vector3^ get()
				{
					return Tools::Math::Vector3::FromFloatPointer(_params->bmin);
				}

				void set(Tools::Math::Vector3^ value)
				{
					_params->bmin[0] = value->X;
					_params->bmin[1] = value->Y;
					_params->bmin[2] = value->Z;
				}
			}

			virtual property Tools::Math::Vector3^ BMax
			{
				Tools::Math::Vector3^ get()
				{
					return Tools::Math::Vector3::FromFloatPointer(_params->bmax);
				}

				void set(Tools::Math::Vector3^ value)
				{
					_params->bmax[0] = value->X;
					_params->bmax[1] = value->Y;
					_params->bmax[2] = value->Z;
				}
			}

			virtual property float WalkableHeight
			{
				float get()
				{
					return _params->walkableHeight;
				}

				void set(float value)
				{
					_params->walkableHeight = value;
				}
			}

			virtual property float WalkableRadius
			{
				float get()
				{
					return _params->walkableRadius;
				}

				void set(float value)
				{
					_params->walkableRadius = value;
				}
			}

			virtual property float WalkableClimb
			{
				float get()
				{
					return _params->walkableClimb;
				}

				void set(float value)
				{
					_params->walkableClimb = value;
				}
			}

			virtual property float CellSize
			{
				float get()
				{
					return _params->cs;
				}

				void set(float value)
				{
					_params->cs = value;
				}
			}

			virtual property float CellHeight
			{
				float get()
				{
					return _params->ch;
				}

				void set(float value)
				{
					_params->ch = value;
				}
			}

			virtual property bool BuildBVTree
			{
				bool get()
				{
					return _params->buildBvTree;
				}

				void set(bool value)
				{
					_params->buildBvTree = value;
				}
			}

			virtual property int TileLayer
			{
				int get()
				{
					return _params->tileLayer;
				}

				void set(int value)
				{
					_params->tileLayer = value;
				}
			}
		};
	}
}
