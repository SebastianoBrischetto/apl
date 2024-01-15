using System;
namespace cs.Exceptions
{
    public class AlreadyAttackedException : Exception
    {
        public AlreadyAttackedException() : base("Cella già attaccata!") { }

        public AlreadyAttackedException(string message) : base(message) { }

        public AlreadyAttackedException(string message, Exception innerException) : base(message, innerException) { }

    }
}