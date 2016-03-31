using System;
using System.Collections.Generic;
using System.Text;

// Definition of problem
// Given an NxN TicTacToe board, find the winner at any given time

namespace TicTacToe
{

    interface IBoardType
    {
        int Size
        { get;}
    }

    abstract class ABoardType
    {
        public enum Player { None = 0, One = 1, Two = -1 };
        public abstract void Initialize();
        public abstract Player CalculateWinner();
        public abstract void MakeMove(Player player,int row, int column);
    }

    class Board : ABoardType,IBoardType
    {
        int[,] _board;
        int _size;
        const int BOARD_INITIALIZER = 0;

        public int Size{ get { return _size; } }

        public Board(int boardsize) 
        { 
            _board = new int[boardsize,boardsize];
            _size = boardsize;
            Initialize();
        }

        public override void MakeMove(Player player, int row, int column)
        {
            if ((row >= _size) || (column >= _size))
                throw new ArgumentOutOfRangeException();
            _board[row, column] = (int)player;
        }

        public override Player CalculateWinner()
        {
            // To find a winner simply sum all the rows, diagonals and then columns

            // Sum rows
            // Sum columns

            int isum = 0; 
            int jsum = 0;

            Player player = Player.None;

            // check rows
            for (int i = 0; i < _size; i++)
            {   
                for (int j = 0; j < _size; j++)
                {
                    jsum += _board[i, j];
                }
                player = DetermineWinner(jsum);
                if (player != Player.None) return player;
                jsum = 0;
            }

            //check columns
            for (int j = 0; j < _size; j++)
            {
                for (int i = 0; i < _size; i++)
                {
                    isum += _board[i, j];
                }
                player = DetermineWinner(isum);
                if (player != Player.None) return player;
                isum = 0;
            }

            isum = 0;
            jsum = 0;

            // Sum diagonals
            for (int i = 0, j = 0; j < _size; i++,j++)
            {
                isum += _board[i, j];
                jsum += _board[i, _size - j -1];
            }
            player = DetermineWinner(isum);
            if (player != Player.None) return player;
            player = DetermineWinner(jsum);
            if (player != Player.None) return player;

            return player;

        }

        private Player DetermineWinner(int sum) {
            if (sum == _size) return Player.One;
            else if (sum == -_size) return Player.Two;
            else return Player.None;
        }

        public override void Initialize() 
        {
            for (int i = 0; i < _size; i++)
            {
                for (int j = 0; j < _size; j++)
                {
                    _board[i,j] = BOARD_INITIALIZER;
                }
            }
        }

    }

    class Program
    {
        static void Main(string[] args)
        {
            Board board = new Board(3);

            board.MakeMove(Board.Player.One, 0, 1);
            board.MakeMove(Board.Player.One, 0, 1);
            board.MakeMove(Board.Player.Two, 1, 1);
            board.MakeMove(Board.Player.Two, 2, 1);
            board.MakeMove(Board.Player.Two, 0, 1);

            Board.Player player = board.CalculateWinner();
            Console.WriteLine("The winner of the boardgame is: {0}",player.ToString());

        }
    }
}
