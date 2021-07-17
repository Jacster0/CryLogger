using System.Collections.Concurrent;

namespace LoggingDisplay.Extensions
{
    public static class QueueExtensions
    {
        public static bool Empty<T>(this ConcurrentQueue<T> queue)
        {
            return queue.Count == 0;
        }
    }
}
