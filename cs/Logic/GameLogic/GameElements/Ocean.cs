using cs.Exceptions;
using cs.GUIConsole;
using cs.Logic.GameLogic.MatchElements;
using cs.Logic.GameLogic.MatchElements.Structs;

namespace cs.Logic.GameLogic.GameElements
{
     public class Ocean
    {
        //Proprietà
        public int Rows { get; set; }
        public int Columns { get; set; }
        public Cell[,] Cells { get; set; }
        public Ship[] Ships { get; set; }
        public List<Cell> OccupiedCells { get; set; }
        public List<Cell> AttackedCells { get; set; }
        public List<Cell> HittenCells { get; set; }

        //Costruttore
        public Ocean(int rows, int columns, int shipsNumber, int[] shipsCodes = null, bool isEmpty = false)
        {
            Rows = rows;
            Columns = columns;
            Cells = new Cell[rows, columns];
            OccupiedCells = new List<Cell>();
            AttackedCells = new List<Cell>();
            HittenCells = new List<Cell>();
            Ships = new Ship[shipsNumber];
            for (int row = 0; row < rows; row++)
            {
                for (int column = 0; column < columns; column++)
                {
                    Cells[row, column] = new Cell(row, column);
                }
            }
            if (!isEmpty)
            {
                AddShips(shipsNumber, this, shipsCodes);
            }
        }
        public Ocean(int rows, int columns, Cell[] occupiedCells)
        {
            Rows = rows;
            Columns = columns;
            Cells = new Cell[rows, columns];
            AttackedCells = new List<Cell>();
            HittenCells = new List<Cell>();
            OccupiedCells = new List<Cell>();
            for (int row = 0; row < rows; row++)
            {
                for (int column = 0; column < columns; column++)
                {
                    bool isOccupied = false;
                    for (int i = 0; i < occupiedCells.Length; i++)
                    {
                        if (occupiedCells[i].Row == row && occupiedCells[i].Column == column)
                        {
                            isOccupied = true;
                            break;
                        }
                    }
                    Cells[row, column] = new Cell(row, column, isOccupied);
                    if (Cells[row, column].IsOccupied)
                    {
                        OccupiedCells.Add(Cells[row,column]);
                    }
                }
            }
        }
        //Metodi
        public void AddShips(int shipsNumber, Ocean ocean, int[] shipsCodes = null)
        {
            int occupiedListLength = 0;
            if (shipsCodes == null)
            {
                for (int i = 0; i < shipsNumber; i++)
                {
                    int row = GUI.GetIntInput($"Inserisci la riga della nave {i + 1} ", 0, ocean.Rows - 1);
                    int column = GUI.GetIntInput($"Inserisci la colonna della nave {i + 1} ", 0, ocean.Columns - 1);
                    int code = GUI.GetIntInput($"Inserisci il codice della nave {i + 1} ", 1, 5);
                    int direction = GUI.GetIntInput($"Inserisci la direzione della nave {i + 1} ", 0, 3);
                    Ship ship = new Ship(row, column, (Direction)direction, code, this);
                    if (ship.OccupiedCells != null)
                    {
                        ocean.Ships[i] = ship;
                        Console.WriteLine("LA TUA GRIGLIA ATTUALE:");
                        PrintPlacement();
                    }
                    else
                    {
                        Console.WriteLine("Impossibile aggiungere la cella, riprova");
                        i--;
                    }
                }
            }
            else
            {
                for (int i = 0; i < shipsNumber; i++)
                {
                    int length = 0;
                    switch (shipsCodes[i])
                    {
                        case 1:
                            length = 3;
                            break;
                        case 2:
                            length = 2;
                            break;
                        case 3:
                            length = 3;
                            break;
                        case 4:
                            length = 4;
                            break;
                        case 5:
                            length = 5;
                            break;
                    }
                    int row = GUI.GetIntInput($"Inserisci la riga della nave con lunghezza {length} ", 0, ocean.Rows - 1);
                    int column = GUI.GetIntInput($"Inserisci la colonna della nave con lunghezza {length} ", 0, ocean.Columns - 1);
                    int code = shipsCodes[i];
                    int direction = GUI.GetIntInput($"Inserisci la direzione della nave con lunghezza {length} ", 0, 3);
                    Ship ship = new Ship(row, column, (Direction)direction, code, this);
                    if (ship.OccupiedCells != null)
                    {
                        ocean.Ships[i] = ship;
                        Console.WriteLine("LA TUA GRIGLIA ATTUALE:");
                        PrintPlacement();
                    }
                    else
                    {
                        Console.WriteLine("Impossibile aggiungere la cella, riprova");
                        i--;
                    }
                }
            }
        }

