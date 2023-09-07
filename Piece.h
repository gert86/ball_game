#ifndef PIECE_H
#define PIECE_H

#include "Types.h"

namespace Color
{
  const std::string RESET = "\033[0m";
  const std::string BLACK = "\033[30m";
  const std::string RED = "\033[31m";
  const std::string GREEN = "\033[32m";
  const std::string YELLOW = "\033[33m";
  const std::string BLUE = "\033[34m";
  const std::string MAGENTA = "\033[35m";
  const std::string CYAN = "\033[36m";
  const std::string WHITE = "\033[37m";
  const std::string BRIGHT_BLACK = "\033[90m";
  const std::string BRIGHT_RED = "\033[91m";
  const std::string BRIGHT_GREEN = "\033[92m";
  const std::string BRIGHT_YELLOW = "\033[93m";
  const std::string BRIGHT_BLUE = "\033[94m";
  const std::string BRIGHT_MAGENTA = "\033[95m";
  const std::string BRIGHT_CYAN = "\033[96m";
  const std::string BRIGHT_WHITE = "\033[97m";
}

class Piece
{
public:
  // determine all possible options to place the given piece on the given board
  static std::vector<BoardPlacementEntry> determinePlaceableOptions(const BoardState& boardState, const Piece* piece, bool constrainToInitialPlaceableOptions);

  // further filter out options that lead to dead-ends w.r.t. yet unplaced pieces -> takes some time
  static std::vector<BoardPlacementEntry> reducePlaceableOptions(const std::vector<BoardPlacementEntry>& originalPlaceableOptions,
                                                                 const BoardState& boardState,
                                                                 const Piece* piece,
                                                                 const std::vector<Piece*>& unplacedPieces);
  // for colored display of pieces
  static std::string getColorForId(char id);

public:
  Piece(char id, Geometry baseGeometry);
  void postInit(const BoardState& boardState);
  void drawBaseOrientation() const;
  void drawAllOrientations() const;
  const Geometries& getGeometryOrientations() const;
  const std::vector<BoundingBox>& getGeometryOrientationBoundingBoxes() const;
  size_t getNumOrientations() const;
  std::vector<BoardPlacementEntry> getInitialPlaceableOptions() const;
  void setInitialPlaceableOptions(const std::vector<BoardPlacementEntry>& initialOptions);  // only if read from cache
  size_t getNumInitialPlaceableOptions() const;
  char id() const;
  string idWithColor() const;
  size_t getExtent() const;

protected:
  char _id;
  Geometry _baseGeometry;

private:
  static void drawGeometry(const Geometry& geometry, const std::string& color);
  static Geometry transformGeometry(const Geometry& geometry, GeometryModification modification);

private:
  //! adds up to 7 additional geometries through rotation and mirroring
  void obtainOrientationsFromBase();
  void obtainPlaceableOptions(const BoardState& boardState);

private:
  Geometries _geometryOrientations;
  std::vector<BoundingBox> _geometryOrientationsBoundingBoxes;
  std::vector<BoardPlacementEntry> _initialPlacableOptions;
};

#endif // PIECE_H
