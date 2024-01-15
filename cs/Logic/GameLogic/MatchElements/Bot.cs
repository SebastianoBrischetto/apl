using cs.Logic.GameLogic.GameElements;
using cs.Logic.GameLogic.MatchElements.Structs;
namespace cs.Logic.GameLogic.MatchElements;

public class Bot
{
    public Ocean Ocean { get; set; }
    public List<Move> Moves { get; set; }
    public List<OccupiedCoordinates> OccupiedCoordinates { get; set; }

    public Bot()
    {
        Ocean = null;
        Moves = new List<Move>();
        OccupiedCoordinates = new List<OccupiedCoordinates>();
    }

    public Bot(int rows, int columns, int shipsNumber)
    {
        Ocean = new Ocean(rows, columns, shipsNumber, null,true);
        Moves = new List<Move>();
        OccupiedCoordinates = new List<OccupiedCoordinates>();
    }

    public Bot(List<Move> moves, List<OccupiedCoordinates> occupiedCoordinates)
    {
        Moves = new List<Move>();
        Moves = moves;
        OccupiedCoordinates = new List<OccupiedCoordinates>();
        OccupiedCoordinates = occupiedCoordinates;
        Cell[] occupiedCells = new Cell[occupiedCoordinates.Count];
        OccupiedCoordinates[] occupiedCoordinatesArray = OccupiedCoordinates.ToArray();
        for (int i = 0; i < occupiedCoordinates.Count; i++)
        {
            Cell cell = new Cell(occupiedCoordinatesArray[i].X, occupiedCoordinatesArray[i].Y, true);
            occupiedCells[i] = cell;
        }

        Ocean = new Ocean(Match.Instance.Rows, Match.Instance.Columns, occupiedCells);
    }

    public void FillCells()
    {
        for (int row = 0; row < Ocean.Rows; row++)
        {
            for (int column = 0; column < Ocean.Columns; column++)
            {
                foreach (OccupiedCoordinates coords in OccupiedCoordinates)
                {
                    if (coords.X == Ocean.Cells[row, column].Row && coords.Y == Ocean.Cells[row, column].Column)
                    {
                        Ocean.Cells[row, column].IsOccupied = true;
                    }
                }
            }
        }
    }
}
