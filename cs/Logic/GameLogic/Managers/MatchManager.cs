using cs.Communications;
using cs.Logic.GameLogic.GameElements;
using cs.Logic.GameLogic.MatchElements;
using cs.GUIConsole;
using cs.Logic.GameLogic.MatchElements.Structs;
using cs.Logic.UserLogic;

namespace cs.Logic.GameLogic.Managers;

public static class MatchManager
{
    public static Ocean PlayerOcean { get; set; }

    public static async Task InizializeBot()
    {
        bool valid = await MatchRequest.GetBotMoves();

        if (valid)
        {
            Match.Instance.Bot.FillCells();
        }
        else
        {
            Console.WriteLine("Bot non caricato correttamente");
        }
    }
    public static void PlayerAttacksBot(Ocean opponentOcean)
    {
        bool valid = false;
        int row;
        int column;
        while (!valid)
        {
            row = GUI.GetIntInput("Digita la riga da attaccare: ", 0, opponentOcean.Rows - 1);
            column = GUI.GetIntInput("Digita la colonna da attaccare: ", 0, opponentOcean.Columns - 1);
            valid = opponentOcean.AttackBot(row, column);
        }
        opponentOcean.PrintInGame();
    }
    public static void BotAttacksPlayer(Ocean playerOcean, int round)
    {
        Move move = Match.Instance.Bot.Moves[round];
        playerOcean.Attack(move.X, move.Y);
        playerOcean.PrintInGame();
    }
    
    public static void OpponentAttacksPlayer(Ocean playerOcean)
    {
        Move move = Match.Instance.OpponentLastMove;
        playerOcean.Attack(move.X, move.Y);
    }
    
    public static void PlayerAttacksOpponent(Ocean opponentOcean)
    {
        do
        {
            MatchRequest.CheckPlayersTurn();
            Thread.Sleep(2000);
        } 
        while (!Match.Instance.IsPlayerOneTurn);
        bool valid = false;
        int row = -1;
        int column = -1;
        while (!valid)
        {
            row = GUI.GetIntInput("Digita la riga da attaccare: ", 0, opponentOcean.Rows - 1);
            column = GUI.GetIntInput("Digita la colonna da attaccare: ", 0, opponentOcean.Columns - 1);
            valid = opponentOcean.CheckAttack(row, column);
            if (!valid)
            {
                Console.WriteLine("Cella già attaccata in precedenza, riprova!");
            }
        }
        MatchRequest.SendMoves(User.Instance.Username, row, column);
        Thread.Sleep(2000);
        Match.Instance.Opponent.Ocean.UpdateOcean
            (Match.Instance.PlayersLastMoves.Last().X, Match.Instance.PlayersLastMoves.Last().Y, Match.Instance.LastMoveHit);
        if (!Match.Instance.IsGameOver)
        {
            Match.Instance.Opponent.Ocean.Cells[row, column].IsOccupied = Match.Instance.LastMoveHit;
            Match.Instance.Opponent.Ocean.Cells[row, column].IsAttacked = true;
            Console.WriteLine("---OCEANO DA ATTACCARE---");
            opponentOcean.PrintInGame();
            OpponentAttacksPlayer(PlayerOcean);
            if (Match.Instance.OpponentLastMove.X != -1 && Match.Instance.OpponentLastMove.Y != -1 )
            {
                PlayerOcean.Attack(Match.Instance.OpponentLastMove.X,Match.Instance.OpponentLastMove.Y);
                Console.WriteLine("---OCEANO DA DIFENDERE---");
                PlayerOcean.PrintInGame();
            }
        }
        else
        {
            Console.WriteLine("Fine della partita!");
        }
    }

    public static bool CheckVictory(Ocean opponentOcean, bool isBot)
    {
        if (isBot)
        {
            if (Match.Instance.Bot.OccupiedCoordinates.Count == opponentOcean.HittenCells.Count)
            {
                return true;
            }

            return false;
        }
        if (opponentOcean.HittenCells.Count == opponentOcean.OccupiedCells.Count)
        {
            return true;
        }

        return false;
    }
    
