using cs.Logic.GameLogic.GameElements;
using cs.Logic.GameLogic.MatchElements;
using cs.GUIConsole;
using cs.Communications.HttpRequests;
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
            /*Console.WriteLine("Mosse del bot:");
            foreach (Move move in Match.Instance.Bot.Moves)
            {
                Console.WriteLine($"{move.X}||{move.Y}");
            }
            Console.WriteLine("Celle occupate dal bot");
            foreach (OccupiedCoordinates coords in Match.Instance.Bot.OccupiedCoordinates)
            {
                Console.WriteLine($"{coords.X}||{coords.Y}");
            }
            Console.WriteLine("GRIGLIA NEMICA:");*/
            Match.Instance.Bot.FillCells();
            //Match.Instance.Bot.Ocean.PrintPlacement();
        }
        else
        {
            Console.WriteLine("Bot attualmente vuoto");
        }
    }
    public static void Attack(Ocean opponentOcean)
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
    public static void BotAttack(Ocean playerOcean, int round)
    {
        Move move = Match.Instance.Bot.Moves[round];
        playerOcean.Attack(move.X, move.Y);
        playerOcean.PrintInGame();
    }
    
    public static void OpponentAttackPlayer(Ocean playerOcean)
    {
        Move move = Match.Instance.OpponentLastMove;
        playerOcean.Attack(move.X, move.Y);
        //playerOcean.PrintInGame();
    }
    
    public static void PlayerAttackOpponent(Ocean opponentOcean)
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
        MatchRequest.SendMoves(User.Instance.Username, row, column, Match.Instance.Opponent);
        Thread.Sleep(2000);
        Console.WriteLine($"Game over: {Match.Instance.IsGameOver}");
        Console.WriteLine($"HIT: {Match.Instance.LastMoveHit}");
        Match.Instance.Opponent.Ocean.UpdateOcean
            (Match.Instance.PlayersLastMoves.Last().X, Match.Instance.PlayersLastMoves.Last().Y, Match.Instance.LastMoveHit);
        if (!Match.Instance.IsGameOver)
        {
            Match.Instance.Opponent.Ocean.Cells[row, column].IsOccupied = Match.Instance.LastMoveHit;
            Match.Instance.Opponent.Ocean.Cells[row, column].IsAttacked = true;
            Console.WriteLine("---OCEANO DA ATTACCARE---");
            opponentOcean.PrintInGame();
            OpponentAttackPlayer(PlayerOcean);
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
                Attack(Match.Instance.Bot.Ocean);
                if (CheckVictory(Match.Instance.Bot.Ocean, isBot))
                {
                    Console.WriteLine("Il giocatore ha vinto!");
                    return;
                }
                Console.WriteLine($"Turno {round+1} del bot: ");
                BotAttack(PlayerOcean, round);
                if (CheckVictory(PlayerOcean, false))
                {
                    Console.WriteLine("Il bot ha vinto!");
                    return;
                }
                round++;
            }
            else
            {
                 PlayerAttackOpponent(Match.Instance.Opponent.Ocean);
                 Match.Instance.IsPlayerOneTurn = false;
            }
        } 
        Console.WriteLine("Fine partita!");
    }
    /////////////////////////////
    public static void TurnsJoin()
    {
        while (!Match.Instance.IsGameOver)
        {
            PlayerTwoAttackPlayerOne(Match.Instance.Opponent.Ocean);
            Match.Instance.IsPlayerOneTurn = true;
        } 
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
        MatchRequest.SendMoves(Match.Instance.Code, row, column, Match.Instance.Opponent);
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
        //playerOcean.PrintInGame();
    }
}