        public bool CheckAttack(int attackedRow, int attackedColumn)
        {
            try
            {
                if (Match.Instance.PlayersLastMoves.Count > 0)
                {
                    foreach (Move move in Match.Instance.PlayersLastMoves)
                    {
                        if (move.X == attackedRow && move.Y == attackedColumn)
                        {
                            throw new AlreadyAttackedException();
                        }
                    }
                }
                return true;
                
            }
            catch (AlreadyAttackedException e)
            {
                Console.WriteLine(e.Message);
                return false;
            }
        }
        public void Attack(int attackedRow, int attackedColumn)
        {
            for (int row = 0; row < Rows; row++)
            {
                for (int column = 0; column < Columns; column++)
                {
                    if (row == attackedRow && column == attackedColumn)
                    {
                        if (!Cells[row, column].IsAttacked)
                        {
                            Cells[row, column].IsAttacked = true;
                            AttackedCells.Add(Cells[row,column]);
                            if (Cells[row, column].IsOccupied)
                            {
                                HittenCells.Add(Cells[row,column]);
                                Console.WriteLine("Colpita!");
                            }
                            else
                            {
                                Console.WriteLine("Non colpita");
                            }
                        }
                    }
                }
            }
        }
        /*
          
         */
        public bool AttackBot(int attackedRow, int attackedColumn)
        {
            try
            {
                for (int row = 0; row < Rows; row++)
                {
                    for (int column = 0; column < Columns; column++)
                    {
                        if (row == attackedRow && column == attackedColumn)
                        {
                            foreach (Cell cell in AttackedCells)
                            {
                                if (cell.Row == row && cell.Column == column)
                                {
                                    throw new AlreadyAttackedException();
                                }
                            }
                            if (!Cells[row, column].IsAttacked)
                            {
                                Cells[row, column].IsAttacked = true;
                                AttackedCells.Add(Cells[row, column]);
                                if (Cells[row, column].IsOccupied)
                                {
                                    HittenCells.Add(Cells[row, column]);
                                    Console.WriteLine("Colpita!");
                                }
                                else
                                {
                                    Console.WriteLine("Non colpita");
                                }
                            }
                        }
                    }
                }

                return true;
            }
            catch (AlreadyAttackedException ex)
            {
                Console.WriteLine(ex.Message);
                return false;
            }
        }

        public void UpdateOcean(int x, int y, bool hit)
        {
            Cells[x, y].IsAttacked = true;
            if (hit)
            {
                Cells[x, y].IsOccupied = true;
            }
        }
        
        public void PrintPlacement()
        {
            for (int row = 0; row < Rows; row++)
            {
                for (int column = 0; column < Columns; column++)
                {
                    if (Cells[row, column].IsOccupied)
                    {
                        Console.Write("|O");
                    }
                    else
                    {
                        Console.Write("|-");
                    }
                }
                Console.WriteLine("|");
            }
        }
        public void PrintInGame()
        {
            for (int row = 0; row < Rows; row++)
            {
                for (int column = 0; column < Columns; column++)
                {
                    if (Cells[row, column].IsAttacked)
                    {
                        if (Cells[row, column].IsOccupied)
                        {
                            Console.Write("|O");
                        }
                        else
                        {
                            Console.Write("|X");
                        }
                    }
                    else
                    {
                        Console.Write("|-");
                    }
                }
                Console.WriteLine("|");
            }
        }
    }
}