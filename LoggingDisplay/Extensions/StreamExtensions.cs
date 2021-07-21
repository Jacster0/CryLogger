using System;
using System.Runtime.InteropServices;
using System.IO;

namespace LoggingDisplay.Extensions
{
    public static class StreamExtensions
    {
        private const int MAX_STACKALLOC_SIZE = 512;

        public static unsafe T ReadStruct<T>(this Stream stream) where T : struct
        {
            var length = Marshal.SizeOf<T>();
            Span<byte> buffer = (length <= MAX_STACKALLOC_SIZE) ? stackalloc byte[length] : new byte[length];

            stream.Read(buffer);

            fixed (byte* ptr = buffer)
            {
                return Marshal.PtrToStructure<T>(new IntPtr(ptr));
            }
        }
    }
}