    public static void Turns(bool isBot)
    {
        int round = 0;
        while (!Match.Instance.IsGameOver)
        {
            if (isBot)
            {
                Console.WriteLine($"Turno {round+1} del giocatore: ");
                PlayerAttacksBot(Match.Instance.Bot.Ocean);
                if (CheckVictory(Match.Instance.Bot.Ocean, isBot))
                {
                    Console.WriteLine("Il giocatore ha vinto!");
                    return;
                }
                Console.WriteLine($"Turno {round+1} del bot: ");
                BotAttacksPlayer(PlayerOcean, round);
                if (CheckVictory(PlayerOcean, false))
                {
                    Console.WriteLine("Il bot ha vinto!");
                    return;
                }
                round++;
            }
            else
            {
                 PlayerAttacksOpponent(Match.Instance.Opponent.Ocean);
                 Match.Instance.IsPlayerOneTurn = false;
            }
        } 
        Console.WriteLine("Fine partita!");
    }
    public static void TurnsJoin()
    {
        while (!Match.Instance.IsGameOver)
        {
            PlayerTwoAttackPlayerOne(Match.Instance.Opponent.Ocean);
            Match.Instance.IsPlayerOneTurn = true;
        } 
        if(Match.Instance.IsGameOver)
        Console.WriteLine("Fine partita!");
    }
    
    
    public static void PlayerTwoAttackPlayerOne(Ocean opponentOcean)
    {
        do
        {
            MatchRequest.CheckPlayersTurn();
            Thread.Sleep(2000);
        } 
        while (Match.Instance.IsPlayerOneTurn);
        bool valid = false;
        int row = -1;
        int column = -1;
        while (!valid)
        {
            row = GUI.GetIntInput("Digita la riga da attaccare: ", 0, opponentOcean.Rows - 1);
            column = GUI.GetIntInput("Digita la colonna da attaccare: ", 0, opponentOcean.Columns - 1);
            valid = opponentOcean.CheckAttack(row, column);
            if (!valid)
            {
                Console.WriteLine("Cella già attaccata in precedenza, riprova!");
            }
        }
        MatchRequest.SendMoves(Match.Instance.Code, row, column);
        Thread.Sleep(2000);
        Console.WriteLine($"Game over: {Match.Instance.IsGameOver}");
        Console.WriteLine($"HIT: {Match.Instance.LastMoveHit}");
        if (Match.Instance.PlayersLastMoves.Count > 0)
        {
            Match.Instance.Opponent.Ocean.UpdateOcean
                (Match.Instance.PlayersLastMoves.Last().X, Match.Instance.PlayersLastMoves.Last().Y, Match.Instance.LastMoveHit);
        }
        if (!Match.Instance.IsGameOver)
        {
            Match.Instance.Opponent.Ocean.Cells[row, column].IsOccupied = Match.Instance.LastMoveHit;
            Match.Instance.Opponent.Ocean.Cells[row, column].IsAttacked = true;
            Console.WriteLine("---OCEANO DA ATTACCARE---");
            opponentOcean.PrintInGame();
            PlayerOneAttackPlayerTwo(PlayerOcean);
            if (Match.Instance.OpponentLastMove.X != -1 && Match.Instance.OpponentLastMove.Y != -1 )
            {
                PlayerOcean.Attack(Match.Instance.OpponentLastMove.X,Match.Instance.OpponentLastMove.Y);
                Console.WriteLine("---OCEANO DA DIFENDERE---");
                PlayerOcean.PrintInGame();
            }
        }
        else
        {
            Console.WriteLine("Fine della partita!");
        }
    }
    public static void PlayerOneAttackPlayerTwo(Ocean playerOcean)
    {
            Move move = Match.Instance.OpponentLastMove;
            playerOcean.Attack(move.X, move.Y);
    }
}