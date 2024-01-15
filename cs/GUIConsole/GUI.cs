namespace cs.GUIConsole;

public static class GUI
{
    public static string GetStringInput(string output)
    {
        Console.WriteLine(output);
        while (true)
        {
            try
            {
                string input = Console.ReadLine() ?? throw new InvalidOperationException();
                return input;
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }
    
    public static string GetStringInput(string output, int min)
    {
        Console.WriteLine(output + $" (minimo {min} caratteri)");
        while (true)
        {
            try
            {
                string input = Console.ReadLine() ?? throw new InvalidOperationException();
                {
                    if (input.Length > min)
                    {
                        return input;
                    }
                    Console.WriteLine("Stringa troppo breve!");
                }
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine(e.Message);
            }
        }
    }

    public static int GetIntInput(string output)
    {
        Console.WriteLine(output);
        do
        {
            Console.WriteLine(output);
            try
            {
                string userInput = Console.ReadLine() ?? throw new InvalidOperationException();
                bool valid = int.TryParse(userInput, out int input);
                if (valid)
                {
                    return input;
                }

                Console.WriteLine("Inserisci un valore valido!");
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine(e.Message);
            }
        } while (true);
    }
    
    public static int GetIntInput(string output, int min)
    {
        Console.WriteLine(output + $" (minimo {min}) ");
        do
        {
            Console.WriteLine(output);
            try
            {
                string userInput = Console.ReadLine() ?? throw new InvalidOperationException();
                bool valid = int.TryParse(userInput, out int input);
                if (input < min)
                {
                    valid = false;
                }
                if (valid)
                {
                    return input;
                }

                Console.WriteLine("Inserisci un valore valido!");
            }
            catch (Exception e)
            {
                Console.WriteLine(e.Message);
            }
        } while (true);
    }
    
    public static int GetIntInput(string output, int min, int max)
    {
        Console.WriteLine(output + $" (minimo {min} e massimo {max}) ");
        do
        {
            Console.WriteLine(output);
            try
            {
                string userInput = Console.ReadLine() ?? throw new InvalidOperationException();
                bool valid = int.TryParse(userInput, out int input);
                if (input < min || input > max)
                {
                    valid = false;
                }
                if (valid)
                {
                    return input;
                }

                Console.WriteLine("Inserisci un valore valido!");
            }
            catch (InvalidOperationException e)
            {
                Console.WriteLine(e.Message);
            }
        } while (true);
    }
}