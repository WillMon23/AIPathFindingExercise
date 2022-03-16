#pragma once
#include "Scene.h"
#include "NodeGraph.h"
#include <Vector2.h>


class Player;

/// <summary>
/// A Scene that generates a grid of Walls.
/// </summary>
class Maze : public Scene
{
public:
	/// <summary>
	/// An enumerator of tile types.
	/// MODIFY this list with any new tiles needed.
	/// The keys are not ordered.
	/// </summary>
	enum class TileKey {
		OPEN,
		WALL,
		MUD,
		PLAYER,
		GHOST
	};

	/// <summary>
	/// A single space in a Maze.
	/// </summary>
	struct Tile {
		int x;
		int y;
		float cost = 1.0f;
		Actor* actor = nullptr;
		NodeGraph::Node* node = nullptr;
	};

	static const int WIDTH = 28;
	static const int HEIGHT = 32;
	static const int TILE_SIZE = 25;

public:
	/// <param name="map">A 2D array of TileKeys arranged height by width</param>
	Maze();
	~Maze();

	virtual void draw() override;

	/// <summary>
	/// Get the size of the maze.
	/// </summary>
	/// <returns>a Vector2 storing the maze's width and height</returns>
	MathLibrary::Vector2 getSize() { return m_size; }

	/// <summary>
	/// Get the tile data at the given position.
	/// </summary>
	/// <param name="position">The position to check</param>
	/// <returns>A Tile with the data at the position</returns>
	Tile getTile(MathLibrary::Vector2 position);

	/// <summary>
	/// Get the position of the given tile.
	/// </summary>
	/// <param name="tile">The tile to check</param>
	/// <returns>A Vector2 with the position of the tile</returns>
	MathLibrary::Vector2 getPosition(Tile tile);

protected:
	/// <summary>
	/// Create a tile from a given key. If an actor is created, it is added to the scene.
	/// MODIFY this function to add support for new tiles.
	/// </summary>
	/// <param name="cost">The cost to use</param>
	/// <returns>The actor created</returns>
	Tile createTile(int x, int y, TileKey key);

private:
	/// <summary>
	/// Generate a new grid of Walls.
	/// </summary>
	void generate(TileKey map[Maze::HEIGHT][Maze::WIDTH]);

private:
	MathLibrary::Vector2 m_size = { WIDTH, HEIGHT };
	Tile m_grid[WIDTH][HEIGHT];

	Player* m_player;
};

