#pragma once
#include "../Unmanaged/Detour/DetourTileCache.h"
#include "../Tools/Math/Vector3.h"

namespace RecastManaged
{
	namespace DetourTileCache
	{
		public ref class TileCacheParams : System::IDisposable
		{
			dtTileCacheParams* m_TileCacheParams;
			bool _disposed = false;

		public:
			~TileCacheParams()
			{
				this->!TileCacheParams();
			}

			!TileCacheParams();

			TileCacheParams();

			dtTileCacheParams* GetPointer()
			{
				return this->m_TileCacheParams;
			}

			virtual property float CellSize
			{
				float get()
				{
					return m_TileCacheParams->cs;
				}

				void set(float value)
				{
					m_TileCacheParams->cs = value;
				}
			}

			virtual property float CellHeight
			{
				float get()
				{
					return m_TileCacheParams->ch;
				}

				void set(float value)
				{
					m_TileCacheParams->ch = value;
				}
			}

			virtual property int TileSize
			{
				int get()
				{
					return m_TileCacheParams->width;
				}

				void set(int value)
				{
					m_TileCacheParams->width = value;
					m_TileCacheParams->height = value;
				}
			}

			virtual property float WalkableHeight
			{
				float get()
				{
					return m_TileCacheParams->walkableHeight;
				}

				void set(float value)
				{
					m_TileCacheParams->walkableHeight = value;
				}
			}

			virtual property float WalkableRadius
			{
				float get()
				{
					return m_TileCacheParams->walkableRadius;
				}

				void set(float value)
				{
					m_TileCacheParams->walkableRadius = value;
				}
			}

			virtual property float WalkableClimb
			{
				float get()
				{
					return m_TileCacheParams->walkableClimb;
				}

				void set(float value)
				{
					m_TileCacheParams->walkableClimb = value;
				}
			}

			virtual property float MaxSimplificationError
			{
				float get()
				{
					return m_TileCacheParams->maxSimplificationError;
				}

				void set(float value)
				{
					m_TileCacheParams->maxSimplificationError = value;
				}
			}

			virtual property int MaxTiles
			{
				int get()
				{
					return m_TileCacheParams->maxTiles;
				}

				void set(int value)
				{
					m_TileCacheParams->maxTiles = value;
				}
			}

			virtual property Tools::Math::Vector3^ Origin
			{
				Tools::Math::Vector3^ get()
				{
					return Tools::Math::Vector3::FromFloatPointer(m_TileCacheParams->orig);
				}

				void set(Tools::Math::Vector3^ value)
				{
					m_TileCacheParams->orig[0] = value->X;
					m_TileCacheParams->orig[1] = value->Y;
					m_TileCacheParams->orig[2] = value->Z;
				}
			}

			virtual property int MaxObstacles
			{
				int get()
				{
					return m_TileCacheParams->maxObstacles;
				}

				void set(int value)
				{
					m_TileCacheParams->maxObstacles = value;
				}
			}
		};
	}
}
