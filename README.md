<!-- ABOUT THE PROJECT -->
## About The Project

Some of implementations using RecastNavigation library for .NET apps (uses C++/Cli).

Works only with tile meshes.


<!-- USAGE EXAMPLES -->
## Usage

First you need obtain area triangles / vertices / areabounds / grid sizes etc.

### There's no example to do this and some of pieces of code, if you want to use this implementation and examples below, then you should know approximately what you are doing.

#### Example of creating tile cache
```C#
_tileCacheParams = new TileCacheParams(); // you should set the params.
var tileCache = new TileCache(_tileCacheParams);
```

#### Example of creating navigation mesh
```C#
var navMeshParams = new NavMeshParams(); // you should set the params.
var navMesh = new NavMesh();
var status = navMesh.Init(navMeshParams);
if (!status.Succeeded)
{
    throw new Exception($"NavMesh.Init failed with status {status}.");
}
```

#### Example of creating navigation mesh query
```C#
var navQuery = new NavMeshQuery();
var status = navQuery.Init(navMesh, ushort.MaxValue * 2);
if (!status.Succeeded)
{
    throw new Exception($"NavMeshQuery.Init failed with status: {status}.");
}

var filter = new QueryFilter(ushort.MaxValue, 0);
filter.SetAreaCost(0, 1f);
filter.SetAreaCost(1, 1f);
```

#### Creating ChunkyTriMesh
https://gist.github.com/LichProject/34714722eb286bac9dcb1be85c824225


#### Rasterizing Tile Layers
https://gist.github.com/LichProject/a46a0068829074cfadb086bc894c9367


#### Adding and building tiles
```C#
var processedTiles = 0;
for (var y = 0; y < tilesHeight; y++)
{
    int cY = y;
    Parallel.For(0, tilesWidth, new ParallelOptions {MaxDegreeOfParallelism = Math.Max(1, Environment.ProcessorCount - 1)}, x =>
    {
        List<NavMeshData> tiles = Mesher.RasterizeTileLayers(x, cY, vertices, indices, ChunkyTriMesh);
        if (tiles != null && tiles.Count > 0)
        {
            foreach (NavMeshData tile in tiles)
            {
                processedTiles++;
                if (!TileCache.AddTile(tile, out _))
                {
                    throw new Exception($"TileCache.AddTile failed for a mesh ({processedTiles} / {tiles.Count}).");
                }
            }
        }
    });
}

for (int y = 0; y < tilesHeight; ++y)
for (int x = 0; x < tilesWidth; ++x)
{
    TileCache.BuildTilesAt(x, y, NavMesh);
}
```