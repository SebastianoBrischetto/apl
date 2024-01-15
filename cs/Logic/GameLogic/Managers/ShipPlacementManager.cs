using System;
using cs.Exceptions;
using cs.Logic.GameLogic.GameElements;
namespace cs.Logic.GameLogic.Managers
{
    public static class ShipPlacementManager
    {
        //UP
        public static Cell[] UpPlacement(int x, int y, int length, Ocean ocean)
        {
            try
            {
                foreach (Cell cell in ocean.OccupiedCells)
                {
                    if ((cell.Row > x - length && cell.Row < x)&&(cell.Column == y))
                    {
                        throw new OutOfOceanException();
                    }
                }
                if (x - length < 0)
                {
                    throw new OutOfOceanException();
                }
            }
            catch (OutOfOceanException e)
            {
                Console.WriteLine(e.Message);
            }

            Cell[] occupiedCells = new Cell[length];
            for (int i = 0; i < length; i++)
            {
                Cell cell = new Cell(x - i, y, true);
                occupiedCells[i] = cell;
                cell.IsOccupied = true;
                ocean.Cells[x - i, y].IsOccupied = true;
                ocean.OccupiedCells.Add(cell);
                foreach (Cell occupiedCell in ocean.OccupiedCells)
                {
                    if (occupiedCell.Row == -1 && occupiedCell.Column == -1)
                    {
                        occupiedCell.Row = x - 1;
                        occupiedCell.Column = y;
                    }
                }
            }
            return occupiedCells;
        }
        
        //RIGHT
        public static Cell[] RightPlacement(int x, int y, int length, Ocean ocean)
        {
            try
            {
                foreach (Cell cell in ocean.OccupiedCells)
                {
                    if ((cell.Row == x) && (cell.Column > y && cell.Column < y + length)) //(cell.Row > x - length && cell.Row < x)&&(cell.Column == y)
                    {
                        throw new OutOfOceanException();
                    }
                }
                if (y + length > ocean.Columns)
                {
                    throw new OutOfOceanException();
                }
            }
            catch (OutOfOceanException e)
            {
                Console.WriteLine(e.Message);
            }
            
            Cell[] occupiedCells = new Cell[length];
            for (int i = 0; i < length; i++)
            {
                Cell cell = new Cell(x, y + i, true);
                occupiedCells[i] = cell;
                cell.IsOccupied = true;
                ocean.Cells[x, y + i].IsOccupied = true;
                ocean.OccupiedCells.Add(cell);
            }
            return occupiedCells;
        }
        
        //DOWN
        public static Cell[] DownPlacement(int x, int y, int length, Ocean ocean)
        {
            try
            {
                foreach (Cell cell in ocean.OccupiedCells)
                {
                    if ((cell.Row > x && cell.Row < x + length)&&(cell.Column == y))
                    {
                        throw new OutOfOceanException();
                    }
                }
                if (x + length > ocean.Rows)
                {
                    throw new OutOfOceanException();
                }
            }
            catch (OutOfOceanException e)
            {
                Console.WriteLine(e.Message);
            }
            
            Cell[] occupiedCells = new Cell[length];
            for (int i = 0; i < length; i++)
            {
                Cell cell = new Cell(x + i, y, true);
                occupiedCells[i] = cell;
                cell.IsOccupied = true;
                ocean.Cells[x + i, y].IsOccupied = true;
                ocean.OccupiedCells.Add(cell);
            }
            return occupiedCells;
        }
        
        
        //LEFT
        public static Cell[] LeftPlacement(int x, int y, int length, Ocean ocean)
        {
            try
            {
                foreach (Cell cell in ocean.OccupiedCells)
                {
                    if ((cell.Row == x) && (cell.Column > y - length && cell.Column < y)){
                        throw new OutOfOceanException();
                    }
                }
                if (y - length < 0)
                {
                    throw new OutOfOceanException();
                }
            }
            catch (OutOfOceanException e)
            {
                Console.WriteLine(e.Message);
            }
            
            Cell[] occupiedCells = new Cell[length];
            for (int i = 0; i < length; i++)
            {
                Cell cell = new Cell(x, y - i, true);
                occupiedCells[i] = cell;
                cell.IsOccupied = true;
                ocean.Cells[x, y - i].IsOccupied = true;
                ocean.OccupiedCells.Add(cell);
            }
            
            return occupiedCells;
        }
    }
}