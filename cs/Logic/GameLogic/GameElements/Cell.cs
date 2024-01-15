namespace cs.Logic.GameLogic.GameElements
{
    public class Cell
    {
        //Attributi
        private bool _isHitten;
        
        //Proprietà
        public int Row { get; set; }

        public int Column { get; set; }

        public bool IsOccupied { get; set; }

        public bool IsAttacked { get; set; }

        public bool IsHitten
        {
            get => _isHitten;
            set => IsAttacked = value;
        }
        
        public Cell(int row, int column, bool isOccupied = false)
        {
            Row = row;
            Column = column;
            IsOccupied = isOccupied;
            IsAttacked = false;
            _isHitten = false;
        }
        
    }
}