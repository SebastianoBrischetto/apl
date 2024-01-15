using System;
using cs.Exceptions;
using cs.Logic.GameLogic.Managers;
namespace cs.Logic.GameLogic.GameElements   
{
    public class Ship
    {
        //Attributi

        //Proprietà
        public int X { get; set; }

        public int Y { get; set; }

        public Direction Direction { get; set; }

        public int Length { get; set; }

        public Cell[] OccupiedCells { get; set; }

        public Ocean Ocean { get; set; }

        public int ShipCode { get; set; }

        //Costruttore
        public Ship(int x, int y, Direction direction, int shipCode, Ocean ocean)
        {
            X = x;
            Y = y;
            Direction = direction;
            Ocean = ocean;
            ShipCode = shipCode;
            switch (shipCode)
            {
                case 1:
                    Length = 3;
                    break;
                case 2:
                    Length = 2;
                    break;
                case 3:
                    Length = 3;
                    break;
                case 4:
                    Length = 4;
                    break;
                case 5:
                    Length = 5;
                    break;
            }
            OccupiedCells = new Cell[Length];
            switch (direction)
            {
                case Direction.Up:
                    OccupiedCells = ShipPlacementManager.UpPlacement(X, Y, Length, Ocean);
                    break;
                case Direction.Right:
                    OccupiedCells = ShipPlacementManager.RightPlacement(X, Y, Length, Ocean);
                    break;
                case Direction.Down:
                    OccupiedCells = ShipPlacementManager.DownPlacement(X, Y, Length, Ocean);
                    break;
                case Direction.Left:
                    OccupiedCells = ShipPlacementManager.LeftPlacement(X, Y, Length, Ocean);
                    break;
            }
        }
    }
}