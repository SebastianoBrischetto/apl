using cs.Logic.GameLogic.MatchElements.Structs;
namespace cs.Logic.GameLogic.MatchElements;

public class Match
{
    private static Match _instance;
    private Bot _bot;
    
    public string Code { get; set; }
    public int Rows { get; set; }
    public int Columns { get; set; }
    public int ShipsNumber { get; set; }
    public int[] ShipsCodes { get; set; }
    public Opponent Opponent { get; set; }
    public bool ExistOpponent { get; set; }
    public List<Move> PlayersLastMoves { get; set; }
    public bool LastMoveHit { get; set; }
    public bool IsPlayerOne { get; set; }
    public bool IsPlayerOneTurn { get; set; }
    public bool IsGameOver { get; set; }
    public Bot Bot 
   {
        get { return _bot;}
        set { _bot = value;}
   } 
    public Move OpponentLastMove { get; set; }
    
    public static Match Instance 
    {
        get
        {
            if (_instance == null)
            {
                _instance = new Match();
            }

            return _instance;
        }
    }

    public Match()
    {
        Bot = new Bot();
        PlayersLastMoves = new List<Move>();
        LastMoveHit = false;
        IsGameOver = false;
        ExistOpponent = false;
        OpponentLastMove = new Move { X = -1, Y = -1 };
    }

    public void InizializeMatch(string code, int rows, int columns, int shipsNumber, bool isPlayerOne)
    {
        Code = code;
        Rows = rows;
        Columns = columns;
        ShipsNumber = shipsNumber;
        Opponent = new Opponent();
        IsPlayerOne = isPlayerOne;
        if (isPlayerOne)
        {
            IsPlayerOneTurn = true;
        }
        else
        {
            IsPlayerOneTurn = false;
        }
        
    }
    public void InizializeMatchBot(string code, int rows, int columns, int shipsNumber)
    {
        Code = code;
        Rows = rows;
        Columns = columns;
        ShipsNumber = shipsNumber;
        IsPlayerOneTurn = true;
        Bot = new Bot(rows, columns, shipsNumber);
    }

    
}