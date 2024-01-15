using System;

namespace cs.Exceptions
{
    public class OutOfOceanException : Exception
    {
        public OutOfOceanException() : base("Username inserito supera il limite dell'oceano!") { }

        public OutOfOceanException(string message) : base(message) { }

        public OutOfOceanException(string message, Exception innerException) : base(message, innerException) { }

    }
}