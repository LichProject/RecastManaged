#pragma once
#include "../Unmanaged/Detour/DetourNavMesh.h"

namespace RecastManaged
{
	namespace Detour
	{
		public ref class Poly
		{
			dtPoly* _p;
			bool _destructWithMe;
			bool _disposed;

		public:
			Poly(dtPoly* p, bool* destructWithMe);

			Poly();

			~Poly();

			!Poly();

			dtPoly* GetPointer();

			unsigned short GetVert(int index);

			virtual property unsigned short Flags
			{
				unsigned short get()
				{
					return _p->flags;
				}
				void set(unsigned short value)
				{
					_p->flags = value;
				}
			}

			virtual property unsigned char VertCount
			{
				unsigned char get()
				{
					return _p->vertCount;
				}
				void set(unsigned char value)
				{
					_p->vertCount = value;
				}
			}

			virtual property array<unsigned short>^ Verts
			{
				array<unsigned short>^ get()
				{
					const int size = DT_VERTS_PER_POLYGON;

					auto arr = gcnew array<unsigned short>(size);
					for (int i = 0; i < size; i++)
					{
						arr[i] = _p->verts[i];
					}

					return arr;
				}
				void set(array<unsigned short>^ value)
				{
					for (int i = 0; i < value->Length; i++)
					{
						_p->verts[i] = value[i];
					}
				}
			}

			virtual property array<short>^ Neis
			{
				array<short>^ get()
				{
					const int size = DT_VERTS_PER_POLYGON;

					auto arr = gcnew array<short>(size);
					for (int i = 0; i < size; i++)
					{
						arr[i] = _p->neis[i];
					}

					return arr;
				}
				void set(array<short>^ value)
				{
					for (int i = 0; i < value->Length; i++)
					{
						_p->neis[i] = value[i];
					}
				}
			}

			virtual property unsigned char Area
			{
				unsigned char get()
				{
					return _p->getArea();
				}
				void set(unsigned char value)
				{
					_p->setArea(value);
				}
			}

			virtual property unsigned char Type
			{
				unsigned char get()
				{
					return _p->getType();
				}
				void set(unsigned char value)
				{
					_p->setType(value);
				}
			}
		};
	}
}
