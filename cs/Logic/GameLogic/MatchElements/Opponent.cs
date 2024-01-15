using cs.Logic.GameLogic.GameElements;

namespace cs.Logic.GameLogic.MatchElements;
public class Opponent
{
    public Ocean Ocean { get; set; }
    
    //public int IntLastMoveX { get; set; }
    //public int IntLastMoveY { get; set; }

    public Opponent()
    {
       Ocean = new Ocean(Match.Instance.Rows, Match.Instance.Columns, Match.Instance.ShipsNumber, null,true);
    }
}