// Acquire locks
// C++11

#include <mutex>

int main()
{
  std::mutex mutex_1;
  std::mutex mutex_2;
  
  // Single lock:
  {
    std::lock_guard<std::mutex> lock{mutex_1};
    
    // mutex_1 is locked here, until end of scope.
  }
  
  // Multiple locks:
  {
    std::lock(mutex_1, mutex_2);
    std::lock_guard<std::mutex> lock_1{mutex_1, std::adopt_lock};
    std::lock_guard<std::mutex> lock_2{mutex_2, std::adopt_lock};
    
    // both mutex_1 and mutex_2 are locked here, until end of scope.
  }
  
  // Multiple unique_locks or shared_locks with defer_lock:
  {
    std::unique_lock<std::mutex> lock_1{mutex_1, std::defer_lock};
    std::unique_lock<std::mutex> lock_2{mutex_2, std::defer_lock};
    std::lock(lock_1, lock_2);
    
    // both mutex_1 and mutex_2 are locked here, until end of scope,
    // or until the locks are manually unlocked.
  }
}

// Acquire locks on one or more lockable objects.
//
// When locking a single lockable object (such as a mutex), we can
// simply use [`std::lock_guard`](cpp/thread/lock_guard) as on [13].
// If it succeeds, the lock will be held until the `lock_guard` is
// destroyed at the end of scope.
//
// When locking multiple lockable objects, we should never try
// locking them individually, as this can lead to deadlock. Instead,
// we should always use [`std::lock`](cpp/thread/lock). There are two
// ways to do this.
//
// The first, safest, and most efficient way is to do the lock first
// as on [20], then create lock objects using
// [`std::adopt_lock`](cpp/thread/lock_tag) as on [21-22]. Creating
// lock objects with `std::adopt_lock` is guaranteed to always
// succeed. The lock objects should always all be created *immediately*
// after the call to `std::lock`, so that all the locks will be safely
// unlocked at the end of scope no matter what else happens.
//
// The second way is to create the lock objects first using
// [`std::defer_lock`](cpp/thread/lock_tag) as on [29-30], then use
// `std::lock` on the lock objects as on [31]. This method is only
// possible if you are using
// [`std::unique_lock`](cpp/thread/unique_lock) or
// [`std::shared_lock`](cpp/thread/shared_lock). As always, the locks
// will be unlocked when the lock objects are destroyed. However, with
// `unique_lock` or `shared_lock`, it is possible to unlock the lock
// earlier if desired.
