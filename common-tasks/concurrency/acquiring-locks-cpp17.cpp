// Acquire locks (C++17 or better)
// C++17

#include <mutex>

int main()
{
  std::mutex mutex_1;
  std::mutex mutex_2;
  
  // Single lock:
  {
    std::scoped_lock lock{mutex_1};
    
    // mutex_1 is locked here, until end of scope.
  }
  
  // Multiple locks:
  {
    std::scoped_lock lock{mutex_1, mutex_2};
    
    // both mutex_1 and mutex_2 are locked here, until end of scope.
  }
}

// Acquire locks on one or more lockable objects.
//
// C++17 provides a new way to safely and consistently lock one or more
// lockable objects.
//
// We can use [`std::scoped_lock`](cpp/thread/scoped_lock) to lock one
// lockable object (as on [13]), or multiple lockable objects (as on
// [20]), in a safe, simple, deadlock-free way. The lock is held until
// the end of scope.
//
// This avoids the risk of forgetting to create a lock object for one
// or more of the lockables when using [`std::lock`](cpp/thread/lock).
