using cs.Logic.GameLogic.Managers;

namespace cs.Logic.UserLogic
{
    public class User
    {
        //Attributi
        private static User _instance = null;

        //Costruttore
        public User()
        {
            Username = "";
            Password = "";
            Score = 1200;
            Token = "";
        }
        public User(string username, string password, string token = "", float score = 1200)
        {
            Username = username;
            Password = password;
            Score = score;
            Token = token;
        }
        public static User Instance
        {
            get
            {
                if (_instance == null)
                {
                    _instance = new User();
                }

                return _instance;

            }
        }
        
        public string Username { get; set; }

        public string Password { get; set; }

        public float Score { get; set; }

        public string Token { get; set; }

        public override string ToString()
        {
            return $"Username: {Username}, Password: {Password}, token: {Token}, score: {Score}";
        }
    }
}